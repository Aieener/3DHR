#Analysis # distribution for the 3-D Rods
#Author: Yuding Ai
#Date: 2015 July 28

import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt


def his():
	N1 = [] # Ver
	N2 = [] # Hor
	N3 = [] # Up
	with open("dataplot.dat","r") as file:
		for line in file:
			words = line.split()
			n1 = float(words[2]) # Ver
			n2 = float(words[3]) # Hor
			n3 = float(words[4]) # Up
			N1.append(n1);
			N2.append(n2);
			N3.append(n3);



	fig1 = plt.figure()
	fig2 = plt.figure()
	fig3 = plt.figure()
	fig4 = plt.figure()
	ax1 = fig1.add_subplot(111)
	ax2 = fig2.add_subplot(111)
	ax3 = fig3.add_subplot(111)
	ax4 = fig4.add_subplot(111)
	numBins = 100
	# if N == "N1":
	# 	ax.hist(N1,numBins,color = 'blue', alpha = 0.8)
	# 	title = 'N1_#distribution.png'
	# 	fig.savefig(title, dpi=180, bbox_inches='tight')
	# elif N == "N2":
	# 	ax.hist(N2,numBins,color = 'red', alpha = 0.8)
	# 	title = 'N2_#distribution.png'
	# 	fig.savefig(title, dpi=180, bbox_inches='tight')
	# elif N == "N3":
	# 	ax.hist(N3,numBins,color = 'green', alpha = 0.8)
	# 	title = 'N3_#distribution.png'
	# 	fig.savefig(title, dpi=180, bbox_inches='tight')
	# else:
	# 	ax.hist(N1,numBins,color = 'blue', alpha = 0.6)
	# 	ax.hist(N2,numBins,color = 'red', alpha = 0.6)
	# 	ax.hist(N3,numBins,color = 'green', alpha = 0.6)
	# 	title = 'All_#distribution.png'
	# 	fig.savefig(title, dpi=720, bbox_inches='tight')

	ax1.hist(N1,numBins,color = 'blue', alpha = 0.8)
	title = 'N1_#distribution.png'
	fig1.savefig(title, dpi=180, bbox_inches='tight')

	ax2.hist(N2,numBins,color = 'red', alpha = 0.8)
	title = 'N2_#distribution.png'
	fig2.savefig(title, dpi=180, bbox_inches='tight')

	ax3.hist(N3,numBins,color = 'green', alpha = 0.8)
	title = 'N3_#distribution.png'
	fig3.savefig(title, dpi=180, bbox_inches='tight')

	ax4.hist(N1,numBins,color = 'blue', alpha = 0.6)
	ax4.hist(N2,numBins,color = 'red', alpha = 0.6)
	ax4.hist(N3,numBins,color = 'green', alpha = 0.6)
	title = 'All_#distribution.png'
	fig4.savefig(title, dpi=180, bbox_inches='tight')



his()



# def main():
# 	print "#=====================================#"
# 	print "# Welcome to the Distribution factory #"
# 	print "#=====================================#"

# 	check = True
# 	while (check):
# 		N = raw_input("Please tell me which specie distribution do you want for this time? \nType 'N1','N2','N3' or 'all'\n")
# 		his(N)
# 		again = raw_input("Do you want to checkout other distribution? y/n\n")
# 		if again == "n":
# 			check = False
# 	print "Thanks for trying on our Drawing tool!\nSee you soon! LOL"


# main()