#include "card.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;
using namespace ariel;

static set<string> VALID_SHAPES {"Hearts", "Diamonds", "Clubs", "Spades"};
static set<int> VALID_NUMBERS {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Card::Card(const int card_number, const string &card_shape) : number(card_number), shape(card_shape) {
    if (VALID_SHAPES.count(card_shape) == 0 || VALID_NUMBERS.count(card_number) == 0) {
        throw invalid_argument("Invalid card number or shape");
    }
}

int Card::getNumber() const {
    return this->number;
}

string Card::getShape() {
    return this->shape;
}


