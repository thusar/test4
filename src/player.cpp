#include <array>

#include "../include/board.h"
#include "../include/socket.h"

using hits = std::array<std::array<char, 10>, 10>;

class Player
{
private:
    hits _playerHits;    
public:
    int connect_judge(SocketPlayer& socketPlayer, SocketJudge& socketJudge)
    {
        int connectResult = socketPlayer.connect(socketJudge);
        return connectResult;
    }
    void write_to_judge_socket(SocketPlayer& socketPlayer, SocketJudge& socketJudge, pairOfTwoCharacters& twoCharacters)
    {
        socketPlayer.write(socketJudge, twoCharacters);
    }

    pairOfTwoCharacters read_from_judge_socket(SocketPlayer& socketPlayer, SocketJudge& socketJudge)
    {
        pairOfTwoCharacters twoChars = socketPlayer.read(socketJudge);
        return twoChars;
    }

};

int main(int argc, char* argv[])
{
    constexpr uint16_t port{8080};
    std::string ipaddr{"127.0.0.1"};
    Player player;
    SocketPlayer socketPlayer;
    SocketJudge socketJudge;
    int connectResult = player.connect_judge(socketPlayer, socketJudge);
    pairOfTwoCharacters readResult = player.read_from_judge_socket(socketPlayer, socketJudge);
    player.write_to_judge_socket(socketPlayer, socketJudge, readResult);
    

    return 0;
}