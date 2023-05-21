t = int(input().strip())
for case in range(1, t + 1):
    websites = []
    best_relevance = -1
    for _ in range(10):
        website, relevance = input().strip().split()
        relevance = int(relevance)
        if relevance > best_relevance:
            websites = []
            best_relevance = relevance
        if relevance == best_relevance:
            websites.append(website)
    print(f'Case #{case}:')
    print('\n'.join(websites))
