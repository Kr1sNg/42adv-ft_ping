# ft_ping

Re-coding the ping command will allow you to become acquainted with raw IP communication between two machines on a network.

## Introduction

**Ping** is the name of a command that allows you to test the accessibility of another machine through the IP network. The command also measures the time taken to receive a response, called the round-trip time.

### Requirements

- A C program named `ft_ping`, with a `Makefile` (usual rules, no unnecessary relinking).
- The reference behavior is ping from `inetutils-2.0` (check it with `ping -V`).
- Mandatory options: `-v` (verbose) and `-?` (help).
- The argument is a single IPv4 target, either an address (`8.8.8.8`) or a hostname (`google.com`).
- FQDN handling without DNS resolution on the packet return.
- No crashes (segfault, double free, etc.), and errors must be handled carefully.
- Output must have indentation identical to `inetutils-2.0`, except for the RTT line and the reverse DNS part.
- A ±30 ms delay is tolerated on packet reception.
- You may not call the system ping or reuse its sources.
- Additional `-f` `-l` `-n` `-w` `-W` `-p` `-r` `-s` `-T` `--ttl` `--ip-timestamp` flags

### What happens when you run ft_ping ?

```text
parse arguments (-v, -?, target)
        ↓
resolve "google.com" → IPv4 address
        ↓
create a raw socket (requires privileges → why?)
        ↓
loop, once per second:
    build ICMP Echo Request (type, code, id, sequence, timestamp, checksum)
        ↓
    sendto() → kernel adds IP header → network → destination
        ↓
    destination answers with ICMP Echo Reply
        ↓
    recvfrom() → you receive IP header + ICMP
        ↓
    check: is this reply MINE? (id, sequence)
        ↓
    compute RTT, print a line
        ↓
Ctrl+C (SIGINT) → print statistics (sent, received, loss %, min/avg/max/stddev)
```

### Observe the reference

```sh
tat-nguy😺vmdeb12:~ $ ping -V
ping (GNU inetutils) 2.0

tat-nguy😺vmdeb12:~ $ ping -c 4 127.0.0.1
PING 127.0.0.1 (127.0.0.1): 56 data bytes
64 bytes from 127.0.0.1: icmp_seq=0 ttl=64 time=0.117 ms
64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.053 ms
64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.032 ms
64 bytes from 127.0.0.1: icmp_seq=3 ttl=64 time=0.046 ms
--- 127.0.0.1 ping statistics ---
4 packets transmitted, 4 packets received, 0% packet loss
round-trip min/avg/max/stddev = 0.032/0.062/0.117/0.033 ms

tat-nguy😺vmdeb12:~ $ ping -c 3 google.com
PING google.com (172.217.22.78): 56 data bytes
64 bytes from 172.217.22.78: icmp_seq=0 ttl=255 time=28.869 ms
64 bytes from 172.217.22.78: icmp_seq=1 ttl=255 time=34.343 ms
64 bytes from 172.217.22.78: icmp_seq=2 ttl=255 time=30.006 ms
--- google.com ping statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max/stddev = 28.869/31.073/34.343/2.359 ms

tat-nguy😺vmdeb12:~ $ ping -?
Usage: ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.

 Options controlling ICMP request types:
      --echo                 send ICMP_ECHO packets (default)
  -t, --type=TYPE            send TYPE packets

 Options valid for all request types:

  -c, --count=NUMBER         stop after sending NUMBER packets

  -n, --numeric              do not resolve host addresses
  -r, --ignore-routing       send directly to a host on an attached network
      --ttl=N                specify N as time-to-live
  -T, --tos=NUM              set type of service (TOS) to NUM
  -v, --verbose              verbose output
  -w, --timeout=N            stop after N seconds
  -W, --linger=N             number of seconds to wait for response

 Options valid for --echo requests:

  -f, --flood                flood ping (root only)
      --ip-timestamp=FLAG    IP timestamp of type FLAG, which is one of
                             "tsonly" and "tsaddr"
  -l, --preload=NUMBER       send NUMBER packets as fast as possible before
                             falling into normal mode of behavior (root only)
  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)
  -s, --size=NUMBER          send NUMBER data octets

  -?, --help                 give this help list
      --usage                give a short usage message
  -V, --version              print program version

tat-nguy😺vmdeb12:~ $ ping -v -c 3 google.com
PING google.com (172.217.22.78): 56 data bytes, id 0xf5c8 = 62920
64 bytes from 172.217.22.78: icmp_seq=0 ttl=255 time=57.526 ms
64 bytes from 172.217.22.78: icmp_seq=1 ttl=255 time=67.796 ms
64 bytes from 172.217.22.78: icmp_seq=2 ttl=255 time=101.337 ms
--- google.com ping statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max/stddev = 57.526/75.553/101.337/18.708 ms

tat-nguy😺vmdeb12:~ $ ping --ttl=1 -v -c 3 google.com
PING google.com (172.217.22.78): 56 data bytes, id 0xf5d0 = 62928
64 bytes from 172.217.22.78: icmp_seq=0 ttl=255 time=30.565 ms
64 bytes from 172.217.22.78: icmp_seq=1 ttl=255 time=46.379 ms
64 bytes from 172.217.22.78: icmp_seq=2 ttl=255 time=112.038 ms
--- google.com ping statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max/stddev = 30.565/62.994/112.038/35.275 ms

tat-nguy😺vmdeb12:~ $ ping nonexistent.invalid
ping: unknown host
```

