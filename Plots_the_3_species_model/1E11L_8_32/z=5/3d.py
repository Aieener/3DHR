#Author: Yuding Ai
#2015-July-15
#Visualize 3D hard rod

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# ================================ Draw Ver Rods ===========================
xpos = []
ypos = []
zpos = []

i = 0
with open("3dplotv.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = float(words[0])
        wy = float(words[1])
        wz = float(words[2])
        xpos.append(wx);
        ypos.append(wy);
        zpos.append(wz);
        i = i+1

dx = np.ones(i)
dz = np.ones(i)
dy = []
for y in range(0,i):
    dy.append(8);
if i != 0:
    ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color='b',alpha=0.2)


# ================================ Draw Hor Rods ===========================
xpos2 = []
ypos2 = []
zpos2 = []

i = 0
with open("3dploth.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = float(words[0])
        wy = float(words[1])
        wz = float(words[2])
        xpos2.append(wx);
        ypos2.append(wy);
        zpos2.append(wz);
        i = i+1

dx2 = []
dy2 = np.ones(i)
dz2 = np.ones(i)

for x in range(0,i):
    dx2.append(8);

if i != 0:
    ax.bar3d(xpos2, ypos2, zpos2, dx2, dy2, dz2, color='r',alpha=0.2)

# ================================ Draw Up Rods ===========================
xpos3 = []
ypos3 = []
zpos3 = []

i = 0
with open("3dplotu.txt", "r") as file:
    for line in file:
        words = line.split()
        wx = float(words[0])
        wy = float(words[1])
        wz = float(words[2])
        xpos3.append(wx);
        ypos3.append(wy);
        zpos3.append(wz);
        i = i+1

dx3 = np.ones(i)
dy3 = np.ones(i)
dz3 = []

for z in range(0,i):
    dz3.append(8);
if i != 0:
    ax.bar3d(xpos3, ypos3, zpos3, dx3, dy3, dz3, color='g',alpha=0.2)

plt.show()