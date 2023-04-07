#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "player.hpp"


namespace ariel {
    class Game {

    private:
        Player &player1;
        Player &player2;
        std::string winner;
        std::vector<Card> deck;
        std::vector<std::string> turnsLog;
        std::vector<int> wins; // counter for each player
        int countRounds;
        int countDraws;

    public:
        Game(Player &firstPlayer, Player &secondPlayer);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        void cleanTables();

        bool gameIsOver();
    };
}

#endif
