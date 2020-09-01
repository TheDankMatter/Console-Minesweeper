#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <Field/Field.hpp>

class Board {
    private:
        std::set<std::array<int, 2>> bombsCoordinatesSet;
        std::vector<std::vector<Field>> board;
        int bombsNumber;
        int height;
        int width;

    public:
        Board(int width, int height, int bombs);
        int getRandomInt(int minValue, int maxValue);
        int printBoard(bool reveal = false, int x = 0, int y = 0);
        int selectField(int x, int y);
        int getBombsNumber();
        void plantBombs();
        void flagField(int x, int y);
        void placeBomb(int x, int y);
        void generateBoard();
        void generateBombsSet();
        void generateNumbers();
};