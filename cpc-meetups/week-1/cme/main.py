t = int(input().strip())
for _ in range(t):
    n = int(input().strip())
    if n == 2:
        print(2)
    elif n % 2 == 1:
        print(1)
    else:
        print(0)
