#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "square.h"
#include "cells.h"
#include "hardrods.h"
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <vector>
#include <vector>
#include <array>
using namespace std;

#ifndef MC_H
#define MC_H

class MC
{
    private:
    	//data members;
    	std::vector<HR> VRodlist; // the list storage the Vertical Rods;
        std::vector<HR> HRodlist; // the list storage the Horizantal Rods;
        std::vector<HR> URodlist; // the list storage the Up Rods;
    	int r,c,h; // size of the box
    	int length; // length of the rod
    	long int step;
    	double z; 
    	double nh,nv,nu,dh,dv,du,ah,av,au;
        

    public:
    	MC(long int ST, int LEN, int C, int R, int H, double Z); //(C==X, R==y,H==z)

    	// ********* Getters********//

        const vector<HR>& getVRodlist() const;
        const vector<HR>& getHRodlist() const;
        const vector<HR>& getURodlist() const;

    	double getTho() const;
    	double getQ() const;
    	double getAaccp() const;
    	double getDaccp() const;
        double getNh() const;
        double getNv() const;
        // ******** Setters ******//
        void setRodlist(std::vector<HR> RodL);


    	// ******** Other Functianality *******//
        void Add(Cells &s,double &prob,double &probav, double &probah, double &probau);
        void Del(Cells &s,double &prob,double &probdv, double &probdh, double &probdu);
    	void MCRUN(); 
        void Zvs_();

    	void plot(const vector<HR>& VRodlist, const vector<HR>& HRodlist,const vector<HR>& URodlist);

};

#endif /* MC_H */