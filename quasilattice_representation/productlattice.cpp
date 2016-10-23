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