#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "card.hpp"

namespace ariel {

    class Player {
        std::string name;
        std::vector<Card> stack;
        std::vector<Card> cardsOnTable;
        int numCardsWon;

    public:
        Player(const std::string &playerName);

        int stacksize() const;

        int cardesTaken() const;

        std::string getName() const;

        void addCardToStack(const Card &card);

        Card getCardOnTable();

        int cardsOnTableCount() const;

        void removeAllCardsFromTable();

        void clearPreviousGames();

        void addNumCardsWon(int, int);
    };
}
#endif