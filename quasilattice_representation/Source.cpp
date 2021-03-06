#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#include<map>
#include<iterator>
#include<fstream>
#include "lattice.h"
#include "productlattice.h"
#include "graph.h"

#define rep(i,n) for(int i = 0; i != n; i++)

using namespace std;

string outfile = "graphviz\\serios";
string infile = "lattice\\modular3.txt";
//string infile = "lattice\\distributive1.txt";

bool oracle(int i, int j, int a, int b){
	return true;
	//return (i != 2 || a == 3) && (j != 2 || b == 3);
	//return (i != 2 || a == 3) && (j != 2 || b == 3) && (i != 1 || a != 1) && (j != 1 || b != 1);
	//return a == b;
	//return (i != 1 || a != 1) && (j != 1 || b != 1);
}

int main(){
	
	std::ifstream file(infile.c_str());
	//quasiLattice l(file);
	modularLattice l(file);
	
	/*
	Edge e1(0,4,0); Edge e2(0,1,0);Edge e3(1,0,0);Edge e4(1,2,0);Edge e5(2,3,0);Edge e6(3,2,0);
	Graph g;
	Edges temp;
	temp.push_back(e1); temp.push_back(e2); g.push_back(temp); temp.clear();
	temp.push_back(e3); temp.push_back(e4); g.push_back(temp); temp.clear();
	temp.push_back(e5); g.push_back(temp); temp.clear();
	temp.push_back(e6); g.push_back(temp); temp.clear();
	g.push_back(temp);

	vector<vector<int>> res;
	stronglyConnectedComponents(g,res);
	*/

	//productDistributiveLattice pl(&l, 3, oracle);
	//auto hoge = pl.calculateBase(1, "b");
	//auto fuga = l.principal_ideal(s);
	 
	//bool flag = pl.compare(2, "a", 1, "b");
	//vector<int> vec;
	/*for(int i = 1; i != 6; i++){
		vec.push_back(i);
	}*/
	//vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4); vec.push_back(5);
	bool funi = l.is_collinear(1,2,3);
	//auto hoge = l.colinearSets(vec);

	//productQuasiLattice pl(&l,3,oracle);
	productModularLattice pl(&l, 3, oracle);
	pl.graphicRepresentation(outfile);
	return 0;
}