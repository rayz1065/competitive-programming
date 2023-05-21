def is_palindrome (number):
    return str(number) == ''.join(reversed(str(number)))


def reverse_and_add (number):
    reversed_num = int(''.join(reversed(str(number))))
    return reversed_num + number


def main ():
    n = int(input().strip())
    numbers = [int(input().strip()) for _ in range(n)]

    for number in numbers:
        iterations = 1
        number = reverse_and_add(number)

        while not is_palindrome(number):
            number = reverse_and_add(number)
            iterations += 1
            if iterations > 1000:
                break
        print(iterations, number)


if __name__ == '__main__':
    main()
