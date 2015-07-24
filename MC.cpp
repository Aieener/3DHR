/*
* MC.cpp
* Simulation of 3-D Hard-Rod By GCMC
* Author: Yuding Ai
* Date: 2015.07.15
* *************************** MC implementation ********************************
* This simulation follows grand canonical ensemble.
* In such simulation, Only Energy and N of particles fluctuate, we accomplish EF by
* using both add/del and displacement moves, while NF by particle addition and 
* deletion moves;
* ******************************************************************************
* The Acceptance relation for Displacement is given by: (Page 130 -- Understanding 
* Molecular Simulations)
*
* The Acceptance relation for Addition is given by: (Page 12 --M.S.Shell 2012)
*  -- Pad = min [1,((r*c/2)/(N + 1)) * exp{-beta*miu}]
*
* The Acceptance relation for Deletion is given by:
*  -- Pde = min [1,(N/(r*c/2))*exp{beta*miu}]
*
* where miu is the chemical potential
*
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "square.h"
#include "cells.h"
#include "MC.h"
#include "hardrods.h"
#include <cstdlib>
#include <cmath>
#include <time.h>
#include "histogram.h"
#include <array>
using namespace std;


MC::MC(long int ST, int LEN, int C, int R, int H, double Z)
{
	VRodlist.clear(); // the list storage the Vertical Rods;
    HRodlist.clear(); // the list storage the Horizantal Rods;
    URodlist.clear(); // the list storage the Up Rods;
	r = R;
	c = C;
	h = H;
	length = LEN;
	step = ST;
	z = Z;
	nh=nv=nu=dh=dv=du=ah=av=au=0;
}

vector<HR> MC::getVRodlist() 
{
	return VRodlist;
}

vector<HR> MC::getHRodlist() 
{
	return HRodlist;
}

vector<HR> MC::getURodlist() 
{
	return URodlist;
}


// double MC::getTho() const
// {
// 	double tho;	
// 	tho = double(length*(av+ah-dv-dh))/double(r*c);
// 	return tho;
// }

// double MC::getQ() const
// {
// 	double Q;	
// 	Q = (nv - nh)/(nv + nh);
// 	return Q;
// }

// double MC::getAaccp() const
// {
// 	double A;
// 	A = z*(double(r*c))/(double(av+ah-dv-dh+1.0)*double(length));
// 	return A;
// }

// double MC::getDaccp() const
// {
// 	double D;
// 	D = (double(av+ah-dv-dh)*double(length))/(z*(double(r*c)));
// 	return D;
// }

// double MC::getNh() const
// {
// 	return nh;
// }
// double MC::getNv() const
// {
// 	return nv;
// }

// void MC::setRodlist(std::vector<HR> RodL)
// {
// 	Rodlist = RodL;
// }

void MC::Add(Cells &s,double &prob,double &probav, double &probah, double &probau)
{
	int x,y,z,o; // pick a random position and orientation for the HR to be added;
	x = rand()%c; // x range[0,c-1]
	y = rand()%r; // y range[0,r-1]
	z = rand()%h; // z range[0,h-1]
	o = rand()%3  ; // 0 range {0,1,2}

	if(s.getSquare(x,y,z).isEmpty()) // if it's open, try to do Addition;
	{
		HR rod(x,y,z,length,o);

		//======================== Vertical inside boundary===============================
		if(o == 0)
		{
			if(prob <= probav)
			{
				if(y + length <= r)
				{
					// the vertical case
					int counter = 0;

					for (int j = 0; j < length; j++)
					{
						// check if the vertical space is wide open
						if(s.getSquare(x,y+j,z).isOccupied())
						{
							counter++;
							break;
							// cout << "!!!"<<endl;
						}						
					}
					// cout <<"counter = "<< counter<< endl;
					if (counter == 0)
					{
						// Do addition;
						// push the new rod into the VRodlist;
						VRodlist.push_back(rod);
						av++;
						nv++;// accumulate the # of ver rod;
						// update new N, E and new config;
						for (int i = 0; i < length; i++)
						{	
							s.getSquare(x,y+i,z).setStatus(1);
						}		
					}						
				}
				//========================== Vertical Apply peiodic boundary ===================

				else 
				{ 
					// the vertical case apply periodic BC
					int counter2 = 0;
					for (int j = 0; j <r-y-1; j++)
					{
						// check if the vertical space is wide open
						if(s.getSquare(x,y+j+1,z).isOccupied())
						{
							counter2++;
						}
					}
					if (counter2 == 0)
					{
						for (int i = 0; i < y+length-r; i++)
						{
							// check if the vertical space is wide open
							if(s.getSquare(x,i,z).isOccupied())
							{								
								counter2++;
							}
						}
					}

					if (counter2 == 0)
					{
						// Do addition;
						// push the new rod into the Rodlist;
						VRodlist.push_back(rod);	
						av++;
						nv++;// accumulate the # of ver rod;
						
						for (int j = 0; j <r-y; j++)
						{
							s.getSquare(x,y+j,z).setStatus(1);
						}
						for (int i = 0; i < y+length-r; i++)
						{
							s.getSquare(x,i,z).setStatus(1);
						}							
					}
				}
			}
		}

		else if(o == 1)
		{
        //======================= Horizontal inside boundary ============================
			if(prob <= probah)
			{
				if( x + length <= c)
				{
					int counter3 = 0;
					for (int j = 0; j< length ; j++)
					{
						// check if the horizontal space is wide open
						if(s.getSquare(x+j,y,z).isOccupied())
						{
							counter3++;
							break;
						}							
					}
					if (counter3 == 0)
					{
						//Do addition;
						//push the new rod into the HRodlist;
						HRodlist.push_back(rod);
						ah++;
						nh++;// accumulate the # of hor rod;

						// update new N, E and new config;
						for (int i = 0; i < length; i++)
						{
							s.getSquare(x+i,y,z).setStatus(1);
						}
					}
				}
				//======================= Horizontal periodic boundary ============================

				else
				{ 		
					// the Horizontal case apply periodic BC
					int counter4 = 0;
					for (int j = 0; j <c-x-1; j++)
					{
						// check if the Horizontal space is wide open
						if(s.getSquare(x+j+1,y,z).isOccupied())
						{
							counter4++;

						}
					}
					if (counter4 == 0)
					{
						for (int i = 0; i < x + length-c; i++)
						{
							// check if the Horizontal space is wide open
							if(s.getSquare(i,y,z).isOccupied())
							{
								counter4++;
							}
						}						
					}

					if (counter4 == 0)
					{
						// Do addition;
						// push the new rod into the HRodlist;
						HRodlist.push_back(rod);	
						ah++;
						nh++;// accumulate the # of hor rod;
						
						for (int j = 0; j <c-x; j++)
						{
							s.getSquare(x+j,y,z).setStatus(1);
						}
						for (int i = 0; i < x+length-c; i++)
						{
							s.getSquare(i,y,z).setStatus(1);
						}							
					}
				}				    												
			}
		}
		else 
		{
        //======================= Horizontal inside boundary ============================
			if(prob <= probau)
			{
				if( z + length <= h)
				{
					int counter3 = 0;
					for (int j = 0; j< length ; j++)
					{
						// check if the horizontal space is wide open
						if(s.getSquare(x,y,z+j).isOccupied())
						{
							counter3++;
							break;
						}							
					}
					if (counter3 == 0)
					{
						//Do addition;
						//push the new rod into the HRodlist;
						URodlist.push_back(rod);
						au++;
						nu++;// accumulate the # of hor rod;

						// update new N, E and new config;
						for (int i = 0; i < length; i++)
						{
							s.getSquare(x,y,z+i).setStatus(1);
						}
					}
				}
				//======================= Horizontal periodic boundary ============================

				else
				{ 		
					// the Horizontal case apply periodic BC
					int counter4 = 0;
					for (int j = 0; j <h-z-1; j++)
					{
						// check if the Horizontal space is wide open
						if(s.getSquare(x,y,z+j+1).isOccupied())
						{
							counter4++;

						}
					}
					if (counter4 == 0)
					{
						for (int i = 0; i < z + length-h; i++)
						{
							// check if the Horizontal space is wide open
							if(s.getSquare(x,y,i).isOccupied())
							{
								counter4++;
							}
						}						
					}

					if (counter4 == 0)
					{
						// Do addition;
						// push the new rod into the HRodlist;
						URodlist.push_back(rod);	
						au++;
						nu++;// accumulate the # of hor rod;
						
						for (int j = 0; j <h-z; j++)
						{
							s.getSquare(x,y,z+j).setStatus(1);
						}
						for (int i = 0; i < z+length-h; i++)
						{
							s.getSquare(x,y,i).setStatus(1);
						}							
					}
				}				    												
			}
		}
    }
}

void MC::Del(Cells &s,double &prob,double &probdv, double &probdh, double &probdu)
{
	//Do Del;
	int DE; //pick a random config of rod to delete with 33% 33% 33%chance for ori;
	DE = rand()%3; // 

	if(DE == 0) // delete Vertical rod; which means delete indx from Rodlist[0,nv-1]
	{
		if(VRodlist.size()!=0)// make sure there are Vertical rod;
		{
			int indx; // pick a random index from the Rodlist;
			indx = rand()%int(nv);

			//remove Rodlist[indx];
			int x,y,z;// the position of the target on the cells;
			x = VRodlist[indx].getX();
			y = VRodlist[indx].getY();
			z = VRodlist[indx].getZ();

			if(prob <= probdv)
			{
			// --------------------- it's a vertical rod -----------------------
			// ============== the case rod is inside the Boundary ==============
				if(y + length <= r)
				{					
					for(int i = 0; i<VRodlist[indx].getLength(); i++)
					{
						// update the new config of cells
						s.getSquare(x,y + i,z).setStatus(0);
					}
					// remove the target rod from the vector Rodlist;
					VRodlist.erase(VRodlist.begin() + indx);
					nv--;// substract the # of ver rod;
					dv++;
				}
				
				else
				{
					// ==============the case apply periodic Boundary============
					for (int j = 0; j <r-y; j++)
					{
						s.getSquare(x,y+j,z).setStatus(0);
					}
					for (int i = 0; i < y+length-r; i++)
					{
						s.getSquare(x,i,z).setStatus(0);
					}
					VRodlist.erase(VRodlist.begin() + indx);
					nv--;// substract the # of ver rod;
					dv++;
				}
			}										
		}
	}

	else if (DE == 1)
	{
		if(HRodlist.size()!=0)// make sure there are Hor rod;
		{
			int indx;
			indx = rand()%int(nh); // redefine indx from Rodlist[nv,nv+nh-1] 

			//remove Rodlist[indx];
			int x,y,z;// the position of the target on the cells;
			x = HRodlist[indx].getX();
			y = HRodlist[indx].getY();
			z = HRodlist[indx].getZ();
			// --------------------- it's a Horizontal rod -----------------------
			if(prob <= probdh)
			{
                // ==============the case rod is inside the Boundary============
				if(x + length <= c)
				{					
					for(int i = 0; i<HRodlist[indx].getLength(); i++)
					{
						// update the new config of cells
						s.getSquare(x+i,y,z).setStatus(0);
					}
					// remove the target rod from the vector Rodlist;
					HRodlist.erase(HRodlist.begin() + indx);
					nh--;// subtract the # of hor rod;
					dh++;
				}

				else
				{
					// ==============the case apply periodic Boundary============
					for (int j = 0; j <c-x; j++)
					{
						s.getSquare(x+j,y,z).setStatus(0);
					}
					for (int i = 0; i < x+length-c; i++)
					{

						s.getSquare(i,y,z).setStatus(0);
					}

					HRodlist.erase(HRodlist.begin() + indx);
					nh--;// substract the # of hor rod;
					dh++;
				}
			}
		}
	}

	else 
	{
		if(URodlist.size()!=0)// make sure there are Hor rod;
		{
			int indx;
			indx = rand()%int(nu); // redefine indx from Rodlist[nv,nv+nh-1] 

			//remove Rodlist[indx];
			int x,y,z;// the position of the target on the cells;
			x = URodlist[indx].getX();
			y = URodlist[indx].getY();
			z = URodlist[indx].getZ();
			// --------------------- it's a Horizontal rod -----------------------
			if(prob <= probdu)
			{
                // ==============the case rod is inside the Boundary============
				if(z + length <= h)
				{					
					for(int i = 0; i<URodlist[indx].getLength(); i++)
					{
						// update the new config of cells
						s.getSquare(x,y,z+i).setStatus(0);
					}
					// remove the target rod from the vector Rodlist;
					URodlist.erase(URodlist.begin() + indx);
					nu--;// substract the # of hor rod;
					du++;
				}

				else
				{
					// ==============the case apply periodic Boundary============
					for (int j = 0; j <h-z; j++)
					{
						s.getSquare(x,y,z+j).setStatus(0);
					}
					for (int i = 0; i < z+length-h; i++)
					{

						s.getSquare(x,y,i).setStatus(0);
					}

					URodlist.erase(URodlist.begin() + indx);
					nu--;// substract the # of hor rod;
					du++;
				}
			}
		}
	}
}


void MC::MCRUN()
{
	//create my grid of empty cells;
	Cells s(c,r,h); 


	// ******************  if there is an initial state:************************** //
	// Rodlist = s.Initial(length,753,1);
	// int k = 0;
	// for(int i = 0; i < Rodlist.size();i++)
	// {
	// 	if (Rodlist[i].getOrientation() == 0)
	// 	{
	// 		k++;
	// 	}
	// }
	// nv = av = k;
	// nh = ah = Rodlist.size() - k;
	// ******************  finish setting initial state************************** //

	stringstream st;

	double addordel; // the prob to decide either add or del;
	double probah, probav, probau; // the acceptance prob of addition; proba = min(1.0,aaccp);
	double probdh, probdv, probdu; // the acceptance prob of deletion; probd = min(1.0,daccp);
	double prob; // the prob to decide either accept add/del;
	double aaccph,aaccpv,aaccpu; 
	double daccph,daccpv,daccpu;
	double Q; // the fraction of hor and ver particle;
	double tho; // the density 
	double AD;// addition and deletion fraction
	double size;
		
	srand(time(NULL));
	long int i = 0;
	Histogram hisv(0, r*c*h/length, 1); // the histogram of nv
	Histogram hish(0, r*c*h/length, 1); // the histogram of nh
	Histogram hisu(0, r*c*h/length, 1); // the histogram of nu
	//================================Start my MC simulation=================================
	while (i<step)
	{
		i++;
		// generate a random probability to decide either add or del;
		addordel = rand()%2 ; 
		size = av+ah+au-dv-dh-du;

		// *****************define the probabilities ***********************************// I HAVE TO CHANGE IT FOR LATTICE GAS CASE!!!
		prob = ((double) rand() / (RAND_MAX)); 
		tho = double(length*size)/double(r*c*h);

		aaccph = z*(double(r*c*h)/3.0)/(double(ah-dh+1.0)*double(length));
		aaccpv = z*(double(r*c*h)/3.0)/(double(av-dv+1.0)*double(length));
		aaccpu = z*(double(r*c*h)/3.0)/(double(au-du+1.0)*double(length));

		daccph = (double(ah-dh)*double(length))/(z*(double(r*c*h)/3.0));
		daccpv = (double(av-dv)*double(length))/(z*(double(r*c*h)/3.0));
		daccpu = (double(au-du)*double(length))/(z*(double(r*c*h)/3.0));

		probdh = min(1.0,daccph);
		probdv = min(1.0,daccpv);
		probdu = min(1.0,daccpu);

		probah = min(1.0,aaccph);
		probav = min(1.0,aaccpv);
		probau = min(1.0,aaccpu);

		//******************* The structure of my vector list of HR ***********************
        // I have 3 lists corresponding to my 3 species
		// *******************************************************************************

        // ===========================Addition ===================================
		if(addordel == 0) 
		{
			//Do Addition;
			Add(s,prob,probav,probah,probau);
		}

		// ============================Deletion=============================
		else
		{
			if (size != 0) // make sure there are rods to be del;
			{
				//Do deletion;
				Del(s,prob,probdv, probdh,probdu);
			}			
		}

		// ======================= Record the datas =============================================		
        Q = (nv - nh)/(nh + nv);
		AD = (av+ah-dv-dh)/(av+ah+dv+dh);

		if (i%(step/10000) == 0)
		{
			hisv.record(nv);
			hish.record(nh);
			hisu.record(nu);

			st << i << "         " << Q <<"        "<< nv << "          "<< nh << "         "<< nu << "         "<< tho<< "         "<< endl;
			cout <<"Process: "<< ((10000*i)/step)/100.00 <<"%"<<"    "<<"SIZE: "<<av+ah+au-dv-dh-du<<"    "<<"# of Ver Rod: "<<nv<<"    "<<"# of Hor Rod: "<< nh <<"   "<<"# of Up Rod "<<nu <<"   "<<"tho is: "<<tho << endl;
		}
	}
	// Record the data into a txt file
	ofstream myfile3 ("dataplot.dat");
	string data = st.str();
	myfile3 << data;
	myfile3.close();
	hisv.plot(1);
	hish.plot(2);
	hisu.plot(3);
}


