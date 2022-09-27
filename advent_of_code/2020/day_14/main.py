import re

def inputData():
    data = []
    try:
        while True:
            line = input()
            access, newValue = line.split(' = ')
            memMatch = re.fullmatch(r'mem\[(\d+)\]', access)
            if memMatch != None:
                address, = memMatch.groups()
                access = int(address)
                newValue = int(newValue)
            data.append((access, newValue))
    except EOFError:
        pass
    return data

def zeroMask(mask):
    zm = 2**len(mask) - 1
    for i, m in enumerate(mask):
        i = (len(mask) - 1) - i
        if m == '0':
            zm-= 2**i
    return zm

def oneMask(mask):
    om = 0
    for i, m in enumerate(mask):
        i = (len(mask) - 1) - i
        if m == '1':
            om+= 2**i
    return om

def calcValue(value, zm, om):
    return (value | om) & zm

def part1(data: list):
    zm, om, mask = None, None, None
    memory = dict()
    for d in data:
        access, newValue = d
        if access == 'mask':
            zm = zeroMask(newValue)
            om = oneMask(newValue)
            mask = newValue
        else:
            assignedValue = calcValue(newValue, zm, om)
            # print('{0:036b}'.format(newValue), mask, '{0:036b}'.format(assignedValue), assignedValue, sep='\n')
            memory[access] = assignedValue
    return sum(memory.values())

def calcAddresses2(address, mask):
    addresses = []
    floatingBits = []
    for i, m in enumerate(mask):
        i = len(mask) - i - 1
        if m == '1':
            address|= 2**i
        if m == 'X':
            floatingBits.append(i)

    addresses.append(address)
    for bit in floatingBits:
        for address in [x for x in addresses]:
            if address & (2**bit):
                addresses.append(address - (2**bit))
            else:
                addresses.append(address + (2**bit))
    return addresses

def part2(data: list):
    mask = None
    memory = dict()
    for d in data:
        access, newValue = d
        if access == 'mask':
            mask = newValue
        else:
            assignedValue = newValue
            addresses = calcAddresses2(access, mask)
            for address in addresses:
                memory[address] = assignedValue
    return sum(memory.values())


def main():
    data = inputData()
    print("1)", part1(data))
    print("2)", part2(data))

if __name__ == "__main__":
    main()