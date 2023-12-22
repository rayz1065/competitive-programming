def main ():
    t = int(input().strip())
    for _ in range(t):
        hour, minutes = (int(x) for x in input().strip().split(':'))
        hour = 12 - hour
        if minutes > 0:
            hour = (hour + 11) % 12
        if hour == 0:
            hour = 12
        minutes = (60 - minutes) % 60
        print(f'{str(hour).rjust(2, "0")}:{str(minutes).rjust(2, "0")}')


if __name__ == '__main__':
    main()
