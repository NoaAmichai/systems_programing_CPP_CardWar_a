#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;
using namespace ariel;

static const set<string> CARD_SHAPES{"Hearts", "Diamonds", "Clubs", "Spades"};
static const set<int> CARD_NUMBERS{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Game::Game(Player &firstPlayer, Player &secondPlayer) : player1(firstPlayer), player2(secondPlayer), deck({}), winner(),
                                                        turnsLog({}) {
    firstPlayer.clearPreviousGames();
    secondPlayer.clearPreviousGames();
    for (const string &shape: CARD_SHAPES) {
        for (const int number: CARD_NUMBERS) {
            deck.emplace_back(number, shape);
        }
    }

// Shuffle the deck
    random_device rd;
    shuffle(deck.begin(), deck.end(), rd);

// Deal the cards alternately to the two players
    for (size_t i = 0; i < 52; i++) {
        if (i % 2 == 0) {
            firstPlayer.addCardToStack(deck[i]);
        } else {
            secondPlayer.addCardToStack(deck[i]);
        }
    }
    deck.clear(); // clear the deck after dealing the cards
}

void Game::playTurn() { //TODO problem with the player's stacks
    if (&player1 == &player2) throw invalid_argument("Same player");
    if (player1.getName() == player2.getName()) throw invalid_argument("Players must have different names.");

    Card p1_card, p2_card;
    string turn;
    do {
        p1_card = player1.getCardOnTable();
        p2_card = player2.getCardOnTable();
        turn = player1.getName() + " played " + p1_card.toString() + " " + player2.getName() + " played " +
               p2_card.toString() + ". ";
        if (p1_card.winRound(p2_card) == RoundResult::Win) {
            player1.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
            cleanTables();
            turn += player1.getName() + " wins.";
        } else if (p1_card.winRound(p2_card) == RoundResult::Loss) {
            player2.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
            cleanTables();
            turn += player2.getName() + " wins.";
        } else turn += "Draw.";
    } while (p1_card.winRound(p2_card) == RoundResult::Tie);
    turnsLog.emplace_back(turn);
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
    Player p1("Noa");
    Player p2("Boaz");
    Game game(p1, p2);
    for (int i = 0; i <= 5; i++) {
        game.playTurn();
        game.printLastTurn();
    }

}
