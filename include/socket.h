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
using maxConnects = int;
constexpr maxConnects maxConnectsValue = 8;
class SocketPlayer;
class SocketJudge
{
private:
    int _socketFileDescriptor{socket(AF_INET, SOCK_STREAM, 0)};
    int _connectionFileDescriptor{0};
    std::uint16_t _port;
    std::shared_ptr<sockaddr> _socketAddress;
    std::string _ip{"0.0.0.0"};
public:
    SocketJudge();
    ~SocketJudge();

    int bind();
    int get_socket_file_descriptor() { return _socketFileDescriptor;}
    std::shared_ptr<sockaddr> get_socket_address() { return _socketAddress; }
    int listen(SocketPlayer& socketPlayer);
    int accept(SocketPlayer& socketPlayer);
    ssize_t read(const pairOfTwoCharacters& buffer);
    void write(const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer);
    pairOfTwoCharacters read(SocketPlayer& socketPlayer);
    void write(SocketPlayer& socketPlayer, pairOfTwoCharacters& buffer);
    std::uint16_t read_uint16();
    void write_uint16(const uint16_t& value);
};

class SocketPlayer
{
private:
    int _socketFileDescriptor{socket(AF_INET, SOCK_STREAM, 0)};
    int _connectionFileDescriptor{0};
    std::uint16_t _port;
    std::shared_ptr<sockaddr> _socketAddress;
    std::string _ip{"0.0.0.0"};
public:
    SocketPlayer();
    ~SocketPlayer();
    int get_socket_file_descriptor() { return _socketFileDescriptor;}
    std::shared_ptr<sockaddr> get_socket_address() { return _socketAddress; }
    int connect(SocketJudge& socketJudge);
    ssize_t read(SocketJudge& socketJudge, const pairOfTwoCharacters& buffer);
    void write(SocketJudge& socketJudge, const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer);
    pairOfTwoCharacters read(SocketJudge& socketJudge);
    void write(SocketJudge& socketJudge, pairOfTwoCharacters& buffer);
    std::uint16_t read_uint16(SocketJudge& socketJudge);
    void write_uint16(SocketJudge& socketJudge, const uint16_t& value);
};
#endif