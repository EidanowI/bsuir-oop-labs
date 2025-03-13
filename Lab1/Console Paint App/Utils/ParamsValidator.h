#pragma once
#include "../Canvas/Canvas.h"


bool ValidateHorizPosition(int param) {
    if (param >= 0 && param < WIDTH) {
        return true;
    }
    return false;
}
bool ValidateVerticalPosition(int param) {
    if (param >= 0 && param < HEIGHT) {
        return true;
    }
    return false;
}

bool ValidateellipseParams(int x, int y, int a, int b) {
    if (!ValidateHorizPosition(x)) return false;
    if (!ValidateVerticalPosition(y)) return false;

    if (a <= 0) return false;
    if (b <= 0) return false;

    return true;
}