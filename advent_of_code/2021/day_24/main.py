import enum

class InstructionType(enum.Enum):
    INP='inp'
    ADD='add'
    MUL='mul'
    DIV='div'
    MOD='mod'
    EQL='eql'

class NodeType(enum.Enum):
    INP='inp'
    ADD='add'
    MUL='mul'
    DIV='div'
    MOD='mod'
    EQL='eql'
    CONST='const'

class NodePrinter:
    def __init__(self, env):
        self.env = env
        self.handlers = {
            NodeType.INP:   self.inp,
            NodeType.ADD:   self.add,
            NodeType.MUL:   self.mul,
            NodeType.DIV:   self.div,
            NodeType.MOD:   self.mod,
            NodeType.EQL:   self.eql,
            NodeType.CONST: self.const
        }
        self.memo = {}

    def print(self, node):
        if node not in self.memo:
            handler = self.handlers[node.node_t]
            self.memo[node] = handler(node)
        return self.memo[node]

    def const(self, node):
        return str(node.args[0])

    def inp(self, node):
        return f'input({node.args[0]})'

    def add(self, node):
        return f'({node.args[0]} + {node.args[1]})'

    def mul(self, node):
        return f'({node.args[0]} * {node.args[1]})'

    def div(self, node):
        return f'({node.args[0]} // {node.args[1]})'

    def mod(self, node):
        return f'({node.args[0]} % {node.args[1]})'

    def eql(self, node):
        return f'({node.args[0]} == {node.args[1]})'

class NodeFactory:
    def __init__(self, env):
        self.env = env
        self.memo = {}

    def generate(self, node_t: NodeType, args):
        args = tuple(args)
        key = (node_t, args)
        if key not in self.memo:
            node = Node(self.env, node_t, args)
            self.memo[key] = node
        return self.memo[key]

class Solver:
    def __init__(self, env):
        self.env = env
        self.memo = {}
        self.handlers = {
            NodeType.INP:   self.inp,
            NodeType.ADD:   self.add,
            NodeType.MUL:   self.mul,
            NodeType.DIV:   self.div,
            NodeType.MOD:   self.mod,
            NodeType.EQL:   self.eql,
            NodeType.CONST: self.const
        }
        self.inputs = []

    def inp(self, node):
        args = [self.solve(x) for x in node.args]
        return self.inputs[args[0]]

    def add(self, node):
        args = [self.solve(x) for x in node.args]
        return args[0] + args[1]

    def mul(self, node):
        args = [self.solve(x) for x in node.args]
        return args[0] * args[1]

    def div(self, node):
        args = [self.solve(x) for x in node.args]
        assert args[1] != 0
        return args[0] // args[1]

    def mod(self, node):
        args = [self.solve(x) for x in node.args]
        assert args[0] >= 0 and args[1] > 0
        return args[0] % args[1]

    def eql(self, node):
        args = [self.solve(x) for x in node.args]
        return int(args[0] == args[1])

    def const(self, node):
        return node.args[0]

    def solve(self, node):
        if node not in self.memo:
            handler = self.handlers[node.node_t]
            self.memo[node] = handler(node)
        return self.memo[node]

class Env:
    def __init__(self):
        self.printer = NodePrinter(self)
        self.factory = NodeFactory(self)
        self.solver = Solver(self)
        self.hashes_memo = {}

    def print(self, node):
        return self.printer.print(node)

    def generate_node(self, node_t: NodeType, args):
        return self.factory.generate(node_t, args)

    def evaluate_node(self, node):
        return self.solver.solve(node)

class Node:
    def __init__(self, env, node_t, args):
        self.node_t = node_t
        self.env = env
        self.args = args

    def __str__(self):
        return self.env.print(self)

    def is_const(self):
        return self.node_t == NodeType.CONST

class Instruction:
    def __init__(self, instr_t, ops):
        self.instr_t = instr_t
        self.ops = ops

    def __str__(self):
        ops_str = ' '.join(str(x) for x in self.ops)
        return f"{self.instr_t} {ops_str}"

class Computer:
    def __init__(self, env, instructions):
        self.env = env
        self.variables = {}
        for variable in ('x', 'y', 'z', 'w'):
            self.variables[variable] = self.env.generate_node(NodeType.CONST, [0])
        self.instructions = instructions
        self.handlers = {
            InstructionType.INP: self.inp,
            InstructionType.ADD: self.add,
            InstructionType.MUL: self.mul,
            InstructionType.DIV: self.div,
            InstructionType.MOD: self.mod,
            InstructionType.EQL: self.eql,
        }
        self.inputs_count = 0

    def parse(self):
        for instruction in self.instructions:
            handler = self.handlers[instruction.instr_t]
            handler(instruction)

    def op_to_node(self, op):
        if op in self.variables:
            return self.variables[op]
        return self.env.generate_node(NodeType.CONST, [int(op)])

    def inp(self, instruction: Instruction):
        variable = instruction.ops[0]
        idx = self.op_to_node(self.inputs_count)
        self.inputs_count+= 1
        self.variables[variable] = self.env.generate_node(NodeType.INP, [idx])

    def add(self, instruction: Instruction):
        variable = instruction.ops[0]
        var = self.variables[variable]
        other = self.op_to_node(instruction.ops[1])
        if other.is_const() and other.args[0] == 0:
            pass
        else:
            node_t = NodeType(instruction.instr_t.value)
            self.variables[variable] = self.env.generate_node(node_t, [var, other])

    def mul(self, instruction: Instruction):
        variable = instruction.ops[0]
        var = self.variables[variable]
        other = self.op_to_node(instruction.ops[1])
        if other.is_const() and other.args[0] == 0:
            self.variables[variable] = other
        else:
            node_t = NodeType(instruction.instr_t.value)
            self.variables[variable] = self.env.generate_node(node_t, [var, other])

    def div(self, instruction: Instruction):
        variable = instruction.ops[0]
        var = self.variables[variable]
        other = self.op_to_node(instruction.ops[1])

        if other.is_const() and other.args[0] == 1:
            pass
        else:
            node_t = NodeType(instruction.instr_t.value)
            self.variables[variable] = self.env.generate_node(node_t, [var, other])

    def mod(self, instruction: Instruction):
        variable = instruction.ops[0]
        var = self.variables[variable]
        other = self.op_to_node(instruction.ops[1])
        node_t = NodeType(instruction.instr_t.value)
        self.variables[variable] = self.env.generate_node(node_t, [var, other])

    def eql(self, instruction: Instruction):
        variable = instruction.ops[0]
        var = self.variables[variable]
        other = self.op_to_node(instruction.ops[1])
        node_t = NodeType(instruction.instr_t.value)
        self.variables[variable] = self.env.generate_node(node_t, [var, other])

def read_in():
    instructions = []
    try:
        while True:
            line = input()
            if line[0] == '#':
                raise EOFError
            line_segments = line.split(' ')
            instr_t = InstructionType(line_segments[0])
            ops = line_segments[1:]
            instructions.append(Instruction(instr_t, ops))
    except EOFError:
        pass
    env = Env()
    return Computer(env, instructions)

def main():
    computer = read_in()
    computer.parse()
    # for variable, val in computer.variables.items():
    #     print(variable, '=', val)
    env = computer.env

    env.solver.inputs = [int(x) for x in '21191861151161']
    for variable, node in computer.variables.items():
        print(variable, env.evaluate_node(node))

if __name__ == '__main__':
    main()
