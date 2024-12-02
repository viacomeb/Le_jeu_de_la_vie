#include "cell.hpp"

Cell::Cell() : living(false) {}

Cell::Cell(bool living) : living(living) {}

bool Cell::getState() const {
    return living;
}

void Cell::editState(bool state) {
    living = state;
}
