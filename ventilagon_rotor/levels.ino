Level levels[] = {
  Level(1, '1', 0x00ffff, 0xff0000),
  Level(2, '2', 0xff00ff, 0xff0000),
  Level(3, '3', 0xffff00, 0xff0000),
  Level(4, '1', 0x0000ff, 0xff0000),
  Level(5, '2', 0x00ff00, 0xff0000),
  Level(6, '3', 0xffffff, 0xff0000),
};

Level& current_level = levels[0];
byte new_level = 0;
