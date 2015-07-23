// Boxgen.h
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
#include <deque>
#include <array>
using namespace std;

#ifndef BOXGEN_H
#define BOXGEN_H
class Boxgen
{
    private:
    	//data members;
    	std::deque<HR> VRodlist; // the list storage the Vertical Rods;
        std::deque<HR> HRodlist; // the list storage the Horizantal Rods;
        std::deque<HR> URodlist; // the list storage the Up Rods;
    	int r,c,h; // size of the volume 'box'
    	int length; // length of the rod
       
    public:
    	MC(long int ST, int LEN, int C, int R, int H, double Z); //(C==X, R==y,H==z)

    	// ********* Getters********//

    	deque<HR> getVRodlist();
        deque<HR> getHRodlist();
        deque<HR> getURodlist();
    	double getTho() const;
    	double getQ() const;
    	double getAaccp() const;
    	double getDaccp() const;
        double getNh() const;
        double getNv() const;
        // ******** Setters ******//
        void setRodlist(std::deque<HR> RodL);


    	// ******** Other Functianality *******//
        void Add(Cells &s,double &prob,double &probav, double &probah, double &probau);
        void Del(Cells &s,double &prob,double &probdv, double &probdh, double &probdu);
    	void MCRUN(); 
        void Zvs_();

    	void plot(const deque<HR>& VRodlist, const deque<HR>& HRodlist,const deque<HR>& URodlist);

};

#endif /* BOXGEN_H */