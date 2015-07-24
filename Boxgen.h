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
    	int r,c,h; // size of the main'box'
        int o; // the orientation of the box
    	int length; // length of the rod
       
    public:
        //Constructer: initialize the oritation of our box
        //and then assighn the corresponding rod pos into a list.
        //when we add a subbox into our Box/Cells, we assign the rod list into the real Rodlist;

    	Boxgen(int Orien,int Len); 

    	// ********* Getters********//

        // ******** Setters ******//

    	// ******** Other Functianality *******//

};

#endif /* BOXGEN_H */