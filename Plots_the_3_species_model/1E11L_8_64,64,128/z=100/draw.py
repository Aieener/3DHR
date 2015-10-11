# Author: Yuding Ai
# 2015-July-22
# Visualize 3D hard rod
# perl -i.bak -pe "s/\t/' 'x(8-pos()%8)/eg" draw.py

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

# Draw2D(plane,layer)
# a function that draws the rods:
# with 2 parameters:
#     plane is a string index indicates with plane we want to draw: 
#         x ------------- y,z plane
#         y ------------- z,x plane
#         z ------------- x,y plane
#     layer is a string index that indicates which layer we want to see: 

def Draw3D(plane, layer, K):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    if plane == "all":
        # -------------------------Visualize the full picture -----------------------
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
                i = i + 1

        dx = np.ones(i)
        dz = np.ones(i)
        dy = np.ones(i)
        for y in range(0, i):
            dy[y] = K;
        if i != 0:
            ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color='b', alpha=0.2)


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
                i = i + 1

        dx2 = np.ones(i)
        dy2 = np.ones(i)
        dz2 = np.ones(i)

        for x in range(0, i):
            dx2[x] = K;

        if i != 0:
            ax.bar3d(xpos2, ypos2, zpos2, dx2, dy2, dz2, color='r', alpha=0.2)

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
                i = i + 1

        dx3 = np.ones(i)
        dy3 = np.ones(i)
        dz3 = np.ones(i)

        for z in range(0, i):
            dz3[z] = K
        if i != 0:
            ax.bar3d(xpos3, ypos3, zpos3, dx3, dy3, dz3, color='g', alpha=0.2)

    else:
        # -----------------------Visualize certain layer only -----------------------
        lay = float(layer)
        # ================================ Draw Ver Rods ===========================
        xpos = []
        ypos = []
        zpos = []
        dx = []
        dy = []
        dz = []

        with open("3dplotv.txt", "r") as file:
            for line in file:
                words = line.split()
                wx = float(words[0])
                wy = float(words[1])
                wz = float(words[2])

                if plane == "x":
                    if wx == lay:
                        xpos.append(wx);
                        ypos.append(wy);
                        zpos.append(wz);
                        dx.append(1);
                        dy.append(K);
                        dz.append(1);

                elif plane == "y":
                #Should be careful about this case because for Ver Rods, in Y-Plane, 
                #when we do the visualization, some part of the rod will extent to next ith Y-plane with length = K-i;

                #Brutal force version:
                #-------------------------------------
                    # if wy == lay:
                    #     xpos.append(wx);
                    #     ypos.append(wy);
                    #     zpos.append(wz);
                    #     dy.append(K);
                    #     dx.append(1);
                    #     dz.append(1);
                    # elif wy == lay - 1:
                    #     xpos.append(wx);
                    #     ypos.append(lay);
                    #     zpos.append(wz);
                    #     dy.append(K-1.0);
                    #     dx.append(1);
                    #     dz.append(1);
                    # elif wy == lay - 2:
                    #     xpos.append(wx);
                    #     ypos.append(lay);
                    #     zpos.append(wz);
                    #     dy.append(K-2.0);
                    #     dx.append(1);
                    #     dz.append(1);
                    # elif wy == lay - 3:
                    #     xpos.append(wx);
                    #     ypos.append(lay);
                    #     zpos.append(wz);
                    #     dy.append(K-3.0);
                    #     dx.append(1);
                    #     dz.append(1);
                #-------------------------------------
                #Regular loop version:
                    Lay = lay
                    for L in range(0,int(K)):
                        Lay = lay - L
                        if wy == Lay:
                            xpos.append(wx);
                            ypos.append(lay);
                            zpos.append(wz);
                            dx.append(1);
                            dy.append(K - float(L));
                            dz.append(1);

                elif plane == "z":
                    if wz == lay:
                        xpos.append(wx);
                        ypos.append(wy);
                        zpos.append(wz);
                        dx.append(1)
                        dy.append(K);
                        dz.append(1);
        l = len(xpos)
        if l !=0:
            ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color='b', alpha=0.2)


        # ================================ Draw Hor Rods ===========================
        xpos2 = []
        ypos2 = []
        zpos2 = []
        dx2 = []
        dy2 = []
        dz2 = []
        with open("3dploth.txt", "r") as file:
            for line in file:
                words = line.split()
                wx = float(words[0])
                wy = float(words[1])
                wz = float(words[2])

                if plane == "x":
                    Lay = lay
                    for L in range(0,int(K)):
                        Lay = lay - L
                        if wx == Lay:
                            xpos2.append(lay);
                            ypos2.append(wy);
                            zpos2.append(wz);
                            dx2.append(K - float(L));
                            dy2.append(1);
                            dz2.append(1);

                elif plane == "y":
                    if wy == lay:
                        xpos2.append(wx);
                        ypos2.append(wy);
                        zpos2.append(wz);
                        dx2.append(K);
                        dy2.append(1);
                        dz2.append(1)

                elif plane == "z":
                    if wz == lay:
                        xpos2.append(wx);
                        ypos2.append(wy);
                        zpos2.append(wz);
                        dx2.append(K);
                        dy2.append(1);
                        dz2.append(1);

        m = len(xpos2)
        if m != 0:
            ax.bar3d(xpos2, ypos2, zpos2, dx2, dy2, dz2, color='r', alpha=0.2)

        # ================================ Draw Up Rods ===========================
        xpos3 = []
        ypos3 = []
        zpos3 = []
        dz3 = []
        dx3 = []
        dy3 = []

        with open("3dplotu.txt", "r") as file:
            for line in file:
                words = line.split()
                wx = float(words[0])
                wy = float(words[1])
                wz = float(words[2])

                if plane == "x":
                    if wx == lay:
                        xpos3.append(wx);
                        ypos3.append(wy);
                        zpos3.append(wz);
                        dx3.append(1);
                        dy3.append(1);
                        dz3.append(K);

                elif plane == "y":
                    if wy == lay:
                        xpos3.append(wx);
                        ypos3.append(wy);
                        zpos3.append(wz);
                        dx3.append(1);
                        dy3.append(1)
                        dz3.append(K);

                elif plane == "z":
                    Lay = lay
                    for L in range(0,int(K)):
                        Lay = lay - L
                        if wz == Lay:
                            xpos3.append(wx);
                            ypos3.append(wy);
                            zpos3.append(lay);
                            dx3.append(1);
                            dy3.append(1);
                            dz3.append(K - float(L));

        n = len(xpos3)
        if n != 0:
            ax.bar3d(xpos3, ypos3, zpos3, dx3, dy3, dz3, color='g', alpha=0.2)
    plt.show()


