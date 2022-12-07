import re

class Command:
    def __init__(self, command, args=None, output=None):
        self.command = command
        if args is None:
            args = []
        if output is None:
            output = []
        self.args = args
        self.output = output

    def __str__(self):
        args_str = ' '.join(self.args)
        out_str = '\n'.join(self.output)
        return f'$ {self.command} {args_str}' + (f'\n{out_str}' if len(self.output) > 0 else '')

class DirNode:
    def __init__(self, name):
        self._cached_size = None
        self.name = name
        self.files = []
        self.dirs = dict()

    def size (self):
        if self._cached_size is None:
            self._cached_size = sum(x[1] for x in self.files) + sum(x.size() for x in self.dirs.values())
        return self._cached_size

    def __str__(self):
        return f'dir({self.name}, {self.size()})'

def parse_input ():
    lines = []
    try:
        while True:
            lines.append(input())
    except EOFError:
        pass
    commands = []
    outputs = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if line == '$ ls':
            # read the output
            j = i + 1
            while j < len(lines) and lines[j][0] != '$':
                j += 1
            comm = Command('ls', None, lines[i + 1:j])
            commands.append(comm)
            i = j
        else:
            res = re.match(r'^\$ cd (.+)$', line)
            assert res is not None, line
            comm = Command('cd', res.groups())
            commands.append(comm)
            i += 1
    return commands

def main ():
    commands = parse_input()
    root = DirNode('/')
    dir_stack = []
    all_dirs = [root]
    for comm in commands:
        if comm.command == 'cd':
            if comm.args[0] == '/':
                dir_stack = [root]
            elif comm.args[0] == '..':
                dir_stack.pop()
            else:
                curr = dir_stack[-1]
                dir_stack.append(curr.dirs[comm.args[0]])
        else: # ls
            dirs = [x for x in comm.output if x.startswith('dir')]
            files = list(set(comm.output) - set(dirs))
            dirs = [x[4:] for x in dirs]
            dirs = { x: DirNode(x) for x in dirs }
            files = [x.split(' ') for x in files]
            files = [(x[1], int(x[0])) for x in files]
            curr = dir_stack[-1]
            curr.files = files
            curr.dirs = dirs
            all_dirs.extend(dirs.values())

    small_dirs = [x for x in all_dirs if x.size() <= 100000]
    print('part_1', sum(x.size() for x in small_dirs))
    total_space = 70000000
    occupied_space = root.size()
    req_space = 30000000
    free_space = total_space - occupied_space
    min_del = req_space - free_space
    possible = [x for x in all_dirs if x.size() >= min_del]
    print('part_2', min(x.size() for x in possible))

if __name__ == '__main__':
    main()
