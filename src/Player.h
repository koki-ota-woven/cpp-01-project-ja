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
        int passenger;

    public:
        Player();
        std::string goLeft();
        std::string goRight();
        std::string goUp();
        std::string goDown();
        void accelerate();
        void decelerate();
        void stop();
        void refuel();
        int getSpeed();
        int getFuel();
        int getPassenger();
        void consumeFuel();
        void passengerRide();
        void showInfo();
};

#endif // PLAYER_H
