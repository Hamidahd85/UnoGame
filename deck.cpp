#include "deck.h"


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

void deck::DealCards(vector<Player*> &players) {
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