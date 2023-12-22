COSTS = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]


def simple_solve (n):
    digits_freq = [0] * 10

    for i in range(n + 1):
        for dig in str(i):
            digits_freq[int(dig)] += 1
    return digits_freq


def calculate_cost (digits_freq):
    return sum(cost * freq for cost, freq in zip(COSTS, digits_freq))


def solve (n):
    digits_freq = [0] * 10
    multiplier = 1
    completed_digits = 0

    while n >= 0:
        while n % 10 != 9:
            # step exactly one number
            for dig in str(n):
                # all of these digits stay the same for multiplier steps
                digits_freq[int(dig)] += multiplier

            for dig in range(10):
                # all of these digits show up for multiplier // 10 of the steps in each place
                digits_freq[dig] += completed_digits * multiplier // 10
            n -= 1

        if n < 0:
            break

        n = n // 10
        multiplier *= 10
        completed_digits += 1

    # over-counted leading zeros
    for j in range(1, completed_digits + 1):
        digits_freq[0] -= 10 ** j

    return digits_freq


def main ():
    with open('input.txt', 'r') as in_file:
        n = int(in_file.read())
    
    with open('output.txt', 'w') as out_file:
        print(calculate_cost(solve(n)), file=out_file)


if __name__ == '__main__':
    main()
