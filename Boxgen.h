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
        int o; // the orientation of the box
    	int length; // length of the rod
       
    public:
    	Boxgen(int Orien,int Len); 

    	// ********* Getters********//

        // ******** Setters ******//

    	// ******** Other Functianality *******//

};

#endif /* BOXGEN_H */