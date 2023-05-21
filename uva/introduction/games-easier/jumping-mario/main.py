t = int(input().strip())

for case in range(1, t + 1):
    input()
    walls = [int(x) for x in input().strip().split()]
    total_high_jumps, total_low_jumps = 0, 0

    curr_height = walls[0]
    for wall in walls:
        if curr_height > wall:
            total_low_jumps += 1
        elif curr_height < wall:
            total_high_jumps += 1
        curr_height = wall
    print(f'Case {case}: {total_high_jumps} {total_low_jumps}')
