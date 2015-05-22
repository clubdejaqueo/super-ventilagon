#include "Tlc5940.h"

const byte NUM_COLUMNS = 6;
const byte NUM_ROWS = 32;
const byte HALL_SENSOR = 2;

const byte ROW_NAVE = 3;
const byte ROW_COLISION = 7;

const int SUBDEGREES = 360 * 16;
const int NAVE_WIDTH = SUBDEGREES / 30;

const byte NAVE_PIN_R = 7;
const byte NAVE_PIN_G = 5;
const byte NAVE_PIN_B = 4;

int nave_pos = 360;

class State {
public:
    static State* current_state;
    static void change_state(State* new_state);
    virtual const char* name() = 0;
    virtual void setup() = 0;
    virtual void loop() {}
};

void State::change_state (State* new_state) {
#ifdef DEBUG
    Serial.println(new_state->name());
#endif
    State::current_state = new_state;
    State::current_state->setup();
}

class GameoverState : public State {
protected:
public:
    const char* name() {
      return "Game Over";
    }
    void apagar_todo();
    void setup();
    void loop();
} gameover_state;

class PlayState : public State {
public:
    const char* name() {
      return "Running Game";
    }
    void setup();
    void loop();
} play_state;

class Pattern {
public:
  byte len;
  prog_uchar* rows;
  
  Pattern(byte len, prog_uchar* rows) : len(len), rows(rows) {
  }
  
  inline byte get_row(byte offset) {
    return pgm_read_byte(rows + offset);
  }
};


// Precalculated transformations
// 64 row combinations
// times 6 possible rotations
// times 2 mirrored options = 768 bytes

