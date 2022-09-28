def read_inputs():
    input()
    purchases = (int(x) for x in input().split())
    from_streaming = (int(x) for x in input().split())
    return (x if s else 0 for x, s in zip(purchases, from_streaming))

values = read_inputs()

def solve():
    prev_v = -1
    best_seq = 0
    curr_seq = 0
    for v in values:
        if v >= prev_v:
            curr_seq += v
            if curr_seq > best_seq:
                best_seq = curr_seq
        else:
            curr_seq = v
        prev_v = v
    return best_seq

if __name__ == '__main__':
    print(solve())
