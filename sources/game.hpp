#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "player.hpp"


namespace ariel {
    class Game {

    private:
        Player player1;
        Player player2;
        std::vector<Card> deck;
        std::string winner;
        std::vector<std::string> turnsLog;

    public:
        Game(Player &p1, Player &p2);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        void cleanTables();
    };
}

#endif
