#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "player.hpp"

using namespace ariel;

class Game {

private:
    Player player1;
    Player player2;

public:
    Game(const Player &p1, const Player &p2) : player1(p1), player2(p2) {}

    void playTurn() {}

    void printLastTurn() {}

    void playAll() {}

    void printWiner() {}

    void printLog() {}

    void printStats() {}
};

#endif