PROGMEM prog_uchar transformations[] = {
  // Mirrored: no
  // Rotated: 0
  0b000000, 0b000001, 0b000010, 0b000011, 0b000100, 0b000101, 0b000110, 0b000111, 0b001000, 0b001001, 0b001010, 0b001011, 0b001100, 0b001101, 0b001110, 0b001111, 0b010000, 0b010001, 0b010010, 0b010011, 0b010100, 0b010101, 0b010110, 0b010111, 0b011000, 0b011001, 0b011010, 0b011011, 0b011100, 0b011101, 0b011110, 0b011111, 0b100000, 0b100001, 0b100010, 0b100011, 0b100100, 0b100101, 0b100110, 0b100111, 0b101000, 0b101001, 0b101010, 0b101011, 0b101100, 0b101101, 0b101110, 0b101111, 0b110000, 0b110001, 0b110010, 0b110011, 0b110100, 0b110101, 0b110110, 0b110111, 0b111000, 0b111001, 0b111010, 0b111011, 0b111100, 0b111101, 0b111110, 0b111111,
  // Rotated: 1
  0b000000, 0b000010, 0b000100, 0b000110, 0b001000, 0b001010, 0b001100, 0b001110, 0b010000, 0b010010, 0b010100, 0b010110, 0b011000, 0b011010, 0b011100, 0b011110, 0b100000, 0b100010, 0b100100, 0b100110, 0b101000, 0b101010, 0b101100, 0b101110, 0b110000, 0b110010, 0b110100, 0b110110, 0b111000, 0b111010, 0b111100, 0b111110, 0b000001, 0b000011, 0b000101, 0b000111, 0b001001, 0b001011, 0b001101, 0b001111, 0b010001, 0b010011, 0b010101, 0b010111, 0b011001, 0b011011, 0b011101, 0b011111, 0b100001, 0b100011, 0b100101, 0b100111, 0b101001, 0b101011, 0b101101, 0b101111, 0b110001, 0b110011, 0b110101, 0b110111, 0b111001, 0b111011, 0b111101, 0b111111,
  // Rotated: 2
  0b000000, 0b000100, 0b001000, 0b001100, 0b010000, 0b010100, 0b011000, 0b011100, 0b100000, 0b100100, 0b101000, 0b101100, 0b110000, 0b110100, 0b111000, 0b111100, 0b000001, 0b000101, 0b001001, 0b001101, 0b010001, 0b010101, 0b011001, 0b011101, 0b100001, 0b100101, 0b101001, 0b101101, 0b110001, 0b110101, 0b111001, 0b111101, 0b000010, 0b000110, 0b001010, 0b001110, 0b010010, 0b010110, 0b011010, 0b011110, 0b100010, 0b100110, 0b101010, 0b101110, 0b110010, 0b110110, 0b111010, 0b111110, 0b000011, 0b000111, 0b001011, 0b001111, 0b010011, 0b010111, 0b011011, 0b011111, 0b100011, 0b100111, 0b101011, 0b101111, 0b110011, 0b110111, 0b111011, 0b111111,
  // Rotated: 3
  0b000000, 0b001000, 0b010000, 0b011000, 0b100000, 0b101000, 0b110000, 0b111000, 0b000001, 0b001001, 0b010001, 0b011001, 0b100001, 0b101001, 0b110001, 0b111001, 0b000010, 0b001010, 0b010010, 0b011010, 0b100010, 0b101010, 0b110010, 0b111010, 0b000011, 0b001011, 0b010011, 0b011011, 0b100011, 0b101011, 0b110011, 0b111011, 0b000100, 0b001100, 0b010100, 0b011100, 0b100100, 0b101100, 0b110100, 0b111100, 0b000101, 0b001101, 0b010101, 0b011101, 0b100101, 0b101101, 0b110101, 0b111101, 0b000110, 0b001110, 0b010110, 0b011110, 0b100110, 0b101110, 0b110110, 0b111110, 0b000111, 0b001111, 0b010111, 0b011111, 0b100111, 0b101111, 0b110111, 0b111111,
  // Rotated: 4
  0b000000, 0b010000, 0b100000, 0b110000, 0b000001, 0b010001, 0b100001, 0b110001, 0b000010, 0b010010, 0b100010, 0b110010, 0b000011, 0b010011, 0b100011, 0b110011, 0b000100, 0b010100, 0b100100, 0b110100, 0b000101, 0b010101, 0b100101, 0b110101, 0b000110, 0b010110, 0b100110, 0b110110, 0b000111, 0b010111, 0b100111, 0b110111, 0b001000, 0b011000, 0b101000, 0b111000, 0b001001, 0b011001, 0b101001, 0b111001, 0b001010, 0b011010, 0b101010, 0b111010, 0b001011, 0b011011, 0b101011, 0b111011, 0b001100, 0b011100, 0b101100, 0b111100, 0b001101, 0b011101, 0b101101, 0b111101, 0b001110, 0b011110, 0b101110, 0b111110, 0b001111, 0b011111, 0b101111, 0b111111,
  // Rotated: 5
  0b000000, 0b100000, 0b000001, 0b100001, 0b000010, 0b100010, 0b000011, 0b100011, 0b000100, 0b100100, 0b000101, 0b100101, 0b000110, 0b100110, 0b000111, 0b100111, 0b001000, 0b101000, 0b001001, 0b101001, 0b001010, 0b101010, 0b001011, 0b101011, 0b001100, 0b101100, 0b001101, 0b101101, 0b001110, 0b101110, 0b001111, 0b101111, 0b010000, 0b110000, 0b010001, 0b110001, 0b010010, 0b110010, 0b010011, 0b110011, 0b010100, 0b110100, 0b010101, 0b110101, 0b010110, 0b110110, 0b010111, 0b110111, 0b011000, 0b111000, 0b011001, 0b111001, 0b011010, 0b111010, 0b011011, 0b111011, 0b011100, 0b111100, 0b011101, 0b111101, 0b011110, 0b111110, 0b011111, 0b111111,
  // Mirrored: yes
  // Rotated: 0
  0b000000, 0b100000, 0b010000, 0b110000, 0b001000, 0b101000, 0b011000, 0b111000, 0b000100, 0b100100, 0b010100, 0b110100, 0b001100, 0b101100, 0b011100, 0b111100, 0b000010, 0b100010, 0b010010, 0b110010, 0b001010, 0b101010, 0b011010, 0b111010, 0b000110, 0b100110, 0b010110, 0b110110, 0b001110, 0b101110, 0b011110, 0b111110, 0b000001, 0b100001, 0b010001, 0b110001, 0b001001, 0b101001, 0b011001, 0b111001, 0b000101, 0b100101, 0b010101, 0b110101, 0b001101, 0b101101, 0b011101, 0b111101, 0b000011, 0b100011, 0b010011, 0b110011, 0b001011, 0b101011, 0b011011, 0b111011, 0b000111, 0b100111, 0b010111, 0b110111, 0b001111, 0b101111, 0b011111, 0b111111,
  // Rotated: 1
  0b000000, 0b010000, 0b001000, 0b011000, 0b000100, 0b010100, 0b001100, 0b011100, 0b000010, 0b010010, 0b001010, 0b011010, 0b000110, 0b010110, 0b001110, 0b011110, 0b000001, 0b010001, 0b001001, 0b011001, 0b000101, 0b010101, 0b001101, 0b011101, 0b000011, 0b010011, 0b001011, 0b011011, 0b000111, 0b010111, 0b001111, 0b011111, 0b100000, 0b110000, 0b101000, 0b111000, 0b100100, 0b110100, 0b101100, 0b111100, 0b100010, 0b110010, 0b101010, 0b111010, 0b100110, 0b110110, 0b101110, 0b111110, 0b100001, 0b110001, 0b101001, 0b111001, 0b100101, 0b110101, 0b101101, 0b111101, 0b100011, 0b110011, 0b101011, 0b111011, 0b100111, 0b110111, 0b101111, 0b111111,
  // Rotated: 2
  0b000000, 0b001000, 0b000100, 0b001100, 0b000010, 0b001010, 0b000110, 0b001110, 0b000001, 0b001001, 0b000101, 0b001101, 0b000011, 0b001011, 0b000111, 0b001111, 0b100000, 0b101000, 0b100100, 0b101100, 0b100010, 0b101010, 0b100110, 0b101110, 0b100001, 0b101001, 0b100101, 0b101101, 0b100011, 0b101011, 0b100111, 0b101111, 0b010000, 0b011000, 0b010100, 0b011100, 0b010010, 0b011010, 0b010110, 0b011110, 0b010001, 0b011001, 0b010101, 0b011101, 0b010011, 0b011011, 0b010111, 0b011111, 0b110000, 0b111000, 0b110100, 0b111100, 0b110010, 0b111010, 0b110110, 0b111110, 0b110001, 0b111001, 0b110101, 0b111101, 0b110011, 0b111011, 0b110111, 0b111111,
  // Rotated: 3
  0b000000, 0b000100, 0b000010, 0b000110, 0b000001, 0b000101, 0b000011, 0b000111, 0b100000, 0b100100, 0b100010, 0b100110, 0b100001, 0b100101, 0b100011, 0b100111, 0b010000, 0b010100, 0b010010, 0b010110, 0b010001, 0b010101, 0b010011, 0b010111, 0b110000, 0b110100, 0b110010, 0b110110, 0b110001, 0b110101, 0b110011, 0b110111, 0b001000, 0b001100, 0b001010, 0b001110, 0b001001, 0b001101, 0b001011, 0b001111, 0b101000, 0b101100, 0b101010, 0b101110, 0b101001, 0b101101, 0b101011, 0b101111, 0b011000, 0b011100, 0b011010, 0b011110, 0b011001, 0b011101, 0b011011, 0b011111, 0b111000, 0b111100, 0b111010, 0b111110, 0b111001, 0b111101, 0b111011, 0b111111,
  // Rotated: 4
  0b000000, 0b000010, 0b000001, 0b000011, 0b100000, 0b100010, 0b100001, 0b100011, 0b010000, 0b010010, 0b010001, 0b010011, 0b110000, 0b110010, 0b110001, 0b110011, 0b001000, 0b001010, 0b001001, 0b001011, 0b101000, 0b101010, 0b101001, 0b101011, 0b011000, 0b011010, 0b011001, 0b011011, 0b111000, 0b111010, 0b111001, 0b111011, 0b000100, 0b000110, 0b000101, 0b000111, 0b100100, 0b100110, 0b100101, 0b100111, 0b010100, 0b010110, 0b010101, 0b010111, 0b110100, 0b110110, 0b110101, 0b110111, 0b001100, 0b001110, 0b001101, 0b001111, 0b101100, 0b101110, 0b101101, 0b101111, 0b011100, 0b011110, 0b011101, 0b011111, 0b111100, 0b111110, 0b111101, 0b111111,
  // Rotated: 5
  0b000000, 0b000001, 0b100000, 0b100001, 0b010000, 0b010001, 0b110000, 0b110001, 0b001000, 0b001001, 0b101000, 0b101001, 0b011000, 0b011001, 0b111000, 0b111001, 0b000100, 0b000101, 0b100100, 0b100101, 0b010100, 0b010101, 0b110100, 0b110101, 0b001100, 0b001101, 0b101100, 0b101101, 0b011100, 0b011101, 0b111100, 0b111101, 0b000010, 0b000011, 0b100010, 0b100011, 0b010010, 0b010011, 0b110010, 0b110011, 0b001010, 0b001011, 0b101010, 0b101011, 0b011010, 0b011011, 0b111010, 0b111011, 0b000110, 0b000111, 0b100110, 0b100111, 0b010110, 0b010111, 0b110110, 0b110111, 0b001110, 0b001111, 0b101110, 0b101111, 0b011110, 0b011111, 0b111110, 0b111111,
};

