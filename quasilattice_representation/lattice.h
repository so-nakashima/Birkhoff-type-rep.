#ifndef __LATTICE_HEDDER_INCLUEDED__
#define __LATTICE_HEDDER_INCLUEDED__
#include<set>
#include<string>
#include<map>
#include<vector>
#include<iostream>

class lattice{
public:
	virtual std::set<std::string> join(std::set<std::string>, std::set<std::string>);
	//virtual std::set<std::string> meet(std::set<std::string>, std::set<std::string>);
	lattice(std::istream&);
	//std::set<std::string> principal_ideal(std::set<std::string>);
	bool valid(std::set<std::string>);
protected:
	std::istream& read(std::istream&);
	//std::set<int> join_int(std::set<int>, std::set<int>);
	//std::set<int> meet_int(std::set<int>, std::set<int>);
	//std::map<std::string, int> string2int;
	//std::vector<std::string> int2string;
	std::set<std::string> labels;
	std::map<std::string, std::string> order;
	//std::set<std::string> reduce(std::set<std::string>);
};



/*

class semilattice : public lattice{
public:
	bool consistent(std::set<std::string>);
	bool consistent(std::set<std::string>, std::set<std::string>);
	semilattice(std::istream&);
protected:
	std::istream& read(std::istream&);
	bool valid(std::set<std::string>);
	//bool consistent_int(std::set<int>, std::set<int>);
};

class modularlattice: public lattice{
public:
	modularlattice(std::istream&);
	std::istream& read(std::istream&);
	bool is_colinear(std::set<std::string>, std::set<std::string>);
	std::vector<std::set<std::string>> colinears;
protected:
	bool valid(std::set<std::string>);
};
*/
#endif