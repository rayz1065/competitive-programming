import re
from day_19.coords import Coords
from day_19.scanner import Scanner

def read_scanner():
    scanner_re = re.compile(r'--- scanner (\d+) ---')
    line = input()
    match = scanner_re.match(line)
    assert match is not None
    scanner_id = int(match.groups()[0])
    beacons = []
    try:
        while True:
            line = input()
            if line == '':
                break
            x, y, z = (int(x) for x in line.split(','))
            coords = Coords(x, y, z)
            beacons.append(coords)
    except EOFError:
        pass
    return Scanner(scanner_id, beacons)

def read_in():
    problem = []
    try:
        while True:
            problem.append(read_scanner())
    except EOFError:
        pass
    return problem
