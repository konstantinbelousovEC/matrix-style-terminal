#include "ui.h"
#include "matrix.h"
#include <unistd.h>

#define REFRESH_DELAY 50000L

int main() {
    UI ui;
    Matrix matrix;
    while (true) {
        matrix.UpdateMatrix();
        matrix.ShowMatrix();
        usleep(REFRESH_DELAY);
    }
}
