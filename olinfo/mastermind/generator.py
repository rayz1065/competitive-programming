from random import choice
bucket_size = 3
all_combs = []
def find_combs (curr):
    global all_combs
    if len(curr) == bucket_size:
        all_combs.append(''.join(curr))
        return
    for x in "BRG":
        curr.append(x)
        find_combs(curr)
        curr.pop()

find_combs([])
# print(len(all_combs) * bucket_size)
# print(0)
# print(''.join(all_combs))

n = 20000
print(n)
print(0)
print(''.join(choice("BRG") for _ in range(n)))