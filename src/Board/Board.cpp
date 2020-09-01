#include "Board/Board.hpp"
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <functional>
#include <array>
#include <stdexcept> 
#include <string>
#include <algorithm>

Board::Board(int width, int height, int bombs) {
    bombsNumber = bombs;
    this->height = height;
    this->width = width;

    generateBoard();
    generateBombsSet();
    plantBombs();
    generateNumbers();
}

void Board::generateBoard() {
    for(int y = 0; y < height; y++) {
        std::vector<Field> tempVector; 
        for(int x = 0; x < width; x++) {
            tempVector.push_back(Field());
        }
        board.push_back(tempVector);
    }
}

void Board::generateBombsSet() {
    while (this->bombsCoordinatesSet.size() < (unsigned)bombsNumber) {
        std::array<int, 2> xy;
        xy[0] = getRandomInt(0, width - 1);
        xy[1] = getRandomInt(0, height - 1);
        this->bombsCoordinatesSet.insert(xy);
    }
}

void Board::flagField(int x, int y) {
    if (board.at(y).at(x).isHidden()) {
        if (board.at(y).at(x).isFlag()) {
            board.at(y).at(x).removeFlag();
        }else {
            board.at(y).at(x).placeFlag();
        }
    }
}

void Board::placeBomb(int x, int y) {
    board.at(y).at(x).placeBomb();
}

int Board::getBombsNumber() {
    return bombsNumber;
}

int Board::printBoard(bool reveal, int x, int y) {
    int yBomb = y;
    int xBomb = x;

    //Print top row numbers
    for (int row = (int) std::to_string(width).length(); row >= 0; row--) {
        std::cout << "      ";
        for(int i = 1; i < (width + 1); i++) {
            std::string number = std::to_string(i);
            std::reverse(number.begin(), number.end());
            try {
                std::cout << number.at(row) << "|";
            } catch (const std::out_of_range& oor) {
                std::cout << "  ";
            }
        }
        std::cout << '\b' << " " << std::endl;
    }

    //Print top row separators "_"
    std::cout << "     ";
    for(int i = 0; i < width; i++) {
        std::cout << "__";
    }
    std::cout << std::endl;

    int hiddenCounter = 0;
    int flagCounter = 0;
    for(int y = 0; y < height; y++) {
        //Left row numbers
        if (y + 1 < 10) {
            std::cout << "  ";
        }else if (y + 1 < 100) {
            std::cout << " ";
        }
        std::cout << y + 1 << "  " << "|";
        for(int x = 0; x < width; x++) {
            if (reveal == true) {
                if (board.at(y).at(x).isBomb()){ //show bombs
                    if (yBomb == y && xBomb == x) {
                        std::cout << "@ ";
                    } else {
                        std::cout << "X ";
                    }
                } else if (board.at(y).at(x).getNumber() == 0) {
                    std::cout << " " << " ";
                } else {
                    std::cout << board.at(y).at(x).getNumber() << " ";
                } 
            } else {
                if (board.at(y).at(x).isFlag()) {
                    std::cout << "F ";
                    flagCounter++;
                    hiddenCounter++;
                } else if (!board.at(y).at(x).isHidden()) {
                    if (board.at(y).at(x).getNumber() == 0) {
                        std::cout << " " << " "; //∙
                    } else {
                        std::cout << board.at(y).at(x).getNumber() << " ";
                    }
                } else {
                    std::cout << "• ";
                    hiddenCounter++;
                }
            }
        }
        std::cout << '\b' << "|" << " " << y+1;
        std::cout << std::endl;
    }
    
    //Bottom line separator
    std::cout << "     ";
    for(int i = 0; i < width; i++) {
        std::cout << "￣";
    }
    std::cout << std::endl;

    //Bottom numbers
    for (unsigned int row = 0; row < std::to_string(width).length(); row++) {
        std::cout << "      ";
        for(int i = 1; i < (width + 1); i++) {
            std::string number = std::to_string(i); 
            try {
                std::cout << number.at(row) << "|";
            } catch (const std::out_of_range& oor) {
                std::cout << "  ";
            }
        }
        std::cout << '\b' << " " << std::endl;
    }

    if (hiddenCounter == bombsNumber) {
        return 1;
    } else if(flagCounter == bombsNumber) {
        for (auto const &pairXY : bombsCoordinatesSet) {
            if (!board.at(pairXY[1]).at(pairXY[0]).isFlag()) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

int Board::getRandomInt(int minValue, int maxValue) {
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(minValue, maxValue); // define the range
    return distr(gen);
}

void Board::plantBombs() {
    for (auto const &pairXY : bombsCoordinatesSet) {
        placeBomb(pairXY[0], pairXY[1]);
        //std::cout << "bomb placed" << " at " << "(" << pairXY[0] << ", "<< pairXY[1]<< ")" << " " << std::endl;
    }
}

int Board::selectField(int x, int y) {
    try {
        if (board.at(y).at(x).isBomb()) {
            return 1;
        } else if (!board.at(y).at(x).isHidden()) {
           return 0;
        } else if (board.at(y).at(x).getNumber() > 0) {
            board.at(y).at(x).revealField();
            return 0;
        } else if (board.at(y).at(x).isHidden()){
            board.at(y).at(x).revealField();
            //Upper row
            selectField(x - 1, y - 1);
            selectField(x    , y - 1);
            selectField(x + 1, y - 1);
            //Left right
            selectField(x - 1, y);
            selectField(x + 1, y);
            //Bottom row
            selectField(x - 1, y + 1);
            selectField(x    , y + 1);
            selectField(x + 1, y + 1);
        }
    } catch (const std::out_of_range& oor) {
        return 0;
    }
    return 0; 
}

void Board::generateNumbers() {
    for (auto const &pairXY : bombsCoordinatesSet) {
        //Top row
        try { board.at(pairXY[1] - 1).at(pairXY[0] - 1).addOne(); } catch (const std::out_of_range& oor) {}
        try { board.at(pairXY[1] - 1).at(pairXY[0]    ).addOne(); } catch (const std::out_of_range& oor) {}
        try { board.at(pairXY[1] - 1).at(pairXY[0] + 1).addOne(); } catch (const std::out_of_range& oor) {}

        //Left right
        try { board.at(pairXY[1]).at(pairXY[0] - 1).addOne();     } catch (const std::out_of_range& oor) {}
        try { board.at(pairXY[1]).at(pairXY[0] + 1).addOne();     } catch (const std::out_of_range& oor) {}

        //Bottom row
        try { board.at(pairXY[1] + 1).at(pairXY[0] - 1).addOne(); } catch (const std::out_of_range& oor) {}
        try { board.at(pairXY[1] + 1).at(pairXY[0]    ).addOne(); } catch (const std::out_of_range& oor) {}
        try { board.at(pairXY[1] + 1).at(pairXY[0] + 1).addOne(); } catch (const std::out_of_range& oor) {}
    }
}