#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const char* host = (argc > 1) ? argv[1] : "172.16.40.1";
    int port = (argc > 2) ? std::atoi(argv[2]) : 13;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) != 1) {
        std::cerr << "Неверный адрес: " << host << "\n";
        close(sock);
        return 1;
    }

    if (sendto(sock, "", 0, 0, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("sendto");
        close(sock);
        return 1;
    }

    char buf[1024] = {0};
    socklen_t len = sizeof(addr);
    int n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (sockaddr*)&addr, &len);
    if (n < 0) {
        perror("recvfrom");
        close(sock);
        return 1;
    }

    std::cout << buf << std::endl;
    close(sock);
    return 0;
}
