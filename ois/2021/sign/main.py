t = int(input())

def solve():
    a, b = (int(x) for x in input().split())
    if a <= 0 <= b:
        return '0'
    if a > 0:
        return '+'
    # both are negative...
    num_count = b - a + 1
    return '+' if num_count % 2 == 0 else '-'

for _ in range(t):
    print(solve())
