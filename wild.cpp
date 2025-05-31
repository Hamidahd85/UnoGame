#include "wild.h"


wildcard::wildcard(Color c, Cardtype ct, int id) : card(c, ct, id) {
    this->color = Color::none;
    this->cardtype = Cardtype::wild;
    this->id = id;
}


Color wildcard::askcolor() {
    while (true) {
        int choice = 0;

        cout << "enter number 0,1,2,3";
        cin >> choice;

        if (choice >= 0 && choice < 4) {
            return static_cast<Color>(choice);
        } else {
            cout << "again";
        }

    }
}

void wildcard::setcolor(Color newcolor) {
    this->color = newcolor;
}

string wildcard::tostring() {
    return "[wild]";
}

bool wildcard::playable(card &TopCard) {
    return true;
}