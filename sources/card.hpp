#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

namespace ariel {
    class Card {
        int number;  //{"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        std::string shape; //{"Hearts", "Diamonds", "Clubs", "Spades"}

    public:
        Card(int card_number, const std::string& card_shape);

        std::string getShape();

        int getNumber() const;

    };
}

#endif