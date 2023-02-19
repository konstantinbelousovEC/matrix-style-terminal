#include "ui.h"

UI::UI() : ui_window_(initscr()) {
    start_color();
    if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
        std::cerr << "Your terminal does not support this program"s << "\n"s;
    }
    set_colors();
}

void UI::CleanUpUI() {
    delwin(ui_window_);
    endwin();
    refresh();
}

void UI::set_colors() const {
    for (int16_t i = 0; i < 8; ++i) {
        init_pair(i + 1, i, COLOR_BLACK);
    }
    for (int16_t i = 0; i <= 5; ++i) {
        init_color(i, 0, i * 200, 0);
    }
    init_color(6, 800, 1000, 800);
}