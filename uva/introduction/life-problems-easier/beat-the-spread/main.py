def main ():
    t = int(input().strip())
    for _ in range(t):
        scores_sum, scores_diff = (int(x) for x in input().strip().split())
        min_score = (scores_sum - scores_diff) // 2
        max_score = min_score + scores_diff

        if min_score < 0 or min_score + max_score != scores_sum:
            print('impossible')
        else:
            print(max_score, min_score)


if __name__ == '__main__':
    main()
