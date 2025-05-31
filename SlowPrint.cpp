#include "SlowPrint.h"

void slowPrint(string &text, int msDelay) {
    text += "\n";
    for (char c: text) {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(msDelay));
    }
}