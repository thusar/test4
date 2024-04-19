#include "../include/board.h"
#include "../include/socket.h"

using armada = std::array<std::array<char, 10>, 10>;
using pairOfTwoArmadas = std::pair<armada, armada>;
using pairOfTwoCharacters = std::pair<char, char>;

class PlayerProcess
{
private:
    int _pid;
public:
    PlayerProcess(const std::string& command)
    {
        _pid = fork();
        if (_pid == 0) {
            execl(command.c_str(), command.c_str(), nullptr);
        }
    }
};

class Judge
{
private:
    pairOfTwoArmadas _armadas;
public:
    const std::string& create_process(const std::string& command) 
    { 
        PlayerProcess player{command}; 
        return command;
    }
    int bind_judge(SocketJudge& socketJudge)
    {
        int bindResult = socketJudge.bind();
        return bindResult;
    }
    int listen_player(SocketJudge& socketJudge, SocketPlayer& socketPlayer)
    {
        int listenResult = socketJudge.listen(socketPlayer);
        return listenResult;
    }
    int accept_player(SocketJudge& socketJudge, SocketPlayer& socketPlayer)
    {
        int acceptResult = socketJudge.accept(socketPlayer);
        return acceptResult;
    }
    pairOfTwoCharacters read_from_player_socket(SocketJudge& socketJudge, SocketPlayer& socketPlayer)
    {
        pairOfTwoCharacters twoChars = socketJudge.read(socketPlayer);
        return twoChars;
    }
    void write_to_player_socket(SocketJudge& socketJudge, SocketPlayer& socketPlayer, pairOfTwoCharacters& twoCharacters)
    {
        socketJudge.write(socketPlayer, twoCharacters);
    }


};

int main(int argc, char *argv[])
{
    constexpr uint16_t port{8080};
    std::string ipaddr{"127.0.0.1"};
    Judge judge;
    std::string player1 = judge.create_process("player1");
    std::string player2 = judge.create_process("player2");
    SocketJudge socketJudge;
    SocketPlayer socketPlayer;
    int bindResult = judge.bind_judge(socketJudge);
    int listenResult = judge.listen_player(socketJudge, socketPlayer);
    int acceptResult = judge.accept_player(socketJudge, socketPlayer);
    pairOfTwoCharacters readResult = judge.read_from_player_socket(socketJudge, socketPlayer);
    judge.write_to_player_socket(socketJudge, socketPlayer, readResult);
    return 0;
}