
// 20 rows
const unsigned char PROGMEM pat0[] = {
  0B000000,
  0B100111,
  0B110011,
  0B111001,
  0B111100,
  0B011110,
  0B001111,
  0B100111,
  0B110011,
  0B111001,
  0B111100,
  0B011110,
  0B001111,
  0B100111,
  0B110011,
  0B111001,
  0B111100,
  0B011110,
  0B001111,
  0B000000,
};

// 12 rows
const unsigned char PROGMEM pat1[] = {
  0B000000,
  0B101111,
  0B000000,
  0B000000,
  0B000000,
  0B111101,
  0B000000,
  0B000000,
  0B000000,
  0B101111,
  0B000000,
  0B000000,
};

// 11 rows
const unsigned char PROGMEM pat2[] = {
  0B000000,
  0B110110,
  0B010010,
  0B011011,
  0B010010,
  0B110110,
  0B010010,
  0B011011,
  0B010010,
  0B110110,
  0B000000,
};

// 10 rows
const unsigned char PROGMEM pat3[] = {
  0B000000,
  0B000000,
  0B010010,
  0B000000,
  0B101010,
  0B000000,
  0B010101,
  0B000000,
  0B101110,
  0B000000,
};

// 9 rows
const unsigned char PROGMEM pat4[] = {
  0B000000,
  0B000001,
  0B000010,
  0B000100,
  0B001000,
  0B010000,
  0B100000,
  0B000000,
  0B000000,
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

BasePattern all_patterns[] = {
  BasePattern(sizeof(pat0), pat0),
  BasePattern(sizeof(pat1), pat1),
  BasePattern(sizeof(pat2), pat2),
  BasePattern(sizeof(pat3), pat3),
  BasePattern(sizeof(pat4), pat4),
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
  BasePattern& base = all_patterns[random(0, elements_in(all_patterns))];
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
