patterns = [
    ("solo_A", [
      0B010101,
      0B000000,
      0B010101,
      0B000000,
      0B000000,
      0B000000,
      0B111011,
    ]),

    ("solo_B", [
      0B010101,
      0B010101,
      0B000000,
      0B000000,
      0B000000,
      0B111011,
    ]),

    ("solo_C", [
      0B010010,
      0B000000,
      0B010010,
      0B000000,
      0B000000,
      0B000000,
      0B111011,
    ]),

    ("solo_D", [
      0B010010,
      0B010010,
      0B000000,
      0B000000,
      0B000000,
      0B111011,
    ]),

    ("triple_C", [
      0B101111,
      0B000000,
      0B000000,
      0B000000,
      0B111101,
      0B000000,
      0B000000,
      0B000000,
      0B101111,
    ]),

    ("bat", [
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
    ]),

    ("whirpool", [
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
    ]),

    ("double_whirpool", [
      0B110110,
      0B010010,
      0B001001,
      0B100100,
      0B010010,
      0B001001,
      0B100100,
      0B010010,
      0B011011,
    ]),

    ("three_21", [
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
    ]),

    ("ladder", [
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
    ]),

    ("four_spin", [
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
    ]),

    ("three_spin", [
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
    ]),

    ("two_spin", [
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
    ]),

    ("multi_C", [
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
    ]),

    ("rain", [
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
    ]),
]

levels = [
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "whirpool",
        "bat",
        "ladder",
    ],
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "multi_C",
        "bat",
        "three_21",
        "ladder",
        "two_spin",
        "four_spin",
        "rain",
    ],
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "double_whirpool",
        "three_21",
        "four_spin",
        "rain",
    ],
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "whirpool",
        "bat",
        "ladder",
        # TODO: fixme
        #  "stair_1",
        "three_21",
    ],
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "multi_C",
        "double_whirpool",
        "bat",
        "three_21",
        "ladder",
        "three_spin",
        "rain",
    ],
    [
        "solo_A",
        "solo_B",
        "solo_C",
        "solo_D",
        "triple_C",
        "double_whirpool",
        # TODO: fixme  
        #  "stair_2",
        "three_21",
        "four_spin",
        "rain",
    ],
]

END = [0,0,0]

for _, values in patterns:
    values += END

sizeof_patterns = sum(len(x) for (name, x) in patterns)
sizeof_levels = sum(len(x) for x in levels) * 2
print "// patterns %d bytes, patterns_levels %d bytes" % (sizeof_patterns, sizeof_levels)
print

for name, values in patterns:
    print "PATTERN %s[] = {" % name
    print "  %d," % len(values)
    for v in values:
        print "  0b{:06b},".format(v)
    print "};"
    print

for n, level_patterns in enumerate(levels):
    print "const byte * const patterns_level%d[] PROGMEM = {" % (n+1)
    for p in level_patterns:
        print "  %s," % p
    print "};"
    print
