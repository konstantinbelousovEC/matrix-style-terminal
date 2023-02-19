#pragma once

#include "curses.h"
#include <vector>

#define MAXX 160
#define MAXY 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

#define NUM_DRIPS 250
#define PROB_DRIP_SPAWN 0.65
#define PROB_CHANGE 0.95
#define RANDOM_PRINTABLE_CHARACTER ( 33 + (rand() % 80) )
#define PROB_DIM 0.55

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
    Matrix(int max_x, int max_y, int drips_num) {
        matrix_.resize(max_x);
        for (int x = 0; x < max_x; x++) {
            matrix_[x].resize(max_y);
            for (int y = 0; y < max_y; y++) {
                matrix_[x][y].char_value_ = 0;
                matrix_[x][y].intensity_ = 0;
            }
        }

        drips_.resize(drips_num);
        for (int i = 0; i < drips_num; i++) {
            drips_[i].live = false;
        }
    }

    void UpdateMatrix() {
        if (Rand01() < PROB_DRIP_SPAWN) {
            TryAddDrips();
        }
        UpdateDrips();
        FadeNChangeMatrix();
    }

    void ShowMatrix() {
        for (int x = 0; x < MAXX; x++) {
            for (int y = 0; y < MAXY; y++) {
                int intensity = matrix_[x][y].intensity_;
                color_set(color_map_[intensity], NULL);
                mvaddch(y, x, matrix_[x][y].char_value_);
            }
        }
        refresh();
    }
private:
    std::vector<std::vector<Cell>> matrix_;
    std::vector<Drip> drips_;
    int color_map_[MAX_INTENSITY + 1] = {1,2,2,3,3,3,4,4,4,4, 4,5,3,6};

    void UpdateDrips() {
        for (int i = 0; i < NUM_DRIPS; i++) {
            if (drips_[i].live == true) {
                if (drips_[i].bright == true) {
                    matrix_[drips_[i].x][drips_[i].y].intensity_ = MAX_INTENSITY;
                } else {
                    matrix_[drips_[i].x][drips_[i].y].intensity_ = MIN_INTENSITY;
                }
                if (++drips_[i].y >= MAXY) {
                    drips_[i].live = false;
                }
            }
        }
    }
    double Rand01() {
        return (double)rand() / (double)RAND_MAX;
    }
    void TryAddDrips() {
        for (int i = 0; i < NUM_DRIPS; i++) {
            if (drips_[i].live == false) {
                drips_[i].live = true;
                drips_[i].x = rand() % MAXX;
                drips_[i].y = 0; // drips[i].y = rand() % MAXY;
                drips_[i].bright = rand() % 2;
                return;
            }
        }
    }
    void FadeNChangeMatrix() {
        for (int x = 0; x < MAXX; x++) {
            for (int y = 0; y < MAXY; y++) {
                if (Rand01() < PROB_CHANGE || matrix_[x][y].char_value_ == 0) {
                    matrix_[x][y].char_value_ = RANDOM_PRINTABLE_CHARACTER;
                }
                if (Rand01() < PROB_DIM) {
                    if (matrix_[x][y].intensity_ > 0) {
                        matrix_[x][y].intensity_--;
                    }
                }
            }
        }
    }
};