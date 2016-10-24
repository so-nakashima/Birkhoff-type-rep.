#ifndef __LATTICE_HEDDER_INCLUEDED__
#define __LATTICE_HEDDER_INCLUEDED__
#include<set>
#include<string>
#include<map>
#include<vector>
#include<iostream>
#include <bitset>

class quasiLattice{
public:
	int join(int, int);
	int meet(int, int);
	quasiLattice(std::istream&);
	bool compare(int, int);
	std::vector<int> joinIrreducibles(const std::vector<int>&);
	int minimum(const std::vector<int>&);
	int maximum(const std::vector<int>&);// may NOT be maximum if inconsistent pairs included!!
	virtual ~quasiLattice(){};
	int size;
	std::vector<int> joinRepresentation(int elem, const std::vector<int>& irreducibles);
	std::vector<int> lowerCover(const std::vector<int>&); // Only for irreducible set; details are explained in productQuasiLattice::coordinate_lowercovers
protected:
	std::istream& read(std::istream&);
	std::vector<std::vector<int>> joinTable;
	std::vector<std::vector<int>> meetTable;
};



/*

class medianSemilattice : public lattice{
public:
	bool consistent(std::set<std::string>);
	bool consistent(std::set<std::string>, std::set<std::string>);
	semiLattice(std::istream&);
protected:
	std::istream& read(std::istream&);
	bool valid(std::set<std::string>);
	//bool consistent_int(std::set<int>, std::set<int>);
};*/

class modularLattice: public quasiLattice{
public:
	modularLattice(std::istream&);
	std::istream& read(std::istream&);
	//bool is_colinear(std::set<std::string>, std::set<std::string>);
	//std::vector<std::set<std::string>> colinears;
protected:
	//bool valid(std::set<std::string>);
};
#endif