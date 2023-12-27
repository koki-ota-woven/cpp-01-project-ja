//
// Created by koki-ota on 23/12/27.
//

#include "Player.h"
#include <iostream>

Player::Player() {
    speed = 0;
    fuel = 100;
    location = "Start";
}

void Player::turnLeft() {
    std::cout << "Turning left" << std::endl;
}

void Player::turnRight() {
    std::cout << "Turning right" << std::endl;
}

void Player::accelerate() {
    speed += 10;
    std::cout << "Accelerating. Current speed: " << speed << std::endl;
}

void Player::decelerate() {
    speed -= 10;
    std::cout << "Decelerating. Current speed: " << speed << std::endl;
}

void Player::stop() {
    speed = 0;
    std::cout << "Stopping" << std::endl;
}

void Player::refuel() {
    fuel = 100;
    std::cout << "Refueling. Fuel level: " << fuel << std::endl;
}

void Player::showInfo() {
    std::cout << "Current speed: " << speed << std::endl;
    std::cout << "Fuel level: " << fuel << std::endl;
    std::cout << "Location: " << location << std::endl;
}