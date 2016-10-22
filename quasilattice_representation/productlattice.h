#ifndef __PRODUCTLATTICE_HEDDER_INCLUDED__
#define __PRODUCTLATTICE_HEDDER_INCLUDED__

#include "lattice.h"
#include <functional>
#include <set>

class productDistributiveLattice{
public:
	productDistributiveLattice(const distributiveLattice*, int, std::function<bool(int,int, std::set<std::string>, std::set<std::string>)>);
	bool compare(int, int, std::set<std::string>, std::set<std::string>);
	bool menbership(std::vector<int>, std::vector<std::set<std::string>>);
	void graphicRepresentation();
	bool calculateBase(std::vector<int>, std::vector<std::set<std::string>>);
protected:
	const distributiveLattice* lattice;
	const int power;
	bool equality(int, int, std::set<std::string>, std::set<std::string>);
	std::map<std::set<std::string>, std::map<std::set<std::string>, bool>> allowed;
private:
};

//developing...

class productMedianSemilattice : public productDistributiveLattice{
public:
	void graphicRepresentation();
protected:
private:
};

class productModularLattice : public productDistributiveLattice{
public:
	void graphicRepresentation();
protected:
private:
};

#endif