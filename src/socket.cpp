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

ssize_t Socket::read(const pairOfTwoCharacters& buffer)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;
    wholeBuffer.resize(2);

    ssize_t twoChars = ::read(_connectionFileDescriptor, static_cast<void*>(const_cast<char*>(wholeBuffer.data())), 2);
    return twoChars;
}

void Socket::write(const pairOfTwoCharacters& buffer, std::size_t lengthOfBuffer=2)
{
    std::string first{buffer.first};
    std::string second{buffer.second};
    std::string wholeBuffer = first + second;

    ::write(_connectionFileDescriptor, wholeBuffer.c_str(), 2);
}

pairOfTwoCharacters Socket::read()
{
    std::uint16_t twoChars = read_uint16();
    char lowerChar = twoChars & 0xFF;
    char higherChar = twoChars >> 8;
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
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
    pairOfTwoCharacters buffer;
    ssize_t twoChars = read(buffer);
    uint16_t result = static_cast<uint16_t>(twoChars);
    return result;
}

void Socket::write_uint16(const uint16_t& value)
{
    char lowerChar = value & 0xFF; // Extract lower 8 bits
    char higherChar = (value >> 8) & 0xFF; // Extract higher 8 bits
    pairOfTwoCharacters buffer = std::make_pair(lowerChar, higherChar);
    write(buffer);
}
