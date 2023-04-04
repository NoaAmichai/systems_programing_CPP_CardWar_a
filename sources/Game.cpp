#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;
using namespace ariel;

static set<string> VALID_SHAPES{"Hearts", "Diamonds", "Clubs", "Spades"};
static set<int> VALID_NUMBERS{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Game::Game(Player &p1, Player &p2) : player1(p1), player2(p2), deck{}{
    for (const string &shape: VALID_SHAPES) {
        for (int number: VALID_NUMBERS) {
            deck.emplace_back(number, shape);
        }
    }

// Shuffle the deck
    random_device rd;
    shuffle(deck.begin(), deck.end(), rd);

// Deal the cards alternately to the two players
    for (int i = 0; i < 52; i++) {
        if (i % 2 == 0) {
            p1.addCardToStack(deck[i]);
        } else {
            p2.addCardToStack(deck[i]);
        }
    }
    deck.clear(); // clear the deck after dealing the cards
}

void Game::playTurn() {
    Card p1_card, p2_card;
    do {
        p1_card = player1.getCardOnTable();
        p2_card = player2.getCardOnTable();
        if (p1_card.winRound(p2_card) == RoundResult::Win) {
            player1.cardsTaken++;
            cleanTables();
            return;
        } else if (p1_card.winRound(p2_card) == RoundResult::Loss) {
            player2.cardsTaken++;
            cleanTables();
            return;
        }
    } while (p1_card.winRound(p2_card) == RoundResult::Tie);
}

void Game::printLastTurn() {}

void Game::playAll() {}

void Game::printWiner() {}

void Game::printLog() {}

void Game::printStats() {}

void Game::cleanTables() {
    player1.removeAllCardsFromTable();
    player2.removeAllCardsFromTable();
}

int main() {
    Player a("Alice");
    Player b("Bob");
    Game game(a, b);

    game.playTurn();
}


