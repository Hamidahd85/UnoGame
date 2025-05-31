#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Card.h"
#include "thread"
using namespace std;

class Player {
protected:
    string Name;
    vector<shared_ptr<card>> InHand;
public:
    Player(string Name);

    virtual ~Player() = default;

    string GetName();

    int GetInHandSize();

    void AddCard(shared_ptr<card> card);

    shared_ptr<card> RemoveHandCard(int i);

    vector<shared_ptr<card>> &GetHand();

    virtual int ChooseCard(shared_ptr<card> &TopCard) = 0;

    virtual Color ChooseColor() = 0;

    bool HasWon();
};