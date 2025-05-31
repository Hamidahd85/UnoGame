#include <iostream>
#include <vector>
#include "NumberCard.h"
#include "actioncard.h"
#include "wild.h"
#include "wilddrawfour.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "Manager.h"
using namespace std;
int main() {
    vector<shared_ptr<Player>> players;

    players.push_back(make_shared<HumanPlayer>("Hamidreza-ahd"));
    players.push_back(make_shared<BotPlayer>("ZahraSh84"));
    players.push_back(make_shared<BotPlayer>("Bot"));
    Manager manager(players);
    manager.StartGame();
    while (!manager.isGameOver()) {
        manager.PlayTurn();
    }
    cout << "\n----Game Over----" << endl;
    cin.get();
    cin.get();
}