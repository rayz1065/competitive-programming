n = int(input())
lines = (input().lower() for _ in range(n))

def is_quasi_isogram(sentence):
    freq = {}
    for x in sentence:
        if 'a' <= x <= 'z':
            freq.setdefault(x, 0)
            freq[x]+= 1
            if freq[x] > 2:
                return False
    return True

def solve():
    s = 0
    for line in lines:
        s+= is_quasi_isogram(line)
    return s

if __name__ == '__main__':
    print(solve())
