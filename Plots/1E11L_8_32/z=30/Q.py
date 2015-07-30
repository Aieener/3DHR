#Analysis Q for the 3-D Rods
#Author: Yuding Ai
#Date: 2015 July 23

import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt


#def CalecQ() is a function that Calculate for Q over the data we've collected
#Here Q is defined as Q = (N3 -(N2+N1)/2) / N1 + N2 + N3 where N3 is for the excessing species
def CalcQ(Excess):
	Q = []
	with open("dataplot.dat","r") as file:
		# i = 0
		for line in file:
			words = line.split()
			N1 = float(words[2]) # Ver
			N2 = float(words[3]) # Hor
			N3 = float(words[4]) # Up
			if Excess == "N3":
				value = (N3 -(N2+N1)/2) / (N1 + N2 + N3) 
			elif Excess == "N2":
				value = (N2 -(N3+N1)/2) / (N1 + N2 + N3) 
			elif Excess == "N1":
				value = (N1 -(N2+N3)/2) / (N1 + N2 + N3) 
			Q.append(value);
			# print Q[i]
			# i = i + 1
	np.savetxt('Q.txt', Q, delimiter=',') 
	return Q

# CalcQ("N3")

#HistoQ generates the histogram for our sets of Q
def HistoQ(Q):
	fig = plt.figure()
	ax = fig.add_subplot(111)
	numBins = 100
	ax.hist(Q,numBins,color = 'green', alpha = 0.8)
	title = 'HitsQ3d.png'
	fig.savefig(title, dpi=180, bbox_inches='tight')
	plt.show()

def main():
	print "#===============================#"
	print "# Welcome to the HistoQ factory #"
	print "#===============================#"
	Excess = raw_input("Please tell me which specie is the Excess one for this time? Type 'N1','N2' or 'N3'\n")
	HistoQ(CalcQ(Excess))


main()


