#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

namespace ariel {
    enum class RoundResult {
        Win,
        Loss,
        Tie
    };

    class Card {
        int number;  //{"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        std::string shape; //{"Hearts", "Diamonds", "Clubs", "Spades"}

    public:
        Card();

        Card(int card_number, const std::string &card_shape);

        std::string getShape() const;

        int getNumber() const;

        RoundResult winRound(const Card &other) const;

        std::string toString() const;

    };
}

#endif