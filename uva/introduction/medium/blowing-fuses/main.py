t = 1
while True:
    devices, m_operations, capacity = (int(x) for x in input().strip().split())
    if devices == 0:
        break
    consumptions = [int(input().strip()) for _ in range(devices)]
    operations = [int(input().strip()) - 1 for _ in range(m_operations)]

    states = [0] * devices
    total_draw = 0
    max_draw = 0

    for device_id in operations:
        total_draw -= states[device_id] * consumptions[device_id]
        states[device_id] = 1 - states[device_id]
        total_draw += states[device_id] * consumptions[device_id]
        max_draw = max(max_draw, total_draw)

    print(f'Sequence {t}')
    if max_draw > capacity:
        print('Fuse was blown.')
    else:
        print('Fuse was not blown.')
        print(f'Maximal power consumption was {max_draw} amperes.')
    print()

    t += 1
