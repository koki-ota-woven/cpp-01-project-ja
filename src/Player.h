//
// Created by koki-ota on 23/12/27.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    private:
        int speed;
        int fuel;
        std::string location;
    
    public:
        Player();
        std::string goLeft();
        std::string goRight();
        std::string goUp();
        std::string goDown();
        void accelerate(int* velocity);
        void decelerate(int* velocity);
        void stop(int* velocity);
        void refuel();
        void showInfo();
};

#endif // PLAYER_H
