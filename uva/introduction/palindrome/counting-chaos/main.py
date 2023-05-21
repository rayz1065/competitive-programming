def is_palindrome (word):
    return ''.join(reversed(word)) == word


def is_palindromic_time (time):
    return time % 100 < 60 and is_palindrome(str(time))


def main ():
    t = int(input().strip())
    times = [int(input().replace(':', '').strip()) for _ in range(t)]

    for time in times:
        time = (time + 1) % 2400
        while not is_palindromic_time(time):
            time = (time + 1) % 2400
        time = str(time).rjust(4, '0')
        print(f'{time[:2]}:{time[2:]}')


if __name__ == '__main__':
    main()
