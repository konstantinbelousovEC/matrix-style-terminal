#pragma once
#include "curses.h"
#include <iostream>

#define MAXX 160
#define MAXY 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

using namespace std::literals;

class UI {
public:
    UI() : ui_window_(initscr()) {
        start_color();
        if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
            std::cerr << "Your terminal does not support this program"s << "\n"s;
        }

        set_colors();
    }

    void CleanUpUI() {
        delwin(ui_window_);
        endwin();
        refresh();
    }
private:
    WINDOW* ui_window_ = nullptr;
    void set_colors() {
        for (int i = 0; i < 8; ++i) {
            init_pair(i + 1, i, COLOR_BLACK);
        }
        for (int i = 0; i <= 5; ++i) {
            init_color(i, 0, i * 200, 0);
        }
        init_color(6, 800, 1000, 800);
    }
};