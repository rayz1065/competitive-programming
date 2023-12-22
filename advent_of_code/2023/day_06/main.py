from functools import reduce


def compute_error_margin(time, record_distance):
    # find the lowest value for which this works
    left, right = 0, time // 2
    feasible = None

    while left <= right:
        speed = (left + right) // 2
        remaining_time = time - speed
        distance = speed * remaining_time
        if distance > record_distance:
            right = speed - 1
            feasible = speed
        else:
            left = speed + 1

    # removes the times at the start and at the end that are unfeasible
    return time + 1 - 2 * feasible


def part_1(times, distances):
    margins = [compute_error_margin(t, d) for t, d in zip(times, distances)]

    return reduce(lambda x, acc: x * acc, margins, 1)


def part_2(times, distances):
    time = int("".join(str(x) for x in times))
    distance = int("".join(str(x) for x in distances))

    return part_1([time], [distance])


def main():
    times = [int(x) for x in input().split(":")[1].split()]
    distances = [int(x) for x in input().split(":")[1].split()]
    print("part_1:", part_1(times, distances))
    print("part_2:", part_2(times, distances))


if __name__ == "__main__":
    main()
