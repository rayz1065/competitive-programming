n_ingredients, m_websites = (int(x) for x in input().split())

total_weights = [0 for _ in range(n_ingredients)]
NORMALIZED_WEIGHT = 10 ** 6

for _ in range(m_websites):
    weights = [int(x) for x in input().split()]
    weights_sum = sum(weights)
    # normalize to 1Kg
    normalizer = NORMALIZED_WEIGHT / weights_sum

    for i in range(n_ingredients):
        total_weights[i] += weights[i] * normalizer

avg_weights = (int(weight / m_websites) for weight in total_weights)
print(' '.join(str(x) for x in avg_weights))
