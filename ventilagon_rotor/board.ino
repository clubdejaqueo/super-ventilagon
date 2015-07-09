Board board;

CircularBuffer::CircularBuffer() {
  reset();
}

void CircularBuffer::reset() {
  first_row = 0;
  int n;
  for (n = 0; n < NUM_ROWS; n++) {
    buffer[n] = 0;
  }
}

void CircularBuffer::push(byte row) {
  cli();
  buffer[first_row] = row;
  first_row = (first_row + 1) % NUM_ROWS;
  sei();
}

byte CircularBuffer::get_row(byte row_num) {
  byte pos = (row_num + first_row) % NUM_ROWS;
  return buffer[pos];
}

Board::Board() {
  reset();
}

void Board::reset() {
  pat.randomize(0);
  visible.reset();
}

void Board::fill_patterns() {
  byte row_num = 20;
  while (row_num != NUM_ROWS) {
    pat.randomize(0);

    while (!pat.finished()) {
      visible.push(pat.next_row());
      row_num++;
      if (row_num == NUM_ROWS) {
        break;
      }
    }
  }
}

boolean Board::colision(int pos, byte num_row) {
  return 0;
  // la nave esta enfrente
  int real_pos = (pos + SUBDEGREES / 2) & SUBDEGREES_MASK;
  byte ship_column = (real_pos * NUM_COLUMNS) / SUBDEGREES;
  byte row_ship = visible.get_row(num_row);
  byte mask = 1 << ship_column;
  return row_ship & mask;
}

void Board::step() {
  visible.push(pat.next_row());

  if (pat.finished()) {
    pat.randomize(99);
  }
}

void Board::draw_column(byte column, Ledbar& ledbar) {
  byte mask = 1 << column;
  ledbar.clear();
  ledbar.alt_row = (column % 2);
  for (byte n = 0; n < NUM_ROWS; n++) {
    byte row = visible.get_row(n);
    boolean value = row & mask;
    ledbar.draw(n, value);
  }
  ledbar.update();
}

