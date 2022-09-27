from day_19.reader import read_in
from day_19.rotations import all_rotations

def match_scanners(scanner_a, scanner_b):
    beacons_a = set(scanner_a.beacons)
    for rotation in all_rotations():
        b_rotated = scanner_b.rotate(rotation)
        for beacon_a in scanner_a.beacons:
            # try to match this beacon with a beacon from scanner_b
            for beacon_b in b_rotated.beacons:
                # if this beacon is the same one, then we should
                # update the relative coordinates of beacon b

                ap = beacon_a
                bp = beacon_b
                ab = bp.sub(ap)

                b_moved = b_rotated.move(ab.invert())
                beacons_b = set(b_moved.beacons)

                # if ab.invert() == (1105,-1205,1229):
                #     print(ab, scanner_a.scanner_id, b_moved.scanner_id, len(beacons_a.intersection(beacons_b)))
                if len(beacons_a.intersection(beacons_b)) >= 12:
                    return b_moved
    return None

def part_1(ordered_scanners):
    all_beacons = set()
    for scanner in ordered_scanners:
        all_beacons.update(scanner.beacons)
    return len(all_beacons)

def part_2(ordered_scanners):
    max_dist = 0
    for scanner_a in ordered_scanners:
        for scanner_b in ordered_scanners:
            dist = scanner_a.offset.dist(scanner_b.offset)
            max_dist = max(dist, max_dist)
    return max_dist

def match_all_scanners(problem):
    ff =  [problem[0]]
    is_matched = [False] * len(problem)
    is_matched[0] = True
    result = [problem[0]]

    while len(ff) > 0:
        scanner_a = ff.pop()
        for scanner_b in problem:
            if is_matched[scanner_b.scanner_id]:
                # already matched
                continue

            # match this scanner with the scanner_a
            print("trying to match", scanner_a.scanner_id, scanner_b.scanner_id)
            match = match_scanners(scanner_a, scanner_b)
            if match is None:
                # no match was found
                continue

            # success!
            ff.append(match)
            result.append(match)
            is_matched[match.scanner_id] = True
            print("found match!", match.scanner_id, match.rotation, match.offset)

    assert all(is_matched)
    return result

def main():
    problem = read_in()
    ordered_scanners = match_all_scanners(problem)
    print("part_1:", part_1(ordered_scanners))
    print("part_2:", part_2(ordered_scanners))

if __name__ == '__main__':
    main()