// 20 rows
PROGMEM prog_uchar pat0[] = {
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B100111, 0B100111, 0B100111, 0B100111, 
  0B110011, 0B110011, 0B110011, 0B110011, 
  0B111001, 0B111001, 0B111001, 0B111001, 
  0B111100, 0B111100, 0B111100, 0B111100, 
  0B011110, 0B011110, 0B011110, 0B011110, 
  0B001111, 0B001111, 0B001111, 0B001111, 
  0B100111, 0B100111, 0B100111, 0B100111, 
  0B110011, 0B110011, 0B110011, 0B110011, 
  0B111001, 0B111001, 0B111001, 0B111001, 
  0B111100, 0B111100, 0B111100, 0B111100, 
  0B011110, 0B011110, 0B011110, 0B011110, 
  0B001111, 0B001111, 0B001111, 0B001111, 
  0B100111, 0B100111, 0B100111, 0B100111, 
  0B110011, 0B110011, 0B110011, 0B110011, 
  0B111001, 0B111001, 0B111001, 0B111001, 
  0B111100, 0B111100, 0B111100, 0B111100, 
  0B011110, 0B011110, 0B011110, 0B011110, 
  0B001111, 0B001111, 0B001111, 0B001111, 
  0B000000, 0B000000, 0B000000, 0B000000, 
};

