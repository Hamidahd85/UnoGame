#include "BotPlayer.h"

BotPlayer::BotPlayer(string Name) : Player(Name) {}

int BotPlayer::ChooseCard(shared_ptr<card> &TopCard) {
    for (int i = 0; i < GetInHandSize(); i++) {
        if (InHand[i]->playable(*TopCard)) {
            return i;
        }
    }
    return -1;
}

Color BotPlayer::ChooseColor() {
    int Redcount = 0;
    int Bluecount = 0;
    int Yellowcount = 0;
    int Greencount = 0;
    for (int i = 0; i < InHand.size(); ++i) {
        Color CurrentColor = InHand[i]->getcolor();
        if (CurrentColor == Color::red) {
            Redcount++;
        } else if (CurrentColor == Color::blue) {
            Bluecount++;
        } else if (CurrentColor == Color::yellow) {
            Yellowcount++;
        } else if (CurrentColor == Color::green) {
            Greencount++;
        }
    }
    Color BestChoice = Color::red;
    int MaxCount = Redcount;
    if (Bluecount > MaxCount) {
        BestChoice = Color::blue;
        MaxCount = Bluecount;
    }
    if (Greencount > MaxCount) {
        BestChoice = Color::green;
        MaxCount = Greencount;
    }
    if (Yellowcount > MaxCount) {
        BestChoice = Color::yellow;
        MaxCount = Yellowcount;
    }
    return MaxCount > 0 ? BestChoice : Color::red;
}