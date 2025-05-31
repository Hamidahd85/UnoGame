cmake_minimum_required(VERSION 3.29)
project(TextBasedUno-CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TextBasedUno-CPP main.cpp
        Card.h
        card.cpp
        NumberCard.h
        NumberCard.cpp
        actioncard.h
        actioncard.cpp
        wild.h
        wild.cpp
        wilddrawfour.h
        wilddrawfour.cpp
        Player.h
        Player.cpp
        HumanPlayer.h
        HumanPlayer.cpp
        BotPlayer.h
        BotPlayer.cpp
        deck.h
        deck.cpp
        Manager.h
        Manager.cpp
        SlowPrint.h
        SlowPrint.cpp
)
