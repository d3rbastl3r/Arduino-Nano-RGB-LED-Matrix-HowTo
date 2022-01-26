#include "RgbLedMatrixCtrl.cpp"

RgbLedMatrixCtrl rgbLedMatrixCtrl;

int main() {
    while(true) {
        rgbLedMatrixCtrl.draw();
    }

    return 0;
}