### ICMP - Internet Control Message Protocol

ICMP is the protocol that netwrok devices use to send each other control and error messages, such as "are you there?", "I'm here" or "I couldn't deliver your packet".

ICMP is defined in RFC 792, it lives at the network layer, alongside IP, and is carried inside IP packets. In the IP header, the protocol field is st to `1` to mean "the payload is ICMP".

`ping` is basically a program that sends one specific ICMP message (Echo Request) and waits for another (Echo Reply).

Diffically, not like TCP and UDP, there's no port to tell in ICMP.

#### The ICMP Echo message format

- Type (1 byte): what kind of message this is (`8` = Echo Request, `0` = Echo Reply)
- Code (1 byte): a sub-type. It is `0` for echo messages.
- Checksum (2 byte): detects corruption. It is computed over the whole ICMP message (header + data).
- Identifier (2 bytes): a value you choose to identify your ping session. The destination copies it into the reply.
- Sequence (2 bytes): a counter, incremented with each packet sent. It is also copied into the reply.
- Data: arbitrary bytes, also copied back by the destination. A common trick is to store the send time here, so the reply carries its own timestamp back to you.

#### The error messages (`-v` verbose output)

- Type `3`: Destination Unreachable: A router or host can't deliver the packet.
- Type `11`: Time Exceeded: TTL reached 0 along the way.

### Raw sockets and privileges

#### Socket

A socket is the door between your program and the kernel's networking stack. We write data into it to send and read data from it to receive.

Normally the kernel does most of protocol work for us. With a TCP socket we hand over bytes, and the kernel builds the TCP and IP headers, handles retransmission, ordering, and ports.

A raw socket skips the transport layer (TCP/UDP): we build the protocol message ourselves, and the kernel only handles IP.

-> ICMP isn't TCP or UDP, so there's no ICMP stream socket type. We need a socket that lets us write the ICMP header bytes ourselves.

```c
int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

// AF_INET: Address family: IPv4
// SOCK_RAW: Socket type: raw (no transport layer handled by kernel)
// IPPROTO_ICMP: Protocol number 1
```

#### What kernel actually does with a raw ICMP socket

- Sending: you pass the ICMP header + data to `sendto()`. The kernel adds the IP header itself (source address, TTL, protocol=1, IP checksum,...)

```c
ssize_t sendto(int sockfd,
                const void buf[.len],
                size_t len,
                int flags,
                const struct sockaddr *dest_addr,
                socklen_t addrlen);
```

- Receiving: `recvfrom()` gives you the full IP header + ICMP. That's the asymmetry, you send ICMP but recieve IP + ICMP. You must skip the IP header before reading the ICMP fields. Its length isn't always 20 bytes, so think about which IP header field tells you its real length.

```c
ssize_t recvfrom(int sockfd,
                  void buf[restrict .len],
                  size_t len,
                  int flags,
                  struct sockaddr *_Nullable restrict src_addr,
                  socklen_t *_Nullable restrict addrlen);
```

- Filtering: a raw `IPPROTO_ICMP` socket receives a copy of every ICMP packet arriving at the machine, not just the replies to your requests. That includes other programs' pings, errors meant for other processes, etc. The kernel does no filtering for you. This is the concrete answer to "ICMP has no ports, so how do I find my replies?" -> You have to filter.

#### Why privileges are needed

Raw socket are powerful in ways that could be abused. A program with raw sockets can forge packets and observe ICMP traffic belonging to other processes. Because of this, Linux restricts them.

Instead of "root can do everything", Linux splits root's powers into pieces.

#### Check the knowledge

1. Your raw socket receives every ICMP packet arriving on the machine. What will you check in each received packet to decide "this reply is mine"?
   -> Check the type first, then the identifier (and sequence for matching), and the location of the identifier depends on the type.

2. When you call `recvfrom()`, what comes first in your buffer before the ICMP header, and how do you find where the ICMP header starts?
   -> IP header. Because 84 bytes received = 20 (IP header) + 8 (ICMP header) + 56 (ICMP data)

