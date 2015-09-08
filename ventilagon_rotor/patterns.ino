// Roughly based on: "Super Hexagon 101 : Know your Patterns"
// http://steamcommunity.com/sharedfiles/filedetails/?id=121153531

#define PATTERN const unsigned char PROGMEM

PATTERN solo_A[] = {
  0B010101,
  0B000000,
  0B010101,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
};

PATTERN solo_B[] = {
  0B010101,
  0B010101,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
};

PATTERN solo_C[] = {
  0B010010,
  0B000000,
  0B010010,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
};

PATTERN solo_D[] = {
  0B010010,
  0B010010,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
};

PATTERN triple_C[] = {
  0B101111,
  0B000000,
  0B000000,
  0B000000,
  0B111101,
  0B000000,
  0B000000,
  0B000000,
  0B101111,
};

PATTERN bat[] = {
  0B011111,
  0B001110,
  0B001110,
  0B001110,
  0B000100,
  0B100100,
  0B100100,
  0B110001,
  0B110001,
  0B111011,
  0B111011,
  0B010001,
};

PATTERN whirpool[] = {
  0B011111,
  0B001111,
  0B000111,
  0B000011,
  0B100001,
  0B110000,
  0B011000,
  0B001100,
  0B000110,
  0B000011,
  0B100001,
  0B110000,
  0B111000,
  0B111100,
  0B111110,
};

PATTERN double_whirpool[] = {
  0B110110,
  0B010010,
  0B001001,
  0B100100,
  0B010010,
  0B001001,
  0B100100,
  0B010010,
  0B011011,
};

PATTERN three_21[] = {
  0B110111,
  0B000000,
  0B000000,
  0B000000,
  0B011100,
  0B111110,
  0B111110,
  0B001000,
  0B001000,
  0B001001,
  0B101011,
  0B101011,
  0B001001,
  0B001001,
  0B011101,
  0B011101,
};

PATTERN ladder[] = {
  0B110110,
  0B010010,
  0B010010,
  0B011011,
  0B010010,
  0B010010,
  0B110110,
  0B010010,
  0B010010,
  0B011011,
  0B010010,
  0B010010,
  0B110110,
};

PATTERN four_spin[] = {
  0B011111,  
  0B000001,
  0B000001,
  0B000001,
  0B000001,
  0B000001,
  0B111101,
  0B000001,
  0B000001,
  0B000001,
  0B000001,
  0B000001,
  0B011111,  
};

PATTERN three_spin[] = {
  0B111101,
  0B100001,
  0B100001,
  0B100001,
  0B101111,
  0B100111,
  0B100011,
  0B100001,
  0B100001,
  0B111101,
  0B111001,
  0B110001,
  0B100001,  
  0B100001,  
  0B101111,
  0B100111,
  0B100011,
  0B100001,
  0B100001,
  0B111101,
  0B111001,
  0B110001,
};

PATTERN two_spin[] = {
  0B111100,
  0B100000,
  0B100000,
  0B100111,
  0B100000,
  0B100000,
  0B111100,
  0B100000,
  0B100000,
  0B100111,
  0B100000,
  0B100000,
  0B111100,
  0B100000,
  0B100000,
  0B100111,
  0B100000,
  0B100000,
};

PATTERN multi_C[] = {
  0B011111,
  0B000000,
  0B000000,
  0B101111,
  0B000000,
  0B000000,
  0B110111,
  0B000000,
  0B000000,
  0B111011,
  0B000000,
  0B000000,
  0B111101,
  0B000000,
  0B000000,
  0B111110,
};

PATTERN rain[] = {
  0B010101,
  0B000000,
  0B000000,
  0B101010,
  0B000000,
  0B000000,
  0B010101,
  0B000000,
  0B000000,
  0B101010,
  0B000000,
  0B000000,
  0B010101,
  0B000000,
  0B000000,
  0B101010,
  0B101010,
};

class BasePattern {
  public:
    byte len;
    const unsigned char PROGMEM* rows;

    BasePattern(byte len, const unsigned char PROGMEM* rows) : len(len), rows(rows) {
    }

    inline byte get_row(byte offset) const {
      return pgm_read_byte(rows + offset);
    }
};

BasePattern patterns_level1[] = {
  BasePattern(sizeof(solo_A), solo_A),
  BasePattern(sizeof(solo_B), solo_B),
  BasePattern(sizeof(solo_C), solo_C),
  BasePattern(sizeof(solo_D), solo_D),
  BasePattern(sizeof(triple_C), triple_C),
  BasePattern(sizeof(whirpool), whirpool),
  BasePattern(sizeof(bat), bat),
  BasePattern(sizeof(ladder), ladder),
};

BasePattern patterns_level2[] = {
  BasePattern(sizeof(solo_A), solo_A),
  BasePattern(sizeof(solo_B), solo_B),
  BasePattern(sizeof(solo_C), solo_C),
  BasePattern(sizeof(solo_D), solo_D),
  BasePattern(sizeof(triple_C), triple_C),
  BasePattern(sizeof(multi_C), multi_C),
  BasePattern(sizeof(double_whirpool), double_whirpool),
  BasePattern(sizeof(bat), bat),
  BasePattern(sizeof(three_21), three_21),
  BasePattern(sizeof(ladder), ladder),
  BasePattern(sizeof(two_spin), two_spin),
  BasePattern(sizeof(three_spin), three_spin),
  BasePattern(sizeof(four_spin), four_spin),
  BasePattern(sizeof(rain), rain),
};


Pattern::Pattern() : base(choose_random()) {
  block_height = DEFAULT_BLOCK_HEIGHT;
  current_height = block_height;
}

BasePattern& Pattern::choose_random() {
  // init to current_height to max, so first call to next_row() calculates the value of row zero
  current_height = block_height;
  row = 0;
  transformation_base = transformations + (random(0, 12) << 6);
  BasePattern& base = patterns_level1[random(0, elements_in(patterns_level1))];
  base_len = base.len;
  return base;
}

void Pattern::randomize(int level) {
  base = choose_random();
}

unsigned char Pattern::transform(unsigned char b) {
  return pgm_read_byte(transformation_base + b);
}

unsigned char Pattern::next_row() {
  static unsigned char value;
  if (current_height++ >= block_height) {
    current_height = 0;
    value = transform(base.get_row(row++));
  }
  return value;
}

bool Pattern::finished() {
  return (row >= base_len) && (current_height >= block_height) ;
}