void MC::plot(const vector<HR>& VRodlist, const vector<HR>& HRodlist,const vector<HR>& URodlist)
{
	stringstream stv,sth,stu;

	for (int i = 0; i < VRodlist.size(); i++)
	{
		stv<< VRodlist[i].getX() << "   "<< VRodlist[i].getY() << "   "<< VRodlist[i].getZ()<<endl;
	}

	ofstream myfilev ("3dplotv.txt");
	string datav = stv.str();
	myfilev << datav;
	myfilev.close();

	for (int j = 0; j < HRodlist.size(); j++)
	{
		sth<< HRodlist[j].getX() << "   "<< HRodlist[j].getY() << "   "<< HRodlist[j].getZ()<<endl;
	}

	ofstream myfileh ("3dploth.txt");
	string datah = sth.str();
	myfileh << datah;
	myfileh.close();

	for (int k = 0; k < URodlist.size(); k++)
	{
		stu<< URodlist[k].getX() << "   "<< URodlist[k].getY() << "   "<< URodlist[k].getZ()<<endl;
	}

	ofstream myfileu ("3dplotu.txt");
	string datau = stu.str();
	myfileu << datau;
	myfileu.close();

}


int main()
{
	double start = clock();

	// ======================= Plotting the final config ========================
	vector<HR> VR,HR,UR;
	MC m(1E7L,8,32,32,32,1);
	m.MCRUN();
	VR = m.getVRodlist();
	HR = m.getHRodlist();
	UR = m.getURodlist();
	m.plot(VR,HR,UR);
	// ======================= end of simulation, print out the time ===========
	double end = clock();
	cout <<"This simulation takes "<< (double(end-start)/CLOCKS_PER_SEC)<<endl;
	return 0;
}

