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

std::string Player::goLeft() {
    return "-x";
}

std::string Player::goRight() {
    return "+x";
}

std::string Player::goUp() {
    return "-y";
}

std::string Player::goDown() {
    return "+y";
}

void Player::accelerate(int* car_velocity) {
    if (*car_velocity <= 3) {
        *car_velocity += 1;
    }
}

void Player::decelerate(int* car_velocity) {
    if (*car_velocity > 0) {
        *car_velocity -= 1;
    }
}

void Player::stop(int* car_velocity) {
    *car_velocity = 0;
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
