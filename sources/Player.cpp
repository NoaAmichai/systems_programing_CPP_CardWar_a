#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Player::Player(const string &playerName) : name(playerName), numCardsWon(0), stack({}), cardsOnTable({}),
                                           currentlyPlaying(false) {
    if (playerName.empty()) {
        throw invalid_argument("Invalid player name");
    }
}

int Player::stacksize() const {
    return stack.size();
}

string Player::getName() const {
    return name;
}

void Player::addCardToStack(const Card &card) {
    stack.emplace_back(card);
}

// Remove the top card from the player's stack and add it to the table
Card Player::getCardOnTable() {
    Card topCard = stack.back();
    stack.pop_back();
    cardsOnTable.emplace_back(topCard);
    return topCard;
}

void Player::removeAllCardsFromTable() {
    cardsOnTable.clear();
}

int Player::cardsOnTableCount() const {
    return cardsOnTable.size();
}

// Getter for the number of cards won by the player
int Player::cardesTaken() const {
    return numCardsWon;
}

// Add the number of cards won by the player to the total count
void Player::addNumCardsWon(int player1_cards, int player2_cards) {
    numCardsWon += player1_cards + player2_cards;
}

// Clear the player's stack, table, and number of cards won
void Player::clearPreviousGames() {
    stack.clear();
    cardsOnTable.clear();
    numCardsWon = 0;
}

bool Player::isCurrentlyPlaying() const {
    return currentlyPlaying;
}

void Player::setCurrentlyPlaying(bool playing) {
    currentlyPlaying = playing;
}

void Player::clearStack() {
    stack.clear();
}








