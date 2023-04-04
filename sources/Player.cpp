#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Player::Player(const std::string &playerName) : name(playerName), cardsTaken(0), stack{}, cardsOnTable{} {
    if (playerName.empty()) { //also need to check the playerName isn't null
        throw std::invalid_argument("Invalid player name");
    }
}

int Player::stacksize() { return stack.size(); }

int Player::cardesTaken() { return cardsTaken; }

string Player::getName() { return this->name; }

void Player::addCardToStack(Card card) {
    stack.emplace_back(card);
}

Card Player::getCardOnTable() {
    if (stack.empty()) {
        throw out_of_range("Player's stack is empty");
    }
    Card topCard = stack.back();
    this->cardsOnTable.emplace_back(topCard);
    stack.pop_back();
    return topCard;
}

void Player::removeAllCardsFromTable() {
    this->cardsOnTable.clear();
}






