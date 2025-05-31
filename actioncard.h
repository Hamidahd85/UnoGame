#pragma once
#include <iostream>
#include "Card.h"
class action : public card {
public:
    action(Color c, Cardtype type, int id);

    string tostring();

    bool playable(card &TopCard);
};