// 12 rows
PROGMEM prog_uchar pat1[] = {
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B101111, 0B101111, 0B101111, 0B101111, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B111101, 0B111101, 0B111101, 0B111101, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B101111, 0B101111, 0B101111, 0B101111, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
};

// 11 rows
PROGMEM prog_uchar pat2[] = {
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B110110, 0B110110, 0B110110, 0B110110, 
  0B010010, 0B010010, 0B010010, 0B010010, 
  0B011011, 0B011011, 0B011011, 0B011011, 
  0B010010, 0B010010, 0B010010, 0B010010, 
  0B110110, 0B110110, 0B110110, 0B110110, 
  0B010010, 0B010010, 0B010010, 0B010010, 
  0B011011, 0B011011, 0B011011, 0B011011, 
  0B010010, 0B010010, 0B010010, 0B010010, 
  0B110110, 0B110110, 0B110110, 0B110110, 
  0B000000, 0B000000, 0B000000, 0B000000, 
};

// 10 rows
PROGMEM prog_uchar pat3[] = {
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B010010, 0B010010, 0B010010, 0B010010, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B101010, 0B101010, 0B101010, 0B101010, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B010101, 0B010101, 0B010101, 0B010101, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B101110, 0B101110, 0B101110, 0B101110, 
  0B000000, 0B000000, 0B000000, 0B000000, 
};

// 9 rows
PROGMEM prog_uchar pat4[] = {
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000001, 0B000001, 0B000001, 0B000001, 
  0B000010, 0B000010, 0B000010, 0B000010, 
  0B000100, 0B000100, 0B000100, 0B000100, 
  0B001000, 0B001000, 0B001000, 0B001000, 
  0B010000, 0B010000, 0B010000, 0B010000, 
  0B100000, 0B100000, 0B100000, 0B100000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
  0B000000, 0B000000, 0B000000, 0B000000, 
};

Pattern all_patterns[] = {
  Pattern(sizeof(pat0), pat0),
  Pattern(sizeof(pat1), pat1),
  Pattern(sizeof(pat2), pat2),
  Pattern(sizeof(pat3), pat3),
  Pattern(sizeof(pat4), pat4),
};

#define elements_in(arrayname) (sizeof arrayname/sizeof *arrayname)

const long color_table[] = {
//  0xff0000,
//  0xffff00,
//  0x00ff00,
//  0xffff00,
//  0x0000ff,
//  0x00ff00,
  0x00ffff,
//  0x808000,
//  0x404000,
};

