# Text-Based UNO Game in C++

![GitHub repo size](https://img.shields.io/github/repo-size/Hamidreza-ahd/TextBasedUNO-Cpp)  
![License](https://img.shields.io/badge/License-MIT-blue)  

A console-based implementation of the classic UNO card game written in modern C++. Designed for both human and AI (bot) players, this project simulates complete UNO gameplay—including number cards, skip, reverse, draw-two, wild, and wild draw-four cards—entirely in a terminal environment with real-time interaction and colorful visual feedback.

---

## 🎯 Overview

**Text-Based UNO** is a faithful, text-only recreation of the popular UNO card game. This project introduces:

- **Core UNO mechanics** (matching by color or number, special action cards, turn order, draw penalties).
- **Human vs. Bot (AI) players**: A simple AI that chooses playable cards and picks the most abundant color when playing wild cards.
- **ANSI‐colored terminal output**: Cards and prompts appear in red, blue, yellow, or green to mimic UNO card colors.
- **Thread‐based “slow print” effect**: Simulates a “typing” animation for bot actions and game status updates.
- **Modular, object‐oriented design**: Classes for `card`, `NumberCard`, `action`, `wildcard`, `wilddrawfour`, `Player` (and its derivatives), `deck`, and `Manager` (game controller).

Whether you want to test your UNO skills against simple AI opponents or explore how to architect a card game in C++ using modern language features (smart pointers, STL containers, enums, and multithreading for I/O effects), this repository provides a clear, educational starting point.

---

## 🛠️ Features

- **Full UNO rule set**  
  - Number cards (0–9) in four colors (Red, Blue, Yellow, Green)  
  - Action cards: Skip, Reverse, Draw Two  
  - Wild cards: Wild (choose any color), Wild Draw Four (choose any color + force next player to draw 4)  
  - Proper turn order adjustment for skip/reverse/draw penalties  
- **Human and Bot players**  
  - `HumanPlayer`: Prompts user to select a playable card or draw from the deck  
  - `BotPlayer`: Automatically selects the first playable card in hand; chooses the color that appears most in its current hand when playing a wild card  
- **Console-based I/O**  
  - ANSI escape codes for colorful text output  
  - “Slow print” for bot moves and game status, creating a more engaging console experience  
  - Simple text‐menu interface for human player interactions  
- **Object-Oriented Design**  
  - Abstract base class `card` with derived types (`NumberCard`, `action`, `wildcard`, `wilddrawfour`)  
  - `Player` base class with two concrete subclasses (`HumanPlayer`, `BotPlayer`)  
  - `deck` class to build, shuffle, deal, draw, and track the top card  
  - `Manager` class to orchestrate the game loop, enforce UNO rules, and manage turn progression  

---

## 🧰 Requirements

- **Compiler:**  
  - A modern C++ compiler with **C++11** (or newer) support, for example:  
    - GCC (&ge; 4.8)  
    - Clang (&ge; 3.3)  
    - MSVC 2015 (or newer)  

- **Standard Library Dependencies:**  
  - `<vector>`, `<string>`, `<memory>`, `<cstdlib>`, `<ctime>`, `<algorithm>`, `<chrono>`, `<thread>`, `<iostream>`  
  - No external (third‐party) libraries are required.  

- **Platform:**  
  - Unix/Linux/macOS terminals (for ANSI‐color support).  
  - Windows 10+ (using a terminal that supports ANSI escape codes, such as Windows Terminal or enabling Virtual Terminal Processing in cmd.exe).  

---

## 🚀 Build & Installation

1. **Clone the Repository**  
   git clone https://github.com/Hamidreza-ahd/TextBasedUNO-Cpp.git
   cd TextBasedUNO-Cpp

2. **Compile the Source**
   Use your preferred compiler. For example, with GCC or Clang:

   # Using g++ (GCC)
   g++ -std=c++11 -pthread main.cpp -o UNO.exe

   # Or using clang++
   clang++ -std=c++11 -pthread main.cpp -o UNO.exe

   * The `-std=c++11` (or newer standard) flag enables required C++11 features.
   * The `-pthread` (or `-lpthread`) flag is needed for `std::thread` (used in `slowPrint`).

3. **Run the Executable**

   ./UNO.exe

   If compilation is successful, you’ll see the game start with a shuffled deck and initial hands dealt to each player.

---

## 🎮 How to Play

1. **Game Start**

   * Three players are created by default (one human named “Hamid” and two bots named “ZahraSh” and “Zahra”).
   * Each player receives 7 cards, and one card is flipped to begin the discard pile (the “Top Card”).

2. **Turns**

   * On your turn (as the human player), the console will display:

     Turn: Hamid | Top: [Green 5] | Top color: green

     * Underneath, you’ll see your current hand listed by index, for example:

       [0] [Blue 5]

       [1] [Red Skip]

        [2] [Yellow 2]
       ...
   * **Choose Card or Draw**

     * Type the index (e.g., `0`) of a card that is playable on the current top card.

       * A card is **playable** if it matches either the color or number/type of the top card.
       * Wild cards (`[wild]` or `[wild +4]`) are always playable.
     * If you cannot (or do not wish) to play any card, type `-1` to draw from the deck.

3. **Playing a Card**

   * Once you play a valid card, the card moves to the discard pile, and any special effects take place:

     * **Skip** (`[color skip]`): Next player loses their turn.
     * **Reverse** (`[color reverse]`): Game direction reverses (in a 2‐player game, acts like a skip).
     * **Draw Two** (`[color +2]`): Next player draws 2 cards and loses their turn.
     * **Wild** (`[wild]`): You choose a new color (0=Red, 1=Blue, 2=Yellow, 3=Green).
     * **Wild Draw Four** (`[wild +4]`): You choose a new color and the next player draws 4 cards (skipped).

   * If you play a wild card or wild draw four, you will be prompted:

     Choose Color (0=Red, 1=Blue, 2=Yellow, 3=Green): 

4. **Bot Turns**

   * Bots automatically scan their hand from left to right, playing the first valid card.
   * If no playable card is found, they draw one card from the deck.
   * When playing a Wild card, bots pick whichever color they have the most of in hand. If tied, they default to Red.

5. **Winning Condition**

   * If a player (you or a bot) empties their hand, the game ends immediately and that player is declared the winner.
   * A final message is printed, for example:

     Zahra has won!

6. **Game Over**

   * After a winner is declared, the program will pause, waiting for a keypress before exiting.

---

## 📂 Code Structure

├── main.cpp           # Entry point. Sets up players and starts the game loop

└── README.md          # This documentation file

*All classes are defined and implemented within a single source file (`main.cpp`). If you’d like to refactor, you can separate declarations into `.hpp` headers and implementations into `.cpp` files.*

### Key Classes & Responsibilities

1. **`card` (Abstract Base Class)**

   * Fields: `color`, `cardtype`, `id`
   * Pure virtual methods: `playable(card &topcard)`, `tostring()`
   * Helper: `colortostring(Color)` returns an ANSI‐colored string (e.g., `"\033[1;31mred\033[0m"`).

2. **`NumberCard` (Derived from `card`)**

   * Represents a numbered UNO card (0–9) of a specific color.
   * `playable(...)` returns true if either color matches or number matches the top card’s number.

3. **`action` (Derived from `card`)**

   * Represents Skip, Reverse, and Draw-Two cards.
   * `playable(...)` returns true if either color matches or card type matches.

4. **`wildcard` & `wilddrawfour` (Derived from `card`)**

   * `wildcard`: Represents a standard Wild card. Always playable; user/bot selects new color.
   * `wilddrawfour`: Represents a Wild Draw Four. Always playable; user/bot selects new color and forces the next player to draw 4 cards.

5. **`Player` (Abstract Base Class)**

   * Fields: `Name`, `InHand` (vector of `shared_ptr<card>`)
   * Virtual methods:

     * `int ChooseCard(shared_ptr<card> &TopCard)`
     * `Color ChooseColor()`
   * Helper methods: `AddCard(...)`, `RemoveHandCard(i)`, `HasWon()`

6. **`HumanPlayer` (Derived from `Player`)**

   * Implements `ChooseCard(...)` by prompting console input.
   * Implements `ChooseColor()` by prompting console input.

7. **`BotPlayer` (Derived from `Player`)**

   * Implements `ChooseCard(...)` by scanning the hand for the first playable card; otherwise returns `-1` to draw.
   * Implements `ChooseColor()` by counting colors in hand and picking the most frequent.

8. **`deck` (Derived from `card`, but primarily treated as a card “container” here)**

   * Fields: `cards` (vector of `shared_ptr<card>>`), `TopCard`
   * Methods:

     * `build()`: Constructs a full UNO deck (0–9 number cards, 2 copies of 1–9 per color; 2 skips, 2 reverses, 2 draw-twos per color; 4 wild; 4 wild draw-four)
     * `shuffle()`: Randomly shuffles `cards` using `std::rand()` and `swap()`
     * `DealCards(vector<Player*>&)`: Deals 7 cards to each player in rotation and sets the initial `TopCard`
     * `DrawCard()`: Removes & returns the top card from `cards`
     * `PlayedCard(shared_ptr<card>)`: Pushes the old `TopCard` back into `cards`, shuffles, and updates `TopCard`

9. **`Manager` (Game Controller)**

   * Fields: `Players` (vector of all players), `Deck`, `CurrentCard` (discard pile top), `CurrentIndex` (index of current player), `turn` (Left/Right to track direction), `GameOver` flag
   * Methods:

     * `StartGame()`: Initializes deck, shuffles, deals 7 cards to each player, sets the first `CurrentCard`
     * `PlayTurn()`:

       1. Prompts either human or bot to `ChooseCard(...)`.
       2. If `-1`, draws one card from deck; otherwise plays chosen card.
       3. If the played card is a wild (or wild draw four), calls `ChooseColor()` to set its color.
       4. Updates `CurrentCard` and applies any special card effects via `HandleSpecialCards(...)` (skip, reverse, draw penalties).
       5. Checks for win condition (`HasWon()`).
       6. Advances to next player (considering `turn` direction).
     * `isGameOver()`: Returns `true` if any player has emptied their hand.
     * `Gamestat()`: A convenience method that returns a string with the current player’s name, top card, and total number of players.


## 📜 Example Gameplay

# After building and running the executable:

Turn: Hamid | Top: [green 5] | Top color: green

Your hand:  
[0] [blue 5]  
[1] [red Skip]  
[2] [yellow 2]  
[3] [green 7]  
[4] [red 7]  
[5] [blue Reverse]  
[6] [yellow +2]

Enter index or -1 to draw: 3

Hamid plays [green 7]

Turn: ZahraSh | Top: [green 7] | Top color: green  
ZahraSh plays [green Skip] ...

* Colors in the console are represented with ANSI escape codes (e.g., `\033[1;31m` for red). If your terminal does not support ANSI, cards will appear without color formatting.
* Bot moves will appear with a slight “typing” animation. You can adjust or remove the `slowPrint` delay in `slowPrint(const string&, int)` if you prefer immediate output.

---

## 📦 Dependencies & Configuration

1. **C++ Standard Library**

   * `<vector>`, `<string>`, `<memory>`, `<cstdlib>`, `<ctime>`, `<algorithm>`, `<chrono>`, `<thread>`, `<iostream>`.
   * All utilized classes and methods are part of the C++11 (or newer) standard. No additional external libraries are required.

2. **Terminal Color Support**

   * Uses ANSI escape sequences for colored text (macOS/Linux terminals and Windows Terminal).
   * If running on Windows’ native Command Prompt (cmd.exe) without ANSI support, colors may not render correctly. Consider using a terminal emulator that supports ANSI or comment out/modify color macros in the code.

3. **Randomization Seed**

   * `deck::shuffle()` calls `srand(time(0))` to seed the RNG. Each run will produce a differently shuffled deck. For reproducible shuffles, you can replace `srand(time(0))` with a fixed seed (e.g., `srand(12345)`).

---

## ⚙️ How to Extend or Modify

* **Add More Players**

  * By default, `main()` creates three players:

    players.push_back(make_shared<HumanPlayer>("Hamid"));
    players.push_back(make_shared<BotPlayer>("ZahraSh"));
    players.push_back(make_shared<BotPlayer>("Zahra"));
    
  * To add more human or bot players, simply push additional `make_shared<HumanPlayer>("Name")` or `make_shared<BotPlayer>("Name")` into the `players` vector (up to a maximum of 10 players).

* **Change Starting Hand Size**

  * In `Manager::StartGame()`, each player is dealt 7 cards. Modify the loop range to change the initial hand size (e.g., `for (int i = 0; i < 5; ++i)` for 5 cards each).

* **Customize Bot Behavior**

  * The current bot strategy is simplistic (play first playable card). You can override `BotPlayer::ChooseCard(...)` and/or `BotPlayer::ChooseColor()` to implement more advanced heuristics or AI strategies.

* **Separate Source Files**

  * For larger projects or cleaner architecture, consider splitting classes into separate header (`.hpp`) and source (`.cpp`) files. For example:

    src/
      card.hpp
      card.cpp
      player.hpp
      player.cpp
      deck.hpp
      deck.cpp
      manager.hpp
      manager.cpp
      main.cpp

* **Optional Features to Add**

  * **UNO Callout Warning**: In real UNO, players must say “UNO” when down to one card. You can add logic to prompt the human player to type “UNO” when they have one card left.
  * **Score Tracking**: Keep track of points according to UNO rules (e.g., number cards are worth their face value, action cards are 20 points, wild cards are 50 points). Play multiple rounds and sum scores.
  * **Multiplayer Over Network**: Extend the `Manager` and `Player` classes to communicate over sockets, allowing remote players to connect.
  * **Graphical User Interface (GUI)**: Port the logic to a GUI framework (e.g., Qt, SFML) and render cards graphically.

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! If you’d like to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeatureName`).
3. Make your changes and commit them with clear messages.
4. Push to your branch (`git push origin feature/YourFeatureName`).
5. Open a Pull Request describing your changes and why they improve the project.

Please ensure your code adheres to the existing style conventions (naming, indentation) and compiles cleanly with `-std=c++11 -pthread`.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute it. See the `LICENSE` file for full details.

---

## 👤 Author & Contact

* **Repository:** [Text-Based UNO Game in C++](https://github.com/Hamidreza-ahd/TextBasedUNO-Cpp)
* **Email:** `hmd.ahd85@gmail.com`
* **Instagram:** [@haamidreza\_ahd](https://instagram.com/haamidreza_ahd)

Enjoy playing UNO in your terminal, and happy coding!

```
```
