#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
    int number;
    std::string shape;

public:
    Card(int card_number, std::string card_shape) : number(card_number), shape(card_shape) {}

    std::string getShape() { return shape; }

};


#endif