#pragma once
#include <iostream>
#include <string>
using namespace std;
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

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