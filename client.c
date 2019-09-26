#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock, val = 1;
    char buf[16];
    struct sockaddr_in addr;
    struct ip_mreq mr;
    socklen_t size = sizeof(addr);
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("sock");
        exit(-1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    
    mr.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mr.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &val, sizeof(val));
    recvfrom(sock, buf, 16, 0, (struct sockaddr*)&addr, &size);
    printf("%s\n", buf);
    close(sock);
    exit(0);
}
