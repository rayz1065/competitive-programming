from itertools import combinations


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(tuple(line.split("-")))
    return res


def make_graph(branches):
    nodes = set(x for branch in branches for x in branch)
    graph = {x: [] for x in nodes}
    for a, b in branches:
        graph[a].append(b)
        graph[b].append(a)
    return graph


def part_1(branches):
    branches_full = set(branches).union((b, a) for a, b in branches)
    graph = make_graph(branches)

    t_nodes = filter(lambda x: x.startswith("t"), graph.keys())
    res = set()
    for node in t_nodes:
        for target_1, target_2 in combinations(graph[node], r=2):
            if (target_1, target_2) in branches_full:
                res.add(tuple(sorted((node, target_1, target_2))))

    return len(res)


def part_2(branches):
    branches_full = set(branches).union((b, a) for a, b in branches)
    graph = make_graph(branches)

    triangles = set()
    for node in graph.keys():
        for target_1, target_2 in combinations(graph[node], r=2):
            if (target_1, target_2) in branches_full:
                triangles.add(tuple(sorted((node, target_1, target_2))))

    triangle_frequencies = {node: 0 for node in graph.keys()}
    for triangle in triangles:
        for node in triangle:
            triangle_frequencies[node] += 1

    # fair assumption about the size of the max clique
    clique_size = len(graph[next(iter(graph))])
    target_triangles = (clique_size - 1) * (clique_size - 2) // 2
    nodes = [
        node
        for node, value in triangle_frequencies.items()
        if value >= target_triangles
    ]

    def find_max_clique(i, curr):
        if i == len(nodes):
            return curr

        res = find_max_clique(i + 1, curr)
        if all((nodes[i], x) in branches_full for x in curr):
            sub_res = find_max_clique(i + 1, curr.union((nodes[i],)))
            if len(sub_res) > len(res):
                res = sub_res

        return res

    return ",".join(sorted(find_max_clique(0, set())))


def main():
    branches = read_input()
    print("part1", part_1(branches))
    print("part2", part_2(branches))


if __name__ == "__main__":
    main()
