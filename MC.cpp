/*
* MC.cpp
* Simulation of 3-D Hard-Rod By GCMC
* Author: Yuding Ai
* Date: 2015.07.15
* *************************** MC implementation ********************************
* This simulation follows grand canonical ensemble.
* In such simulation, Only Energy and N of particles fluctuate, we accomplish EF by
* using only add/del moves, and so does NF;
* ******************************************************************************
*
* The Acceptance relation for Addition is given by: (Page 12 --M.S.Shell 2012)
*  -- Pad = min [1,((n0*n1*n2)/(length*(N + 1))) * exp{-beta*miu}]
*
* The Acceptance relation for Deletion is given by:
*  -- Pde = min [1,(N*length/(n0*n1*n2))*exp{beta*miu}]
*
* where miu is the chemical potential
*
*/

#include "MC.h"

MC::MC(long int ST, int LEN, int N0, int N1, int N2, double Z)
{
	VRodlist.clear(); // the list storage the Vertical Rods;
    HRodlist.clear(); // the list storage the Horizantal Rods;
    URodlist.clear(); // the list storage the Up Rods;
	n0 = N0;          // length of the box
	n1 = N1;          // weight of the box
	n2 = N2;          // hight  of the box
	length = LEN;     // length of rod
	step = ST;        // MC steps
	z = Z;            // activity z = exp(beta*miu)
	nh=nv=nu=dh=dv=du=ah=av=au=0;            // initialize all my number count into 0; ie. nh stands for number of horizontal rods
	                                         // dh stands for the times of deletion for for horizontal rods and ah is for addition.
}

const vector<HR>& MC::getVRodlist() const
{
	return VRodlist;
}

const vector<HR>& MC::getHRodlist() const
{
	return HRodlist;
}

const vector<HR>& MC::getURodlist() const
{
	return URodlist;
}


void MC::Add(Cells &s,double &prob,double &proba)
{
	int x,y,z,o; // pick a random position and orientation for the HR to be added;
	x = rand()%n0; // x range[0,n0-1]
	y = rand()%n1; // y range[0,n1-1]
	z = rand()%n2; // z range[0,n2-1]
	o = rand()%3  ; // 0 range {0,1,2}

	if(s.getSquare(x,y,z).isEmpty()) // if it's open, try to do Addition;
	{
		HR rod(x,y,z,length,o);

		if(o == 0)
		{
		//======================== Vertical ===============================
			// the vertical case
			int counter = 0;

			for (int j = 0; j < length-1; j++)
			{
				// check if the vertical space is wide open
				if(s.getSquare(x,(y+j+1)%n1,z).isOccupied())
				{
					counter++;
					break;
				}						
			}
			// cout <<"counter = "<< counter<< endl;
			if (counter == 0)
			{
				if(prob<=proba)
				{
					// Do addition;
					// push the new rod into the VRodlist;
					VRodlist.push_back(rod);
					av++;
					nv++;// accumulate the # of ver rod;
					// update new N, E and new config;
					for (int i = 0; i < length; i++)
					{	
						s.getSquare(x,(y+i)%n1,z).setStatus(1);
					}					
				}		
			}									
		}

		else if(o == 1)
		{
        //======================= Horizontal  ============================
			int counter = 0;
			for (int j = 0; j< length-1 ; j++)
			{
				// check if the horizontal space is wide open
				if(s.getSquare((x+1+j)%n0,y,z).isOccupied())
				{
					counter++;
					break;
				}							
			}
			if (counter == 0)
			{
				if(prob<= proba)
				{
					//Do addition;
					//push the new rod into the HRodlist;
					HRodlist.push_back(rod);
					ah++;
					nh++;// accumulate the # of hor rod;

					// update new N, E and new config;
					for (int i = 0; i < length; i++)
					{
						s.getSquare((x+i)%n0,y,z).setStatus(1);
					}
				}
			}
		}
		else 
		{
        //======================= Up  ============================
			int counter = 0;
			for (int j = 0; j< length-1 ; j++)
			{
				// check if the horizontal space is wide open
				if(s.getSquare(x,y,(z+j+1)%n2).isOccupied())
				{
					counter++;
					break;
				}							
			}
			if (counter == 0)
			{
				if(prob<= proba)
				{
					//Do addition;
					//push the new rod into the HRodlist;
					URodlist.push_back(rod);
					au++;
					nu++;// accumulate the # of hor rod;

					// update new N, E and new config;
					for (int i = 0; i < length; i++)
					{
						s.getSquare(x,y,(z+i)%n2).setStatus(1);
					}
				}
			}							
		}
    }
}