### 1 - Build Echo Request

#### Layout

```
offset  0      1      2      3      4      5      6      7      8 ...           63
      +------+------+------+------+------+------+------+------+--------------------+
      | type | code |  checksum   | identifier  |  sequence   |   56 bytes data    |
      |  8   |  0   |   (later)   |  (yours)    |   0,1,2...  | (timestamp + fill) |
      +------+------+------+------+------+------+------+------+--------------------+
```

```c
struct icmphdr
{
  uint8_t type;		/* message type */
  uint8_t code;		/* type sub-code */
  uint16_t checksum;
  union
  {
    struct
    {
      uint16_t	id;
      uint16_t	sequence;
    } echo;			/* echo datagram */
    uint32_t	gateway;	/* gateway address */
    struct
    {
      uint16_t	__glibc_reserved;
      uint16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};

// or

/*
 * Internal of an ICMP Router Advertisement
 */
struct icmp_ra_addr
{
  uint32_t ira_addr;
  uint32_t ira_preference;
};

struct icmp
{
  uint8_t  icmp_type;	/* type of message, see below */
  uint8_t  icmp_code;	/* type sub code */
  uint16_t icmp_cksum;	/* ones complement checksum of struct */
  union
  {
    unsigned char ih_pptr;	/* ICMP_PARAMPROB */
    struct in_addr ih_gwaddr;	/* gateway address */
    struct ih_idseq		/* echo datagram */
    {
      uint16_t icd_id;
      uint16_t icd_seq;
    } ih_idseq;
    uint32_t ih_void;

    /* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
    struct ih_pmtu
    {
      uint16_t ipm_void;
      uint16_t ipm_nextmtu;
    } ih_pmtu;

    struct ih_rtradv
    {
      uint8_t irt_num_addrs;
      uint8_t irt_wpa;
      uint16_t irt_lifetime;
    } ih_rtradv;
  } icmp_hun;
#define	icmp_pptr	icmp_hun.ih_pptr
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define	icmp_pmvoid	icmp_hun.ih_pmtu.ipm_void
#define	icmp_nextmtu	icmp_hun.ih_pmtu.ipm_nextmtu
#define	icmp_num_addrs	icmp_hun.ih_rtradv.irt_num_addrs
#define	icmp_wpa	icmp_hun.ih_rtradv.irt_wpa
#define	icmp_lifetime	icmp_hun.ih_rtradv.irt_lifetime
  union
  {
    struct
    {
      uint32_t its_otime;
      uint32_t its_rtime;
      uint32_t its_ttime;
    } id_ts;
    struct
    {
      struct ip idi_ip;
      /* options and then 64 bits of data */
    } id_ip;
    struct icmp_ra_addr id_radv;
    uint32_t   id_mask;
    uint8_t    id_data[1];
  } icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
#define	icmp_ip		icmp_dun.id_ip.idi_ip
#define	icmp_radv	icmp_dun.id_radv
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
};
```

#### Byte order

- Byte order (endianness) is the order in which a multi-byte number is stored in memory.

- x86 machines store the low-order byte first (little-endian). Network protocols are defined with the high-order byte first (big-endian).

#### The checksum

Purpose: The receiver recomputes it to detect corrupted packets. A packet with a wrong checksum is silenty dropped. That means a broken checksum looks exactly like "the host doesn't answer".

The algorithm:
- Set the checksum field to 0 first.
- Treat the whole ICMP message (header + data) as a sequence of 16-bit words and add them together in a 32-bit accumulator.
- If there's one leftover byte (odd length), add it too, as if padded with a zero byte.
- "Fold" the carries: while the accumulator has bits above the low 16, add the high part to the low part.
- Take the one's complement (`~`) of the result and keep 16 bits. That's the checksum.

A subtle but well-known property: this one's complement sum gives correct results regardless of the machine's byte order, as long as we read the 16-bit words directly from the packet's memory and store the result back the same way.

#### The data part

`inetutils` sends 56 data bytes by default. Since the destination echoes the data back unchanged, many implementations store the send time (`struct timeval` from ``gettimeofday()`) at the start of the data and fill the rest with a pattern.

#### Sending it: `sendto()`

```c
ssize_t sendto(int sockfd,
                const void *buf,
                size_t len,
                int flags,
                const struct sockaddr *dest,
                socklen_t dest_len);
```

- `buf`, `len`: your ICMP message only (64 bytes) with no IP header, because the kernel adds it.
- `dest`: a `struct sockaddr_in` holding the destination IPv4 address. It's cast to the generic `struct sockaddr *` because `sendto()` works for every address family.
- Return value: the number of bytes sent, or `-1` with `errno` set.