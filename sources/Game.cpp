#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;
using namespace ariel;

static set <string> VALID_SHAPES{"Hearts", "Diamonds", "Clubs", "Spades"};
static set<int> VALID_NUMBERS{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Game::Game(Player &p1, Player &p2) : player1(p1), player2(p2), deck{} {

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

void Game::playTurn() {}

void Game::printLastTurn() {}

void Game::playAll() {}

void Game::printWiner() {}

void Game::printLog() {}

void Game::printStats() {}

int main() {
    Player a("Alice");
    Player b("Bob");
    Game game(a, b);

    game.playTurn();
}


