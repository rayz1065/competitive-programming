from math import ceil

def read_transfers (remaining):
    while remaining > 0:
        transfer = int(input().strip())
        yield transfer
        remaining -= transfer

def main ():
    tc = 0
    while True:
        tc += 1
        remaining = int(input().strip())
        if remaining == 0:
            break

        transfers = list(read_transfers(remaining))

        print(f'Output for data set {tc}, {remaining} bytes:')
        for i in range(0, len(transfers) - len(transfers) % 5, 5):
            current_upload = sum(transfers[i:i + 5])
            remaining -= current_upload
            speed = max(1e-9, current_upload / 5) # avoid division by 0
            remaining_time = ceil(remaining / speed)

            remaining_str = 'stalled' if current_upload == 0 else f'{remaining_time} seconds'
            print(f'   Time remaining: {remaining_str}')

        print(f'Total time: {len(transfers)} seconds')
        print()


if __name__ == '__main__':
    main()
