#include "Manager.h"

Manager::Manager(vector<shared_ptr<Player>> &players) : Players(players), CurrentIndex(0), turn(Turn::Left), GameOver(
        false) {
    if (players.size() < 2 || players.size() > 10) {
        throw invalid_argument("Number of players must be between 2 & 10.");
    }
}

void Manager::StartGame() {
    Deck.shuffle();
    for (auto &player: Players) {
        for (int i = 0; i < 7; ++i) {
            auto card = Deck.DrawCard();
            if (card) player->AddCard(card);
        }
    }
    CurrentCard = Deck.DrawCard();
    sookhtecard.push_back(CurrentCard);
}

void Manager::NextPlayer() {
    if (turn == Turn::Left) {
        CurrentIndex = (CurrentIndex + 1) % Players.size();
    } else {
        CurrentIndex = (CurrentIndex - 1 + Players.size()) % Players.size();
    }
}

void Manager::HandleSpecialCards(shared_ptr<card> &card, Color ChoosenColor) {
    if (card->gettype() == Cardtype::skip) {
        NextPlayer();
    } else if (card->gettype() == Cardtype::reverse) {
        if (Players.size() == 2) {
            NextPlayer();
        } else {
            turn = (turn == Turn::Left) ? Turn::Right : Turn::Left;
        }
    } else if (card->gettype() == Cardtype::drawtwo) {
        size_t nextIndex = (CurrentIndex + (turn == Turn::Left ? 1 : -1)) % Players.size();
        for (int i = 0; i < 2; ++i) {
            auto drawnCard = Deck.DrawCard();
            if (drawnCard) Players[nextIndex]->AddCard(drawnCard);
        }
        NextPlayer();
    }
    if (card->gettype() == Cardtype::wild || card->gettype() == Cardtype::wilddrawfour) {
        if (ChoosenColor != Color::none) {
            card->setcolor(ChoosenColor);
        }
        if (card->gettype() == Cardtype::wilddrawfour) {
            int nextIdx = static_cast<int>(CurrentIndex)
                          + (turn == Turn::Left ? 1 : -1);
            if (nextIdx < 0) nextIdx += Players.size();
            else if (nextIdx >= static_cast<int>(Players.size()))
                nextIdx -= Players.size();
            for (int i = 0; i < 4; ++i) {
                auto drawnCard = Deck.DrawCard();
                if (drawnCard)
                    Players[nextIdx]->AddCard(drawnCard);
            }
            CurrentIndex = nextIdx;
        }
    }
}

void Manager::PlayTurn() {
    if (GameOver) return;

    auto player = Players[CurrentIndex];
    bool isBot = dynamic_cast<BotPlayer *>(player.get()) != nullptr;
    string status = "\nTurn: " + player->GetName() + " | Top: " + CurrentCard->tostring() + " | Top color: " +
                    card::colortostring(CurrentCard->getcolor());
    if (isBot) slowPrint(status);
    else cout << status << endl;
    int choice = player->ChooseCard(CurrentCard);

    if (choice == -1) {
        auto c = Deck.DrawCard();
        if (c) {
            string drawMsg = player->GetName() + (" draws ") + c->tostring();
            if (isBot) slowPrint(drawMsg);
            else cout << drawMsg << endl;
            player->AddCard(c);
        }
    } else {
        auto c = player->RemoveHandCard(choice);
        string playMsg = player->GetName() + string(" plays ") + c->tostring();
        if (isBot) slowPrint(playMsg);
        else cout << endl << playMsg << endl;

        Color col = Color::none;
        if (c->gettype() == Cardtype::wild ||
            c->gettype() == Cardtype::wilddrawfour) {
            col = player->ChooseColor();
            cout << "\nColor chosen: "
                 << card::colortostring(col) << "\n";
            /*if (c->gettype() == Cardtype::wilddrawfour){
                cout << Players[CurrentIndex + 1]->GetName() << " draw 4 cards!" << "\n";
            }*/
        }

        sookhtecard.push_back(c);
        CurrentCard = c;
        HandleSpecialCards(c, col);

        if (player->HasWon()) {
            GameOver = true;
            cout << player->GetName() << " has won!\n";
        }
    }

    if (!GameOver)
        NextPlayer();
}


string Manager::Gamestat() {
    string state = "Current Player: " + Players[CurrentIndex]->GetName() + "\n";
    state += "Top Card: " + CurrentCard->tostring() + "\n";
    state += "Number of Players: " + to_string(Players.size()) + "\n";
    return state;
}

bool Manager::isGameOver() {
    return GameOver;
}