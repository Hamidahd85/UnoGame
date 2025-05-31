#pragma once
#include "Player.h"
#include <iostream>
using namespace std;
class HumanPlayer : public Player {
public:
    HumanPlayer(string Name);

    int ChooseCard(shared_ptr<card> &TopCard) override;

    Color ChooseColor() override;
};