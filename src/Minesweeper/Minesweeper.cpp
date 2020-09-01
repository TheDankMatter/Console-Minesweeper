#include <iostream>
#include <stdio.h>
#include <string.h>
#include <regex>
#include "Minesweeper/Minesweeper.hpp"

Minesweeper::Minesweeper() {}

void Minesweeper::start() {
    int width, height, bombs;
    std::cout << "Enter desired game width: ";
    width = getUserInt();
    std::cout << "Enter desired game height: ";
    height = getUserInt();
    std::cout << "Enter desired number of bombs: ";
    while (1) {
        bombs = getUserInt();
        if (bombs <= (width*height)) {
            break;
        } else {
            std::cout << "Too many bombs! Enter a number lower or equal than " << width*height << ": ";
        }
    }
    board = new Board(width, height, bombs);
    gameLoop();
}

int Minesweeper::getUserInt() {
    char line[20];
    while (1) {
        std::cin.getline(line, 20);
        std::string argument(line);
        if (std::regex_match(argument, std::regex("[0-9]*"))) {
            return stoi(argument);
            break;
        } else {
            std::cout << "Please enter a correct number: ";
        }
    }
}

void Minesweeper::gameLoop() {
    
    board->printBoard();

    while (1) {
        char line[20];
        std::cout << "Command: ";
        try {
            std::cin.getline(line, 20);

            char *token;
            int x, y;

            //First argument
            token = strtok(line, " ");
            std::string argument(line);

            if (argument.compare("exit") == 0) {
                exit(0);
            } else if (argument.compare("flag") == 0) { //argument.compare("flag") == 0
                //Second argument
                token = strtok(NULL, " ");
                //Split second argument on ","
                token = strtok(token, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);
                board->flagField(x - 1, y - 1);
            } else if (argument.compare("select") == 0) { //argument.compare("select") == 0
                //Second argument
                token = strtok(NULL, " ");
                //Split second argument on ","
                token = strtok(token, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);

                if (board->selectField(x - 1, y - 1) == 1) {
                    board->printBoard(true, x - 1, y - 1);
                    std::cout << "You lost!" << std::endl;
                    break;
                }
            } else if (std::regex_match(argument, std::regex("[0-9]*\\,[0-9]+"))) { //Any lenght number separeted by "," followed by any lenght number
                token = strtok(token, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);
                if (board->selectField(x - 1, y - 1) == 1) {
                    board->printBoard(true, x - 1, y - 1);
                    std::cout << "You lost!" << std::endl;
                    break;
                }
            } else if (argument.compare("help") == 0 || argument.compare("?") == 0) {
                std::cout << std::endl;
                std::cout << "Your goal is to uncover all fields without bombs, or flag all bombs locations." << std::endl;
                std::cout << "Selecting a field with bomb ends the game." << std::endl;
                std::cout << "Use \"select\" + coordinates x,y to select a field." << std::endl;
                std::cout << "Typing cooridinates only, uses \"select\" as default command." << std::endl;
                std::cout << "Use \"flag\" + coordinates x,y to flag/unflag a field." << std::endl;
                std::cout << "Use \"exit\" to exit." << std::endl;
                std::cout << std::endl;
                continue;

            } else {
                std::cout << "Invalid input. Type \"help\" or \"?\" for help"  << std::endl;
                continue;
            }

            if (board->printBoard() == 1) {
                std::cout << "You win!" << std::endl;
                break;
             }
        } catch (...) {
            std::cout << "Invalid input. Type \"help\" or \"?\" for help" << std::endl;
        }
        
    }
}