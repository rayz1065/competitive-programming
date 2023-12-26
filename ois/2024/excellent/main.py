def main ():
    n = int(input().strip())

    for i in range(min(3, n)):
        ones = n - i
        fives = i

        if (ones + fives * 5) % 3 == 0:
            print('1' * ones + '5' * fives)
            return

    print(-1)



if __name__ == '__main__':
    main()
