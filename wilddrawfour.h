#pragma once
#include <iostream>
#include "wild.h"
class wilddrawfour : public wildcard {

public:
    wilddrawfour(Color c, Cardtype ct, int id);

    Color askcolor();

    void setcolor(Color newcolor);

    string tostring();

    bool playable(card &TopCard);

};