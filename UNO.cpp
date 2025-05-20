#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"


using namespace std;

enum class Color {
    red,
    blue,
    yellow,
    green,
    none
};
enum class Cardtype {
    number,
    skip,
    wild,
    reverse,
    drawtwo,
    wilddrawfour
};
enum class Turn {
    Left, Right
};

void slowPrint(const string &text, int msDelay = 30) {
    for (char c: text) {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
}

#define BOT_PRINT(msg) slowPrint(msg + "\n")


class card {
protected:
    int id;
    Color color;
    Cardtype cardtype;

public:
    card();

    card(Color co, Cardtype ct, int id);

    Cardtype gettype();

    Color getcolor();

    int GetId();

    void setcolor(Color new_color);

    static string colortostring(Color color);

    virtual bool playable(card &topcard) = 0;

    virtual string tostring() = 0;


};

card::card() {
    this->color = Color::none;
    this->cardtype = Cardtype::number;
    this->id = 0;
}

card::card(Color co, Cardtype ct, int id) {
    this->color = co;
    this->cardtype = ct;
    this->id = id;
};

Color card::getcolor() {
    return color;
};

int card::GetId() {
    return id;
}

Cardtype card::gettype() { return cardtype; };

void card::setcolor(Color new_color) { color = new_color; };


string card::colortostring(Color color) {
    switch (color) {
        case Color::red :
            return (RED "red" RESET);
        case Color::blue :
            return (BLUE "blue" RESET);
        case Color::yellow :
            return (YELLOW "yellow" RESET);
        case Color::green :
            return (GREEN "green" RESET);
        default:
            return "none";
    }
}

class NumberCard : public card {
private:
    int number;
public:
    NumberCard(Color c, int num, int id);

    int GetNumber();

    string tostring();

    bool playable(card &TopCard);
};

NumberCard::NumberCard(Color c, int num, int id) {
    this->color = c;
    this->cardtype = Cardtype::number;
    this->number = num;
    this->id = id;
}

int NumberCard::GetNumber() {
    return number;
}

string NumberCard::tostring() {
    return "[" + colortostring(color) + " " + to_string(number) + "]";
}

bool NumberCard::playable(card &TopCard) {
    return (color == TopCard.getcolor()) ||
           (TopCard.gettype() == Cardtype::number && number == static_cast<NumberCard &>(TopCard).GetNumber());
}

class action : public card {
public:
    action(Color c, Cardtype type, int id);

    string tostring();

    bool playable(card &TopCard);
};

action::action(Color c, Cardtype type, int id) : card(c, type, id) {}

string action::tostring() {

    string res = "[";
    res += colortostring(color);


    if (this->cardtype == Cardtype::skip) {
        res += " skip]";
    } else if (this->cardtype == Cardtype::drawtwo) {
        res += " +2]";
    } else if (this->cardtype == Cardtype::reverse) {
        res += " reverse]";

    }
    return res;
}

bool action::playable(card &TopCard) {
    return (color == TopCard.getcolor() || cardtype == TopCard.gettype());
}

class wildcard : public card {
public:
    wildcard(Color c, Cardtype ct, int id);

    Color askcolor();


    void setcolor(Color newcolor);

    string tostring();

    bool playable(card &TopCard);
};

wildcard::wildcard(Color c, Cardtype ct, int id) : card(c, ct, id) {
    this->color = Color::none;
    this->cardtype = Cardtype::wild;
    this->id = id;
}


Color wildcard::askcolor() {
    while (true) {
        int choice = 0;

        cout << "enter number 0,1,2,3";
        cin >> choice;

        if (choice >= 0 && choice < 4) {
            return static_cast<Color>(choice);
        } else {
            cout << "again";
        }

    }
}

void wildcard::setcolor(Color newcolor) {
    this->color = newcolor;
}

string wildcard::tostring() {
    return "[wild]";
}

bool wildcard::playable(card &TopCard) {
    return true;
}

class wilddrawfour : public wildcard {

public:
    wilddrawfour(Color c, Cardtype ct, int id);

    Color askcolor();

    void setcolor(Color newcolor);

    string tostring();

    bool playable(card &TopCard);

};

wilddrawfour::wilddrawfour(Color c, Cardtype ct, int id) : wildcard(c, ct, id) {
    this->cardtype = Cardtype::wilddrawfour;
}

string wilddrawfour::tostring() {
    return "[wild +4]";
}

bool wilddrawfour::playable(card &TopCard) {
    return true;

}

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

Player::Player(string Name) {
    this->Name = Name;
}

string Player::GetName() {
    return Name;
}

int Player::GetInHandSize() {
    return InHand.size();
}

void Player::AddCard(shared_ptr<card> card) {
    InHand.push_back(move(card));
}

shared_ptr<card> Player::RemoveHandCard(int i) {
    auto card = InHand.at(i);
    InHand.erase(InHand.begin() + i);
    return card;
}

vector<shared_ptr<card>> &Player::GetHand() {
    return InHand;
}

bool Player::HasWon() {
    return InHand.empty();
};

class HumanPlayer : public Player {
public:
    HumanPlayer(string Name);

    int ChooseCard(shared_ptr<card> &TopCard) override;

    Color ChooseColor() override;
};

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

class BotPlayer : public Player {
public:
    BotPlayer(string Name);

    int ChooseCard(shared_ptr<card> &TopCard) override;

    Color ChooseColor() override;
};

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

bool deck::playable(card &topcard) {
    return true;
}

string deck::tostring() {
    return "";
}

deck::deck() : id(0) {
    build();
}


void deck::build() {

    vector<Color> colors = {Color::red, Color::blue, Color::yellow, Color::green};

    for (auto color: colors) {
        cards.push_back(make_shared<NumberCard>(color, 0, id));

        for (int num = 1; num < 9; num++) {
            cards.push_back(make_shared<NumberCard>(color, num, id++));
            cards.push_back(make_shared<NumberCard>(color, num, id++));

        }
        for (int i = 0; i < 2; i++) {
            cards.push_back(make_shared<action>(color, Cardtype::skip, id++));
            cards.push_back(make_shared<action>(color, Cardtype::reverse, id++));
            cards.push_back(make_shared<action>(color, Cardtype::drawtwo, id++));
        }
    }
    for (int i = 0; i < 4; ++i) {
        cards.push_back(make_shared<wildcard>(color, Cardtype::wild, id++));
        cards.push_back(make_shared<wilddrawfour>(color, Cardtype::wilddrawfour, id++));
    }
}

void deck::shuffle() {
    srand(time(0));
    for (int i = cards.size(); i > 0; i--) {
        int k = rand() % (i + 1);
        swap(cards[i], cards[k]);
    }
}

void deck::DealCards(vector<Player *> &players) {
    int cardp = 7;

    for (int i = 0; i < cardp; i++) {
        for (auto &player: players) {
            if (!cards.empty()) {
                shared_ptr<card> c = cards.back();

                player->AddCard(c);

                cards.pop_back();
            }
        }
    }
    if (!cards.empty()) {
        TopCard = cards.back();

    }
}

void deck::PlayedCard(shared_ptr<card> newCard) {
    if (TopCard != nullptr) {
        cards.push_back(TopCard);
        shuffle();
    }
    TopCard = newCard;
}

shared_ptr<card> deck::DrawCard() {
    if (!cards.empty()) {
        shared_ptr<card> c = cards.back();
        cards.pop_back();
        return c;
    }
    return nullptr;
}

shared_ptr<card> deck::getTopCard() {
    return TopCard;
}

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
    } else if (card->gettype() == Cardtype::wild || card->gettype() == Cardtype::wilddrawfour) {
        if (ChoosenColor != Color::none) {
            card->setcolor(ChoosenColor);
        }
        if (card->gettype() == Cardtype::wilddrawfour) {
            size_t nextIndex = (CurrentIndex + (turn == Turn::Left ? 1 : -1)) % Players.size();
            for (int i = 0; i < 4; ++i) {
                auto drawnCard = Deck.DrawCard();
                if (drawnCard) Players[nextIndex]->AddCard(drawnCard);
            }
            NextPlayer();
        }
    }
}

