//
// Created by koki-ota on 23/12/27.
//

#include <iostream>
#include "../include/Player.h"

int main() {
    Player player;

    std::string command;
    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);

        if (command == "turn left") {
            player.turnLeft();
        } else if (command == "turn right") {
            player.turnRight();
        } else if (command == "continue straight") {
            std::cout << "Continuing straight" << std::endl;
        } else if (command == "accelerate") {
            player.accelerate();
        } else if (command == "decelerate") {
            player.decelerate();
        } else if (command == "stop") {
            player.stop();
        } else if (command == "refuel") {
            player.refuel();
        } else if (command == "show info") {
            player.showInfo();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    return 0;
}