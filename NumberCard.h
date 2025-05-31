#pragma once
#include "iostream"
#include "Card.h"
using namespace std;

class NumberCard : public card {
private:
    int number;
public:
    NumberCard(Color c, int num, int id);

    int GetNumber();

    string tostring();

    bool playable(card &TopCard);
};