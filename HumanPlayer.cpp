#include "HumanPlayer.h"
HumanPlayer::HumanPlayer(string Name) : Player(Name) {}

int HumanPlayer::ChooseCard(shared_ptr<card> &TopCard) {
    while (true) {
        for (int i = 0; i < (int) InHand.size(); ++i) {
            cout << "[" << i << "]" << InHand[i]->tostring() << '\n';

        }
        cout << "Enter index or -1 to draw: ";
        int Choice;
        cin >> Choice;
        if (Choice == -1) {
            return -1;
        }
        if (Choice < 0 || Choice >= (int) InHand.size()) {
            cout << "Invalid index\n\n";
            continue;
        }
        if (!InHand[Choice]->playable(*TopCard)) {
            cout << "Cannot play " << InHand[Choice]->tostring() << " on " << TopCard->tostring() << "\n\n";
            continue;
        }
        return Choice;
    }
}

Color HumanPlayer::ChooseColor() {
    while (true) {
        cout << "Chosse Color (" << RED "0=Red" RESET ", " BLUE "1=Blue" RESET
                                    ", " YELLOW "2=Yellow" RESET ", " GREEN "3=Green" RESET "): ";
        int Choice;
        cin >> Choice;

        switch (Choice) {
            case 0 :
                return Color::red;
            case 1 :
                return Color::blue;
            case 2 :
                return Color::yellow;
            case 3 :
                return Color::green;
            default :
                cout << "Invalid number! please try again.\n";
        }
    }
}