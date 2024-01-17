//
// Created by koki-ota on 23/12/27.
//

#include "Player.h"
#include <iostream>

Player::Player() {
    speed = 1;
    fuel = 100;
    passenger = 0;
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

void Player::accelerate() {
    if (speed <= 3){
        speed += 1;
    }
}

void Player::decelerate() {
    if (speed > 0) {
        speed -= 1;
    }
}

void Player::stop() {
    speed = 0;
}

void Player::refuel() {
    fuel = 100;
    std::cout << "Refueling. Fuel level: " << fuel << std::endl;
}

int Player::getSpeed() {
    return speed;
}

int Player::getFuel() {
    return fuel;
}

int Player::getPassenger() {
    return passenger;
}

void Player::consumeFuel() {
    fuel -= speed;
}

void Player::passengerRide() {
    passenger++;
}

void Player::showInfo() {
    std::cout << "Current speed: " << speed << "   Fuel level: " << fuel << std::endl;
}
