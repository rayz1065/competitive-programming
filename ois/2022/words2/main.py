def read_input():
    return input()

word = read_input()
mod = 1000000007

def solve():
    # hash the input string
    s = 0
    for x in word:
        s = (s * 26 + ord(x) - ord('a') + 1) % mod
    return s - 1

if __name__ == '__main__':
    print(solve())
