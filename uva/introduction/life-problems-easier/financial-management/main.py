def main ():
    t = int(input().strip())
    for tc in range(t):
        months = [float(input().strip()) for _ in range(12)]
        mean = sum(months) / len(months)
        print(f'{tc + 1} ${mean:,.2f}')


if __name__ == '__main__':
    main()
