/*cells_test.cpp
*/
#include <cassert>
#include "cells.h"
#include "square.h"
#include "hardrods.h"
#include <tuple>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

void test_basic()
{

	Cells sb(32,32,32,true,8);
	sb.getBoxlist();
	std::vector<Boxgen> list;
	list = sb.getBoxlist();
	// cout << sb.getBoxlist().size() << endl;
	for ( int i = 0; i<list.size(); i++)
	{
		int x = list[i].getPos()[0];
		int y = list[i].getPos()[1];
		int z = list[i].getPos()[2];
		int ori = list[i].getOri();
		int v = list[i].getBVRodlist().size();
		int h = list[i].getBHRodlist().size();
		int u = list[i].getBURodlist().size();
		cout << v<< "       "<< h << "       "<< u << endl;
		// cout <<"x = "<< x <<",y = "<< y << ", z = "<< z<< " Orientation is :"<< ori <<endl;
	}
}

int main()
{
	test_basic();
	return 0;
}