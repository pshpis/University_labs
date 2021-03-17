from math import sqrt, acos, asin, atan, pi
from sys import stdin
from copy import copy


class Vector3d:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other):
        return Vector3d(self.x + other.x, self.y + other.y, self.z + other.z)

    def __copy__(self):
        tmp = Vector3d()
        tmp.x = self.x
        tmp.y = self.y
        tmp.z = self.z
        return tmp

    def __neg__(self):
        return Vector3d(-self.x, -self.y, -self.z)

    def __sub__(self, other):
        return self + (-other)

    # scalar
    def __mul__(self, other):
        if isinstance(other, self.__class__):
            return self.x * other.x + self.y * other.y + self.z * other.z
        else:
            return Vector3d(self.x * other, self.y * other, self.x * other)

    def __repr__(self):
        return str(self.x) + " " + str(self.y) + " " + str(self.z) + "\n"

    def __rmul__(self, other):
        return self * other

    def __abs__(self):
        return sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.z == other.z

    def scan(self, input_file=stdin):
        tmp = [float(i) for i in input_file.readline().split()]
        self.x = tmp[0]
        self.y = tmp[1]
        self.z = tmp[2]
        return self


class Matrix:
    def __init__(self, width=0, height=0):
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

    def scan(self, input_file=stdin):
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

    def determinant(self):
        if self.width != self.height:
            return -1

        a = copy(self)
        det = 1
        n = a.width
        for i in range(n):
            k = i
            for j in range(i + 1, n):
                if abs(a.table[j][i]) > abs(a.table[k][i]):
                    k = j
            if a.table[k][i] == 0:
                det = 0
                break
            a.table[i], a.table[k] = a.table[k], a.table[i]
            if i != k:
                det = - det
            det *= a.table[i][i]
            for j in range(i + 1, n):
                a.table[i][j] /= a.table[i][i]
            for j in range(n):
                if j != i and a.table[j][i] != 0:
                    for k in range(i + 1, n):
                        a.table[j][k] -= a.table[i][k] * a.table[j][i]

        return det


class Plane:
    def __init__(self, point=Vector3d(), normal=Vector3d()):
        self.point = point
        self.normal = normal

    def scan(self, input_file=stdin):
        tmp = [float(i) for i in input_file.readline().split()]
        self.normal = Vector3d(tmp[0], tmp[1], tmp[2])
        self.point = Vector3d(tmp[3], tmp[4], tmp[5])
        return self

    def __repr__(self):
        return str(self.point) + str(self.normal)

    def point_side(self, r0):
        arr = self.getABCD()
        return r0.x * arr[0] + r0.y * arr[1] + r0.z * arr[2] + arr[3]

    def getABCD(self):
        arr = [self.normal.x, self.normal.y, self.normal.z, -self.normal * self.point]
        return arr

    def is_intersection3(self, plane2, plane3):
        m = Matrix(3, 3)
        plane1_ABCD = self.getABCD()
        plane2_ABCD = plane2.getABCD()
        plane3_ABCD = plane3.getABCD()

        m.table[0] = [plane1_ABCD[0], plane1_ABCD[1], plane1_ABCD[2]]
        m.table[1] = [plane2_ABCD[0], plane2_ABCD[1], plane2_ABCD[2]]
        m.table[2] = [plane3_ABCD[0], plane3_ABCD[1], plane3_ABCD[2]]

        det = m.determinant()
        return det != 0

    def intersection3(self, plane2, plane3):
        m = Matrix(3, 3)
        plane1_ABCD = self.getABCD()
        plane2_ABCD = plane2.getABCD()
        plane3_ABCD = plane3.getABCD()

        m.table[0] = [plane1_ABCD[0], plane1_ABCD[1], plane1_ABCD[2]]
        m.table[1] = [plane2_ABCD[0], plane2_ABCD[1], plane2_ABCD[2]]
        m.table[2] = [plane3_ABCD[0], plane3_ABCD[1], plane3_ABCD[2]]

        det = m.determinant()
        res = Vector3d()

        m.table[0] = [plane1_ABCD[3], plane1_ABCD[1], plane1_ABCD[2]]
        m.table[1] = [plane2_ABCD[3], plane2_ABCD[1], plane2_ABCD[2]]
        m.table[2] = [plane3_ABCD[3], plane3_ABCD[1], plane3_ABCD[2]]

        res.x = -m.determinant() / det

        m.table[0] = [plane1_ABCD[0], plane1_ABCD[3], plane1_ABCD[2]]
        m.table[1] = [plane2_ABCD[0], plane2_ABCD[3], plane2_ABCD[2]]
        m.table[2] = [plane3_ABCD[0], plane3_ABCD[3], plane3_ABCD[2]]

        res.y = -m.determinant() / det

        m.table[0] = [plane1_ABCD[0], plane1_ABCD[1], plane1_ABCD[3]]
        m.table[1] = [plane2_ABCD[0], plane2_ABCD[1], plane2_ABCD[3]]
        m.table[2] = [plane3_ABCD[0], plane3_ABCD[1], plane3_ABCD[3]]

        res.z = -m.determinant() / det

        return res


