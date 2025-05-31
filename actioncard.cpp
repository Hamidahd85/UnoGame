#include "actioncard.h"

action::action(Color c, Cardtype type, int id) : card(c, type, id) {}

string action::tostring() {

    string res = "[";
    res += colortostring(color);


    if (this->cardtype == Cardtype::skip) {
        res += " skip]";
    } else if (this->cardtype == Cardtype::drawtwo) {
        res += " +2]";
    } else if (this->cardtype == Cardtype::reverse) {
        res += " reverse]";

    }
    return res;
}

bool action::playable(card &TopCard) {
    return (color == TopCard.getcolor() || cardtype == TopCard.gettype());
}