void MC::Del(Cells &s,double &prob,double &probd, double &size)
{

	if(nv + nh + nu >0)// make sure there are Vertical rod;
	{
		int indx; // pick a random index from the Rodlist;
		indx = rand()%int(nv+nh+nu);

		//remove Rodlist[indx];
		int x,y,z;// the position of the target on the cells;

		if(prob <= probd)
		{					
			if(indx < nv)
			{
				x = VRodlist[indx].getX();
				y = VRodlist[indx].getY();
				z = VRodlist[indx].getZ();	
				// --------------------- it's a vertical rod -----------------------

				for(int i = 0; i<VRodlist[indx].getLength(); i++)
				{
					// update the new config of cells
					s.getSquare(x,(y+i)%n1,z).setStatus(0);
				}
				// remove the target rod from the vector Rodlist;
				VRodlist.erase(VRodlist.begin() + indx);
				nv--;// substract the # of ver rod;
				dv++;
			}
			
			else if (indx < nv + nh)
			{
				x = HRodlist[indx - nv].getX();
				y = HRodlist[indx - nv].getY();
				z = HRodlist[indx - nv].getZ();	
				// --------------------- it's a horizontal rod -----------------------

				for(int i = 0; i<HRodlist[indx-nv].getLength(); i++)
				{
					// update the new config of cells
					s.getSquare((x+i)%n0,y,z).setStatus(0);
				}
				// remove the target rod from the vector Rodlist;
				HRodlist.erase(HRodlist.begin() + indx - nv);
				nh--;// substract the # of ver rod;
				dh++;
			}
			else
			{
				x = URodlist[indx - nv - nh].getX();
				y = URodlist[indx - nv - nh].getY();
				z = URodlist[indx - nv - nh].getZ();	
				// --------------------- it's a up rod -----------------------
				for(int i = 0; i<URodlist[indx-nv-nh].getLength(); i++)
				{
					// update the new config of cells
					s.getSquare(x,y,(z+i)%n2).setStatus(0);
				}
				// remove the target rod from the vector Rodlist;
				URodlist.erase(URodlist.begin()+indx-nv-nh);
				nu--;// substract the # of ver rod;
				du++;

			}
		}
	}	
}


