#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

namespace ariel {

    class Player {
        std::string name;

    public:
        Player(const std::string &playerName):name(playerName){}

        int stacksize(){ return 0;}

        int cardesTaken(){return 0;}
    };
}
#endif