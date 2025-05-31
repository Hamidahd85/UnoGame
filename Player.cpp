#include "Player.h"

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