testcases = int(input().strip())

for _ in range(testcases):
    n_farmers = int(input().strip())
    farmers = [tuple(int(x) for x in input().strip().split())
               for _ in range(n_farmers)]

    s = 0
    for farm_size, _, env_score in farmers:
        s += farm_size * env_score
    print(s)
