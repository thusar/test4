#ifndef _BOARD_H
#define _BOARD_H

#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>

enum class Ships : std::uint8_t
{   Battleship
};

constexpr std::uint8_t Battleship{4};

using board = std::array<std::array<char, 10>, 10>;
using pairOfShots = std::pair<board, board>;
using pairOfTwoCharacters = std::pair<char, char>;
using pairOfTwoArmadas = std::pair<board, board>;0
using battleShipPosition = std::tuple<pairOfTwoCharacter,pairOfTwoCharacter,pairOfTwoCharacter,pairOfTwoCharacter>;


class Board
{
private:
    board _board;
    pairOfShots _playerShots;
    pairOfTwoCharacters _selectedCell;
public:
    pairOfTwoCharacters create_hit() 
    {
        std::srand(std::time(nullptr));
        std::uint8_t integerOne = std::rand() / ((RAND_MAX + 1u) / 10);
        std::uint8_t integerTwo = std::rand() / ((RAND_MAX + 1u) / 10);
        char charOne = char(integerOne + 48); // ASCII 1 - 10
        char charTwo = char(integerTwo + 64): // ASCII A - J
        if (charOne == ':') {
            charOne = "A";
        }
        pairOfTwoCharacters twoCharacters = std::make_pair(charOne, charTwo);
        return twoCharacters; 
    }

    pairOfTwoCharacters create_start_position()
    {
        pairOfTwoCharacters placeForShip = create_hit();
        return placeForShip;    
    }

    battleShipPosition put_player_one_ship_on_board() 
    {
        pairOfTwoCharacters position = std::make_pair('4', 'D');
        pairOfTwoCharacters position2 = std::make_pair('4', 'E');
        pairOfTwoCharacters position3 = std::make_pair('4', 'F');
        pairOfTwoCharacters position4 = std::make_pair('4', 'G');
        std::srand(std::time(nullptr));
        // std::uint8_t integerOne = std::rand() / ((RAND_MAX + 1u) / 2);  // 1 -horizontal, 2 -vertical
        battleShipPosition shipPosition = std::make_tuple(position, position2, position3, position4);
        return shipPosition; 
    }
    battleShipPosition put_player_two_ship_on_board() 
    {
        pairOfTwoCharacters position = std::make_pair('8', 'D');
        pairOfTwoCharacters position2 = std::make_pair('8', 'E');
        pairOfTwoCharacters position3 = std::make_pair('8', 'F');
        pairOfTwoCharacters position4 = std::make_pair('8', 'G');
        std::srand(std::time(nullptr));
        // std::uint8_t integerOne = std::rand() / ((RAND_MAX + 1u) / 2);  // 1 -horizontal, 2 -vertical
        battleShipPosition shipPosition = std::tuple(position, position2, position3, position4);
        return shipPosition;    
    }

    battleShipPosition create_armada_one()
    {
        battleShipPosition battleShip = put_player_one_ship_on_board();
        return battleShip;

    }

    battleShipPosition create_armada_two()
    {
        battleShipPosition battleShip = put_player_two_ship_on_board();
        return battleShip;
    }

    pairOfShots create_shots_boards()
    {
        pairOfTwoCharacters create_hit();    
    }




};

#endif