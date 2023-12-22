def main ():
    while True:
        hour_from, minute_from, hour_to, minute_to = (int(x) for x in input().strip().split())
        if (hour_from, minute_from, hour_to, minute_to) == (0, 0, 0, 0):
            break
        time_from = hour_from * 60 + minute_from
        time_to = hour_to * 60 + minute_to

        if time_from > time_to:
            time_to += 24 * 60

        print(time_to - time_from)


if __name__ == '__main__':
    main()
