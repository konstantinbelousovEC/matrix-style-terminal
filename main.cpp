#include "ui.h"
#include "matrix.h"

#include <unistd.h>

#define REFRESH_DELAY 50000L
#define MAXX 160
#define MAXY 50
#define NUM_DRIPS 250

int main() {

    UI ui;
    Matrix matrix{MAXX, MAXY, NUM_DRIPS};
    while (true) {
        matrix.UpdateMatrix();
        matrix.ShowMatrix();
        usleep(REFRESH_DELAY);
    }
}
