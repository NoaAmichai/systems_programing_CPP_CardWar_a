#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;
using namespace ariel;

#define TOTAL_CARDS 52
static const set<string> &CARD_SHAPES = {"Hearts", "Diamonds", "Clubs", "Spades"};
static const set<int> &CARD_NUMBERS = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

Game::Game(Player &firstPlayer, Player &secondPlayer) : player1(firstPlayer), player2(secondPlayer), deck({}), winner(),
                                                        turnsLog({}), countRounds(0), countDraws(0), wins(2, 0),
                                                        gameOver(false) {
    // Check if either player is already playing another game
    if (player1.isCurrentlyPlaying() || player2.isCurrentlyPlaying())
        throw runtime_error("One of the players (or both) are currently playing in other game");

    // Clear the previous games of both players and set them as currently playing
    player1.clearPreviousGames();
    player2.clearPreviousGames();

    player1.setCurrentlyPlaying(true);
    player2.setCurrentlyPlaying(true);

    // Create the deck
    for (const string &shape: CARD_SHAPES) {
        for (const int number: CARD_NUMBERS) {
            deck.emplace_back(number, shape);
        }
    }

    // Shuffle the deck
    random_device rd;
    shuffle(deck.begin(), deck.end(), rd);

    // Deal the cards to the players
    for (size_t i = 0; i < 26; i++) {
        player1.addCardToStack(deck[i * 2]);
        player2.addCardToStack(deck[i * 2 + 1]);
    }

    // Clear the deck after dealing the cards
    deck.clear();
}

void Game::playTurn() {
    // Check if the game is valid to play a turn

    if (&player1 == &player2) throw invalid_argument("Same player");
    if (player1.getName() == player2.getName()) throw invalid_argument("Players must have different names.");
    if (player1.stacksize() == 0 && player2.stacksize() == 0) throw runtime_error("The game is already over.");
    if (gameIsOver()) {
        cout << "The winner is: " << winner << endl;
        return;
    }

    Card p1_card = player1.getCardOnTable();
    Card p2_card = player2.getCardOnTable();

    // Create a log entry for the turn
    string turn = player1.getName() + " played " + p1_card.toString() + " " + player2.getName() + " played " +
                  p2_card.toString() + ". ";

    // Check the result of the round (win, loss, or tie)
    while (true) {
        RoundResult result = p1_card.winRound(p2_card);
        if (result == RoundResult::Win) {
            // Player 1 wins the round
            player1.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
            resetTables();
            turn += player1.getName() + " wins.";
            wins[0]++;
            break;
        } else if (result == RoundResult::Loss) {
            // Player 2 wins the round
            player2.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
            resetTables();
            turn += player2.getName() + " wins.";
            wins[1]++;
            break;
        } else { //Tie
            turn += "Draw. ";
            countDraws++;
            if (player1.stacksize() < 2) { //the game ended in the middle of a tie
                gameOver = true;
                player1.addNumCardsWon(player1.cardsOnTableCount(), 0);
                player2.addNumCardsWon(player2.cardsOnTableCount(), 0);
                player1.clearStack();
                player2.clearStack();
                break;
            }

            // Draw another card from each player's stack
            player1.getCardOnTable();
            player2.getCardOnTable();

            p1_card = player1.getCardOnTable();
            p2_card = player2.getCardOnTable();
            turn += player1.getName() + " played " + p1_card.toString() + " " + player2.getName() + " played " +
                    p2_card.toString() + ". ";
            result = p1_card.winRound(p2_card);
            if (result != RoundResult::Tie) { // A winner is found
                if (result == RoundResult::Win) {
                    // Player 1 wins the round
                    player1.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
                    resetTables();
                    wins[0]++;
                    turn += player1.getName() + " wins.";
                } else { // result == RoundResult::Loss
                    // Player 2 wins the round
                    player2.addNumCardsWon(player1.cardsOnTableCount(), player2.cardsOnTableCount());
                    resetTables();
                    wins[1]++;
                    turn += player2.getName() + " wins.";

                }
                break;
            } else {
                p1_card = player1.getCardOnTable();
                p2_card = player2.getCardOnTable();
            }
        }
    }
    // Add the turn to the turns log and increment the number of rounds played
    turnsLog.emplace_back(turn);
    countRounds++;
}

void Game::printLastTurn() {
    if (turnsLog.empty()) {
        throw runtime_error("No turns played yet.");
    } else {
        cout << turnsLog.back() << endl;
    }
}

void Game::playAll() {
    if (!winner.empty()) {
        throw runtime_error("The game has already finished.");
    }
    while (!gameIsOver()) {
        playTurn();
    }
}

void Game::printWiner() const {
    if (winner.empty()) {
        cout << "The game is still ongoing." << endl;
    } else if (winner == "The game ended in a tie.") {
        cout << "The game ended in a tie." << endl;
    } else {
        cout << "The winner is: " << winner << "." << endl;
    }
}

void Game::printLog() const {
    if (turnsLog.empty()) {
        throw runtime_error("No turns played yet.");
    }

    for (const string &turn: turnsLog) {
        cout << turn << endl;
    }
}

void Game::printStats() {
    if (countRounds == 0) {
        cout << "No turns played yet." << endl;
        return;
    }

    // print game statistics
    cout << "Number of rounds played: " << countRounds << endl;
    cout << "Number of draws: " << countDraws << endl;
    cout << "Number of cards in " << player1.getName() << "'s stack: " << player1.stacksize() << endl;
    cout << "Number of cards in " << player2.getName() << "'s stack: " << player2.stacksize() << endl;
    cout << "Number of cards taken by " << player1.getName() << ": " << player1.cardesTaken() << endl;
    cout << "Number of cards taken by " << player2.getName() << ": " << player2.cardesTaken() << endl;

    // print win rates
    double player1WinRate = (double) wins[0] / (double) countRounds;
    double player2WinRate = (double) wins[1] / (double) countRounds;
    cout << "Win rate for " << player1.getName() << ": " << player1WinRate * 100 << "%" << endl;
    cout << "Win rate for " << player2.getName() << ": " << player2WinRate * 100 << "%" << endl;

    printWiner();
}

void Game::resetTables() {
    player1.removeAllCardsFromTable();
    player2.removeAllCardsFromTable();
}

bool Game::gameIsOver() {
    if (player1.cardesTaken() + player2.cardesTaken() == TOTAL_CARDS || gameOver) {
        winner = (player1.cardesTaken() > player2.cardesTaken()) ? player1.getName() :
                 (player2.cardesTaken() > player1.cardesTaken()) ? player2.getName() :
                 "The game ended in a tie.";
        player1.setCurrentlyPlaying(false);
        player2.setCurrentlyPlaying(false);
        return true;
    }
    return false;
}