#ifndef __PRODUCTLATTICE_HEDDER_INCLUDED__
#define __PRODUCTLATTICE_HEDDER_INCLUDED__

#include "lattice.h"
#include <functional>
#include <set>

class productDistributiveLattice{
public:
	productDistributiveLattice(distributiveLattice*, int, std::function<bool(int,int, const std::set<std::string>&, const std::set<std::string>&)>); //oracle can be used for 1 coordinate as A[i][i]......
	bool compare(int, const std::string&, int, const std::string&);
	bool menbership(const std::vector<int>&, const std::vector<std::set<std::string>>&);
	void graphicRepresentation();
	std::pair<bool, std::vector<std::set<std::string>>> calculateBase(const std::vector<int>&, const std::vector<std::set<std::string>>&);
	std::pair<bool, std::vector<std::set<std::string>>> calculateBase(int, const std::string&);
	std::vector<std::set<std::string>> minimum;
	std::vector<std::set<std::set<std::string>>> projections; // projections[i] is proj_{i} B (here B is subalgebra)
	std::vector<std::set<std::set<std::string>>> coordinate_irreducibles; // coordinate_irreducibles[i] is join-irreducible element in proj_{i}  B
protected:
	distributiveLattice* lattice;
	const int power;
	bool equality(int, int, std::set<std::string>, std::set<std::string>);
	std::vector<std::map<std::string, std::vector<std::set<std::string>>>> groundBases; //groundBases[i][a] = e^i_a in my notes
	std::vector<std::vector<std::map<std::set<std::string>, std::map<std::set<std::string>, bool>>>> allowed; //allowed[i][j][s1][s2] means "is there an elements S s.t. S[i] = s1 and S[j] = s2; 
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