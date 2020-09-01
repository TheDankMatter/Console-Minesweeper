#include <Board/Board.hpp>

class Minesweeper {
    private:
        Board* board;
    public:
        Minesweeper();
        void start();
        void gameLoop();
        int getUserInt();
};