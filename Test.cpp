#include "sources/game.hpp"
#include "sources/player.hpp"
#include "doctest.h"
#include <iostream>
#include <stdexcept>

using namespace ariel;
using namespace std;

TEST_CASE("Start Game: Each Player Should Have 26 Cards and 0 Cards Taken") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    CHECK((p1.stacksize() == 26));
    CHECK((p2.stacksize() == 26));
    CHECK((p1.cardesTaken() == 0));
    CHECK((p2.cardesTaken() == 0));
}

TEST_CASE("All Cards are Played and One Player Wins after PlayAll") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    game.playAll();

    //Both players should have 0 cards left in their stack
    CHECK((p1.stacksize() == 0));
    CHECK((p2.stacksize() == 0));

    //Only one player should have taken cards
    bool p1CardsTaken = (p1.cardesTaken() > 0);
    bool p2CardsTaken = (p2.cardesTaken() > 0);
    CHECK((p1CardsTaken != p2CardsTaken));

    //The winning player should have more than 0 cards taken
    if (p1CardsTaken) {
        CHECK((p1.cardesTaken() > 0));
        CHECK((p2.cardesTaken() == 0));
    } else {
        CHECK((p2.cardesTaken() > 0));
        CHECK((p1.cardesTaken() == 0));
    }
}

TEST_CASE("PlayTurn: Player has fewer cards after playing a turn") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    game.playTurn();

    CHECK((p1.stacksize() < 26 && p2.stacksize() < 26));
    CHECK((p1.stacksize() == p2.stacksize()));
}

TEST_CASE("Playing Against the Same Player Throws an Exception") {
    Player p1("Alice");

    CHECK_THROWS(Game(p1, p1));
}

TEST_CASE("Creating a Player with Null or Empty Name Should Throw an Exception") {
    CHECK_THROWS_AS(Player(nullptr), invalid_argument);
    CHECK_THROWS_AS(Player(""), invalid_argument);
}

TEST_CASE("Check Stack Before and After Register") {
    Player p1("Alice");
    Player p2("Bob");

    // check that both players stack is empty
    CHECK((p1.stacksize() == 0));
    CHECK((p2.stacksize() == 0));

    Game game(p1, p1);
    // check that both players stack isn't empty
    CHECK((p1.stacksize() != 0));
    CHECK((p2.stacksize() != 0));
}

TEST_CASE("Players Take Valid Amount of Cards after a Turn") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    game.playTurn();
    // check that valid amount of cards taken by each player
    CHECK((p1.cardesTaken() >= 0 && p1.cardesTaken() <= 26));
    CHECK((p2.cardesTaken() >= 0 && p2.cardesTaken() <= 26));
}

TEST_CASE("Total Number of Cards in the Game Should be 52") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    for (int i = 0; i <= 5; i++) {
        game.playTurn();
    }
    int totalCards = p1.stacksize() + p1.cardesTaken() + p2.cardesTaken() + p2.stacksize();
    CHECK((totalCards == 52));
}

TEST_CASE("Game functions throws exceptions") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    CHECK_NOTHROW(game.playTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.playAll());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLastTurn());
}

TEST_CASE("Play Turn After Play All Test") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);

    CHECK_NOTHROW(game.playAll());
    // checks that an exception is thrown if the players tries to play a turn after the game has ended
    CHECK_THROWS(game.playTurn());
}