class Polyhedron:
    def __init__(self, arr=None):
        if arr is None:
            arr = []
        self.planes = arr

    def is_inner(self, point=Vector3d()):
        for plane in self.planes:
            if plane.point_side(point) > 0:
                return False
        return True

    def get_points(self):
        points = []
        for i in range(len(self.planes)):
            for j in range(i + 1, len(self.planes)):
                for k in range(j + 1, len(self.planes)):
                    plane1 = copy(self.planes[i])
                    plane2 = copy(self.planes[j])
                    plane3 = copy(self.planes[k])
                    point_intersection = Vector3d()
                    if plane1.is_intersection3(plane2, plane3):
                        point_intersection = plane1.intersection3(plane2, plane3)
                    else:
                        continue
                    if self.is_inner(point_intersection):
                        if point_intersection not in points:
                            points.append(point_intersection)
        return points

    def delete_1_extra_plane(self):
        sum_vector = Vector3d()
        for plane in self.planes:
            sum_vector += plane.normal
        if sum_vector == Vector3d():
            return
        k = -1
        for i in range(len(self.planes)):
            if sum_vector == self.planes[i].normal:
                k = i
                break
        if k != -1:
            self.planes.pop(k)
        return

    def sum_normal_vector(self):
        sum_vector = Vector3d()
        for plane in self.planes:
            sum_vector += plane.normal
        return sum_vector

    def delete_2_extra_plane(self):
        sum_vector = self.sum_normal_vector()
        if sum_vector == Vector3d():
            return
        k1 = -1
        k2 = -1
        for i in range(len(self.planes)):
            for j in range(i + 1, len(self.planes)):
                if sum_vector == self.planes[i].normal + self.planes[j].normal:
                    k1 = i
                    k2 = j
                    break
        if k1 != -1 and k2 != -1:
            self.planes.pop(k1)
            self.planes.pop(k2)
        return

    def get_edges(self):
        points = self.get_points()
        output_data = []
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                k = 0
                for plane in self.planes:
                    if plane.point_side(points[i]) == 0 and plane.point_side(points[j]) == 0:
                        k += 1
                if k == 2:
                    output_data.append([points[i].x, points[i].y, points[i].z, points[j].x, points[j].y, points[j].z])
        return output_data

    def delete_extra_planes(self):
        points = self.get_points()
        delete_arr = []
        for plane in self.planes:
            k = 0
            for point in points:
                if plane.point_side(point) == 0:
                    k += 1
            if k <= 2:
                delete_arr.append(plane)
        for plane in delete_arr:
            self.planes.remove(plane)


def main():
    input_file = open("input.txt", "rt")
    output_file = open("output.txt", "wt")

    m = int(input_file.readline())
    planes = []
    for i in range(m):
        new_plane = Plane().scan(input_file)
        if new_plane not in planes:
            planes.append(new_plane)

    polyhedron = Polyhedron(planes)
    polyhedron.delete_extra_planes()

    sum_vector = polyhedron.sum_normal_vector()

    balance = len(polyhedron.get_points()) - len(polyhedron.get_edges()) + len(polyhedron.planes)
    print(balance)

    if balance != 2:
        print(0, file=output_file)
    else:
        output_data = polyhedron.get_edges()

        print(len(output_data), file=output_file)
        for arr in output_data:
            for num in arr:
                print(num, file=output_file, end=' ')
            print('\n', file=output_file, end='')


if __name__ == '__main__':
    main()