# Draw2D(plane,layer)
# a function that draws the rods:
# with 2 parameters:
#     plane indicates with plane we want to draw: 
# choice: 
#         0 ------------- x,y plane
#         1 ------------- y,z plane
#         2 ------------- z,x plane
#     layer is a string index that indicates which layer we want to see: 
def Draw2D(plane, layer, K):
    fig = plt.figure()
    ax = fig.add_subplot(111, aspect='equal')
    # -----------------------Visualize certain layer only -----------------------
    lay = float(layer)
    # ================================ Draw Ver Rods ===========================
    xpos = []
    ypos = []
    zpos = []
    dx = []
    dz = []
    dy = []

    with open("3dplotv.txt", "r") as file:
        for line in file:
            words = line.split()
            wx = float(words[0])
            wy = float(words[1])
            wz = float(words[2])
            if plane == "x":
                if wx == lay:
                    xpos.append(wx);
                    ypos.append(wy);
                    zpos.append(wz);
                    dx.append(1);
                    dy.append(K);
                    dz.append(1);

            elif plane == "y":
                Lay = lay
                for L in range(0,int(K)):
                    Lay = lay - L
                    if wy == Lay:
                        xpos.append(wx);
                        ypos.append(lay);
                        zpos.append(wz);
                        dx.append(1);
                        dy.append(K - float(L));
                        dz.append(1);

            elif plane == "z":
                if wz == lay:
                    xpos.append(wx);
                    ypos.append(wy);
                    zpos.append(wz);
                    dx.append(1)
                    dy.append(K);
                    dz.append(1);

    l = len(xpos)

    if plane == "x":
        for y in range(0, l):
            dy[y] = K;
            ax.add_patch(
                patches.Rectangle(
                    (ypos[y], zpos[y]),
                    dy[y],
                    dz[y],
                    facecolor="blue"
                )
            )

    if plane == "y":
        for y in range(0, l):
            dy[y] = K;
            ax.add_patch(
                patches.Rectangle(
                    (zpos[y], xpos[y]),
                    dz[y],
                    dx[y],
                    facecolor="blue"
                )
            )

    if plane == "z":
        for y in range(0, l):
            dy[y] = K;
            ax.add_patch(
                patches.Rectangle(
                    (xpos[y], ypos[y]),
                    dx[y],
                    dy[y],
                    facecolor="blue"
                )
            )
    # ================================ Draw Hor Rods ===========================
    xpos2 = []
    ypos2 = []
    zpos2 = []
    dx2 = []
    dy2 = []
    dz2 = []

    with open("3dploth.txt", "r") as file:
        for line in file:
            words = line.split()
            wx = float(words[0])
            wy = float(words[1])
            wz = float(words[2])
            if plane == "x":
                Lay = lay
                for L in range(0,int(K)):
                    Lay = lay - L
                    if wx == Lay:
                        xpos2.append(lay);
                        ypos2.append(wy);
                        zpos2.append(wz);
                        dx2.append(K - float(L));
                        dy2.append(1);
                        dz2.append(1);

            elif plane == "y":
                if wy == lay:
                    xpos2.append(wx);
                    ypos2.append(wy);
                    zpos2.append(wz);
                    dx2.append(K);
                    dy2.append(1);
                    dz2.append(1)

            elif plane == "z":
                if wz == lay:
                    xpos2.append(wx);
                    ypos2.append(wy);
                    zpos2.append(wz);
                    dx2.append(K);
                    dy2.append(1);
                    dz2.append(1);
    m = len(xpos2)

    if plane == "x":
        for x in range(0, m):
            dx2[x] = K;
            ax.add_patch(
                patches.Rectangle(
                    (ypos2[x], zpos2[x]),
                    dy2[x],
                    dz2[x],
                    facecolor="red"
                )
            )

    if plane == "y":
        for x in range(0, m):
            dx2[x] = K;
            ax.add_patch(
                patches.Rectangle(
                    (zpos2[x], xpos2[x]),
                    dz2[x],
                    dx2[x],
                    facecolor="red"
                )
            )

    if plane == "z":
        for x in range(0, m):
            dx2[x] = K;
            ax.add_patch(
                patches.Rectangle(
                    (xpos2[x], ypos2[x]),
                    dx2[x],
                    dy2[x],
                    facecolor="red"
                )
            )

    # ================================ Draw Up Rods ===========================
    xpos3 = []
    ypos3 = []
    zpos3 = []
    dx3 = []
    dz3 = []
    dy3 = []

    with open("3dplotu.txt", "r") as file:
        for line in file:
            words = line.split()
            wx = float(words[0])
            wy = float(words[1])
            wz = float(words[2])
            if plane == "x":
                if wx == lay:
                    xpos3.append(wx);
                    ypos3.append(wy);
                    zpos3.append(wz);
                    dx3.append(1);
                    dy3.append(1);
                    dz3.append(K);

            elif plane == "y":
                if wy == lay:
                    xpos3.append(wx);
                    ypos3.append(wy);
                    zpos3.append(wz);
                    dx3.append(1);
                    dy3.append(1)
                    dz3.append(K);

            elif plane == "z":
                Lay = lay
                for L in range(0,int(K)):
                    Lay = lay - L
                    if wz == Lay:
                        xpos3.append(wx);
                        ypos3.append(wy);
                        zpos3.append(lay);
                        dx3.append(1);
                        dy3.append(1);
                        dz3.append(K - float(L));

    n = len(xpos3)

    if plane == "x":
        for z in range(0, n):
            dz3[z] = K;
            ax.add_patch(
                patches.Rectangle(
                    (ypos3[z], zpos3[z]),
                    dy3[z],
                    dz3[z],
                    facecolor="green"
                )
            )

    if plane == "y":
        for z in range(0, n):
            dz3[z] = K;
            ax.add_patch(
                patches.Rectangle(
                    (zpos3[z], xpos3[z]),
                    dz3[z],
                    dx3[z],
                    facecolor="green"
                )
            )

    if plane == "z":
        for z in range(0, n):
            dz3[z] = K;
            ax.add_patch(
                patches.Rectangle(
                    (xpos3[z], ypos3[z]),
                    dx3[z],
                    dy3[z],
                    facecolor="green"
                )
            )

    plt.axis('equal')
    title = '2dplot' + '_' + plane + '_' + layer + '.png'
    fig.savefig(title, dpi=180, bbox_inches='tight')
    # plt.show()


