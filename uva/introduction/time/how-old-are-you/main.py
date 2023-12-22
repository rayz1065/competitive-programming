def solve (date_today, date_birth):
    # age at the end of the year
    age = date_today[0] - date_birth[0]
    if date_today[1:] < date_birth[1:]:
        # not had birthday yet
        age -= 1

    if age < 0:
        return 'Invalid birth date'
    if age > 130:
        return 'Check birth date'
    return age


def main ():
    t = int(input().strip())
    for tc in range(t):
        input()
        date_a, date_b = (tuple(int(x) for x in reversed(date.split('/')))
                          for date in (input(), input()))

        print(f'Case #{tc + 1}: {solve(date_a, date_b)}')


if __name__ == '__main__':
    main()
