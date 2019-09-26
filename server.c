#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    char buf[] = "Multicast!\n";
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = inet_addr("224.0.0.1");
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
    close(sock);
    exit(0);
}
