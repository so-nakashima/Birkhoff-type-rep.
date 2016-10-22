#ifndef __LATTICE_HEDDER_INCLUEDED__
#define __LATTICE_HEDDER_INCLUEDED__
#include<set>
#include<string>
#include<map>
#include<vector>
#include<iostream>

class distributiveLattice{
public:
	virtual std::set<std::string> join(std::set<std::string>, std::set<std::string>);
	virtual std::set<std::string> meet(std::set<std::string>, std::set<std::string>);
	distributiveLattice(std::istream&);
	std::set<std::string> principal_ideal(std::set<std::string>);
	bool valid(std::set<std::string>);
	bool compare(std::set<std::string>, std::set<std::string>);
	virtual ~distributiveLattice(){};
	std::set<std::string> labels;
	std::set<std::set<std::string>> elements;
protected:
	std::istream& read(std::istream&);
	std::map<std::string, std::string> order;
	std::set<std::string> bit2stringset(int);
	//std::set<int> join_int(std::set<int>, std::set<int>);
	//std::set<int> meet_int(std::set<int>, std::set<int>);
	//std::map<std::string, int> string2int;
	//std::vector<std::string> int2string;
	//std::set<std::string> reduce(std::set<std::string>);
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