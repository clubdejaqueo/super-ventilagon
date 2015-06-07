import unittest

SUBDEGREES = 8192
SHIP_RADIUS = 10

class Ship:
    def __init__(self, heading):
        self.heading = heading
        self.ship_radius = SHIP_RADIUS

    def contain(self, pos):
        return pos & (SUBDEGREES-1)

    def touches(self, pos):
        if abs(self.heading - self.contain(pos)) <= self.ship_radius:
            return True
        if abs(self.contain(self.heading+180) - self.contain(pos+180)) <= self.ship_radius:
            return True
        return False

class TestShipCalculations(unittest.TestCase):

    def ship_on(self, ship_at, pos):
        ship = Ship(ship_at)
        self.assertTrue(ship.touches(pos))

    def ship_off(self, ship_at, pos):
        ship = Ship(ship_at)
        self.assertFalse(ship.touches(pos))

    def test_inside(self):
        self.ship_on(SUBDEGREES/2, SUBDEGREES/2)

    def test_inside_left(self):
        self.ship_on(SUBDEGREES/2, SUBDEGREES/2-SHIP_RADIUS)

    def test_inside_right(self):
        self.ship_on(SUBDEGREES/2, SUBDEGREES/2+SHIP_RADIUS)

    def test_it_wraps(self):
        self.ship_on(SUBDEGREES/2, SUBDEGREES/2+SUBDEGREES)

    def test_it_wraps_to_zero(self):
        self.ship_on(0, SUBDEGREES)

    def test_outside(self):
        self.ship_off(SUBDEGREES/2, SUBDEGREES)

    def test_wraparound(self):
        self.ship_on(0, SUBDEGREES-1)

    def test_reverse_wraparound(self):
        self.ship_on(SUBDEGREES-1, 0)
    """

    def test_outside(self):
        self.ship_off(120, 359.9)

    def test_outside(self):
        self.ship_off(120, 359.9)

    def test_outside(self):
        self.ship_off(120, 359.9)

    def test_outside(self):
        self.ship_off(120, 359.9)
        """

if __name__ == '__main__':
    unittest.main()
