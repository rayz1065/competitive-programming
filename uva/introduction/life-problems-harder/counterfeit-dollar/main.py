MEASURE_MAP = {
    'down': -1,
    'even': 0,
    'up': +1,
}


def compute_results (coins_a, coins_b, counterfeit):
    if counterfeit in coins_a:
        return -1
    if counterfeit in coins_b:
        return +1
    return 0


def solve ():
    weights = [input().strip().split() for _ in range(3)]
    tests = [(a, b) for a, b, _ in weights]
    actual_results = [MEASURE_MAP[c] for _, _, c in weights]
    for coin in 'ABCDEFGHIJKL':
        desired_results = [compute_results(a, b, coin) for a, b in tests]

        if all(x == y for x, y in zip(actual_results, desired_results)):
            return (coin, 'light')

        if all(x == -y for x, y in zip(actual_results, desired_results)):
            return (coin, 'heavy')

    return (None, None)



def main ():
    t = int(input().strip())
    for _ in range(t):
        coin, coin_type = solve()
        print(f'{coin} is the counterfeit coin and it is {coin_type}.')


if __name__ == '__main__':
    main()
