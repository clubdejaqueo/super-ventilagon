// Roughly based on: "Super Hexagon 101 : Know your Patterns"
// http://steamcommunity.com/sharedfiles/filedetails/?id=121153531

#define PATTERN const unsigned char PROGMEM
#define END 0,0,0

PATTERN solo_A[] = {
  0B010101,
  0B000000,
  0B010101,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
  END
};

PATTERN solo_B[] = {
  0B010101,
  0B010101,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
  END
};

PATTERN solo_C[] = {
  0B010010,
  0B000000,
  0B010010,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
  END
};

PATTERN solo_D[] = {
  0B010010,
  0B010010,
  0B000000,
  0B000000,
  0B000000,
  0B111011,
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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
  END
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

Level levels[] = {
  Level(1, '1', 0x00ffff, 0xff0000, patterns_level1, elements_in(patterns_level1)),
  Level(2, '2', 0xff00ff, 0xff0000, patterns_level2, elements_in(patterns_level2)),
  Level(3, '3', 0xffff00, 0xff0000, patterns_level1, elements_in(patterns_level1)),
  Level(4, '1', 0x0000ff, 0xff0000, patterns_level1, elements_in(patterns_level1)),
  Level(5, '2', 0x00ff00, 0xff0000, patterns_level2, elements_in(patterns_level2)),
  Level(6, '3', 0xffffff, 0xff0000, patterns_level1, elements_in(patterns_level1)),
};

Level& current_level = levels[0];
byte new_level = 0;
