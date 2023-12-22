import re
from collections import namedtuple

Conversion = namedtuple("Conversion", ["source", "dest", "mappings"])
Mapping = namedtuple("Mapping", ["destination", "source", "range"])


def read_conversion():
    line = ""
    while (res := re.match(r"^(\w+)-to-(\w+)\s+map:$", line)) is None:
        line = input().strip()

    source, dest = res.groups()

    mappings = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        if line == "":
            break

        mapping = Mapping(*(int(x) for x in line.strip().split()))
        mappings.append(mapping)

    return Conversion(source, dest, mappings)


def read_lines():
    line = input().strip()
    seeds = [int(x) for x in re.match(r"^seeds:\s*([\d\s]+)$", line).group(1).split()]

    conversions = []
    while True:
        try:
            conversion = read_conversion()
        except EOFError:
            break

        conversions.append(conversion)

    return seeds, conversions


def find_mapping(mappings: list[Conversion], source_t, source, dest_t):
    if source_t == dest_t:
        return source

    conversion = next(x for x in mappings if x.source == source_t)
    for mapping in conversion.mappings:
        if mapping.source <= source < mapping.source + mapping.range:
            # found correct remapping
            remapped = mapping.destination + (source - mapping.source)
            return find_mapping(mappings, conversion.dest, remapped, dest_t)

    # unchanged
    return find_mapping(mappings, conversion.dest, source, dest_t)


def part_1(seeds, mappings):
    return min([find_mapping(mappings, "seed", seed, "location") for seed in seeds])


def is_overlapping(a_left, a_right, b_left, b_right):
    return not (a_right < b_left or a_left > b_right)


def split(a_left, a_right, b_left, b_right):
    # splits the interval [a_left, b_left] by the portion [b_left, b_right] (all ends inclusive)
    if not is_overlapping(a_left, a_right, b_left, b_right):
        return [(a_left, a_right)]

    splits = []
    if a_left < b_left:
        # leftmost portion is not overlapping
        splits.append((a_left, b_left - 1))
        a_left = b_left

    if a_right > b_right:
        # rightmost portion is not overlapping
        splits.append((b_right + 1, a_right))
        a_right = b_right

    # center portion
    splits.append((a_left, a_right))

    return splits


def remap_range(mappings: list[Conversion], source_t, source_start, source_end, dest_t):
    if source_t == dest_t:
        return source_start

    res = 2**32

    conversion = next(x for x in mappings if x.source == source_t)
    # find the first overlapping mapping
    mapping = next(
        (
            mapping
            for mapping in conversion.mappings
            if is_overlapping(
                source_start,
                source_end,
                mapping.source,
                mapping.source + mapping.range - 1,
            )
        ),
        None,
    )

    if mapping is None:
        # unchanged
        return remap_range(mappings, conversion.dest, source_start, source_end, dest_t)

    # split through this mapping, call the appropriate function to deal with each split
    splits = split(
        source_start, source_end, mapping.source, mapping.source + mapping.range - 1
    )

    for split_start, split_end in splits:
        if is_overlapping(
            split_start, split_end, mapping.source, mapping.source + mapping.range - 1
        ):
            split_start = mapping.destination + (split_start - mapping.source)
            split_end = mapping.destination + (split_end - mapping.source)
            res = min(
                res,
                remap_range(mappings, conversion.dest, split_start, split_end, dest_t),
            )
        else:
            res = min(
                res,
                remap_range(mappings, source_t, split_start, split_end, dest_t),
            )

    return res


def part_2(seeds, mappings):
    res = 2**32
    for i in range(len(seeds) // 2):
        seed, seed_range = seeds[i * 2], seeds[i * 2 + 1]
        res = min(
            res,
            remap_range(mappings, "seed", seed, seed + seed_range - 1, "location"),
        )

    return res


def main():
    seeds, mappings = read_lines()
    print("part_1:", part_1(seeds, mappings))
    print("part_2:", part_2(seeds, mappings))


if __name__ == "__main__":
    main()
