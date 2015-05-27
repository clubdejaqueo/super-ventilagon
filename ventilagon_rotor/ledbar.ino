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

void Ledbar::draw(byte num_row, boolean value) {
  const long BLUE = 0xffff00;
  long color;
  if (num_row == ROW_NAVE) {
    color = value ? BLUE : colorizer.color2;
  } else {
    color = value ? colorizer.color1 : colorizer.color2;
  }
  setPixelColor(num_row, color);
}

void Ledbar::update() {
  Tlc.update();
}
