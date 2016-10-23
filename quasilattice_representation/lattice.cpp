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

int quasiLattice::compare(int i, int j){
	return i == meet(i,j);
}

int quasiLattice::minimum(const std::vector<int>& subuniv){
	assert(subuniv.size() != 0);
	int res = subuniv[0];
	for(int i = 1; i != subuniv.size(); i++){
		res = meet(res, subuniv[i]);
	}
	return res;
}

vector<int> quasiLattice::joinIrreducibles(const vector<int>& subuniv){
	//initialize
	vector<bool> flags(size,0);
	for(int i = 0; i != subuniv.size(); i++){
		flags[subuniv[i]] = 1;
	}
	int min = minimum(subuniv);
	flags[min] = 0;
	//Full search of table
	for(int i = 0; i != subuniv.size(); i++){
		int I = subuniv[i];
		if(I == min)
			continue;
		for(int j = 0; j != subuniv.size(); j++){
			int J = subuniv[j];
			if(J==min || I == J)
				continue;
			int joined = join(I,J);
			if(joined != I && joined != J)
				flags[joined] = 0;
		}
	}
	//output
	vector<int> res;
	for(int i = 0; i != size; i++){
		if(flags[i])
			res.push_back(i);
	}
	return res;
};