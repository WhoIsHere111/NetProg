#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const char* host = (argc > 1) ? argv[1] : "172.16.40.1";
    int port = (argc > 2) ? std::atoi(argv[2]) : 7;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &addr.sin_addr) != 1) {
        std::cerr << "Неверный адрес\n";
        close(sock);
        return 1;
    }

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    std::string msg;
    std::cout << "Введите сообщение: ";
    std::getline(std::cin, msg);

    if (send(sock, msg.c_str(), msg.size(), 0) < 0) {
        perror("send");
        close(sock);
        return 1;
    }

    char buf[1024] = {0};
    int n = recv(sock, buf, sizeof(buf) - 1, 0);
    if (n < 0) {
        perror("recv");
        close(sock);
        return 1;
    }

    std::cout << "Ответ сервера: " << buf << "\n";
    close(sock);
    return 0;
}
