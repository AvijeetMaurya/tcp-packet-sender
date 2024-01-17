#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstring>
#include <string>
#include <iostream>
#include <vector>

#include "packet.hpp"
#include "util.hpp"

#include <x86intrin.h>

#define SERVER_IP_ADDR "localhost"
#define SERVER_TCP_PORT 31415

int main(int argc, char *argv[]) {
    struct sockaddr_in sa;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        std::cerr << "Socket error\n" << strerror(errno);
        return -1;
    }

    std::memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    inet_aton(SERVER_IP_ADDR, &sa.sin_addr);
    sa.sin_port = htons(SERVER_TCP_PORT);
    if (connect(fd, (struct sockaddr *)&sa, sizeof(sa))) {
        std::cerr << "Connect error\n" << strerror(errno);
        return -1;
    }

    int packetSize = sizeof(fo_ms_om_request_tr);
    send(fd, &packetSize, sizeof(int), 0);

    std::vector<unsigned long long> cycles;
    unsigned int temp;

    while (true) {
        fo_ms_om_request_tr packet;
        auto start = __rdtscp(&temp);
        send(fd, &packet, packetSize, 0);
        auto end = __rdtscp(&temp);
        cycles.push_back(end - start);
        print_stats(cycles);
    }
}