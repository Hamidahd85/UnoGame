#include "NumberCard.h"

NumberCard::NumberCard(Color c, int num, int id) {
    this->color = c;
    this->cardtype = Cardtype::number;
    this->number = num;
    this->id = id;
}

int NumberCard::GetNumber() {
    return number;
}

string NumberCard::tostring() {
    return "[" + colortostring(color) + " " + to_string(number) + "]";
}

bool NumberCard::playable(card &TopCard) {
    return (color == TopCard.getcolor()) ||
           (TopCard.gettype() == Cardtype::number && number == static_cast<NumberCard &>(TopCard).GetNumber());
}