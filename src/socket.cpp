#include <memory>
#include <sstream>
#include <sys/socket.h>
#include <type_traits>
#include "../include/socket.h"

SocketJudge::SocketJudge()
{
    socklen_t length{0};

    _socketAddress->sa_family = AF_INET;
    std::istringstream tempInputStringStream;
    tempInputStringStream >> _socketAddress->sa_data;
    std::istringstream::int_type myIntType;
}

SocketJudge::~SocketJudge()
{
    close(_socketFileDescriptor);
}

int SocketJudge::bind()
{
    int bindResult = ::bind(_socketFileDescriptor, reinterpret_cast<const struct sockaddr *>(_socketAddress.get()), sizeof(*_socketAddress));
    return bindResult;
}

int SocketJudge::listen(SocketPlayer& socketPlayer)
{
    int listenResult = ::listen(socketPlayer.get_socket_file_descriptor(), maxConnectsValue);
    return listenResult;
}

int SocketJudge::accept(SocketPlayer& socketPlayer)
{
    socklen_t socketAddressSize = sizeof(*(socketPlayer.get_socket_address().get()));
    int clientFileDescriptor = ::accept(socketPlayer.get_socket_file_descriptor(), socketPlayer.get_socket_address().get(), &socketAddressSize);
    return clientFileDescriptor;
}

ssize_t SocketJudge::read(const pairOfTwoCharacters& buffer)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;
    wholeBuffer.resize(2);

    ssize_t twoChars = ::read(_connectionFileDescriptor, static_cast<void*>(const_cast<char*>(wholeBuffer.data())), 2);
    return twoChars;
}

void SocketJudge::write(const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer=2)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;

    ::write(_connectionFileDescriptor, wholeBuffer.c_str(), 2);
}

pairOfTwoCharacters SocketJudge::read(SocketPlayer& socketPlayer)
{
    std::uint16_t twoChars = socketPlayer.read_uint16();
    char lowerChar = twoChars & 0xFF;
    char higherChar = twoChars >> 8;
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
    return buffer;
}

void SocketJudge::write(SocketPlayer& socketPlayer, pairOfTwoCharacters& buffer)
{
  uint16_t length = 2;
  socketPlayer.write_uint16(length);
  socketPlayer.write(buffer);
}

uint16_t SocketJudge::read_uint16()
{
    pairOfTwoCharacters buffer;
    ssize_t twoChars = read(buffer);
    uint16_t result = static_cast<uint16_t>(twoChars);
    return result;
}

void SocketJudge::write_uint16(const uint16_t& value)
{
    char lowerChar = value & 0xFF; // Extract lower 8 bits
    char higherChar = (value >> 8) & 0xFF; // Extract higher 8 bits
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
    write(buffer);
}

SocketPlayer::SocketPlayer()
{
    socklen_t length{0};

    _socketAddress->sa_family = AF_INET;
    std::istringstream tempInputStringStream;
    tempInputStringStream >> _socketAddress->sa_data;
    std::istringstream::int_type myIntType;
}

SocketPlayer::~SocketPlayer()
{
    close(_socketFileDescriptor);
}

int SocketPlayer::connect(SocketJudge& socketJudge)
{
    return 0;
}

ssize_t SocketPlayer::read(const pairOfTwoCharacters& buffer)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;
    wholeBuffer.resize(2);

    ssize_t twoChars = ::read(_connectionFileDescriptor, static_cast<void*>(const_cast<char*>(wholeBuffer.data())), 2);
    return twoChars;
}

void SocketPlayer::write(const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer=2)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;

    ::write(_connectionFileDescriptor, wholeBuffer.c_str(), 2);
}

pairOfTwoCharacters SocketPlayer::read()
{
    std::uint16_t twoChars = read_uint16();
    char lowerChar = twoChars & 0xFF;
    char higherChar = twoChars >> 8;
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
    return buffer;
}

void SocketPlayer::write(pairOfTwoCharacters& buffer)
{
  uint16_t length = 2;
  write_uint16(length);
  write(buffer);
}

uint16_t SocketPlayer::read_uint16()
{
    pairOfTwoCharacters buffer;
    ssize_t twoChars = read(buffer);
    uint16_t result = static_cast<uint16_t>(twoChars);
    return result;
}

void SocketPlayer::write_uint16(const uint16_t& value)
{
    char lowerChar = value & 0xFF; // Extract lower 8 bits
    char higherChar = (value >> 8) & 0xFF; // Extract higher 8 bits
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
    write(buffer);
}
