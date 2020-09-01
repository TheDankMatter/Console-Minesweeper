#include "Field/Field.hpp"

Field::Field() {
    hidden = true;
    number = 0;
    flag = false;
    bomb = false;
}


bool Field::isHidden() {
    return hidden;
}

unsigned short int Field::getNumber() {
    return number;
}

bool Field::isFlag() {
    return flag;
}

bool Field::isBomb() {
    return bomb;
}

void Field::revealField() {
    hidden = false;
}

void Field::setNumber(unsigned short int newNumber) {
    number = newNumber;
}

void Field::placeBomb() {
    bomb = true;
}

void Field::placeFlag() {
    flag = true;
}

void Field::removeFlag() {
    flag = false;
}

void Field::addOne() {
    number++;
}