class Colorizer {
  volatile byte pos;
  byte plof;
public:
  long color1;
  long color2;
  Colorizer() {
    plof = 0;
    color1 = color_table[0];
    color2 = 0x000000;
  }
  void step() {
    pos++;
    color1 = color_table[(pos>>4)%elements_in(color_table)];

    /*
    if ((plof++)==7) {
      plof = 0;
      pos++;
      color1 = color_table[pos%elements_in(color_table)];
    }
    */
  } 
};

Colorizer colorizer;

class CircularBuffer {
  byte buffer[NUM_ROWS];
  byte first_row;
public:
  CircularBuffer() {
    reset();
  }
  void reset() {
    first_row = 0;
    int n;
    for (n=0; n<NUM_ROWS; n++) {
      buffer[n] = 0;
    }  
  }
  void push(byte row) {
    cli();
    buffer[first_row] = row;
    first_row = (first_row + 1) % NUM_ROWS;
    sei();
  }
  byte get_row(byte row_num) {
    byte pos = (row_num + first_row) % NUM_ROWS;
    return buffer[pos];
  }
};

class Ledbar {
  void setPixelColor(int pixel, long color) {
    byte red = (color >> 16) & 0xff;
    byte green = (color >> 8) & 0xff;
    byte blue = (color >> 0) & 0xff;
    byte base = pixel * 3;
    Tlc.set(base + 0, blue<<4);
    Tlc.set(base + 1, green<<4);
    Tlc.set(base + 2, red<<4);
  }

public:
  boolean alt_row;
  
  void init() {
    Tlc.init();
    clear();
  }
  
  void clear() {
    Tlc.clear();
  }
  
  void draw(byte num_row, boolean value) {
    const long BLUE = 0xffff00;
    long color;
    if (num_row == ROW_NAVE) {
      color = value ? BLUE : colorizer.color2;
    } else {
      color = value ? colorizer.color1 : colorizer.color2;
    }
    setPixelColor(num_row, color);
  }
  
  void update() {
    Tlc.update();
  }
  
};

class Board {
  CircularBuffer visible;
  byte first_row;
  Pattern& pat;
  byte pat_offset;
  int transformation_base;
  
public:

  Board(): pat(random_pattern()) {
    reset();
  }
  
  void reset() {
    first_row = 0;
    pat = random_pattern();
    visible.reset();    
  }
  
  Pattern& random_pattern() {
    visible.push(0);
    visible.push(0);
    visible.push(0);
    visible.push(0);
    transformation_base = random(0, 12) << 6;
    return all_patterns[random(0, elements_in(all_patterns))];
  }
  
  byte transform(byte b) {
    return pgm_read_byte(transformations + transformation_base + b);
  }

  void fill_patterns() {
    byte row_num = 20;
    while (row_num != NUM_ROWS) {
      pat = random_pattern();
      for (pat_offset = 0; pat_offset < pat.len; pat_offset++) {
        byte row = pat.get_row(pat_offset);
        visible.push(transform(row));
        row_num++;
        if(row_num == NUM_ROWS) {
          break;
        }
      }
    }
  }
  
  boolean colision(int pos, byte num_row) {
    return 0;
    // la nave esta enfrente
    int real_pos = (pos + SUBDEGREES/2)%SUBDEGREES;
    byte nave_column = (real_pos * NUM_COLUMNS) / SUBDEGREES;
    byte row_nave = visible.get_row(num_row);
    byte mask = 1 << nave_column;
    return row_nave & mask;
  }

  void step() {
    visible.push(transform(pat.get_row(pat_offset)));
    pat_offset++;
    if (pat_offset > pat.len) {
      pat = random_pattern();
      pat_offset = 0;
    }
  }
  
  void draw_column(byte column, Ledbar& ledbar) {
    byte mask = 1 << column;
    ledbar.clear();
    ledbar.alt_row = (column % 2);
    for (byte n=0; n<NUM_ROWS; n++) {
      byte row = visible.get_row(n);
      boolean value = row & mask;
      ledbar.draw(n, value);
    }
  }
  
};

class Display {
  int last_column_drawn;
  int drift_pos;
  int drift_speed;
public:
  Display() : last_column_drawn(-1), drift_pos(0), drift_speed(0) {
  }
  void step() {
      drift_pos = (drift_pos + drift_speed) % SUBDEGREES;
  }
};

