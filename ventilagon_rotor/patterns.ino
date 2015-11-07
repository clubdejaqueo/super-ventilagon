
Pattern::Pattern() {
  randomize();
  block_height = current_level.block_height;
  current_height = block_height;
}

void Pattern::randomize() {
  // init current_height to max, so first call to next_row() calculates the value of row zero
  current_height = block_height = current_level.block_height;
  row = 0;
  transformation_base = transformations + (random(0, 12) << 6);
  int new_pattern = random(0, current_level.num_patterns);
  rows_base = (const byte*) pgm_read_ptr(current_level.patterns + new_pattern);
  rows_len = pgm_read_byte(rows_base++);
}

byte Pattern::transform(byte b) {
  return pgm_read_byte(transformation_base + b);
}

byte Pattern::next_row() {
  static byte value;
  if (current_height++ >= block_height) {
    current_height = 0;
    byte base_value = pgm_read_byte(rows_base + row++);
    value = transform(base_value);
  }
  return value;
}

bool Pattern::finished() {
  return (row >= rows_len) && (current_height >= block_height) ;
}
