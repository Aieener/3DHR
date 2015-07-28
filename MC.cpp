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

#include "MC.h"

MC::MC(long int ST, int LEN, int N0, int N1, int N2, double Z)
{
	VRodlist.clear(); // the list storage the Vertical Rods;
    HRodlist.clear(); // the list storage the Horizantal Rods;
    URodlist.clear(); // the list storage the Up Rods;
	n0 = N0;
	n1 = N1;
	n2 = N2;
	length = LEN;
	step = ST;
	z = Z;
	nh=nv=nu=dh=dv=du=ah=av=au=0;
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


void MC::Add(Cells &s,double &prob,double &probav, double &probah, double &probau)
{
	int x,y,z,o; // pick a random position and orientation for the HR to be added;
	x = rand()%n0; // x range[0,n0-1]
	y = rand()%n1; // y range[0,n1-1]
	z = rand()%n2; // z range[0,n2-1]
	o = rand()%3  ; // 0 range {0,1,2}

	if(s.getSquare(x,y,z).isEmpty()) // if it's open, try to do Addition;
	{
		HR rod(x,y,z,length,o);

		//======================== Vertical inside boundary===============================
		if(o == 0)
		{
			if(prob <= probav)
			{
				if(y + length <= n1)
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
					for (int j = 0; j <n1-y-1; j++)
					{
						// check if the vertical space is wide open
						if(s.getSquare(x,y+j+1,z).isOccupied())
						{
							counter2++;
						}
					}
					if (counter2 == 0)
					{
						for (int i = 0; i < y+length-n1; i++)
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
						
						for (int j = 0; j <n1-y; j++)
						{
							s.getSquare(x,y+j,z).setStatus(1);
						}
						for (int i = 0; i < y+length-n1; i++)
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
				if( x + length <= n0)
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
					for (int j = 0; j <n0-x-1; j++)
					{
						// check if the Horizontal space is wide open
						if(s.getSquare(x+j+1,y,z).isOccupied())
						{
							counter4++;

						}
					}
					if (counter4 == 0)
					{
						for (int i = 0; i < x + length-n0; i++)
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
						
						for (int j = 0; j <n0-x; j++)
						{
							s.getSquare(x+j,y,z).setStatus(1);
						}
						for (int i = 0; i < x+length-n0; i++)
						{
							s.getSquare(i,y,z).setStatus(1);
						}							
					}
				}				    												
			}
		}
		else 
		{
        //======================= Up inside boundary ============================
			if(prob <= probau)
			{
				if( z + length <= n2)
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
					for (int j = 0; j <n2-z-1; j++)
					{
						// check if the Horizontal space is wide open
						if(s.getSquare(x,y,z+j+1).isOccupied())
						{
							counter4++;

						}
					}
					if (counter4 == 0)
					{
						for (int i = 0; i < z + length-n2; i++)
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
						
						for (int j = 0; j <n2-z; j++)
						{
							s.getSquare(x,y,z+j).setStatus(1);
						}
						for (int i = 0; i < z+length-n2; i++)
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
				if(y + length <= n1)
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
					for (int j = 0; j <n1-y; j++)
					{
						s.getSquare(x,y+j,z).setStatus(0);
					}
					for (int i = 0; i < y+length-n1; i++)
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
			indx = rand()%int(nh); // redefine indx from Rodlist[0,nh] 

			//remove Rodlist[indx];
			int x,y,z;// the position of the target on the cells;
			x = HRodlist[indx].getX();
			y = HRodlist[indx].getY();
			z = HRodlist[indx].getZ();
			// --------------------- it's a Horizontal rod -----------------------
			if(prob <= probdh)
			{
                // ==============the case rod is inside the Boundary============
				if(x + length <= n0)
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
					for (int j = 0; j <n0-x; j++)
					{
						s.getSquare(x+j,y,z).setStatus(0);
					}
					for (int i = 0; i < x+length-n0; i++)
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
			indx = rand()%int(nu); // redefine indx from Rodlist[0,nu]

			//remove Rodlist[indx];
			int x,y,z;// the position of the target on the cells;
			x = URodlist[indx].getX();
			y = URodlist[indx].getY();
			z = URodlist[indx].getZ();
			// --------------------- it's a Horizontal rod -----------------------
			if(prob <= probdu)
			{
                // ==============the case rod is inside the Boundary============
				if(z + length <= n2)
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
					for (int j = 0; j <n2-z; j++)
					{
						s.getSquare(x,y,z+j).setStatus(0);
					}
					for (int i = 0; i < z+length-n2; i++)
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


void MC::MCRUN(int init)
{
	stringstream st;

	double addordel; // the prob to decide either add or del;
	double probah, probav, probau; // the acceptance prob of addition; proba = min(1.0,aaccp);
	double probdh, probdv, probdu; // the acceptance prob of deletion; probd = min(1.0,daccp);
	double prob; // the prob to decide either accept add/del;
	double aaccph,aaccpv,aaccpu; 
	double daccph,daccpv,daccpu;
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

		aaccph = z*(double(n0*n1*n2)/3.0)/(double(ah-dh+1.0)*double(length));
		aaccpv = z*(double(n0*n1*n2)/3.0)/(double(av-dv+1.0)*double(length));
		aaccpu = z*(double(n0*n1*n2)/3.0)/(double(au-du+1.0)*double(length));

		daccph = (double(ah-dh)*double(length))/(z*(double(n0*n1*n2)/3.0));
		daccpv = (double(av-dv)*double(length))/(z*(double(n0*n1*n2)/3.0));
		daccpu = (double(au-du)*double(length))/(z*(double(n0*n1*n2)/3.0));

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
			if ( init == EMPTY)
			{
				Add(s1,prob,probav,probah,probau);
			}

			else if (init == BOX)
			{
				Add(s2,prob,probav,probah,probau);
			}
			else if (init == PLANE)
			{
				Add(s3,prob,probav,probah,probau);
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
					Del(s1,prob,probdv, probdh,probdu);					
				}
				else if (init == BOX)
				{
					Del(s2,prob,probdv, probdh,probdu);
				}
				else if (init == PLANE)
				{
					Del(s3,prob,probdv, probdh,probdu);
				}

			}			
		}

		// ======================= Record the datas =============================================		
        Q = (nv - nh)/(nh + nv);
        if (step >= 10000)
        {
    		if (i%(step/10000) == 0)
			{
				hisv.record(nv);
				hish.record(nh);
				hisu.record(nu);

				st << i << "         " << Q <<"        "<< nv << "          "<< nh << "         "<< nu << "         "<< tho<< "         "<< endl;
				cout <<"Process: "<< ((10000*i)/step)/100.00 <<"%"<<"    "<<"SIZE: "<<av+ah+au-dv-dh-du<<"    "<<"# of Ver Rod: "<<nv<<"    "<<"# of Hor Rod: "<< nh <<"   "<<"# of Up Rod "<<nu <<"   "<<"tho is: "<<tho << endl;
			}    	
        }


		else 
		{
			hisv.record(nv);
			hish.record(nh);
			hisu.record(nu);
			st << i << "         " << Q <<"        "<< nv << "          "<< nh << "         "<< nu << "         "<< tho<< "         "<< endl;
			cout <<"Process: "<< 100*(double(i)/double(step)) <<"%"<<"    "<<"SIZE: "<<av+ah+au-dv-dh-du<<"    "<<"# of Ver Rod: "<<nv<<"    "<<"# of Hor Rod: "<< nh <<"   "<<"# of Up Rod "<<nu <<"   "<<"tho is: "<<tho << endl;
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


// int main()
// {
// 	double start = clock();
// 	// ======================= Plotting the final config ========================
// 	vector<HR> VR,HR,UR;
// 	MC m(1E8L,4,16,16,16,20000);
// 	m.MCRUN();
// 	VR = m.getVRodlist();
// 	HR = m.getHRodlist();
// 	UR = m.getURodlist();
// 	m.plot(VR,HR,UR);
// 	// ======================= end of simulation, print out the time ===========
// 	double end = clock();
// 	cout <<"This simulation takes "<< (double(end-start)/CLOCKS_PER_SEC)<<endl;
// 	return 0;
// }

