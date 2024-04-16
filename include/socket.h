#ifndef _SOCKET_H
#define _SOCKET_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <bits/sockaddr.h>
#include <bits/socket.h>
#include <csignal>
#include <cstdint>
#include <cuchar>
#include <csignal>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <utility>

using pairOfTwoCharacters = std::pair<char, char>;

class Socket
{
private:
    int _socketFileDescriptor{socket(AF_INET, SOCK_STREAM, 0)};
    int _connectionFileDescriptor{0};
    std::uint16_t _port;
    sockaddr _serverAddress;
    std::string _ip{"0.0.0.0"};
public:
    Socket();
    ~Socket();
    ssize_t read(const pairOfTwoCharacters& buffer);
    void write(const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer);
    pairOfTwoCharacters read();
    void write(pairOfTwoCharacters& buffer);
    std::uint16_t read_uint16();
    void write_uint16(const uint16_t& value);
};

#endif