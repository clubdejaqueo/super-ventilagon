#include <Tlc5940.h>

Ledbar ledbar;

void Ledbar::setPixelColor(int pixel, long color) {
  byte red = (color >> 16) & 0xff;
  byte green = (color >> 8) & 0xff;
  byte blue = (color >> 0) & 0xff;
  byte base = pixel * 3;
  Tlc.set(base + 0, blue << 4 + 0xf);
  Tlc.set(base + 1, green << 4 + 0xf);
  Tlc.set(base + 2, red << 4 + 0xf);
}

void Ledbar::init() {
  Tlc.init();
  clear();
}

void Ledbar::clear() {
  Tlc.clear();
}

const long BLACK = 0x000000;
const long WALL_COLOR = 0x00ffff;
const long CALIBRATE_COLOR = 0xff0000;

void Ledbar::draw(byte num_row, boolean value) {
  long color;
  if (num_row == ROW_SHIP) {
    color = value ? CALIBRATE_COLOR : BLACK;
  } else {
    color = value ? WALL_COLOR : BLACK;
  }
  setPixelColor(num_row, color);
}

void Ledbar::update() {
  Tlc.update();
}
