// The following two changes are needed in Tlc5940/tlc_config.h
// to enable grayscales:
//
//#define TLC_PWM_PERIOD    2048
//#define TLC_GSCLK_PERIOD    1
//

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

const long RED = 0xff0000;

void Ledbar::draw(byte num_row, boolean value, boolean alt_column) {
  long color;
  if (num_row == ROW_SHIP && value) {
    color = RED;
  } else {
    if (value) {
      color = current_level.color;
    } else { 
      color = alt_column ? current_level.bg1 : current_level.bg2;
    }
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
