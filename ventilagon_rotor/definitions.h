#include <Arduino.h>

const byte NUM_COLUMNS = 6;
const byte NUM_ROWS = 32;
const byte HALL_SENSOR = 2;

const byte ROW_SHIP = 3;
const byte ROW_COLISION = 7;

const int SUBDEGREES = 8192;
const int SUBDEGREES_MASK = 8191;
const int SHIP_WIDTH = 272;
const byte DEFAULT_BLOCK_HEIGHT = 4;

class BasePattern;

class Pattern {
    BasePattern& base;
    const unsigned char PROGMEM* transformation_base;
    inline unsigned char transform(unsigned char b);
    int current_height;
    int block_height;
    int row;
    int base_len;
    BasePattern& choose_random();
  public:
    Pattern();
    void randomize(int level);
    inline unsigned char next_row();
    inline bool finished();
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
    Pattern pat;

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
    void tick(unsigned long now);
    bool ship_on(int current_pos);
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

class Ship {
  public:
    void init();
    void prender();
    void apagar();
};

class Level {
    const int speed;
    const char* song;
    const long color;
  public:
    Level(int speed, char* song, long color) : speed(speed), song(song), color(color) {
    }
};

extern Ledbar ledbar;
extern Board board;
extern Display display;
extern Ship ship;
extern GameoverState gameover_state;
extern PlayState play_state;
extern const unsigned char PROGMEM transformations[];
extern Level levels[];
extern Level& current_level;

#define elements_in(arrayname) (sizeof arrayname/sizeof *arrayname)
