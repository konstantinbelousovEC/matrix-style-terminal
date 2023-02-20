#include "matrix.h"

Matrix::Matrix(Settings settings) {
    matrix_.resize(settings_.max_x);
    for (auto& v : matrix_) {
        v.resize(settings_.max_y);
        for (auto& cell : v) {
            cell.char_value_ = 0;
            cell.intensity_ = 0;
        }
    }

    drips_.resize(settings_.drips_num);
    for (auto& drip : drips_) {
        drip.live = false;
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
    for (auto& drip : drips_) {
        if (drip.live) {
            if (drip.bright) {
                matrix_[drip.x][drip.y].intensity_ = settings_.max_intensity;
            } else {
                matrix_[drip.x][drip.y].intensity_ = settings_.min_intensity;
            }
            if (++drip.y >= settings_.max_y) {
                drip.live = false;
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
    for (auto& drip : drips_) {
        if (!drip.live) {
            drip.live = true;
            drip.x = rand() % settings_.max_x;
            drip.y = 0; // drips[i].y = rand() % MAXY;
            drip.bright = rand() % 2;
            return;
        }
    }
}

void Matrix::FadeNChangeMatrix() {
    for (auto& v : matrix_) {
        for (auto& cell : v) {
            if (RandomProbability() < settings_.change_probability || cell.char_value_ == 0) {
                cell.char_value_ = RandomPrintableCharacter();
            }
            if (RandomProbability() < settings_.dim_probability) {
                if (cell.intensity_ > 0) {
                    cell.intensity_--;
                }
            }
        }
    }
}
