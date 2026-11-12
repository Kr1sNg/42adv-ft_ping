# 🏓 ft_ping 🏓

A from-scratch reimplementation of `ping` in C, modelled on **GNU inetutils 2.0**.
It sends ICMP Echo Requests over a raw IPv4 socket, matches the replies to its own requests, measures the round-trip time (RTT), and prints the same output and statistics as the reference.

---

## Table of contents

- [Quick start](#quick-start)
- [Usage](#usage)
- [Example output](#example-output)
- [How it works](#how-it-works)
  - [Program flow](#program-flow)
  - [Building the Echo Request](#building-the-echo-request)
  - [The Internet checksum](#the-internet-checksum)
  - [Receiving and filtering](#receiving-and-filtering)
  - [Timing model](#timing-model)
  - [RTT and statistics](#rtt-and-statistics)
  - [Signal handling](#signal-handling)
- [Project layout](#project-layout)
- [Error handling and exit codes](#error-handling-and-exit-codes)
- [Differences from inetutils 2.0](#differences-from-inetutils-20)
- [Testing](#testing)
- [References](#references)

---

## Quick start

```sh
make                         # builds ./ft_ping
sudo ./ft_ping 8.8.8.8       # raw sockets need privileges
```

To run it without `sudo`, give the binary the one capability it needs:

```sh
sudo setcap cap_net_raw+ep ./ft_ping
./ft_ping google.com
```

Makefile rules: `all`, `clean`, `fclean`, `re`. Compiled with `cc -Wall -Wextra -Werror`.

**Requirements:** Linux, a C compiler, `make`. Tested on Debian 12.

---

## Usage

```text
Usage: ft_ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.

 Options valid for all request types:
  -v, --verbose              verbose output

  -?, --help                 give this help list
```

| Option | Effect |
|---|---|
| `-v`, `--verbose` | Prints the ICMP identifier in the header line. For ICMP errors (Destination Unreachable, Time Exceeded), it also dumps the IP and ICMP headers of the request that caused the error. |
| `-?`, `--help` | Prints the help text and exits with status `0`. |

`HOST` is a single IPv4 address (`8.8.8.8`) or a hostname / FQDN (`google.com`). The name is resolved **once**, before sending. Reply addresses are printed numerically, with no reverse DNS lookup.

Stop with **Ctrl+C**. The statistics are printed on exit.

---

## Example output

Loopback:

```text
$ sudo ./ft_ping 127.0.0.1
PING 127.0.0.1 (127.0.0.1): 56 data bytes
64 bytes from 127.0.0.1: icmp_seq=0 ttl=64 time=0.042 ms
64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.072 ms
64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.065 ms
64 bytes from 127.0.0.1: icmp_seq=3 ttl=64 time=0.068 ms
^C--- 127.0.0.1 ft_ping statistics ---
4 packets transmitted, 4 packets received, 0% packet loss
round-trip min/avg/max/stddev = 0.042/0.062/0.072/0.012 ms
```

Verbose mode, with a hostname:

```text
$ sudo ./ft_ping -v localhost
PING localhost (127.0.0.1): 56 data bytes, id 0x0126 = 294
64 bytes from 127.0.0.1: icmp_seq=0 ttl=64 time=0.032 ms
...
```

ICMP error with `-v`. Here a gateway reports the destination as unreachable, and ft_ping dumps the request that was rejected:

```text
$ sudo ./ft_ping -v 10.255.255.1
PING 10.255.255.1 (10.255.255.1): 56 data bytes, id 0x0133 = 307
92 bytes from 21.4.109.201: Destination Port Unreachable
IP Hdr Dump:
 4500 0054 2072 4000 3e01 5034 c000 0202 0aff ff01
Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src	Dst	Data
 4  5  00 0054 2072   2 0000  3e  01 5034 192.0.2.2  10.255.255.1
ICMP: type 8, code 0, size 64, id 0x0133, seq 0x0000
^C--- 10.255.255.1 ft_ping statistics ---
1 packets transmitted, 0 packets received, 100% packet loss
```

Argument errors:

```text
$ ./ft_ping
./ft_ping: missing host operand
Try './ft_ping --help' for more information.

$ ./ft_ping nonexistent.invalid
ft_ping: unknown host
```

---

## How it works

### Program flow

```text
main
 ├─ parse_args()          -v / -? / HOST            (parse.c)
 ├─ resolve_dest()        getaddrinfo(AF_INET)      (network.c)
 ├─ create_icmp_socket()  socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)
 ├─ handle_signal()       SIGINT -> g_stop = true   (signal.c)
 └─ run_loop()                                      (loop.c)
     ├─ print_header()
     ├─ while (!g_stop)
     │   ├─ time to send?   -> send_echo_request(), next_send += 1000 ms
     │   └─ recv_echo_reply(until next_send)        (receive.c)
     │        ├─ Echo Reply for us  -> record_reply() + print_reply()
     │        └─ ICMP error for us  -> print_error()
     └─ print_stats()
```

The program is **single-threaded** and uses **no `SIGALRM`**. Sending and receiving are driven by one `select()` loop with an absolute deadline (see [Timing model](#timing-model)).

### Building the Echo Request

The packet is 64 bytes: an 8-byte ICMP header followed by a 56-byte payload. The kernel adds the 20-byte IPv4 header, so 84 bytes go on the wire.

```text
 0      1      2      3      4      5      6      7      8                     63
+------+------+------+------+------+------+------+------+------------------------+
| type | code |  checksum   | identifier  |  sequence   |   payload (56 bytes)   |
|  8   |  0   |   RFC 1071  | pid & 0xffff|  0, 1, 2…   | timespec | 0x10 0x11… |
+------+------+------+------+------+------+------+------+------------------------+
```

- **Identifier**: `getpid() & 0xffff`, in network byte order. ICMP has no ports, so this field is how replies are matched to this process.
- **Sequence**: starts at 0 and goes up by one per packet. It is stored on 16 bits and wraps at 65536.
- **Payload**: the first 16 bytes hold the send time (`struct timespec`, `CLOCK_MONOTONIC`). The remaining bytes are the filler pattern `i`, so byte *i* has the value *i*. The destination echoes the payload back unchanged, so every reply brings its own send timestamp with it.

### The Internet checksum

RFC 1071 one's-complement sum over the whole ICMP message (header + payload):

1. Set the checksum field to 0.
2. Read the message as big-endian 16-bit words and add them into a 32-bit accumulator. If the length is odd, pad the last byte with a zero.
3. Fold the carries back in: `sum = (sum & 0xffff) + (sum >> 16)` until nothing is above bit 15.
4. Take the one's complement, then store it with `htons()`.

The same function **validates** incoming replies. A correct message, checksum field included, sums to `0`. Replies that fail this test are dropped.

### Receiving and filtering

A raw `IPPROTO_ICMP` socket gets a copy of **every** ICMP packet the host receives. That includes other `ping` processes, unrelated errors and, on loopback, ft_ping's own outgoing requests. `recvfrom()` returns the full IP datagram, so the parser:

1. Reads the IP header and skips it using `ip_hl * 4`. The header is not always 20 bytes, because IP options can make it longer.
2. Checks each length before reading the next header, so a truncated or malformed packet cannot cause an out-of-bounds read.
3. Dispatches on the ICMP type:

| Type | Accepted when | Result |
|---|---|---|
| `0` Echo Reply | identifier = ours, payload holds a timestamp, checksum is valid | RTT computed, reply line printed |
| `3` Destination Unreachable / `11` Time Exceeded | the **quoted** original packet (`[ICMP err hdr][orig IP hdr][orig ICMP hdr]`) carries our identifier | error line printed (+ header dump with `-v`) |
| anything else, including our own Echo Requests seen on loopback | — | silently ignored |

For errors, the identifier sits inside the *quoted* packet, after a second IP header of variable length. The parser skips that header with its own `ip_hl` before it reads the identifier.

### Timing model

```text
next_send = now
loop:
    if now >= next_send: send; next_send += 1000 ms
    select(sock, timeout = next_send - now)    # wake on a packet OR at next_send
```

- Each send time is computed as `previous + 1000 ms`, not as "1 s after the previous send finished". Processing time therefore does not add up, and the interval does not drift over a long run.
- All times come from **`CLOCK_MONOTONIC`**, so NTP corrections or a manual clock change cannot produce a negative or wrong RTT.
- A reply is handled as soon as it arrives, even if it is late and its request was not the last one sent. Its RTT is still correct because the RTT comes from the timestamp inside the reply, not from the sender's own records.

### RTT and statistics

- **RTT** = `now_ms() - timestamp_echoed_in_payload`, printed with 3 decimals.
- **Duplicates**: a `seen[65536]` table indexed by sequence number. A second reply for the same sequence is printed with `(DUP!)` and counted separately, so it does not change the received count or the RTT figures. The entry is cleared when that sequence number is sent again, which handles wrap-around.
- **Packet loss** = `(transmitted - received) * 100 / transmitted`, using integer division as inetutils does.
- **min / avg / max / stddev**: running min and max, plus the sum and the sum of squares, so the statistics use constant memory:

```text
avg    = Σrtt / n
stddev = sqrt( Σrtt² / n − avg² )
```

### Signal handling

`SIGINT` is installed with `sigaction()`. The handler only sets `volatile sig_atomic_t g_stop`. If `select()` or `recvfrom()` is interrupted with `EINTR`, this is not treated as an error: the loop checks `g_stop`, exits cleanly, prints the statistics and closes the socket.

---

## Project layout

```text
.
├── Makefile
├── includes/
│   └── ft_ping.h       constants, structs, prototypes
└── src/
    ├── main.c          start-up sequence, socket cleanup
    ├── parse.c         command-line parsing (-v, -?, HOST)
    ├── network.c       DNS resolution, raw socket creation
    ├── loop.c          send loop, packet building, checksum, statistics
    ├── receive.c       select() wait, recvfrom(), packet filtering/parsing
    ├── print.c         every user-facing line (header, replies, errors, stats, help)
    ├── signal.c        SIGINT handler
    └── time.c          monotonic clock helpers
```

Main data structures (`includes/ft_ping.h`):

| Struct | Role |
|---|---|
| `t_ping_option` | parsed CLI: `verbose`, `dest` |
| `t_ping_context` | read-only run context: socket, resolved `sockaddr_in`, display name and IP, options |
| `t_ping_reply` | one packet that belongs to us: Echo Reply or ICMP error, with source, TTL, size, seq, RTT, type/code, pointer to the quoted IP header |
| `t_ping_stats` | counters, RTT accumulators, duplicate table |

---

## Error handling and exit codes

| Situation | Message | Exit |
|---|---|---|
| `-?` / `--help` | help text | `0` |
| missing host, more than one host, unknown option | `missing host operand` / `too many destinations` / `invalid option -- 'x'` / `unrecognized option '--x'` + `Try '... --help'` | `64` (`EX_USAGE`) |
| host does not resolve | `ft_ping: unknown host` | `1` |
| not root and no `CAP_NET_RAW` | `ft_ping: Lacking privilege for icmp socket.` | `1` |
| `sendto` / `select` / `recvfrom` / `sigaction` failure | `ft_ping: <call>: strerror(errno)` | `1` |
| interrupted, at least one reply received | statistics | `0` |
| interrupted, no reply received | statistics | `1` |

Memory: no heap allocation in the main code path. The `addrinfo` list is freed right after resolution, the receive buffer is a fixed 64 KiB static, and the socket is closed on every exit path after it is opened.

---

## Differences from inetutils 2.0

- Only `-v` and `-?` are implemented. The other inetutils flags are part of the bonus.
- Reply addresses are numeric. There is no reverse DNS, which the subject allows.
- The statistics banner reads `--- HOST ft_ping statistics ---`, so the output can be told apart from the system `ping`.
- The subject allows ±30 ms of difference on the measured RTT.

---

## Testing

Comparing with the reference on the same machine:

```sh
ping -V                                   # must say: ping (GNU inetutils) 2.0
sudo ping     -v -c 3 8.8.8.8
sudo ./ft_ping -v 8.8.8.8                 # Ctrl+C after 3 replies
```

Scenarios worth checking:

| Scenario | How |
|---|---|
| Loopback / LAN / Internet | `127.0.0.1`, your gateway, `8.8.8.8` |
| Hostname resolution | `google.com`, `localhost` |
| Unknown host | `nonexistent.invalid` |
| Silent host (100% loss, exit 1) | an unused address on your LAN |
| Time Exceeded | `sudo iptables -t mangle -A OUTPUT -p icmp -j TTL --ttl-set 1` (remove afterwards) or test against a router that drops TTL=1 |
| Destination Unreachable + `-v` dump | an unroutable address behind a gateway that answers |
| Concurrent pings don't mix | run ft_ping and system `ping` to the same host at the same time: each one must count only its own replies |
| Packet loss | `sudo tc qdisc add dev lo root netem loss 30%` then ping `127.0.0.1` (`tc qdisc del dev lo root` to undo) |
| Privileges | run without `sudo`: clean error, exit 1 |
| Leaks / FDs | `sudo valgrind --leak-check=full --track-fds=yes ./ft_ping 127.0.0.1` |

To see the packets on the wire:

```sh
sudo tcpdump -ni any icmp -vv
```

---

## References

- RFC 792 — Internet Control Message Protocol
- RFC 1071 — Computing the Internet Checksum
- RFC 791 — Internet Protocol
- `man 7 raw`, `man 7 icmp`, `man 2 socket`, `man 2 sendto`, `man 2 recvfrom`, `man 2 select`, `man 3 getaddrinfo`, `man 7 capabilities`
- GNU inetutils 2.0 `ping` (behaviour reference only. No code from it was reused)
- [NOTES.md](NOTES.md): my learning notes on ICMP, raw sockets, byte order and the checksum
