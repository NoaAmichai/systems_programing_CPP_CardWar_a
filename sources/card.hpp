#pragma once

#include <iostream>

namespace ariel {

    enum class RoundResult {
        Win,
        Loss,
        Tie
    };

    // A Card represents a playing card in a standard deck of 52 cards.
    // It has a number and a shape.
    class Card {

        int number;  // The number of the card, from 1 (Ace) to 13 (King)
        std::string shape; // Hearts, Diamonds, Clubs, Spades

    public:

        Card(int card_number, const std::string &card_shape);

        RoundResult winRound(const Card &other) const;

        std::string toString() const;

    };
}