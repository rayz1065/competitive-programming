a, b, k = (int(x) for x in input().split())

count_numbers_memo = {}

def count_numbers_2(remaining_b, remaining_digits, curr_modulo):
    if remaining_digits == 0:
        return 1 if remaining_b == 0 and curr_modulo == 0 else 0
    if (remaining_b, remaining_digits, curr_modulo) in count_numbers_memo:
        return count_numbers_memo[remaining_b, remaining_digits, curr_modulo]
    s = 0
    for i in range(1, min(9, remaining_b) + 1):
        s += count_numbers_2(remaining_b - i, remaining_digits - 1, (curr_modulo + (10 ** (remaining_digits - 1)) * i) % a)
    count_numbers_memo[remaining_b, remaining_digits, curr_modulo] = s
    return s

def search_sol():
    # find the number of digits
    left_k, right_k = 0, None
    for digits in range(1, b + 1):
        delta = count_numbers_2(b, digits, 0)
        print(f'With {digits} digits there are {delta} numbers')
        if left_k + delta <= k - 1:
            left_k += delta
        else:
            right_k = left_k + delta
            break
    curr = [0] * digits
    # determine each digit
    for found_digits in range(digits):
        remaining_digits = digits - found_digits - 1
        curr_found = int(''.join(str(x) for x in curr))
        curr_modulo = curr_found % a
        remaining_b = b - sum(curr)
        print(f"Found {found_digits} digits, mod {curr_modulo}, rem {remaining_b}", curr_found)
        for next_digit in range(1, min(9, remaining_b) + 1):
            delta = count_numbers_2(remaining_b - next_digit, digits - found_digits - 1, (curr_modulo + (10 ** remaining_digits) * next_digit) % a)
            if left_k + delta > k - 1:
                right_k = left_k + delta
                break
            left_k += delta
        curr[found_digits] = next_digit
    return int(''.join(str(x) for x in curr))

def main():
    print(search_sol())

if __name__ == '__main__':
    main()
