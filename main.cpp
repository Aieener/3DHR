// My main file for HR3D
// Data: July27 2015
// Authur: Yuding Ai
#include <iostream>
#include "MC.h"
using namespace std;

int main()
{
	stringstream t;
	double start = clock();

	// ======================= Plotting the final config ========================
	vector<HR> VR,HR,UR;
	MC m(1E9L,8,32,32,32,300);
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