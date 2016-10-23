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
#include<assert.h>

#define rep(i,n) for(int i = 0; i != n; i++) 

using std::string;
using std::istream;
using std::vector;
using std::set;
using std::map;

productQuasiLattice::productQuasiLattice(quasiLattice* lat, int n, std::function<bool(int,int, int, int)> oracle): power(n), lattice(lat){
	initializeAllowed(oracle);
	initializeProjection();
	initializeMinimum();
	initializeCoordinate_irreducibles();
	initializeGroundBases();
}

void productQuasiLattice::initializeAllowed(std::function<bool(int,int, int, int)> oracle){
	for(int i = 0; i != power; i++){
		vector<vector<vector<bool>>> bind1;
		for(int j = 0; j != power; j++){
			vector<vector<bool>> bind2;
			for(int k = 0; k != lattice->size; k++){
				vector<bool> bind3;
				for(int l = 0; l != lattice->size; l++){
					bind3.push_back(oracle(i,j,k,l));
				}
				bind2.push_back(bind3);
			}
			bind1.push_back(bind2);
		}
		allowed.push_back(bind1);
	}
}

void productQuasiLattice::initializeProjection(){
	for(int i = 0; i != power; i++){
		vector<int> ithproj;
		for(int e = 0; e != lattice->size; e++){
			if(allowed[i][i][e][e])
				ithproj.push_back(e);
		}
		projections.push_back(ithproj);
	}
}

void productQuasiLattice::initializeMinimum(){
	for(int i = 0; i != power; i++)
		minimum.push_back(lattice->minimum(projections[i]));
}

void productQuasiLattice::initializeCoordinate_irreducibles(){
	for(int i = 0; i != power; i++)
		coordinate_irreducibles.push_back(lattice->joinIrreducibles(projections[i]));
}

void productQuasiLattice::initializeGroundBases(){
	for(int i = 0; i != power; i++){
		map<int, vector<int>> ithBase;
		for(int j = 0; j !=  coordinate_irreducibles[i].size(); j++){
			int e = coordinate_irreducibles[i][j];
			vector<int> ethBase;
			for(int k = 0; k != power; k++){
				if(i == k)
					ethBase.push_back(e);
				else{
					vector<int> allowedpair;
					for(int l = 0; l != projections[k].size(); l++){
						int f = projections[k][l];
						if(allowed[i][k][e][f])
							allowedpair.push_back(f);
					}
					ethBase.push_back(lattice->minimum(allowedpair));
				}
			}
			ithBase[e] = ethBase;
		}
		groundBases.push_back(ithBase);
	}
}