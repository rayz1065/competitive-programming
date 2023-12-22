def main ():
    t = int(input().strip())
    for tc in range(t):
        w_hour_from, w_hour_to = input().strip().split()
        hour_from, hour_to = input().strip().split()

        hits = hour_from > w_hour_to or hour_to < w_hour_from

        print(f'Case {tc + 1}: {"Hits" if hits else "Mrs"} Meeting')


if __name__ == '__main__':
    main()
