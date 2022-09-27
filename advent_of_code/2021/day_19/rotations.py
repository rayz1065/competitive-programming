from math import sin, cos, pi
import numpy as np
from day_19.coords import Coords

rotation_matrix_memo = {}

def rotation_matrix(rotation):
    if rotation in rotation_matrix_memo:
        return rotation_matrix_memo[rotation]
    x_rot, y_rot, z_rot = rotation
    matrot_x = [
        [1, 0, 0],
        [0, cos(x_rot*pi/2), -sin(x_rot*pi/2)],
        [0, sin(x_rot*pi/2), cos(x_rot*pi/2)],
    ]
    matrot_y = [
        [cos(y_rot*pi/2), 0, sin(y_rot*pi/2)],
        [0, 1, 0],
        [-sin(y_rot*pi/2), 0, cos(y_rot*pi/2)],
    ]
    matrot_z = [
        [cos(z_rot*pi/2), -sin(z_rot*pi/2), 0],
        [sin(z_rot*pi/2), cos(z_rot*pi/2), 0],
        [0, 0, 1]
    ]
    matrot_x = [[round(x) for x in row] for row in matrot_x]
    matrot_y = [[round(x) for x in row] for row in matrot_y]
    matrot_z = [[round(x) for x in row] for row in matrot_z]
    res = np.matmul(np.matmul(matrot_x, matrot_y), matrot_z)
    rotation_matrix_memo[rotation] = res
    return res

def all_rotations():
    found = set()
    for other in range(-1, 3):
        for x_rot in range(-1, 3):
            rot = (x_rot, other, 0)
            if rot not in found:
                found.add(rot)
                yield rot
        for y_rot in range(-1, 3):
            rot = (other, y_rot, 0)
            if rot not in found:
                found.add(rot)
                yield rot
        for z_rot in range(-1, 3):
            rot = (other, 0, z_rot)
            if rot not in found:
                found.add(rot)
                yield rot

def rotated_coords(coords, rotation):
    vec = list(coords)
    mat = rotation_matrix(rotation)
    x, y, z = np.matmul(mat, vec)
    return Coords(x, y, z)
