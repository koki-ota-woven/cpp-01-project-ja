//
// Created by koki-ota on 23/12/27.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "Player.h"

const int row = 52;
const int column = 72;
const int reload_time = 1000;
const char car_icon = 'O';

std::atomic_bool inputReady(false);
std::string input;

void getInput() {
    std::string command;
    std::cin >> command;

    if (command != "") {
        input = command;
        inputReady = true;
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
				array2[i][j] = 'X';
			} else if (i == 51) {
				array2[i][j] = 'X';
			} else if (i > 0 && j == 0) {
				array2[i][j] = 'X';
			} else if (j == column-1) {
				array2[i][j] = 'X';
			} else {
				array2[i][j] = ' ';
			}
		}
	}
}

int main() {
    Player player;
    char track[row][column];
    int car_position_x = 5;
    int car_position_y = 1;
    int velocity = 1;
    std::string direction = "+y";
    std::string command;

    std::cout << "Enter a command: ";
    std::getline(std::cin, command);
    std::cout << std::endl;

    while (command != "q") {
        initRace(track);
        track[car_position_y][car_position_x] = car_icon;
        printRace(track);
        std::this_thread::sleep_for(std::chrono::milliseconds(x));
        if (direction == "+y") {
            car_position_y += velocity;
        } else if (direction == "-y") {
            car_position_y -= velocity;
        } else if (direction == "+x") {
            car_position_x += velocity;
        } else if (direction == "-x") {
            car_position_x -= velocity;
        }

        if (command == "h") {
            direction = player.goLeft();
        } else if (command == "l") {
            direction = player.goRight();
        } else if (command == "k") {
            direction = player.goUp();
        } else if (command == "j") {
            direction = player.goDown();
        } else if (command == "a") {
            player.accelerate(&velocity);
        } else if (command == "d") {
            player.decelerate(&velocity);
        } else if (command == "s") {
            player.stop(&velocity);
        } else if (command == "r") {
            player.refuel();
        } else if (command == "help") {
            player.showInfo();
        } else {
            std::cout << "!!!!Invalid command!!!!" << std::endl;
        }

        std::cout << "Enter a command: ";
        std::getline(std::cin, command);
        std::cout << std::endl;
    }

    return 0;
}
