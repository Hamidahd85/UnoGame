#include "Card.h"

card::card() {
    this->color = Color::none;
    this->cardtype = Cardtype::number;
    this->id = 0;
}

card::card(Color co, Cardtype ct, int id) {
    this->color = co;
    this->cardtype = ct;
    this->id = id;
};

Color card::getcolor() {
    return color;
};

int card::GetId() {
    return id;
}

Cardtype card::gettype() { return cardtype; };

void card::setcolor(Color new_color) { color = new_color; };


string card::colortostring(Color color) {
    switch (color) {
        case Color::red :
            return (RED "red" RESET);
        case Color::blue :
            return (BLUE "blue" RESET);
        case Color::yellow :
            return (YELLOW "yellow" RESET);
        case Color::green :
            return (GREEN "green" RESET);
        default:
            return "none";
    }
}