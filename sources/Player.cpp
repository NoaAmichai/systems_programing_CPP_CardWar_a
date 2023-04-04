#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Player::Player(const std::string &playerName) : name(playerName), cardsTaken(0), stack{} {
    if(playerName.empty()) { //also need to check the playerName isn't null
        throw std::invalid_argument("Invalid player name");
    }
}

int Player::stacksize() { return stack.size(); }

int Player::cardesTaken() { return cardsTaken; }

string Player::getName() { return this->name; }

void Player::addCardToStack(Card card) {
    stack.emplace_back(card);
}






