def check (number):
    number = [int(x) for x in str(number)]
    doubled_digits = [x * 2 for i, x in enumerate(number) if i % 2 == 0]
    all_doubled = ''.join(str(y) for y in doubled_digits)
    sum_doubled = sum(int(x) for x in all_doubled)

    undoubled_digits = [x for i, x in enumerate(number) if i % 2 == 1]
    sum_undoubled = sum(undoubled_digits)

    return (sum_doubled + sum_undoubled) % 10 == 0


def main ():
    t = int(input().strip())
    for _ in range(t):
        number = input().replace(' ', '')
        print('Valid' if check(number) else 'Invalid')


if __name__ == '__main__':
    main()