Ledbar ledbar;
Board board;
Display display;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup(){
  Serial.begin(57600);
  inputString.reserve(200);

  randomSeed(analogRead(0));
  //randomSeed(83);
  
  pinMode(HALL_SENSOR, INPUT_PULLUP);
  attachInterrupt(0, handle_interrupt, FALLING);
  ledbar.init();
  init_nave();
  board.fill_patterns();
  State::change_state(&play_state);
}

volatile unsigned long last_turn = 0;
volatile unsigned long last_turn_duration = 100000L;

void handle_interrupt() {
  unsigned long this_turn = micros();
  last_turn_duration = this_turn - last_turn;
  last_turn = this_turn;
  colorizer.step();
}

unsigned long last_step = 0;
const unsigned long step_delay = 100000L;

void init_nave() {
  pinMode(NAVE_PIN_R, OUTPUT);
  pinMode(NAVE_PIN_G, OUTPUT);
  pinMode(NAVE_PIN_B, OUTPUT);
}

void prender_nave() {
  digitalWrite(NAVE_PIN_R, LOW);
  digitalWrite(NAVE_PIN_G, LOW);
  digitalWrite(NAVE_PIN_B, LOW);
}

void apagar_nave() {
  digitalWrite(NAVE_PIN_R, HIGH);
  digitalWrite(NAVE_PIN_G, HIGH);
  digitalWrite(NAVE_PIN_B, HIGH);
}

bool boton_cw = false;
bool boton_ccw = false;

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    switch (inChar) {
      case 'L':
        boton_ccw = true;
        break;
      case 'l':
        boton_ccw = false;
        break;
      case 'R':
        boton_cw = true;
        break;
      case 'r':
        boton_cw = false;
        break;
      default:
        inputString += inChar;
        if (inChar == ' ') {
          stringComplete = true;
        } 
    }
  }
}

void PlayState::loop() {
  
  if (stringComplete) {
    Serial.print("recibi:");
    Serial.println(inputString);
    Serial.print("velocidad:");
    Serial.println(last_turn_duration);
    char c = inputString.charAt(0);
    if (c == 'n') {
        board.fill_patterns();
    }
    inputString = "";
    stringComplete = false;
  }

/*
  int drift_random = random(0, 6000);
  if (drift_random < 7) {
    drift_speed = drift_random - 3;
    if (drift_speed == 0) {
      drift_speed = 4;
    }
  }
*/
 
  unsigned long loop_start = micros();
  
  unsigned long pos_width = min(last_turn_duration / SUBDEGREES, 100000L);
  unsigned long column_width = min(last_turn_duration / NUM_COLUMNS, 100000L);

  unsigned long drift = pos_width * drift_pos;
  unsigned int current_pos = ((drift + loop_start - last_turn) / pos_width) % SUBDEGREES;
  unsigned int current_column = ((drift + loop_start - last_turn) / column_width) % NUM_COLUMNS;
  
  
  if (boton_cw || boton_ccw) {
    int new_pos;
  
    if (boton_cw) {
      new_pos = nave_pos + 5;
    }
    if (boton_ccw) {
      new_pos = nave_pos - 5;
    } 
    
    boolean colision_futura = board.colision(new_pos, ROW_COLISION);
    boolean colision_actual = board.colision(nave_pos, ROW_NAVE);
    
    if (!colision_futura || colision_actual) {
      nave_pos = (new_pos+SUBDEGREES) % SUBDEGREES;
    }
  }
  
  // FIXME: arreglar cuando la nave cruza la zona oscura,
  //        que se va a ver finito
  if (abs(nave_pos-current_pos) < NAVE_WIDTH/2) {
    prender_nave();
  } else {
    apagar_nave();
  }
  
  if (loop_start > (last_step + step_delay)) {
    if (!board.colision(nave_pos, ROW_NAVE)) {    
      board.step();
    }
    last_step = loop_start;
  }
  
  if (current_column != last_column_drawn) {
    board.draw_column(current_column, ledbar);
    ledbar.update();
  }
  
  /*
  while (1) {
    int wait = micros()-(loop_start+slice);
    if (wait > 16000) {
      delayMicroseconds(10000);
    } else {
      delayMicroseconds(micros()-(loop_start+slice));
      break;
    }
  }
  */
  
  //colorizer.step();
}

State* State::current_state;

void PlayState::setup() {
  board.reset();
}

void GameoverState::setup() {
  
}

void GameoverState::loop() {
  
}

void loop() {
    State::current_state->loop();
}
