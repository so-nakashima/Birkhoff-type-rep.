#ifndef __PRODUCTLATTICE_HEDDER_INCLUDED__
#define __PRODUCTLATTICE_HEDDER_INCLUDED__

#include "lattice.h"
#include <functional>
#include <set>
#include "graph.h"

class productQuasiLattice{
public:
	productQuasiLattice(quasiLattice*, int, std::function<bool(int,int, int, int)>); //oracle can be used for 1 coordinate as A[i][i]......
	bool compare(int,int,int,int); //compare(i,a,j,b) means e^i_a < e^j_b
	bool equality(int, int, int, int);
	//bool menbership(std::vector<int>, std::vector<int>);//partial ver.
	//bool membership(std::vector<int>);
	void graphicRepresentation(const std::string&);
	//std::vector<int> calculateBase(std::vector<int>, std::vector<int>);
	//std::vector<int> calculateBase(int, int);
	std::vector<int> minimum;
	std::vector<std::vector<int>> projections; // projections[i] is proj_{i} B (here B is subalgebra)
	std::vector<std::vector<int>> coordinate_irreducibles; // coordinate_irreducibles[i] is join-irreducible element in proj_{i}  B
	std::vector<std::map<int,int>> coordinate_irreducibles2iterator; // coordinate_irreducibles2iterator[i][a] = itr e s.t. cooredinate_irreducibles[i][e] = a 
	std::vector<std::vector<int>> coordinate_lowercovers; //coordinate_lowercovers[i][e] = the unique lower cover of coordinate_irreducible[i][e]
	std::vector<std::pair<int,int>> int2indices;
	std::vector<std::map<int,int>> indices2int;
protected:
	quasiLattice* lattice;
	const int power;
	std::vector<std::map<int, std::vector<int>>> groundBases; //groundBases[i][a] = e^i_a in my notes
	std::vector<std::vector<std::vector<std::vector<bool>>>> allowed; //allowed[i][j][s1][s2] means "is there an elements S s.t. S[i] = s1 and S[j] = s2; 
	void initializeAllowed(std::function<bool(int,int, int, int)>);
	void initializeProjection();
	void initializeMinimum();
	void initializeCoordinate_irreducibles();
	void initializeGroundBases();
	void initializeCoordinate_lowercovers();
	void initializeIndicesConvertors();
	Graph computeIrreducibleGraph();
	std::pair<std::vector<std::vector<int>>, std::vector<std::map<int,int>>> SCCdecomposited();
private:
};

//developing...

class productMedianSemilattice : public productQuasiLattice{
public:
	void graphicRepresentation();
protected:
private:
};

class productModularLattice : public productQuasiLattice{
public:
	void graphicRepresentation();
protected:
private:
};

#endif