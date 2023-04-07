#include "card.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;
using namespace ariel;

static const set<string> CARDS_SHAPES{"Hearts", "Diamonds", "Clubs", "Spades"};
static const set<int> CARDS_NUMBERS{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Card::Card(const int card_number, const string &card_shape) : number(card_number), shape(card_shape) {
    // Verify that the card number and shape are valid.
    if (CARDS_SHAPES.count(card_shape) == 0 || CARDS_NUMBERS.count(card_number) == 0) {
        throw invalid_argument("Invalid card number or shape");
    }
}

RoundResult Card::winRound(const Card &other) const {
    // Compare the card numbers and return the result of the round
    if (this->number == other.number) {
        return RoundResult::Tie;
    } else if (this->number == 1) {
        return other.number == 2 ? RoundResult::Loss : RoundResult::Win;
    } else if (this->number == 2) {
        return other.number == 1 ? RoundResult::Win : RoundResult::Loss;
    } else if (this->number > other.number && other.number != 1) {
        return RoundResult::Win;
    } else {
        return RoundResult::Loss;
    }
}

string Card::toString() const {
    if (number == 1) return "Ace of " + shape;
    if (number == 11) return "Jack of " + shape;
    if (number == 12) return "Queen of " + shape;
    if (number == 13) return "King of " + shape;
    if (CARDS_NUMBERS.count(number) == 0) {
        throw invalid_argument("Invalid card number");
    }
    return to_string(number) + " of " + shape;
}

