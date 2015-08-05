# Author: Yuding Ai
# 2015-July-30
# Plot NvsRun
# perl -i.bak -pe "s/\t/' 'x(8-pos()%8)/eg" *.py
# echo z=5/ z=9/ z=10/ z=11/ z=14/ z=19/ z=20/ z=21/ | xargs -n 1 cp QvsR.py


import numpy as np
import matplotlib.pyplot as plt

N1 = [] # Ver
N2 = [] # Hor
N3 = [] # Up
N = [] #total
Run = []

with open("dataplot.dat", "r") as file:
	for line in file:
		words = line.split()
		r = float(words[0]) # Runs
		n1 = float(words[2]) # Ver
		n2 = float(words[3]) # Hor
		n3 = float(words[4]) # Up
		tot = n1 + n2 + n3
		Run.append(r);
		N1.append(n1);
		N2.append(n2);
		N3.append(n3);
		N.append(tot);

fig1 = plt.figure()
ax1 = fig1.add_subplot(111)
ax1.set_title("Runs VS Numbers of Vertical Rods")    
ax1.set_xlabel('Runs')
ax1.set_ylabel('Numbers of Vertical Rods')
ax1.plot(Run,N1, c='b', label='Vertical Rods')
title = 'Runs_VS_N1.png'
leg = ax1.legend()
fig1.savefig(title, dpi=180, bbox_inches='tight')

fig2 = plt.figure()
ax2 = fig2.add_subplot(111)
ax2.set_title("Runs VS Numbers of Horizontal Rods")    
ax2.set_xlabel('Runs')
ax2.set_ylabel('Numbers of Horizontal Rods')
ax2.plot(Run,N2, c='r', label='Horizontal Rods')
title = 'Runs_VS_N2.png'
leg = ax2.legend()
fig2.savefig(title, dpi=180, bbox_inches='tight')


fig3 = plt.figure()
ax3 = fig3.add_subplot(111)
ax3.set_title("Runs VS Numbers of Up Rods")    
ax3.set_xlabel('Runs')
ax3.set_ylabel('Numbers of Up Rods')
ax3.plot(Run,N3, c='g', label='Up Rods')
title = 'Runs_VS_N3.png'
leg = ax3.legend()
fig3.savefig(title, dpi=180, bbox_inches='tight')

fig4 = plt.figure()
ax4 = fig1.add_subplot(111)
ax4.set_title("Runs VS Total Numbers of Rods")    
ax4.set_xlabel('Runs')
ax4.set_ylabel('Total Numbers of Rods')
ax4.plot(Run,N1, c='y', label='Total Numbers')
title = 'Runs_VS_Ntot.png'
leg = ax4.legend()
fig4.savefig(title, dpi=180, bbox_inches='tight')



# plt.show()