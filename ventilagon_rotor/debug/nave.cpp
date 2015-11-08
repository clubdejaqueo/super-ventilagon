#include <stdio.h>
#include <stdlib.h>

const int SUBDEGREES = 256;
const int SUBDEGREES_MASK = 255;
const int SHIP_WIDTH = 6;

bool func(int current_pos, int nave_pos) {

    if (abs(nave_pos - current_pos) < (SHIP_WIDTH / 2)) {
        return true;
    }
    if (abs( ((nave_pos + SUBDEGREES / 2) & SUBDEGREES_MASK) - 
        ((current_pos + SUBDEGREES / 2) & SUBDEGREES_MASK))
        < (SHIP_WIDTH / 2)) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    for (int i=0; i<SUBDEGREES; i++) {
        for (int n=0; n<SUBDEGREES; n++) {
            printf(func(n, i)?"*":"-");
        }
        printf("\n");
    }
}
