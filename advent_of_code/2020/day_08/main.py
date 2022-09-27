from typing import List
from enum import Enum

class InstructionType(Enum):
    NOP = "nop"
    ACC = "acc"
    JMP = "jmp"
    
class Instruction:
    op: InstructionType
    value: int

    def __init__(self, instructionString: str):
        op, value = instructionString.split(' ')
        self.op = InstructionType(op)
        self.value = int(value)
    
    def __str__(self):
        return self.op.value + ' ' + str(self.value)

class Computer:
    counter: int
    instructionPointer: int
    instructions: List[Instruction]
    visited: dict

    lastCounter: int
    jump: bool
    alreadyVisited: bool

    finished: bool
    invalidIP: bool

    def __init__(self, instructions: List[Instruction]):
        self.instructions = instructions
        self.visited = dict()
        self.counter = 0
        self.instructionPointer = 0
        self.lastCounter = None
        self.alreadyVisited = False
        self.jump = False
        self.finished = False
        self.invalidIP = False

    def canContinue(self):
        return not self.invalidIP and not self.finished

    def step(self):
        if self.finished:
            raise Exception('Computer has already finished executing')
        if self.instructionPointer >= len(self.instructions):
            raise Exception('Instruction out of bounds')

        curr: Instruction = self.instructions[self.instructionPointer]

        self.jump = False
        self.alreadyVisited = False
        self.lastCounter = self.counter

        if curr.op == InstructionType.ACC:
            self.counter+= curr.value

        if curr.op == InstructionType.NOP:
            pass

        if curr.op == InstructionType.JMP:
            self.instructionPointer+= curr.value
            self.jump = True

        if not self.jump:
            self.instructionPointer+= 1
        
        if self.visited.get(self.instructionPointer, False):
            self.alreadyVisited = True
        self.visited[self.instructionPointer] = True

        if len(self.instructions) == self.instructionPointer:
            self.finished = True
        if self.instructionPointer > len(self.instructions):
            self.invalidIP = True

def inputData():
    data = []

    try:
        while True:
            data.append(input())
    except EOFError:
        pass
    return data

def part1(computer: Computer):
    while not computer.alreadyVisited:
        computer.step()
    return computer.lastCounter

def simPart2(computer: Computer):
    while not computer.alreadyVisited and computer.canContinue():
        computer.step()
    return computer.finished

def part2(instructions: List[Instruction]):
    for instruction in instructions:
        currType = instruction.op
        otherType = None

        if currType == InstructionType.JMP:
            otherType = InstructionType.NOP
        if currType == InstructionType.NOP:
            otherType = InstructionType.JMP
        
        if otherType != None:
            instruction.op = otherType
            computer = Computer(instructions)
            if simPart2(computer):
                return computer.counter
            instruction.op = currType

def main():
    lines = inputData()
    instructions = []
    for line in lines:
        instructions.append(Instruction(line))

    computer = Computer(instructions)
    print("1)", part1(computer))
    print("2)", part2(instructions))

    
if __name__ == "__main__":
    main()
