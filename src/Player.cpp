#include "Player.h"
#include <iostream>

// ガソリンカーかハイブリッドカーを作るコンストラクタ
Player::Player(char car_type) {
    speed = 1;
    fuel = 100;
    max_speed = 6;
    passenger = 0;
    balance = 100;
    if (car_type == 'G') {
        car = "Gasoline";
        fuel_efficiency = 2;
        acceleration = 2;
    } else if (car_type == 'H'){
        car = "Hybrid";
        fuel_efficiency = 1;
        acceleration = 1;
    }
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
        speed += acceleration;
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
    fuel -= speed * fuel_efficiency;
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
    std::cout <<"Car type: " << car
        << ",   Current speed: " << speed
        << ",   Fuel level: " << fuel
        << ",   Passenger: " << passenger
        << ",   Balance: $" << balance << std::endl;
}
