#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "Player.h"

const int row = 50;
const int column = 100;
const int reload_time = 1000;
const char player_icon = 'O';
const char fuel_station_icon = 'F';
const char passenger_icon = 'P';
const char goal_icon = 'G';

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

void initRace(char track[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0) {
                track[i][j] = '-';
            } else if (i == row-1) {
                track[i][j] = '-';
            } else if (j == 0) {
                track[i][j] = '|';
            } else if (i == 18 && j > 20 && j < 60) {
                track[i][j] = '-';
            } else if (i == 22 && j > 20 && j < 60) {
                track[i][j] = '-';
            } else if (i == 20 && j > 25 && j < 40) {
                track[i][j] = '=';
            } else if (i == 20 && j == 40) {
                track[i][j] = '>';
            } else if (j == column-1) {
                track[i][j] = '|';
            } else {
                track[i][j] = ' ';
            }
        }
    }
}

bool detectPosition(int player_position_x, int player_position_y, char track[row][column]){
    if (track[player_position_y][player_position_x] == '-') {
        return false;
    } else if (track[player_position_y][player_position_x] == '|'){
        return false;
    }
    return true;
}

int main() {
    std::thread inputThread(getInput);  // Start a thread for user input
    Player player;

    int player_position_x = 5;
    int player_position_y = 1;
    int fuel_position_x = 30;
    int fuel_position_y = 30;
    int passenger_position_x = 50;
    int passenger_position_y = 20;
    int goal_position_x = 95;
    int goal_position_y = 46;
    std::string direction = "+y";

    while (true) {  // Continuous game loop
        if (player.getFuel() <= 0) {
            std::cout << "GAME OVER: There is no fuel" << std::endl;
            break;
        }

        char track[row][column];
        initRace(track);

        if (player.getPassenger() == 0) {
            track[passenger_position_y][passenger_position_x] = passenger_icon;
        }
        track[fuel_position_y][fuel_position_x] = fuel_station_icon;
        track[player_position_y][player_position_x] = player_icon;
        track[goal_position_y][goal_position_x] = goal_icon;

        std::cout << "Mission: Take a passenger to goal" << std::endl;
        std::cout << "ICON  O: player, P: passenger, F: gas station, G: Goal" << std::endl;
        printRace(track);
        player.showInfo();
        std::cout << std::endl << std::endl;

        player.consumeFuel();
        std::this_thread::sleep_for(std::chrono::milliseconds(reload_time));

        if ((player_position_x == fuel_position_x) && (player_position_y == fuel_position_y)) {
            player.refuel();
        }

        if ((player_position_x == passenger_position_x) && (player_position_y == passenger_position_y)) {
            player.passengerRide();
        }

        if ((player.getPassenger() == 1) &&
            (player_position_x == goal_position_x) && (player_position_y == goal_position_y)) {
            std::cout << "Clear: Well Done!!" << std::endl;
            break;
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
                player.accelerate();
            } else if (input == "d") {
                player.decelerate();
            } else if (input == "s") {
                player.stop();
            } else if (input == "r") {
                player.refuel();
            } else if (input == "q") {
                break;  // Exit the game loop when the user enters "q"
            } else {
                std::cout << "!!!!Invalid command!!!!" << std::endl;
            }
            inputReady = false;  // Reset the flag
        }

        if (direction == "+y") {
            if (not detectPosition(player_position_x, player_position_y + 1, track)) {
                player.stop();
                continue;
            }
            player_position_y += player.getSpeed();
        } else if (direction == "-y") {
            if (not detectPosition(player_position_x, player_position_y - 1, track)) {
                player.stop();
                continue;
            }
            player_position_y -= player.getSpeed();
        } else if (direction == "+x") {
            if (not detectPosition(player_position_x + 1, player_position_y, track)) {
                player.stop();
                continue;
            }
            player_position_x += player.getSpeed();
        } else if (direction == "-x") {
            if (not detectPosition(player_position_x - 1, player_position_y, track)) {
                player.stop();
                continue;
            }
            player_position_x -= player.getSpeed();
        }
    }

    inputThread.join();  // Wait for the input thread to finish
    return 0;
}
