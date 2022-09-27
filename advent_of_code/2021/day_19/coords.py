from collections import namedtuple

class Coords(namedtuple('coord', ('x', 'y', 'z'))):
    def __str__(self):
        return f"{self.x},{self.y},{self.z}"

    def sub(self, other):
        return self.add(other.invert())

    def add(self, other):
        return Coords(self.x + other.x, self.y + other.y, self.z + other.z)

    def invert(self):
        return Coords(-self.x, -self.y, -self.z)

    def dist(self, other):
        return sum(abs(a - b) for a, b in zip(self, other))
