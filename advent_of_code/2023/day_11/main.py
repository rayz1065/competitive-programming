from itertools import combinations


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def get_galaxy_coordinates(universe):
    for r, row in enumerate(universe):
        for c, cell in enumerate(row):
            if cell == "#":
                yield r, c


def get_empty(galaxies, coord_idx):
    coord_max = max(x[coord_idx] for x in galaxies)
    empty_coords = set(range(coord_max + 1))

    for galaxy in galaxies:
        empty_coords.discard(galaxy[coord_idx])

    return list(empty_coords)


def compute_distances(galaxies):
    base = 0
    for galaxy_a, galaxy_b in combinations(galaxies, r=2):
        for coord_idx in range(2):
            base += abs(galaxy_a[coord_idx] - galaxy_b[coord_idx])

    expansion = 0
    for coord_idx in range(2):
        empty_xs = get_empty(galaxies, coord_idx)
        for x in empty_xs:
            before = sum(1 for galaxy in galaxies if galaxy[coord_idx] < x)
            after = sum(1 for galaxy in galaxies if galaxy[coord_idx] > x)
            expansion += before * after

    return base, expansion


def main():
    universe = list(read_lines())
    galaxies = list(get_galaxy_coordinates(universe))

    base, expansion = compute_distances(galaxies)

    print("part_1:", base + expansion)
    print("part_2:", base + expansion * (1000000 - 1))


if __name__ == "__main__":
    main()
