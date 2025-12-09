import enum
from re import sub
from typing import DefaultDict


class AddOp:
    def __init__(self) -> None:
        self.res = 0

    def op(self, num):
        print(f"{self.res} += {num}")
        self.res += num

    def reset(self):
        self.res = 0


class MulOp:
    def __init__(self) -> None:
        self.res = 1

    def op(self, num):
        print(f"{self.res} *= {num}")
        self.res *= num

    def reset(self):
        self.res = 1


def main():
    with open("/Users/whysoserious/repos/aoc/aoc25/day6/input.txt", "r") as inputFile:
        lines = inputFile.readlines()

    cols = DefaultDict(int)
    for line in lines[:-1]:
        for i in range(len(line) - 1, -1, -1):
            if line[i].isdigit():
                cols[i] = cols[i] * 10 + int(line[i])

    op = AddOp()
    total_sum = 0
    print(cols)
    for col_num in sorted(cols):
        if lines[-1][col_num] == "+":
            total_sum += op.res
            op = AddOp()
        elif lines[-1][col_num] == "*":
            total_sum += op.res
            op = MulOp()

        op.op(cols[col_num])

    total_sum += op.res

    print(total_sum)


if __name__ == "__main__":
    main()
