import heapq

n_tag, t = (int(x) for x in input().split())
tags = list(input() for _ in range(n_tag))

freqs = {}
freq_map = [[] for _ in range(50001)]
highest_freq = 0

def add_tag(tag):
    freqs.setdefault(tag, 0)
    freqs[tag] += 1
    heapq.heappush(freq_map[freqs[tag]], tag)
    globals()['highest_freq'] = max(freqs[tag], highest_freq)

def rem_tag(tag):
    freqs[tag] -= 1
    if freqs[tag] == 0:
        freqs.pop(tag)

def popular_tag():
    while freqs.get(freq_map[highest_freq][0], 0) != highest_freq:
        heapq.heappop(freq_map[highest_freq])
        if len(freq_map[highest_freq]) == 0:
            globals()['highest_freq'] -= 1
    return freq_map[highest_freq][0]

def solve():
    for i, tag in enumerate(tags):
        add_tag(tag)
        if i >= t:
            rem_tag(tags[i - t])
        if i >= t - 1:
            print(popular_tag())

if __name__ == '__main__':
    # this is probably not fast enough
    # also it's not very elegant without a BST
    solve()