void Manager::PlayTurn() {
    if (GameOver) return;

    auto player = Players[CurrentIndex];
    bool isBot = dynamic_cast<BotPlayer *>(player.get()) != nullptr;
    string status = "\nTurn: " + player->GetName() + " | Top: " + CurrentCard->tostring() + " | Top color: " +
                    card::colortostring(CurrentCard->getcolor());
    if (isBot) BOT_PRINT(status);
    else cout << status << endl;
    int choice = player->ChooseCard(CurrentCard);

    if (choice == -1) {
        auto c = Deck.DrawCard();
        if (c) {
            string drawMsg = player->GetName() + (" draws ") + c->tostring();
            if (isBot) BOT_PRINT(drawMsg);
            else cout << drawMsg << endl;
            player->AddCard(c);
        }
    } else {
        auto c = player->RemoveHandCard(choice);
        string playMsg = player->GetName() + string(" plays ") + c->tostring();
        if (isBot) BOT_PRINT(playMsg);
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

int main() {
    vector<shared_ptr<Player>> players;

    players.push_back(make_shared<HumanPlayer>("Hamid"));
    players.push_back(make_shared<BotPlayer>("ZahraSh"));
    players.push_back(make_shared<BotPlayer>("Zahra"));


    Manager manager(players);
    manager.StartGame();
    while (!manager.isGameOver()) {
        /*slowPrint("....................................\n" + manager.Gamestat() + "\n");*/
        manager.PlayTurn();
    }
    cout << "\n----Game Over----" << endl;
    cin.get();
}