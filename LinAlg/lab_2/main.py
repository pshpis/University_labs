from math import sqrt, acos, asin, atan, pi

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
        return self.x * other.x + self.y * other.y + self.z * other.z

    def __repr__(self):
        return str(self.x) + " " + str(self.y) + " " + str(self.z) + "\n"

    def point_side(self, point):
        res = self.x * point.y - self.y * point.x
        if res > 0:
            return 1
        if res < 0:
            return -1
        return 0

    def __abs__(self):
        return sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    def angle_between(self, other):
        return acos(self * other / (abs(self) * abs(other)))

    def get_normal(self):
        return Vector3d(self.y, -self.x)

    def angle_from_normal(self, other):
        return self.get_normal().angle_between(other) * self.get_normal().point_side(other)


def main():
    input_file = open("input.txt", "rt")
    output_file = open("output.txt", "wt")
    ship_str = [float(i) for i in input_file.readline().split()]
    ship = Vector3d(ship_str[0], ship_str[1])

    keel_str = [float(i) for i in input_file.readline().split()]
    keel = Vector3d(keel_str[0], keel_str[1])

    mast_str = [float(i) for i in input_file.readline().split()]
    mast = Vector3d(mast_str[0], mast_str[1])

    enemy_str = [float(i) for i in input_file.readline().split()]
    enemy = Vector3d(enemy_str[0], enemy_str[1])

    enemy = enemy - ship

    output_file.write(str(keel.point_side(enemy)) + "\n")

    ang = keel.angle_from_normal(enemy) / pi * 180
    if ang > 90:
        ang = 180 - ang
    if abs(ang) > 60:
        ang = 0
    output_file.write(str(ang) + "\n")

    if abs(mast) == 0:
        output_file.write("0\n")
    else:
        # print(1 / abs(mast))
        mast.z = 1
        print(-keel.get_normal().angle_between(mast) / pi * 180)
        ang = 90 - mast.angle_between(-keel.get_normal()) / pi * 180
        # ang = atan(1/abs(mast)) / pi * 180 * (keel.point_side(mast))
        if ang > 90:
            ang = 180 - ang
        output_file.write(str(ang) + "\n")
    output_file.write("Bye\n")


if __name__ == '__main__':
    main()


