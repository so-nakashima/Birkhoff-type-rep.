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
	int compare(int, int);
	std::vector<int> joinIrreducibles(const std::vector<int>&);
	virtual ~quasiLattice(){};
	int size;
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
};

class modularLattice: public lattice{
public:
	modularLattice(std::istream&);
	std::istream& read(std::istream&);
	bool is_colinear(std::set<std::string>, std::set<std::string>);
	std::vector<std::set<std::string>> colinears;
protected:
	bool valid(std::set<std::string>);
};
*/
#endif