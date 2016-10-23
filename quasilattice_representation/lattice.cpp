#include<iostream>
#include "lattice.h"
#include<vector>
#include<string>
#include<math.h>
#include<map>
#include<iterator>
#include<algorithm>
#include<assert.h>
#include<queue>


using std::string;
using std::istream;
using std::vector;
using std::set;


istream& quasiLattice::read(istream& in){
	in >> size;
	//reading meet table
	for(int i = 0; i != size; i++){
		vector<int> row;
		for(int j = 0; j != size; j++){
			int temp; in >> temp;
			row.push_back(temp);
		}
		meetTable.push_back(row);
	}
	//reading join table
	for(int i = 0; i != size; i++){
		vector<int> row;
		for(int j = 0; j != size; j++){
			int temp; in >> temp;
			row.push_back(temp);
		}
		joinTable.push_back(row);
	}
	return in;
};

quasiLattice::quasiLattice(istream& in){
	read(in);
}

int quasiLattice::join(int i, int j){
	return joinTable[i][j];
}

int quasiLattice::meet(int i, int j){
	return meetTable[i][j];
}