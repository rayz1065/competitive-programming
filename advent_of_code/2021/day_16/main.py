from enum import Enum
# from functools import reduce
from math import prod

class OperationType(Enum):
    SUM = 0
    PRODUCT = 1
    MINIMUM = 2
    MAXIMUM = 3
    LITERAL = 4
    GT = 5
    LT = 6
    EQ = 7

def read_in():
    return input()

def hex_to_bin(hex_str):
    bin_str = []
    for hex_dig in hex_str:
        digit = int(hex_dig, 16)
        bin_str.append(bin(digit)[2:].zfill(4))
    return ''.join(bin_str)

class Packet:
    def __init__(self, version, p_type):
        self.version = version
        self.p_type = OperationType(p_type)
        self.literal_value = None
        self.sub_packets = []

    def set_val(self, literal_value):
        self.literal_value = literal_value

    def is_literal(self):
        return self.p_type == OperationType.LITERAL

    def is_operator(self):
        return not self.is_literal()

    def sum_of_versions(self):
        return self.version + sum(x.sum_of_versions() for x in self.sub_packets)

    def compute_value(self):
        operators = {
            OperationType.SUM: sum,
            # lambda values: reduce(lambda acc, x: acc * x, values, 1)
            OperationType.PRODUCT: prod,
            OperationType.MINIMUM: min,
            OperationType.MAXIMUM: max,
            OperationType.LITERAL: lambda _: self.literal_value,
            OperationType.GT: lambda xs: int(next(xs)  > next(xs)),
            OperationType.LT: lambda xs: int(next(xs)  < next(xs)),
            OperationType.EQ: lambda xs: int(next(xs) == next(xs)),
        }
        values = (x.compute_value() for x in self.sub_packets)
        return operators[self.p_type](values)

def parse(packet_str):
    i = 0
    version = int(packet_str[i:i+3], 2)
    i+= 3
    p_type = int(packet_str[i:i+3], 2)
    i+= 3
    packet = Packet(version, p_type)

    if packet.is_literal():
        # read 5 bits at the time, if the first one is zero
        # it means we've reached the end of the literal value
        val = 0
        stop_found = False
        while not stop_found:
            if packet_str[i] == '0':
                stop_found = True
            i+= 1
            val = val * 16 + int(packet_str[i:i+4], 2)
            i+= 4
        packet.set_val(val)
    else:
        # this is an operator
        # check the length ID
        length_id = packet_str[i]
        i+= 1
        if length_id == '0':
            # the next 15 bits represent the total length in bits
            # of the sub-packets contained in this packet
            subp_len = int(packet_str[i:i + 15], 2)
            i+= 15
            nxt_i = i
            while nxt_i < i + subp_len:
                subp, count_read = parse(packet_str[nxt_i:i + subp_len])
                packet.sub_packets.append(subp)
                nxt_i+= count_read
            assert nxt_i == i + subp_len, f"should be {i + subp_len} got {nxt_i}"
            i = nxt_i
        else:
            # the next 11 bits represent the number
            # of subpackets contained in this one
            subp_count = int(packet_str[i:i + 11], 2)
            i+= 11
            for _ in range(subp_count):
                subp, count_read = parse(packet_str[i:])
                packet.sub_packets.append(subp)
                i+= count_read
    return packet, i

def main():
    problem = read_in()
    bin_problem = hex_to_bin(problem)
    packet, _ = parse(bin_problem)
    print('part_1:', packet.sum_of_versions())
    print('part_2:', packet.compute_value())

if __name__ == '__main__':
    main()
