t = int(input().strip())

for case in range(1, t + 1):
    speeds = [int(x) for x in input().strip().split()][1:]
    print(f'Case {case}: {max(speeds)}')
