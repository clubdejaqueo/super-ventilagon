
Pattern::Pattern() : base(choose_random()) {
  block_height = DEFAULT_BLOCK_HEIGHT;
  current_height = block_height;
}

BasePattern& Pattern::choose_random() {
  // init to current_height to max, so first call to next_row() calculates the value of row zero
  current_height = block_height;
  row = 0;
  transformation_base = transformations + (random(0, 12) << 6);
  BasePattern& base = current_level.patterns[random(0, current_level.patterns_size)];
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
