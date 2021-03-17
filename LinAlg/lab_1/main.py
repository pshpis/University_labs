from sys import stdin
from copy import copy


class Matrix:
    def __init__(self, width = 0, height = 0):
        self.width = width
        self.height = height
        self.table = []

        for i in range(self.height):
            self.table.append([])
            for j in range(self.width):
                self.table[i].append(0.0)
    def __add__(self, other):
        if self.width == other.width and self.height == other.height:
            res = Matrix(self.width, self.height)
            for i in range(self.height):
                for j in range(self.width):
                    res.table[i][j] = self.table[i][j] + other.table[i][j]

            print(res.table)
            return res
        else:
            raise RuntimeError

    def __copy__(self):
        tmp = Matrix()
        tmp.height = self.height
        tmp.width = self.width

        for i in range(self.height):
            tmp.table.append([])
            for j in range(self.width):
                tmp.table[i].append(self.table[i][j])

        return tmp

    def __getitem__(self, item):
        return self.table[item]

    def __neg__(self):
        res = copy(self)
        for i in range(self.height):
            for j in range(self.width):
                res.table[i][j] = -res.table[i][j]
        return res

    def __sub__(self, other):
        return self + (-other)

    def __mul__(self, other):
        if isinstance(other, self.__class__):
            if self.width == other.height:
                res = Matrix(other.width, self.height)
                for i in range(self.height):
                    for j in range(other.width):
                        for k in range(self.width):
                            res.table[i][j] += self.table[i][k] * other.table[k][j]
                return res
            else:
                raise RuntimeError

        elif isinstance(other, (int, float)):
            res = Matrix(self.width, self.height)
            for i in range(self.height):
                for j in range(self.width):
                    res.table[i][j] = self.table[i][j] * other
            return res

    def transpose(self):
        res = Matrix(self.height, self.width)
        for i in range(self.height):
            for j in range(self.width):
                res.table[j][i] = self.table[i][j]
        return res

    def __rmul__(self, other):
        return self * other

    def scan(self, input_file = stdin):
        print("Here1.5")
        tmp = input_file.readline().split()
        print(tmp)
        self.height = int(tmp[0])
        self.width = int(tmp[1])
        self.table = []

        print("Here2")
        tmp = list(input_file.readline().split())
        print(tmp)
        k = 0

        for i in range(self.height):
            self.table.append([])
            for j in range(self.width):
                self.table[i].append(float(tmp[k]))
                k = k + 1

    def __repr__(self):
        result_str = str(self.height) + " " + str(self.width) + "\n"
        for i in range(self.height):
            for j in range(self.width):
                result_str = result_str + str(self.table[i][j]) + " "
            result_str = result_str + "\n"
        return result_str


if __name__ == '__main__':
    input_file = open("input.txt", "rt")
    output_file = open("output.txt", "wt")

    tmp = input_file.readline().split()
    alpha = float(tmp[0])
    beta = float(tmp[1])
    A = Matrix()
    B = Matrix()
    C = Matrix()
    D = Matrix()
    F = Matrix()
    print("Here1")
    A.scan(input_file)
    B.scan(input_file)
    C.scan(input_file)
    D.scan(input_file)
    F.scan(input_file)

    print("Here")
    try:
        print(1, C * ((alpha * A + beta * (B.transpose())).transpose()) * D - F, sep = '\n', end = '', file = output_file)
        # print(A * -1)
    except RuntimeError:
        print(0, sep = '\n', end = '', file = output_file)

    input_file.close()
    output_file.close()

