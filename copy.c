
#define _POSIX_C_SOURCE 200809L

#include "ft_ping.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PING_PAYLOAD_SIZE 32
#define PING_INTERVAL_MS 1000
#define REPLY_TIMEOUT_MS 1000

static volatile sig_atomic_t g_stop_requested = 0;

static void handle_sigint(int signal_number)
{
    (void)signal_number;
    g_stop_requested = 1;
}

void print_help(const char *program_name)
{
    printf("Usage: %s [OPTIONS] DESTINATION\n", program_name);
    printf("Send ICMP Echo Requests to a destination.\n\n");
    printf("Options:\n");
    printf("  -v, --verbose  Verbose output\n");
    printf("  -?, --help     Display this help and exit\n");
}

static void print_usage_error(const char *program_name, const char *message)
{
    fprintf(stderr, "ft_ping: %s\n", message);
    fprintf(stderr, "Try '%s -?' for more information.\n", program_name);
}

int parse_arguments(int argc, char **argv, t_ping_options *options)
{
    int i;

    options->verbose = false;
    options->destination = NULL;
    i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0)
        {
            print_help(argv[0]);
            return 1;
        }
        else if (strcmp(argv[i], "-v") == 0 ||
                 strcmp(argv[i], "--verbose") == 0)
            options->verbose = true;
        else if (argv[i][0] == '-')
        {
            print_usage_error(argv[0], "unknown option");
            return -1;
        }
        else if (options->destination != NULL)
        {
            print_usage_error(argv[0], "only one destination is supported");
            return -1;
        }
        else
            options->destination = argv[i];
        i++;
    }
    if (options->destination == NULL)
    {
        print_usage_error(argv[0], "missing destination");
        return -1;
    }
    return 0;
}

int resolve_destination(const char *destination, struct sockaddr_in *address,
                        char *ip_string, size_t ip_string_size)
{
    struct addrinfo hints;
    struct addrinfo *result;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    status = getaddrinfo(destination, NULL, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "ft_ping: %s: %s\n", destination, gai_strerror(status));
        return -1;
    }
    if (result == NULL || result->ai_addrlen < sizeof(*address))
    {
        fprintf(stderr, "ft_ping: could not resolve %s\n", destination);
        if (result != NULL)
            freeaddrinfo(result);
        return -1;
    }
    memcpy(address, result->ai_addr, sizeof(*address));
    if (inet_ntop(AF_INET, &address->sin_addr, ip_string, ip_string_size) ==
        NULL)
    {
        perror("ft_ping: inet_ntop");
        freeaddrinfo(result);
        return -1;
    }
    freeaddrinfo(result);
    return 0;
}

static int create_icmp_socket(void)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1)
    {
        if (errno == EACCES || errno == EPERM)
            fprintf(stderr, "ft_ping: raw socket permission denied; "
                            "try running with sudo\n");
        else
            perror("ft_ping: socket");
        return -1;
    }
    return sockfd;
}

static uint16_t calculate_checksum(const uint8_t *data, size_t length)
{
    uint32_t sum;
    size_t i;

    sum = 0;
    i = 0;
    while (i + 1 < length)
    {
        sum += ((uint32_t)data[i] << 8) | (uint32_t)data[i + 1];
        i += 2;
    }
    if (i < length)
        sum += (uint32_t)data[i] << 8;
    while (sum >> 16)
        sum = (sum & 0xffffU) + (sum >> 16);
    return (uint16_t)(~sum & 0xffffU);
}

int send_echo_request(int sockfd, struct sockaddr_in *destination,
                      uint16_t identifier, uint16_t sequence)
{
    struct s_icmp_packet
    {
        struct icmphdr header;
        uint8_t payload[PING_PAYLOAD_SIZE];
    } packet;
    ssize_t sent_bytes;
    size_t i;

    memset(&packet, 0, sizeof(packet));
    packet.header.type = ICMP_ECHO;
    packet.header.code = 0;
    packet.header.un.echo.id = htons(identifier);
    packet.header.un.echo.sequence = htons(sequence);

    i = 0;
    while (i < sizeof(packet.payload))
    {
        packet.payload[i] = 'A';
        i++;
    }

    packet.header.checksum = 0;
    packet.header.checksum =
        htons(calculate_checksum((const uint8_t *)&packet, sizeof(packet)));

    sent_bytes = sendto(sockfd, &packet, sizeof(packet), 0,
                        (struct sockaddr *)destination, sizeof(*destination));
    if (sent_bytes == -1)
    {
        perror("ft_ping: sendto");
        return -1;
    }
    if ((size_t)sent_bytes != sizeof(packet))
    {
        fprintf(stderr, "ft_ping: incomplete ICMP packet sent\n");
        return -1;
    }
    return 0;
}

static int get_monotonic_time(struct timespec *time_value)
{
    if (clock_gettime(CLOCK_MONOTONIC, time_value) == -1)
    {
        perror("ft_ping: clock_gettime");
        return -1;
    }
    return 0;
}

