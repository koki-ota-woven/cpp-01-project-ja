#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "Player.h"

const int row = 50;
const int column = 100;
const int reload_time = 1000;
const char fuel_station_icon = 'F';
const char passenger_icon = 'P';
const char goal_icon = 'G';
const char player_icon = 'O';
const int gas_price = 20;
const int direction_fine = 50;
const int speed_limit_fine = 10;
const int speed_limit = 4;

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
    if (player_position_x > column || player_position_x < 0){
        return false;
    } else if (player_position_y > row || player_position_y < 0){
        return false;
    } if (track[player_position_y][player_position_x] == '-') {
        return false;
    } else if (track[player_position_y][player_position_x] == '|'){
        return false;
    }
    return true;
}

bool movePlayer(int& player_position_x, int& player_position_y, const std::string& direction, char track[row][column], Player player) {
    int new_player_position_x = player_position_x;
    int new_player_position_y = player_position_y;

    if (direction == "+y") {
        new_player_position_y += player.getSpeed();
    } else if (direction == "-y") {
        new_player_position_y -= player.getSpeed();
    } else if (direction == "+x") {
        new_player_position_x += player.getSpeed();
    } else if (direction == "-x") {
        new_player_position_x -= player.getSpeed();
    }

    if (!detectPosition(new_player_position_x, new_player_position_y, track)) {
        std::cout << "GAME OVER: Bump into a guard rail" << std::endl;
        player.stop();
        return false;
    } else {
        player_position_x = new_player_position_x;
        player_position_y = new_player_position_y;
        return true;
    }
}


int main() {
    char car_type;
    std::cout << "G (Gasoline) or H (Hybrid): ";
    std::cin >> car_type;
    if (car_type != 'G' && car_type != 'H'){
        std::cout << "Please select T(Toyota) or H(Honda)" << std::endl;
        return 1;
    }

    std::thread inputThread(getInput);  // Start a thread for user input
    Player player(car_type);

    int player_position_x = 5;
    int player_position_y = 1;
    int fuel_position_x = 30;
    int fuel_position_y = 30;
    int passenger_position_x = 50;
    int passenger_position_y = 20;
    int goal_position_x = 95;
    int goal_position_y = 46;
    std::string direction = "+y";
    std::string weather = "Sunny";

    while (true) {  // Continuous game loop
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int weather_number = std::rand() % 10;
        if (weather_number > 7){
            weather = "Rain";
        } else {
            weather = "Sunny";
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
        std::cout << "<ICON> O: player, F: gas station, P: passenger, G: Goal" << std::endl;
        std::cout << "Weather: " << weather << std::endl;
        printRace(track);
        player.showInfo();
        std::cout << std::endl << std::endl;

        player.consumeFuel();
        std::this_thread::sleep_for(std::chrono::milliseconds(reload_time));

        if ((player_position_x == fuel_position_x) && (player_position_y == fuel_position_y)) {
            player.refuel();
            player.pay(gas_price);
        }

        if ((player_position_x == passenger_position_x) && (player_position_y == passenger_position_y)) {
            player.passengerRide();
        }

        if ((player_position_x > 20) && (player_position_x < 60) && (player_position_y > 18) && (player_position_y < 22)) {
            player.pay(direction_fine);
        }

        if (player.getSpeed() >speed_limit) {
            player.pay(speed_limit_fine);
        }

        if (player.getSpeed() >speed_limit) {
            player.pay(speed_limit_fine);
        }

        if ((player.getPassenger() == 1) &&
            (player_position_x == goal_position_x) && (player_position_y == goal_position_y)) {
            std::cout << "Clear: Well Done!!" << std::endl;
            break;
        }

        if (player.getFuel() < 0) {
            std::cout << "GAME OVER: There is no fuel" << std::endl;
            break;
        }

        if (player.getBalance() < 0) {
            std::cout << "GAME OVER: Bankrupt" << std::endl;
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
                if (weather == "Rain"){
                    continue;
                }
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

        if (not movePlayer(player_position_x, player_position_y, direction, track, player)){
            break;
        }
    }

    inputThread.join();  // Wait for the input thread to finish
    return 0;
}