def main():
    print "#===============================#"
    print "# Welcome to the world of Rods! #"
    print "#===============================#"
    print "Here is how it works:"
    print "----------------------------------------------------------------------------------"
    print "First of all, kindly inform us whether you want to visualize the Rods in 3D or 2D;"
    print "Then, please remind us what is length of our Rods for this time;\nNext pick a direction of the 'plane':"
    print "x ----------> y,z plane\ny ----------> z,x plane\nz ----------> x,y plane\nall----------> the entire picture"
    print "Last, choose a layer to specify the exact plane you want to see.\n\nGood Luck!"
    print "----------------------------------------------------------------------------------"

    check = True
    while (check):
        d = raw_input('Do you want to Visualize in 3D or 2D? Answer 3 or 2\n')

        if d == '3':
            K = float(raw_input('Please remind me what is the length of our Rods this time?\n'))
            plane = raw_input("Which plane do you want to see?\n"
                              "type 'x', 'y', 'z' or type 'all' if you want to see the entire picture\n")
            if plane == "all":
                layer = 0
                Draw3D(plane, layer, K)
                check = False

            elif plane == 'x' or plane == 'y' or plane == 'z':
                layer = raw_input("And on which layer?\n")
                Draw3D(plane, layer, K)
                again = "a"
                while (again != "n"):
                    again = raw_input("Do you want to checkout other layers on this plane? y/n\n")
                    if again == "y":
                        layer = raw_input("And on which layer this time?\n")
                        Draw3D(plane, layer, K)
                    else:
                        again = "n"
                check = False
            else:
                print "I don't understand what do you mean\n"


        elif d == '2':
            K = float(raw_input('Please remind me what is the length of our Rods this time?\n'))
            p = raw_input("Which plane do you want to see?\n"
                          "type 'x', 'y' or 'z'\n")
            if p == 'x' or p == 'y' or p == 'z':
                l = raw_input('And on which layer?\n')
                Draw2D(p, l, K)
                again = "a"
                while (again != "n"):
                    again = raw_input("Do you want to check out other layers on this plane? y/n\n")
                    if again == "y":
                        l = raw_input("And on which layer this time?\n")
                        Draw2D(p, l, K)
                    else:
                        again = "n"      
                while (p != "n"):
                    p = raw_input("Do you want to check out other planes? \n"
                                  "type 'x','y','z' for Yes or 'n' for No\n")
                    if p != "n":
                        l = raw_input('And on which layer?\n')
                        Draw2D(p, l, K)
                        again = "a"
                        while (again != "n"):
                            again = raw_input("Do you want to check out other layers on this plane? y/n\n")
                            if again == "y":
                                l = raw_input("And on which layer this time?\n")
                                Draw2D(p, l, K)
                            else:
                                again = "n"
                check = False
            else:
                print "I don't understand what do you mean\n"

        else:
            print "I don't understand what do you mean\n"

    print "Thanks for trying on our Drawing tool!\nSee you soon! LOL"


main()
