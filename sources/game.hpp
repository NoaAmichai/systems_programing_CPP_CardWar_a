#pragma once

#include "player.hpp"

namespace ariel {
    class Game {

    private:
        Player &player1;
        Player &player2;
        std::string winner;
        std::vector<Card> deck;
        std::vector<std::string> turnsLog;
        std::vector<int> wins; // count wins for each player
        int countRounds;
        int countDraws;
        bool gameOver;

    public:
        Game(Player &firstPlayer, Player &secondPlayer);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner() const;

        void printLog() const;

        void printStats();

        void resetTables();

        bool gameIsOver();
    };
}