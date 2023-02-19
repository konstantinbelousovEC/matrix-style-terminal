#include "matrix.h"

Matrix::Matrix(Settings settings) {
    matrix_.resize(settings_.max_x);
    for (int x = 0; x < settings_.max_x; x++) {
        matrix_[x].resize(settings_.max_y);
        for (int y = 0; y < settings_.max_y; y++) {
            matrix_[x][y].char_value_ = 0;
            matrix_[x][y].intensity_ = 0;
        }
    }

    drips_.resize(settings_.drips_num);
    for (int i = 0; i < settings_.drips_num; i++) {
        drips_[i].live = false;
    }
}

void Matrix::UpdateMatrix() {
    if (RandomProbability() < settings_.drip_spawn_probability) {
        TryAddDrips();
    }
    UpdateDrips();
    FadeNChangeMatrix();
}

void Matrix::ShowMatrix() {
    for (int x = 0; x < settings_.max_x; x++) {
        for (int y = 0; y < settings_.max_y; y++) {
            int intensity = matrix_[x][y].intensity_;
            color_set(color_map_[intensity], nullptr);
            mvaddch(y, x, matrix_[x][y].char_value_);
        }
    }
    refresh();
}

void Matrix::UpdateDrips() {
    for (int i = 0; i < settings_.drips_num; i++) {
        if (drips_[i].live == true) {
            if (drips_[i].bright == true) {
                matrix_[drips_[i].x][drips_[i].y].intensity_ = settings_.max_intensity;
            } else {
                matrix_[drips_[i].x][drips_[i].y].intensity_ = settings_.min_intensity;
            }
            if (++drips_[i].y >= settings_.max_y) {
                drips_[i].live = false;
            }
        }
    }
}

double Matrix::RandomProbability() {
    return (double)rand() / (double)RAND_MAX;
}

char Matrix::RandomPrintableCharacter() {
    return 33 + (rand() % settings_.printable_characters);
}

void Matrix::TryAddDrips() {
    for (int i = 0; i < settings_.drips_num; i++) {
        if (drips_[i].live == false) {
            drips_[i].live = true;
            drips_[i].x = rand() % settings_.max_x;
            drips_[i].y = 0; // drips[i].y = rand() % MAXY;
            drips_[i].bright = rand() % 2;
            return;
        }
    }
}

void Matrix::FadeNChangeMatrix() {
    for (int x = 0; x < settings_.max_x; x++) {
        for (int y = 0; y < settings_.max_y; y++) {
            if (RandomProbability() < settings_.change_probability || matrix_[x][y].char_value_ == 0) {
                matrix_[x][y].char_value_ = RandomPrintableCharacter();
            }
            if (RandomProbability() < settings_.dim_probability) {
                if (matrix_[x][y].intensity_ > 0) {
                    matrix_[x][y].intensity_--;
                }
            }
        }
    }
}
