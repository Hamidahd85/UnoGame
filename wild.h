#pragma once
#include <iostream>
#include "Card.h"
class wildcard : public card {
public:
    wildcard(Color c, Cardtype ct, int id);

    Color askcolor();


    void setcolor(Color newcolor);

    string tostring();

    bool playable(card &TopCard);
};