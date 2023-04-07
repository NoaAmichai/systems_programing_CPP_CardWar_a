#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Player::Player(const string &playerName) : name(playerName), numCardsWon(0), stack{}, cardsOnTable{},
                                           currentlyPlaying(false){
    //also need to check the playerName isn't null
    if (playerName.empty()) {
        throw invalid_argument("Invalid player name");
    }
}

void Player::setCurrentlyPlaying(bool playing) {
    currentlyPlaying = playing;
}

int Player::stacksize() const { return stack.size(); }

int Player::cardesTaken() const { return numCardsWon; }

string Player::getName() const { return name; }

void Player::addCardToStack(const Card &card) {
    if (stack.size() > 26) {
        throw out_of_range("Player's stack is full");
    }
    stack.emplace_back(card);
}

Card Player::getCardOnTable() {
    if (stack.empty()) {
        throw out_of_range("Player's stack is empty");
    }
    Card topCard = stack.back();
    cardsOnTable.emplace_back(topCard);
    stack.pop_back();
    return topCard;
}

void Player::removeAllCardsFromTable() {
    cardsOnTable.clear();
}

int Player::cardsOnTableCount() const {
    return cardsOnTable.size();
}

void Player::addNumCardsWon(int player1_cards, int player2_cards) {
    numCardsWon += player1_cards + player2_cards;
}

void Player::clearPreviousGames() {
    stack.clear();
    cardsOnTable.clear();
    numCardsWon = 0;
}

bool Player::isCurrentlyPlaying() const {
    return currentlyPlaying;
}








