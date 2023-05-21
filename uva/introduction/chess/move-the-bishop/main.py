t = int(input().strip())
for _ in range(t):
    input()
    q_queries, n = (int(input().strip()) for _ in range(2))
    queries = [tuple(int(x) for x in input().strip().split()) for _ in range(q_queries)]

    for x, y, x_to, y_to in queries:
        if (x + y) % 2 != (x_to + y_to) % 2:
            print('no move')
        elif (x, y) == (x_to, y_to):
            print('0')
        elif abs(x - x_to) == abs(y - y_to):
            print('1')
        else:
            print('2')
