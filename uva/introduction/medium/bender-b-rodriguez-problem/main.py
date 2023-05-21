DIRECTION_MAPS = {
    # rotate counterclockwise
    '-z': ['+x', '-z', '-x', '+z'],
    # rotate clockwise
    '+z': ['+x', '+z', '-x', '-z'],
    # rotate counterclockwise
    '-y': ['+x', '-y', '-x', '+y'],
    # rotate clockwise
    '+y': ['+x', '+y', '-x', '-y'],
    'No': []
}

while True:
    if input().strip() == '0':
        break
    decisions = input().strip().split()

    direction = '+x'
    for decision in decisions:
        direction_map = DIRECTION_MAPS[decision]
        if direction in direction_map:
            curr_idx = direction_map.index(direction)
            direction = direction_map[(curr_idx + 1) % 4]

    print(direction)
