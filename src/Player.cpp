#include "Player.h"
#include <iostream>

Player::Player(char car_type) {
    speed = 1;
    if (car_type == 'T') {
        fuel = 150;
        max_speed = 4;
    } else if (car_type == 'H'){
        fuel = 100;
        max_speed = 5;
    }
    passenger = 0;
    balance = 100;
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
    if (speed < max_speed){
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
    std::cout << "Refueled" << std::endl;
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

void Player::pay(int cost) {
    balance -= cost;
}

int Player::getBalance() {
    return balance;
}

void Player::passengerRide() {
    passenger += 1;
    std::cout << "A passenger rides" << std::endl;
}

void Player::showInfo() {
    std::cout << "Current speed: " << speed
        << ",   Fuel level: " << fuel
        << ",   Passenger: " << passenger
        << ",   Balance: " << balance << std::endl;
}
