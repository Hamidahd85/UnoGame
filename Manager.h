#pragma once
#include "iostream"
#include <vector>
#include <string>
#include "Player.h"
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include "Card.h"
#include "NumberCard.h"
#include "deck.h"
#include "SlowPrint.h"

enum class Turn {
    Left, Right
};

class Manager {
private:
    vector<shared_ptr<Player>> Players;
    deck Deck;
    vector<shared_ptr<card>> sookhtecard;
    shared_ptr<card> CurrentCard;
    size_t CurrentIndex;
    Turn turn;
    bool GameOver;

    void NextPlayer();

    void HandleSpecialCards(shared_ptr<card> &card, Color ChoosenCard = Color::none);

public:
    Manager(vector<shared_ptr<Player>> &players);

    void StartGame();

    void PlayTurn();

    bool isGameOver();

    string Gamestat();
};