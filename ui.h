#pragma once

#define MAXX 160
#define MAXY 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

struct cell {
    char char_value;
    int intensity;
};

extern cell matrix[MAXX][MAXY];

bool init_ui();
void cleanup_ui();
void show_matrix();