void MC::MCRUN(int init)
{
	stringstream st;

	double addordel; // the prob to decide either add or del;
	double proba,probd; // the acceptance prob of addition; proba = min(1.0,aaccp);
	// double probdh, probdv, probdu; // the acceptance prob of deletion; probd = min(1.0,daccp);
	double prob; // the prob to decide either accept add/del;
	double aaccp,daccp; 
	// double daccph,daccpv,daccpu;
	double Q; // the fraction of hor and ver particle;
	double tho; // the density 
	double size;
	Cells s1(n0,n1,n2,EMPTY,length); 
	Cells s2(n0,n1,n2,BOX, length);
	Cells s3(n0,n1,n2,PLANE,length);
	
	srand(time(NULL));
	long int i = 0;
	Histogram hisv(0, n0*n1*n2/length, 1); // the histogram of nv
	Histogram hish(0, n0*n1*n2/length, 1); // the histogram of nh
	Histogram hisu(0, n0*n1*n2/length, 1); // the histogram of nu

	// ****************** if start with an empty Box ***************************** //
	//create my grid of empty cells;
	if ( init == EMPTY)
	{		
		// do nothing since it's empty
	}

	// ******************  if there is an initial state:************************** //
	else if (init == BOX)
	{
	    // merge the rodlists to be the BOX initial config
		std::vector<Boxgen> list;
		list = s2.getBoxlist();
		for(int i = 0; i<list.size(); i ++)
		{
			if(list[i].getOri() == 0)
			{
				av += length*length;
				nv = av;
			    VRodlist.insert(VRodlist.end(),list[i].getBVRodlist().begin(),list[i].getBVRodlist().end());
			}
			else if (list[i].getOri() == 1)
			{
				ah += length*length;
				nh = ah;
				HRodlist.insert(HRodlist.end(),list[i].getBHRodlist().begin(),list[i].getBHRodlist().end());
			}
			else if(list[i].getOri() == 2)
			{
				au += length*length;
				nu = au;
				URodlist.insert(URodlist.end(),list[i].getBURodlist().begin(),list[i].getBURodlist().end());
			}
		}
	}

	else if (init == PLANE)
	{
		// merge the rodlists to be the BOX initial config
		std::vector<Planegen> list;
		list = s3.getPlanelist();
		for(int i =0; i<list.size(); i++)
		{
			if(list[i].getOri() == 0)
			{
				av += double(n2*n0)/length;
				nv = av;
			    VRodlist.insert(VRodlist.end(),list[i].getPVRodlist().begin(),list[i].getPVRodlist().end());
			}

			else if (list[i].getOri() == 1)
			{
				ah += double(n1*n2)/length;
				nh = ah;
				HRodlist.insert(HRodlist.end(),list[i].getPHRodlist().begin(),list[i].getPHRodlist().end());
			}

			else if(list[i].getOri() == 2)
			{
				au += double(n0*n2)/length;
				nu = au;
				URodlist.insert(URodlist.end(),list[i].getPURodlist().begin(),list[i].getPURodlist().end());
			}
		}
	}


	// ******************  finish setting initial state************************** //


	//================================Start my MC simulation=================================
	while (i<step)
	{
		i++;
		// generate a random probability to decide either add or del;
		addordel = rand()%2 ; 
		size = av+ah+au-dv-dh-du;

		// *****************define the probabilities ***********************************
		prob = ((double) rand() / (RAND_MAX)); 
		tho = double(length*size)/double(n0*n1*n2);

		aaccp = z*double(n0*n1*n2)/(double(nh+nv+nu+1.0)*double(length));

		daccp = (double(nh+nv+nu)*double(length))/(z*double(n0*n1*n2));

		proba = min(1.0,aaccp);
		probd = min(1.0,daccp);


		//******************* The structure of my vector list of HR ***********************
        // I have 3 lists corresponding to my 3 species
		// *******************************************************************************

        // ===========================Addition ===================================
		if(addordel == 0) 
		{
			//Do Addition;
			if ( init == EMPTY)
			{
				Add(s1,prob,proba);
			}

			else if (init == BOX)
			{
				Add(s2,prob,proba);
			}
			else if (init == PLANE)
			{
				Add(s3,prob,proba);
			}
			
		}

		// ============================Deletion=============================
		else
		{
			if (size != 0) // make sure there are rods to be del;
			{
				//Do deletion;
				if (init == EMPTY)
				{
					Del(s1,prob,probd,size);					
				}
				else if (init == BOX)
				{
					Del(s2,prob,probd,size);
				}
				else if (init == PLANE)
				{
					Del(s3,prob,probd,size);
				}
			}			
		}

		// ======================= Record the datas =============================================		
        Q = (nv - nh)/(nh + nv);
        if (step >= 10000)
        {
    		if (i%(step/10000) == 0)
			{
				// hisv.record(nv);
				// hish.record(nh);
				// hisu.record(nu);

				st << i << "         " << Q <<"        "<< nv << "          "<< nh << "         "<< nu << "         "<< tho<< "         "<< endl;
				cout <<"Process: "<< ((10000*i)/step)/100.00 <<"%"<<"    "<<"SIZE: "<<av+ah+au-dv-dh-du<<"    "<<"# of Ver Rod: "<<nv<<"    "<<"# of Hor Rod: "<< nh <<"   "<<"# of Up Rod "<<nu <<"   "<<"tho is: "<<tho << endl;
			}    	
        }


		else 
		{
			// hisv.record(nv);
			// hish.record(nh);
			// hisu.record(nu);
			st << i << "         " << Q <<"        "<< nv << "          "<< nh << "         "<< nu << "         "<< tho<< "         "<< endl;
			cout <<"Process: "<< 100*(double(i)/double(step)) <<"%"<<"    "<<"SIZE: "<<av+ah+au-dv-dh-du<<"    "<<"# of Ver Rod: "<<nv<<"    "<<"# of Hor Rod: "<< nh <<"   "<<"# of Up Rod "<<nu <<"   "<<"tho is: "<<tho << endl;
		}


	}
	// Record the data into a txt file
	ofstream myfile3 ("dataplot.dat");
	string data = st.str();
	myfile3 << data;
	myfile3.close();
	// hisv.plot(1);
	// hish.plot(2);
	// hisu.plot(3);
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




