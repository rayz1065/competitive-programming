n = int(input())
paths = (input().split()
         for _ in range(n))

def tree_update (node, segments, changed):
    curr_segment = next(segments, None)
    if changed:
        node['.haschanges'] = True
    if curr_segment is not None:
        if not changed:
            node['.hasunchanged'] = True
        node.setdefault(curr_segment, {})
        tree_update(node[curr_segment], segments, changed)

def print_tree (node, curr_path):
    if not '.haschanges' in node:
        return
    if '.hasunchanged' not in node:
        print('/', '/'.join(curr_path), sep='')
        return
    for subdir_name, subdir in node.items():
        if subdir_name.startswith('.'):
            continue
        curr_path.append(subdir_name)
        print_tree(subdir, curr_path)
        curr_path.pop()

def solve():
    tree = {}
    for changed, path in paths:
        segments = iter(path.split('/'))
        next(segments)
        tree_update(tree, segments, changed == '1')
    print_tree(tree, [])

if __name__ == '__main__':
    solve()
