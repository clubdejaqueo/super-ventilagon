#include <Arduino.h>

#define DEBUG

#ifdef DEBUG
#define debug Serial.print
#define debugln Serial.println
#else
#define debug
#define debugln
#endif

const byte NUM_COLUMNS = 6;
const byte NUM_ROWS = 32;
const byte HALL_SENSOR = 2;

const byte ROW_SHIP = 3;
const byte ROW_COLISION = 7;

const int SUBDEGREES = 8192;
const int SUBDEGREES_MASK = 8191;
const int SHIP_WIDTH = 272;

class Pattern {
    const byte* transformation_base;
    inline byte transform(byte b);
    int current_height;
    int block_height;
    int row;
    const byte* rows_base;
    byte rows_len;
  public:
    Pattern();
    void randomize();
    inline byte next_row();
    inline bool finished();
};

class CircularBuffer {
    byte buffer[NUM_ROWS];
    byte first_row;
  public:
    CircularBuffer();
    void reset();
    void push_back(byte row);
    void push_front(byte row);
    byte get_row(byte row_num);
};

class Ledbar {
    void setPixelColor(int pixel, long color);

  public:
    void init();
    void clear();
    void draw(byte num_row, boolean value, boolean alt_column);
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
    void step_back();
    void draw_column(byte column);
};

class Display {
    unsigned int last_column_drawn;
    int drift_pos;
    int drift_speed;
    bool calibrating;
  public:
    Display() : last_column_drawn(-1), drift_pos(0), drift_speed(0), calibrating(false) {
    }
    void dump_debug();
    void adjust_drift();
    void tick(unsigned long now);
    void calibrate(bool calibrating);
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
    bool keys_pressed;
  public:
    const char* name() {
      return "GAME OVER";
    }
    void apagar_todo();
    void setup();
    void loop();
};

class PlayState : public State {
  public:
    int section;
    unsigned long section_init_time;
    unsigned long section_duration;
    bool paused;
    
    void check_section(unsigned long now);
    void advance_section(unsigned long now);

    const char* name() {
      return "RUNNING GAME";
    }
    void toggle_pause() {
      paused = !paused;
    }
    void setup();
    void loop();
};

class ResettingState : public State {
  public:
    long int last_step;
    byte counter;
    const char* name() {
      return "RESETTING";
    }
    void setup();
    void loop();
};

class Ship {
    bool on;
  public:
    void init();
    void prender();
    void apagar();
};

class Level {
  public:
    unsigned long step_delay;
    char song;
    long color;
    long bg1, bg2;
    const byte* const* patterns;
    int num_patterns;
    byte block_height;
    Level(unsigned long step_delay, byte block_height, char song, long color, long bg1, long bg2, const byte* const* patterns, int num_patterns) : 
      step_delay(step_delay), block_height(block_height), song(song), color(color), bg1(bg1), bg2(bg2), patterns(patterns), num_patterns(num_patterns){
    }
};

class Audio {
  public:
    void inline play_superventilagon();
    void inline play_crash();
    void inline play_game_over();
    void inline begin();
    void inline stop_song();
    void inline play_song(char song);
};

extern Ledbar ledbar;
extern Board board;
extern Display display;
extern Ship ship;
extern Audio audio;
extern GameoverState gameover_state;
extern PlayState play_state;
extern ResettingState resetting_state;
extern const byte PROGMEM transformations[];
extern Level levels[];
extern Level& current_level;
extern byte new_level;
extern int nave_calibrate;

#define elements_in(arrayname) (sizeof arrayname/sizeof *arrayname)
