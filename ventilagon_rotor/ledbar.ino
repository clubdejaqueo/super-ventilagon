#include <Tlc5940.h>

Ledbar ledbar;

void Ledbar::setPixelColor(int pixel, long color) {
  byte red = (color >> 16) & 0xff;
  byte green = (color >> 8) & 0xff;
  byte blue = (color >> 0) & 0xff;
  byte base = pixel * 3;
  Tlc.set(base + 0, (blue << 4));
  Tlc.set(base + 1, (green << 4));
  Tlc.set(base + 2, (red << 4));
}

void Ledbar::init() {
  debugln("INIT LEDBAR");
  Tlc.init();
  clear();
}

void Ledbar::clear() {
  Tlc.clear();
}

const long BLACK = 0x000000;

void Ledbar::draw(byte num_row, boolean value) {
  long color;
  if (num_row == ROW_SHIP) {
    color = value ? current_level.calibrate_color : BLACK;
  } else {
    color = value ? current_level.color : BLACK;
  }
  setPixelColor(num_row, color);
//  debug("row: ");
//  debug(num_row);
//  debug(" color: ");
//  debugln(color, HEX);
}

void Ledbar::update() {
//  debugln("updating tlc");
  Tlc.update();
}
