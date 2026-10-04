#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (fd < 0)
    {
        printf("socket failed: errno=%d (%s)\n", errno, strerror(errno));
        return 1;
    }
    printf("socket ok: fd=%d\n", fd);

    unsigned char buffer[65536];

    while (1)
    {
      ssize_t bytes_received = recvfrom(fd, buffer, sizeof(buffer), 0, NULL, NULL);
      if (bytes_received < 0)
      {
        printf("received %zd bytes, first byte=0x%02x, byte[20]=0x%02x\n", bytes_received, buffer[0], buffer[20]);
      }
      else
      {
        printf("received %zd bytes, first byte=0x%02x, but packet is too short for byte[20]\n", bytes_received, buffer[0]);
      }
    }
    
    close(fd);
    return 0;
}