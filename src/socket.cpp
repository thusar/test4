#include <sstream>
#include <type_traits>
#include <../include/socket.h>

Socket::Socket()
{
    socklen_t length{0};
    //bzero(_serverAddress, sizeof(_serverAddress));
    _serverAddress.sa_family = AF_INET;
    std::istringstream tempInputStringStream;
    tempInputStringStream >> _serverAddress.sa_data;
    std::istringstream::int_type myIntType;
    
}

Socket::~Socket()
{
    close(_socketFileDescriptor);
}

void Socket::read(pairOfTwoCharacters& buffer)
{
    ::read(_connectionFileDescriptor, static_cast<char*>(buffer), 2);
}

void Socket::write(const pairOfTwoCharacters& buffer)
{
    ::write(_connectionFileDescriptor, static_cast<char*>(buffer), 2);
}

pairOfTwoCharacters& Socket::read()
{
    std::size_t length = read_uint16();
    pairOfTwoCharacters& buffer{std::make_pair(length)};
    read(buffer);
    return buffer;
}

void Socket::write(pairOfTwoCharacters& buffer)
{
  uint16_t length = 2;
  write_uint16(length);
  write(buffer);
}

uint16_t Socket::read_uint16()
{
    pairOfTwoCharacters& buffer;
    read(buffer);
    uint16_t result = static_cast<uint16_t>(buffer);
    return result;
}

uint8_t Socket::read_uint8()
{
    char buffer;
    read(&buffer, 1);
    return static_cast<uint8_t>(buffer);
}

void Socket::write_uint16(const uint16_t& value)
{
    pairOfTwoCharacters buffer;
    buffer = static_cast<pairOfTwoCharacters>(value);
    write(buffer);
}

void Socket::write_uint8(const uint8_t& value)
{
    write(static_cast<const char*>(value));
}


