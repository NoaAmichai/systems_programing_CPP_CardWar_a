#pragma once

#include <vector>
#include "card.hpp"

namespace ariel {

    class Player {
        std::string name;
        std::vector<Card> stack;
        std::vector<Card> cardsOnTable;
        int numCardsWon;
        bool currentlyPlaying;

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

        void setCurrentlyPlaying(bool currentlyPlaying);

        bool isCurrentlyPlaying() const;

        void clearStack();
    };
}
