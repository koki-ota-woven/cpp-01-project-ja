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
    void turnLeft();
    void turnRight();
    void accelerate();
    void decelerate();
    void stop();
    void refuel();
    void showInfo();
};

#endif // PLAYER_H
