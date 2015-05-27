#include <Arduino.h>

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

class BasePattern;

class Pattern {
    BasePattern& base;
    const unsigned char PROGMEM* transformation_base;
    inline unsigned char transform(unsigned char b);

  public:
    Pattern();
    void randomize(int level);
    int len();
    inline unsigned char get_row(int row);
};

class CircularBuffer {
    byte buffer[NUM_ROWS];
    byte first_row;
  public:
    CircularBuffer();
    void reset();
    void push(byte row);
    byte get_row(byte row_num);
};

class Ledbar {
    void setPixelColor(int pixel, long color);

  public:
    boolean alt_row;
    void init();
    void clear();
    void draw(byte num_row, boolean value);
    inline void update();
};

class Board {
    CircularBuffer visible;
    byte first_row;
    Pattern pat;
    byte pat_offset;

  public:
    Board();
    void reset();
    void fill_patterns();
    boolean colision(int pos, byte num_row);
    void step();
    void draw_column(byte column, Ledbar& ledbar);
};

class Display {
    int last_column_drawn;
    int drift_pos;
    int drift_speed;
  public:
    Display() : last_column_drawn(-1), drift_pos(0), drift_speed(0) {
    }
    void adjust_drift();
    void step(unsigned long now);
};

class State {
  public:
    static State* current_state;
    static void change_state(State* new_state);
    virtual const char* name() = 0;
    virtual void setup() = 0;
    virtual void loop() {}
};

class GameoverState : public State {
  protected:
  public:
    const char* name() {
      return "Game Over";
    }
    void apagar_todo();
    void setup();
    void loop();
};

class PlayState : public State {
  public:
    const char* name() {
      return "Running Game";
    }
    void setup();
    void loop();
};

class Nave {
  public:
    void init();
    void prender();
    void apagar();
};

extern Ledbar ledbar;
extern Board board;
extern Display display;
extern Nave nave;
extern GameoverState gameover_state;
extern PlayState play_state;

