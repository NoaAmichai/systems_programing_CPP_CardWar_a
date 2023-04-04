#include "card.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;
using namespace ariel;

static set<string> VALID_SHAPES{"Hearts", "Diamonds", "Clubs", "Spades"};
static set<int> VALID_NUMBERS{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

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

RoundResult Card::winRound(const Card &other) {
    if (this->getNumber() == other.getNumber()) {
        return RoundResult::Tie;
    } else if (this->getNumber() == 1 && other.getNumber() != 2) {
        return RoundResult::Win;
    } else if (this->getNumber() > other.getNumber()) {
        return RoundResult::Win;
    } else {
        return RoundResult::Loss;
    }
}

string Card::toString() {
    if (this->getNumber() == 1) return "Ace of " + this->getShape();
    if (this->getNumber() == 11) return "Jack of " + this->getShape();
    if (this->getNumber() == 12) return "Queen of " + this->getShape();
    if (this->getNumber() == 13) return "King of " + this->getShape();
    else return to_string(this->getNumber()) + " of " + this->getShape();
}

Card::Card() = default;



