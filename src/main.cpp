#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "Player.h"

const int row = 50;
const int column = 100;
const int reload_time = 1000;
const char car_icon = 'O';
const char fuel_station_icon = 'F';
const char passenger_icon = 'P';

std::atomic_bool inputReady(false);
std::string input;

void getInput() {
    while (true) {
        std::string command;
        std::cin >> command;

        if (command != "") {
            input = command;
            inputReady = true;
        }
    }
}

void printRace(char array1[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            std::cout << array1[i][j];
        }
        std::cout << std::endl;
    }
}

void initRace(char array2[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0) {
                array2[i][j] = '-';
            } else if (i == row-1) {
                array2[i][j] = '-';
            } else if (i > 0 && j == 0) {
                array2[i][j] = '|';
            } else if (j == column-1) {
                array2[i][j] = '|';
            } else {
                array2[i][j] = ' ';
            }
        }
    }
}

int main() {
    std::thread inputThread(getInput);  // Start a thread for user input
    Player player;
    char track[row][column];
    int car_position_x = 5;
    int car_position_y = 1;
    int fuel_position_x = 30;
    int fuel_position_y = 30;
    int passenger_position_x = 40;
    int passenger_position_y = 20;
    int velocity = 1;
    std::string direction = "+y";

    while (true) {  // Continuous game loop
        initRace(track);
        track[fuel_position_y][fuel_position_x] = fuel_station_icon;
        track[car_position_y][car_position_x] = car_icon;
        track[passenger_position_y][passenger_position_x] = passenger_icon;
        printRace(track);
        player.showInfo();
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(reload_time));

        // if ((car_position_y == passenger_position_y) && (car_position_x == passenger_position_x)){
        //     Person._fuel += 1;
        // }

        if (direction == "+y") {
            car_position_y += velocity;
        } else if (direction == "-y") {
            car_position_y -= velocity;
        } else if (direction == "+x") {
            car_position_x += velocity;
        } else if (direction == "-x") {
            car_position_x -= velocity;
        }

        if (inputReady) {
            // Handle user input here
            if (input == "h") {
                direction = player.goLeft();
            } else if (input == "l") {
                direction = player.goRight();
            } else if (input == "k") {
                direction = player.goUp();
            } else if (input == "j") {
                direction = player.goDown();
            } else if (input == "a") {
                player.accelerate(&velocity);
            } else if (input == "d") {
                player.decelerate(&velocity);
            } else if (input == "s") {
                player.stop(&velocity);
            } else if (input == "r") {
                player.refuel();
            } else if (input == "q") {
                break;  // Exit the game loop when the user enters "q"
            } else {
                std::cout << "!!!!Invalid command!!!!" << std::endl;
            }

            inputReady = false;  // Reset the flag
        }
    }

    inputThread.join();  // Wait for the input thread to finish
    return 0;
}

