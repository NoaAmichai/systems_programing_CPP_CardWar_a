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

Game::Game(Player &p1, Player &p2) : player1(p1), player2(p2), deck({}), winner(""), turnsLog({}) {
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
    string turn;
    do {
        p1_card = player1.getCardOnTable();
        p2_card = player2.getCardOnTable();
        turn = player1.getName() + " played " + p1_card.toString() + " " + player2.getName() + " played " +
               p2_card.toString() + ". ";
        if (p1_card.winRound(p2_card) == RoundResult::Win) {
            player1.cardsTaken++;
            cleanTables();
            turn += player1.getName() + " wins.";
            return;
        } else if (p1_card.winRound(p2_card) == RoundResult::Loss) {
            player2.cardsTaken++;
            cleanTables();
            turn += player2.getName() + " wins.";
            return;
        }
    } while (p1_card.winRound(p2_card) == RoundResult::Tie);
    turnsLog.push_back(turn);
}

void Game::printLastTurn() {
    if (turnsLog.empty()) {
        throw runtime_error("No turns played yet.");
    } else {
        cout << turnsLog.back() << endl;
    }
}

void Game::playAll() {
    while (player1.stacksize() != 0 && player2.stacksize() != 0) {
        playTurn();
    }
    //check how is the winner
    if (player1.cardesTaken() > player2.cardesTaken()) winner = player1.getName();
    else if (player1.cardesTaken() < player2.cardesTaken()) winner = player2.getName();
    else winner = "Tie"; //TODO change
}

void Game::printWiner() {
    if (winner.empty()) {
        throw runtime_error("No winner yet!");
    } else {
        cout << "The winner is: " << winner << endl;
    }
}

void Game::printLog() {
    if (turnsLog.empty())
        throw runtime_error("No turns played yet.");
    for (const string &turn: turnsLog) {
        cout << turn << endl;
    }
}


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


