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

#define rep(i,n) for(int i = 0; i != n; i++) 

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

bool quasiLattice::compare(int i, int j){
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

int quasiLattice::maximum(const std::vector<int>& subuniv){
	assert(subuniv.size() != 0);
	int res = subuniv[0];
	for(int i = 1; i != subuniv.size(); i++){
		res = join(res, subuniv[i]);
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

vector<int> quasiLattice::lowerCover(const vector<int>& irreducibles){
	vector<int> res;
	for(int i = 0; i != irreducibles.size(); i++){
		vector<int> lowerset;
		for(int j = 0; j != irreducibles.size(); j++){
			if(irreducibles[j] != irreducibles[i] && compare(irreducibles[j],irreducibles[i]))
				lowerset.push_back(irreducibles[j]);
		}
		if(lowerset.size() > 0)
			res.push_back(maximum(lowerset));
		else
			res.push_back(-1);
	}
	return res;
}

vector<int> quasiLattice::joinRepresentation(int elem, const std::vector<int>& irreducibles){
	vector<int> lowers;
	//set<int> taboo;
	//vector<int> covers = lowerCover(irreducibles);
	if(elem == -1)
		return vector<int>();
	for(int i = 0; i != irreducibles.size(); i++){
		if(compare(irreducibles[i], elem)){
			lowers.push_back(irreducibles[i]);
			//taboo.insert(covers[i]);
		}
	}
	/*
	rep(i,lowers.size()){
		rep(j, lowers.size()){
			if(lowers[i] == lowers[j])
				continue;
			if(compare(lowers[j],lowers[i]))
				taboo.insert(lowers[j]);
		}
	}
	vector<int> res;
	for(int i = 0; i != lowers.size(); i++){
		if(taboo.find(lowers[i]) == taboo.end())
			res.push_back(lowers[i]);
	}
	return res;*/
	return lowers;
}

modularLattice::modularLattice(istream& in): quasiLattice(in){}

bool modularLattice::pairwiseIncomparable(int a, int b, int c){
	return !compare(a,b) && !compare(a,c) && !compare(b,a) && !compare(b,c) && !compare(c,a) && !compare(c,b);
}

std::vector<std::vector<int>> modularLattice::colinearSets(std::vector<int> irreducibles){
	//list up candidate pair for colinearity
	vector<vector<int>> res; 
	rep(i,irreducibles.size()){
		int a = irreducibles[i];
		for(int j = i; j != irreducibles.size(); j++){
			int b = irreducibles[j];
			for(int k = j; k != irreducibles.size(); k++){
				int c = irreducibles[k];
				if(pairwiseIncomparable(a,b,c) && join(a,b) == join(b,c) && join(b,c) == join(c,a)){
					vector<int> temp; temp.push_back(i);temp.push_back(j);temp.push_back(k);
					res.push_back(temp);
				}
			}
		}
	}
	return res;
}