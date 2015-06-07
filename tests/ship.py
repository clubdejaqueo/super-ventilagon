import unittest

class Ship:
    def __init__(self, heading):
        self.heading = heading
        self.ship_radius = 10

    def touches(self, pos):
        if abs(self.heading - (pos%360)) <= self.ship_radius:
            return True
        if abs(((self.heading+180)%360) - ((pos+180)%360)) <= self.ship_radius:
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
        self.ship_on(120, 120)

    def test_inside_left(self):
        self.ship_on(120, 110)

    def test_inside_right(self):
        self.ship_on(120, 130)

    def test_it_wraps(self):
        self.ship_on(120, 120+360)

    def test_it_wraps_to_zero(self):
        self.ship_on(0, 360)

    def test_outside(self):
        self.ship_off(120, 360)

    def test_wraparound(self):
        self.ship_on(0, 359)

    def test_reverse_wraparound(self):
        self.ship_on(359, 0)
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
