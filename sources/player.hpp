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
        int cardsTaken;

    public:
        Player(const std::string &playerName);

        int stacksize();

        int cardesTaken();

        std::string getName();

        void addCardToStack(Card &card);
    };
}
#endif