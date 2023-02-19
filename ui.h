#pragma once
#include "curses.h"
#include <iostream>

using namespace std::literals;

class UI {
public:
    UI();
    void CleanUpUI();
private:
    WINDOW* ui_window_ = nullptr;
    void set_colors() const;
};