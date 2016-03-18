// My main file for HR3D
// Data: July27 2015
// Authur: Yuding Ai
#include <iostream>
#include "MC.h"
using namespace std;

/**************************** Data Analysis ***********************************
*  After finish the MC simulation, we can use python to do the data analysis:
*  1.we can plot the final config by running draw.py :  python draw.py
*  2.we obtain the N distribution historgams by running his.py:  python his.py
*  3.we obtain the N vs Run plots by running NvsR.py: python NvsR.py
*  4.we obtain the data for the mean values by running mean.py: python mean.py
*******************************************************************************
*/


int main()
{
	stringstream t;
	double start = clock();

	// ======================= Plotting the final config ========================
	vector<HR> VR,HR,UR;
	MC m(1E9L,12,64,64,64,2.96);
	m.MCRUN(0);
	VR = m.getVRodlist();
	HR = m.getHRodlist();
	UR = m.getURodlist();
	m.plot(VR,HR,UR);
	// ======================= end of simulation, print out the time ===========
	double end = clock();
	cout <<"This simulation takes "<< (double(end-start)/CLOCKS_PER_SEC)<<" sec."<<endl;
	t <<"This simulation takes "<< (double(end-start)/CLOCKS_PER_SEC) <<" sec."<<endl;
	ofstream myfile ("time.txt");
	string datat = t.str();
	myfile << datat;
	myfile.close();	
	return 0;
}