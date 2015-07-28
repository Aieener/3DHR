// My main file for HR3D
// Data: July27 2015
// Authur: Yuding Ai
#include <iostream>
#include "MC.h"
using namespace std;

int main()
{
	double start = clock();

	// ======================= Plotting the final config ========================
	vector<HR> VR,HR,UR;
	MC m(1E7L,5,25,25,25,20000);
	m.MCRUN(2);
	VR = m.getVRodlist();
	HR = m.getHRodlist();
	UR = m.getURodlist();
	m.plot(VR,HR,UR);
	// ======================= end of simulation, print out the time ===========
	double end = clock();
	cout <<"This simulation takes "<< (double(end-start)/CLOCKS_PER_SEC)<<endl;
	return 0;
}