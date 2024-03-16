def count_peaks(heights):
    s = 0
    heights = [-1, *heights, -1]
    for i, height in enumerate(heights):
        if i == 0 or i + 1 == len(heights):
            continue

        if heights[i] > heights[i - 1] and heights[i] > heights[i + 1]:
            s += 1

    return s


def main ():
    input()
    row_heights = [int(x) for x in input().strip().split()]
    col_heights = [int(x) for x in input().strip().split()]

    print(count_peaks(row_heights) * count_peaks(col_heights))


if __name__ == '__main__':
    main()
