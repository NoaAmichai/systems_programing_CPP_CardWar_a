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

    public:
        int cardsTaken;

        Player(const std::string &playerName);

        int stacksize();

        int cardesTaken();

        std::string getName();

        void addCardToStack(Card card);

        Card getCardOnTable();

        void removeAllCardsFromTable();
    };
}
#endif