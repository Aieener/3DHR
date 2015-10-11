#Author: Yuding Ai
#2015-July-22
#Visualize 3D hard rod on each layer

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()

# ================================ Draw Ver Rods ===========================
ax = fig.add_subplot(111, projection='3d')
a=0
with open("3dplotv.txt", "r") as file:
    for line in file:
        a= a+1

xpos = np.zeros(a)
ypos = np.ones(a)
zpos = np.zeros(a)

i = 0
with open("3dplotv.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = words[0]
        wy = words[1]
        wz = words[2]
        xpos[i] = wx
        # ypos[i] = wy
        zpos[i] = wz
        i = i+1

dx = np.ones(a)
dy = np.ones(a)
dz = np.ones(a)

for y in range(0,a):
    dy[y] = 8
if a != 0:
    ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color='b',alpha=0.2)


# ================================ Draw Hor Rods ===========================
a2=0
with open("3dploth.txt", "r") as file:
    for line in file:
        a2= a2+1

xpos2 = np.zeros(a2)
ypos2 = np.ones(a2)
zpos2 = np.zeros(a2)

i = 0
with open("3dploth.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = words[0]
        wy = words[1]
        wz = words[2]
        xpos2[i] = wx
        # ypos2[i] = wy
        zpos2[i] = wz
        i = i+1

dx2 = np.ones(a2)
dy2 = np.ones(a2)
dz2 = np.ones(a2)

for x in range(0,a2):
    dx2[x] = 1

if a2 != 0:
    ax.bar3d(xpos2, ypos2, zpos2, dx2, dy2, dz2, color='r',alpha=0.2)

# ================================ Draw Up Rods ===========================
a3=0
with open("3dplotu.txt", "r") as file:
    for line in file:
        a3= a3+1

xpos3 = np.zeros(a3)
ypos3 = np.ones(a3)
zpos3 = np.zeros(a3)

i = 0
with open("3dplotu.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = words[0]
        wy = words[1]
        wz = words[2]
        xpos3[i] = wx
        # ypos3[i] = wy
        zpos3[i] = wz
        i = i+1

dx3 = np.ones(a3)
dy3 = np.ones(a3)
dz3 = np.ones(a3)

for z in range(0,a3):
    dz3[z] = 8
if a3 != 0:
    ax.bar3d(xpos3, ypos3, zpos3, dx3, dy3, dz3, color='g',alpha=0.2)

plt.show()