static int deadline_remaining(struct timespec *deadline,
                              struct timeval *timeout)
{
    struct timespec now;
    long long remaining_ns;

    if (get_monotonic_time(&now) == -1)
        return -1;
    remaining_ns =
        ((long long)deadline->tv_sec - (long long)now.tv_sec) * 1000000000LL +
        ((long long)deadline->tv_nsec - (long long)now.tv_nsec);
    if (remaining_ns <= 0)
        return 0;

    timeout->tv_sec = (time_t)(remaining_ns / 1000000000LL);
    timeout->tv_usec =
        (suseconds_t)((remaining_ns % 1000000000LL + 999LL) / 1000LL);
    if (timeout->tv_usec >= 1000000)
    {
        timeout->tv_sec++;
        timeout->tv_usec -= 1000000;
    }
    return 1;
}

static void report_ignored_packet(bool verbose, const char *reason)
{
    if (verbose)
        fprintf(stderr, "ft_ping: ignored packet: %s\n", reason);
}

int receive_echo_reply(int sockfd, uint16_t identifier, uint16_t sequence,
                       uint32_t timeout_ms, bool verbose, char *source_ip,
                       size_t source_ip_size, uint8_t *ttl, size_t *reply_size)
{
    uint8_t buffer[1500];
    struct sockaddr_in sender;
    socklen_t sender_length;
    ssize_t bytes_received;
    struct iphdr ip_header;
    struct icmphdr icmp_header;
    struct timespec deadline;
    struct timeval timeout;
    fd_set read_fds;
    size_t ip_header_size;
    size_t total_length;
    size_t icmp_length;
    int wait_result;

    if (get_monotonic_time(&deadline) == -1)
        return -1;
    deadline.tv_sec += (time_t)(timeout_ms / 1000);
    deadline.tv_nsec += (long)(timeout_ms % 1000) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L)
    {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }

    while (!g_stop_requested)
    {
        wait_result = deadline_remaining(&deadline, &timeout);
        if (wait_result == -1)
            return -1;
        if (wait_result == 0)
            return 1;

        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        wait_result = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
        if (wait_result == -1)
        {
            if (errno == EINTR)
                continue;
            perror("ft_ping: select");
            return -1;
        }
        if (wait_result == 0)
            continue;

        memset(&sender, 0, sizeof(sender));
        sender_length = sizeof(sender);
        bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *)&sender, &sender_length);
        if (bytes_received == -1)
        {
            if (errno == EINTR)
                continue;
            perror("ft_ping: recvfrom");
            return -1;
        }

        /* Validate that a complete IPv4 header is present. */
        if ((size_t)bytes_received < sizeof(struct iphdr))
        {
            report_ignored_packet(verbose, "truncated IPv4 header");
            continue;
        }
        memcpy(&ip_header, buffer, sizeof(ip_header));
        if (ip_header.version != 4)
        {
            report_ignored_packet(verbose, "not an IPv4 packet");
            continue;
        }
        ip_header_size = (size_t)ip_header.ihl * 4;
        if (ip_header_size < sizeof(struct iphdr) ||
            ip_header_size > (size_t)bytes_received)
        {
            report_ignored_packet(verbose, "invalid IPv4 header length");
            continue;
        }
        if (ip_header.protocol != IPPROTO_ICMP)
        {
            report_ignored_packet(verbose, "not an ICMP packet");
            continue;
        }

        /*
         * IPv4 total length includes the IPv4 header and its payload.
         * Do not parse beyond either the declared length or the
         * bytes actually received.
         */
        total_length = (size_t)ntohs(ip_header.tot_len);
        if (total_length < ip_header_size + sizeof(struct icmphdr))
        {
            report_ignored_packet(verbose, "invalid IPv4 total length");
            continue;
        }
        if (total_length > (size_t)bytes_received)
        {
            report_ignored_packet(verbose, "truncated IPv4 packet");
            continue;
        }

        icmp_length = total_length - ip_header_size;
        memcpy(&icmp_header, buffer + ip_header_size, sizeof(icmp_header));

        if (icmp_header.type != ICMP_ECHOREPLY || icmp_header.code != 0)
        {
            report_ignored_packet(verbose, "not an ICMP Echo Reply");
            continue;
        }

        /* A valid ICMP message has a zero result when checksummed
         * together with its checksum field. */
        if (calculate_checksum(buffer + ip_header_size, icmp_length) != 0)
        {
            report_ignored_packet(verbose, "invalid ICMP checksum");
            continue;
        }

        if (ntohs(icmp_header.un.echo.id) != identifier ||
            ntohs(icmp_header.un.echo.sequence) != sequence)
        {
            report_ignored_packet(verbose,
                                  "identifier or sequence number mismatch");
            continue;
        }

        if (inet_ntop(AF_INET, &sender.sin_addr, source_ip, source_ip_size) ==
            NULL)
        {
            perror("ft_ping: inet_ntop");
            return -1;
        }
        *ttl = ip_header.ttl;
        *reply_size = icmp_length;
        return 0;
    }
    return 2;
}

