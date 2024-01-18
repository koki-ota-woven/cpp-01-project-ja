//
// Created by koki-ota on 23/12/27.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    private:
        std::string car;
        int speed;
        int fuel;
        int passenger;
        int balance;
        int max_speed;
        int fuel_efficiency;
        int acceleration;

    public:
        Player(char car_type);
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
        int getBalance();
        void consumeFuel();
        void passengerRide();
        void pay(int cost);
        void showInfo();
};

#endif // PLAYER_H
