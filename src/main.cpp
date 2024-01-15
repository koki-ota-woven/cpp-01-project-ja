#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include <iomanip> // Include iomanip for formatting
#include "Player.h"
#include <ncurses.h> // Include ncurses library

const int row = 52;
const int column = 72;
const int reload_time = 1000;
const char car_icon = 'O';

std::atomic_bool inputReady(false);
std::string input;

void getInput() {
    while (true) {
        int ch = getch(); // Non-blocking input using ncurses

        if (ch != ERR) {
            input = static_cast<char>(ch);
            inputReady = true;
        }
    }
}

void printRace(char array1[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printw("%2c", array1[i][j]); // Use printw for ncurses
        }
        printw("\n");
    }
}

void initRace(char array2[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0 || i == row - 1) {
                array2[i][j] = '-';
            } else if (j == 0 || j == column - 1) {
                array2[i][j] = '|';
            } else {
                array2[i][j] = ' ';
            }
        }
    }
}

int main() {
    initscr(); // Initialize ncurses
    timeout(0); // Set non-blocking input mode
    keypad(stdscr, true); // Enable keypad input
    noecho(); // Disable automatic echoing of input

    std::thread inputThread(getInput);  // Start a thread for user input
    Player player;
    char track[row][column];
    int car_position_x = 5;
    int car_position_y = 1;
    int velocity = 1;
    std::string direction = "+y";

    while (true) {  // Continuous game loop
        clear();  // Clear the screen before printing new frame

        initRace(track);
        if (car_position_x > 0 && car_position_x < column - 1 && car_position_y > 0 && car_position_y < row - 1) {
            track[car_position_y][car_position_x] = car_icon;
        }

        printRace(track);
        refresh();  // Refresh the screen to update the changes

        std::this_thread::sleep_for(std::chrono::milliseconds(reload_time));

        // Update car position based on direction
        if (direction == "+y" && car_position_y < row - 2) {
            car_position_y += velocity;
        } else if (direction == "-y" && car_position_y > 1) {
            car_position_y -= velocity;
        } else if (direction == "+x" && car_position_x < column - 2) {
            car_position_x += velocity;
        } else if (direction == "-x" && car_position_x > 1) {
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
            } else if (input == "help") {
                player.showInfo();
            } else if (input == "q") {
                break;  // Exit the game loop when the user enters "q"
            } else {
                printw("!!!!Invalid command!!!!\n");
            }

            inputReady = false;  // Reset the flag
        }
    }

    endwin(); // Cleanup ncurses
    inputThread.join();  // Wait for the input thread to finish
    return 0;
}

