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
	Run = []
	with open("dataplot.dat","r") as file:
		# i = 0
		for line in file:
			words = line.split()
			r = float(words[0]) # Runs
			N1 = float(words[2]) # Ver
			N2 = float(words[3]) # Hor
			N3 = float(words[4]) # Up
			if Excess == "N3":
				value = (N3 -(N2+N1)/2) / (N1 + N2 + N3) 
			elif Excess == "N2":
				value = (N2 -(N3+N1)/2) / (N1 + N2 + N3) 
			elif Excess == "N1":
				value = (N1 -(N2+N3)/2) / (N1 + N2 + N3) 
			Run.append(r);
			Q.append(value);
			# print Q[i]
			# i = i + 1
	np.savetxt('Q.txt', Q, delimiter=',') 
	return [Q,Run]

# CalcQ("N3")

#HistoQ generates the histogram for our sets of Q
def HistoQ(D):
	fig = plt.figure()
	ax = fig.add_subplot(111)
	ax.set_title("Distribution for Q")
	ax.set_xlabel('Q')
	ax.set_ylabel('Frequency')
	numBins = 100
	ax.hist(D[0],numBins,color = 'purple', alpha = 0.8, label ='Q')
	leg = ax.legend()
	title = 'HitsQ3d.png'
	fig.savefig(title, dpi=180, bbox_inches='tight')
	
	fig2 = plt.figure()
	ax2 = fig2.add_subplot(111)
	ax2.set_title("Runs VS Q")    
	ax2.set_xlabel('Runs')
	ax2.set_ylabel('Q')
	ax2.plot(D[1],D[0], c='purple', label='Q')
	leg = ax2.legend()
	title = 'Runs_VS_Q.png'
	fig2.savefig(title, dpi=180, bbox_inches='tight')

def main():
	print "#===============================#"
	print "# Welcome to the HistoQ factory #"
	print "#===============================#"
	Excess = raw_input("Please tell me which specie is the Excess one for this time? Type 'N1','N2' or 'N3'\n")
	HistoQ(CalcQ(Excess))


main()


