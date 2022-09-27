from day_19.rotations import rotated_coords
from day_19.coords import Coords

class Scanner:
    def __init__(self, scanner_id, beacons, rotation=None, offset=None):
        self.scanner_id: int = scanner_id
        self.beacons = list(beacons)
        if rotation is None:
            rotation = (0, 0, 0)
        if offset is None:
            offset = Coords(0, 0, 0)
        self.rotation = rotation
        self.offset = offset

    def rotate(self, rotation):
        beacons = []
        for beacon in self.beacons:
            beacons.append(rotated_coords(beacon, rotation))
        return Scanner(self.scanner_id, beacons, rotation, offset=self.offset)

    def move(self, vec):
        beacons = []
        for beacon in self.beacons:
            beacons.append(beacon.add(vec))
        return Scanner(self.scanner_id, beacons, rotation=self.rotation, offset=vec)
