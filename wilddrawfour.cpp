#include "wilddrawfour.h"

wilddrawfour::wilddrawfour(Color c, Cardtype ct, int id) : wildcard(c, ct, id) {
    this->cardtype = Cardtype::wilddrawfour;
}

string wilddrawfour::tostring() {
    return "[wild +4]";
}

bool wilddrawfour::playable(card &TopCard) {
    return true;

}
