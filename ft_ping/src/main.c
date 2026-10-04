#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

  // Step 1: Put 64 correct bytes in a buffer, send them to 127.0.0.1, and see a reply in tcpdump.
    unsigned char buf[64];
    struct icmphdr *hdr;
    int i;

    memset(buf, 0, sizeof(buf));
    hdr = (struct icmphdr *)buf;

    /* TODO: set the type to Echo Request */
    hdr->type = ICMP_ECHO; // `8` = Echo Request, `0` = Echo Reply

    /* TODO: set the code */
    hdr->code = 0; // it is `0` for echo messages.

    /* TODO: set the identifier to 42   (field: hdr->un.echo.id) */
    hdr->un.echo.id = 42;

    /* TODO: set the sequence to 1      (field: hdr->un.echo.sequence) */
    hdr->un.echo.sequence = 1;

    for (i = 0; i < 8; i++)
      printf("%02x ", buf[i]);

    printf("\n");
    return (0);
}