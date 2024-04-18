#ifndef _BOARD_H
#define _BOARD_H

#include <array>
#include <cstdint>

enum class Ships : std::uint8_t
{   Battleship
};

constexpr std::uint8_t Battleship{4};

using board = std::array<std::array<char, 10>, 10>;

class Board
{
private:
    board _board;
public:
};

#endif