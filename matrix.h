#pragma once

#include "curses.h"
#include <vector>
#include <array>

struct Settings {
    int max_x = 160;
    int max_y = 50;
    int max_intensity = 13;
    int min_intensity = 4;
    int drips_num = 250;
    int printable_characters = 92;
    double drip_spawn_probability = 0.65;
    double change_probability = 0.95;
    double dim_probability = 0.55;
};

struct Cell {
    char char_value_;
    int intensity_;
};

struct Drip {
    int x, y;
    bool live, bright;
};

class Matrix {
public:
    explicit Matrix(Settings settings = Settings{});

    void UpdateMatrix();
    void ShowMatrix();
private:
    std::vector<std::vector<Cell>> matrix_;
    std::vector<Drip> drips_;
    constexpr static Settings settings_;
    std::array<int, settings_.max_intensity + 1> color_map_ = {1,2,2,3,3,3,4,4,4,4,4,5,3,6};

    void UpdateDrips();
    double RandomProbability();
    char RandomPrintableCharacter();
    void TryAddDrips();
    void FadeNChangeMatrix();
};