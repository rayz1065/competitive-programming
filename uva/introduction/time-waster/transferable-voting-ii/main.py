def is_valid (vote):
    n_candidates = len(vote)
    if len(set(vote)) != len(vote):
        return False
    if any(not (1 <= x <= n_candidates) for x in vote):
        return False
    return True


def count_votes (votes):
    candidates = {}
    for vote in votes:
        if len(vote) > 0:
            candidates.setdefault(vote[0], 0)
            candidates[vote[0]] += 1
    return candidates


def compute_results (votes):
    required_votes = len(votes) // 2 + 1
    while True:
        candidates = count_votes(votes)
        min_score = min(y for y in candidates.values())
        max_score = max(y for y in candidates.values())

        if max_score >= required_votes:
            winner = [x for x, y in candidates.items() if y == max_score]
            return winner

        if min_score == max_score:
            return list(candidates.keys())

        loser = next(x for x, y in candidates.items() if y == min_score)
        for vote in votes:
            vote.remove(loser)


def main ():
    tc = 0
    while True:
        n_candidates, m_voters = (int(x) for x in input().strip().split())
        if n_candidates == 0:
            break
        votes = [[int(x) for x in input().strip().split()]
                 for _ in range(m_voters)]

        invalid_votes = sum(1 for x in votes if not is_valid(x))
        votes = [x for x in votes if is_valid(x)]
        results = compute_results(votes)

        tc += 1
        print(f'Election #{tc}')
        if invalid_votes > 0:
            print(f'   {invalid_votes} bad ballot(s)')
        if len(results) == 1:
            print(f'   Candidate {results[0]} is elected.')
        else:
            print('   The following candidates are tied:', ' '.join(str(x) for x in results))


if __name__ == '__main__':
    main()
