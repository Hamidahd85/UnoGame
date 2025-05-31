#pragma once
#include "iostream"
#include <vector>
#include <memory>
#include "Card.h"
#include "NumberCard.h"
#include "wild.h"
#include "wilddrawfour.h"
#include "actioncard.h"
#include "Player.h"
using namespace std;

class deck : public card {
public:

    deck();

    int id;

    void build();

    void shuffle();

    void DealCards(vector<Player *> &players);

    vector<shared_ptr<card>> cards;
    shared_ptr<card> TopCard;

    shared_ptr<card> getTopCard();

    shared_ptr<card> DrawCard();

    bool playable(card &topcard) override;

    string tostring() override;

    vector<shared_ptr<card>> &getcards();

    void PlayedCard(shared_ptr<card> newCard);


};