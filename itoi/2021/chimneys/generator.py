from random import randint, random, shuffle

def random_ints (count, total_sum):
    res = [total_sum // count] * count
    missing_segments = total_sum - (total_sum // count) * count
    for i in range(missing_segments):
        res[i] += 1
    for i in range(count):
        a, b = randint(0, count - 1), randint(0, count - 1)
        if res[a] < res[b]:
            a, b = b, a
        delta = randint(0, res[a] - 1) // 2
        res[a] -= delta
        res[b] += delta
    return res


def perfect_chimneys (n_segments, k_chimneys, desired_length=10**9, starting_pos=0):
    '''Generate chimneys with perfect score

    :param n_segments: How many segments to generate
    :param k_chimneys: How many chimneys the segments compose to ideally
    :param desired_length: Total length of each chimney, defaults to 10**9
    :param starting_pos: Starting position of every chimney, defaults to 0
    '''
    chimney_lengths = random_ints(k_chimneys, n_segments)
    edges = []
    for chimney_length in chimney_lengths:
        segment_lengths = random_ints(chimney_length, desired_length)
        chimney = []
        for length in segment_lengths:
            prev_end = starting_pos if len(chimney) == 0 else chimney[-1][1]
            chimney.append((prev_end, prev_end + randint(1, 2), length))
        edges.extend(chimney)
    return edges


def main ():
    edges = [
        *perfect_chimneys(5000, 2500),
        *perfect_chimneys(5000, 500),
    ]

    # shuffle(edges)

    print(len(edges))
    for u, v, length in edges:
        print(u, v, length)

if __name__ == '__main__':
    main()
