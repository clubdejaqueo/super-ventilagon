
Pattern::Pattern() {
  randomize(99);
  block_height = DEFAULT_BLOCK_HEIGHT;
  current_height = block_height;
}

void Pattern::randomize(int level) {
  // init to current_height to max, so first call to next_row() calculates the value of row zero
  current_height = block_height;
  row = 0;
  transformation_base = transformations + (random(0, 12) << 6);
  const BasePattern* base = &current_level.patterns[random(0, current_level.patterns_size)];
  base_len = pgm_read_byte(&base->len);
  rows_base = (const unsigned char*) pgm_read_ptr(&base->rows);
}

unsigned char Pattern::transform(unsigned char b) {
  return pgm_read_byte(transformation_base + b);
}

unsigned char Pattern::next_row() {
  static unsigned char value;
  if (current_height++ >= block_height) {
    current_height = 0;
    unsigned char base_value = pgm_read_byte(rows_base + row++);
    value = transform(base_value);
  }
  return value;
}

bool Pattern::finished() {
  return (row >= base_len) && (current_height >= block_height) ;
}