static int monotonic_milliseconds(double *milliseconds)
{
    struct timespec now;

    if (get_monotonic_time(&now) == -1)
        return -1;
    *milliseconds =
        (double)now.tv_sec * 1000.0 + (double)now.tv_nsec / 1000000.0;
    return 0;
}

static int wait_for_next_interval(double request_start_ms)
{
    struct timespec remaining;
    double now_ms;
    double remaining_ms;
    int result;

    while (!g_stop_requested)
    {
        if (monotonic_milliseconds(&now_ms) == -1)
            return -1;
        remaining_ms = (double)PING_INTERVAL_MS - (now_ms - request_start_ms);
        if (remaining_ms <= 0.0)
            return 0;

        remaining.tv_sec = (time_t)(remaining_ms / 1000.0);
        remaining.tv_nsec =
            (long)((remaining_ms - (double)remaining.tv_sec * 1000.0) *
                   1000000.0);
        result = nanosleep(&remaining, NULL);
        if (result == -1 && errno != EINTR)
        {
            perror("ft_ping: nanosleep");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    t_ping_options options;
    struct sockaddr_in destination_address;
    struct sigaction action;
    char ip_string[INET_ADDRSTRLEN];
    char reply_ip[INET_ADDRSTRLEN];
    uint16_t identifier;
    uint16_t sequence;
    uint8_t ttl;
    size_t reply_size;
    unsigned long transmitted;
    unsigned long received;
    double request_start_ms;
    double reply_time_ms;
    double rtt_ms;
    double min_rtt;
    double max_rtt;
    double total_rtt;
    double packet_loss;
    int sockfd;
    int result;
    int exit_status;

    result = parse_arguments(argc, argv, &options);
    if (result == 1)
        return 0;
    if (result == -1)
        return 2;

    memset(&destination_address, 0, sizeof(destination_address));
    destination_address.sin_family = AF_INET;
    if (resolve_destination(options.destination, &destination_address,
                            ip_string, sizeof(ip_string)) == -1)
        return 2;

    sockfd = create_icmp_socket();
    if (sockfd == -1)
        return 2;

    memset(&action, 0, sizeof(action));
    action.sa_handler = handle_sigint;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGINT, &action, NULL) == -1)
    {
        perror("ft_ping: sigaction");
        close(sockfd);
        return 1;
    }

    identifier = (uint16_t)(getpid() & 0xffff);
    sequence = 0;
    transmitted = 0;
    received = 0;
    min_rtt = 0.0;
    max_rtt = 0.0;
    total_rtt = 0.0;
    exit_status = 0;

    printf("PING %s (%s) %d(%d) bytes of data.\n", options.destination,
           ip_string, PING_PAYLOAD_SIZE,
           PING_PAYLOAD_SIZE + (int)sizeof(struct icmphdr) +
               (int)sizeof(struct iphdr));

    while (!g_stop_requested)
    {
        sequence++;
        if (monotonic_milliseconds(&request_start_ms) == -1)
        {
            exit_status = 1;
            break;
        }
        if (send_echo_request(sockfd, &destination_address, identifier,
                              sequence) == -1)
        {
            exit_status = 1;
            break;
        }
        transmitted++;

        result = receive_echo_reply(sockfd, identifier, sequence,
                                    REPLY_TIMEOUT_MS, options.verbose, reply_ip,
                                    sizeof(reply_ip), &ttl, &reply_size);

        if (result == 0)
        {
            if (monotonic_milliseconds(&reply_time_ms) == -1)
            {
                exit_status = 1;
                break;
            }
            rtt_ms = reply_time_ms - request_start_ms;
            received++;
            if (received == 1 || rtt_ms < min_rtt)
                min_rtt = rtt_ms;
            if (received == 1 || rtt_ms > max_rtt)
                max_rtt = rtt_ms;
            total_rtt += rtt_ms;
            printf("%zu bytes from %s: icmp_seq=%u ttl=%u "
                   "time=%.3f ms\n",
                   reply_size, reply_ip, sequence, ttl, rtt_ms);
        }
        else if (result == 1)
            printf("Request timeout for icmp_seq=%u\n", sequence);
        else if (result == 2)
            break;
        else
        {
            exit_status = 1;
            break;
        }

        if (wait_for_next_interval(request_start_ms) == -1)
        {
            exit_status = 1;
            break;
        }
    }

    if (close(sockfd) == -1)
    {
        perror("ft_ping: close");
        exit_status = 1;
    }

    if (transmitted > 0)
    {
        packet_loss =
            ((double)(transmitted - received) / (double)transmitted) * 100.0;
        printf("\n--- %s ping statistics ---\n", options.destination);
        printf("%lu packets transmitted, %lu received, "
               "%.1f%% packet loss\n",
               transmitted, received, packet_loss);
        if (received > 0)
            printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n", min_rtt,
                   total_rtt / (double)received, max_rtt);
    }
    return exit_status;
}
