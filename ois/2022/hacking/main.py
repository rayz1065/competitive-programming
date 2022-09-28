import heapq

def read_input():
    input()
    return [int(x) for x in input().split()]

def calc_hash(x):
    v = []
    for i, ch in enumerate(x):
        before = sum(x[j] == ch for j in range(i))
        after = sum(x[j] == ch for j in range(i + 1, len(x)))
        v.append(before - after)
    return v

hsh = read_input()

def solve():
    curr = {}
    s = 0
    for val in hsh:
        if val not in curr:
            s+= 1
            if val > 0:
                # no solution
                return 0
            if val < 0:
                # need to search for more values
                curr.setdefault(val + 2, [])
                # uses the negative value to work with the min heap properly
                heapq.heappush(curr[val + 2], val)
        else:
            best = heapq.heappop(curr[val])
            if len(curr[val]) == 0:
                curr.pop(val)
            if val < -best:
                curr.setdefault(val + 2, [])
                heapq.heappush(curr[val + 2], best)
    if len(curr) > 0:
        # couldn't close all
        return 0
    return s

def solve_slow():
    curr = []
    s = 0
    for val in hsh:
        best = None
        for searched_val, max_val in curr:
            if val == searched_val and (best is None or max_val > best):
                best = max_val
        if best is None:
            s+= 1
            if val > 0:
                # no solution
                return 0
            if val < 0:
                # need to search for more values
                curr.append((val + 2, -val))
        else:
            curr.remove((val, best))
            if val < best:
                curr.append((val + 2, best))
    if len(curr) > 0:
        # couldn't close all
        return 0
    return s

if __name__ == '__main__':
    print(solve())
