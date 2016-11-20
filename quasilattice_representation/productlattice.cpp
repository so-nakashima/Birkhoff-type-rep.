#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#include<map>
#include<iterator>
#include<fstream>
#include "lattice.h"
#include "productlattice.h"
#include<assert.h>
#include "graph.h"

#define rep(i,n) for(int i = 0; i != n; i++) 

using std::string;
using std::istream;
using std::vector;
using std::set;
using std::pair;
using std::map;
using std::endl;

productQuasiLattice::productQuasiLattice(quasiLattice* lat, int n, std::function<bool(int,int, int, int)> oracle): power(n), lattice(lat){
	initializeAllowed(oracle);
	initializeProjection();
	initializeMinimum();
	initializeCoordinate_irreducibles();
	initializeCoordinate_lowercovers();
	initializeGroundBases();
	initializeIndicesConvertors();
}

void productQuasiLattice::initializeAllowed(std::function<bool(int,int, int, int)> oracle){
	for(int i = 0; i != power; i++){
		vector<vector<vector<bool>>> bind1;
		for(int j = 0; j != power; j++){
			vector<vector<bool>> bind2;
			for(int k = 0; k != lattice->size; k++){
				vector<bool> bind3;
				for(int l = 0; l != lattice->size; l++){
					bind3.push_back(oracle(i,j,k,l));
				}
				bind2.push_back(bind3);
			}
			bind1.push_back(bind2);
		}
		allowed.push_back(bind1);
	}
}

void productQuasiLattice::initializeProjection(){
	for(int i = 0; i != power; i++){
		vector<int> ithproj;
		for(int e = 0; e != lattice->size; e++){
			if(allowed[i][i][e][e])
				ithproj.push_back(e);
		}
		projections.push_back(ithproj);
	}
}

void productQuasiLattice::initializeMinimum(){
	for(int i = 0; i != power; i++)
		minimum.push_back(lattice->minimum(projections[i]));
}

void productQuasiLattice::initializeCoordinate_irreducibles(){
	for(int i = 0; i != power; i++){
		coordinate_irreducibles.push_back(lattice->joinIrreducibles(projections[i]));
		map<int,int> ithIrreducibles2itr;
		for(int j = 0; j != coordinate_irreducibles[i].size(); j++){
			ithIrreducibles2itr[coordinate_irreducibles[i][j]]=j;
		}
		coordinate_irreducibles2iterator.push_back(ithIrreducibles2itr);
	}
}

void productQuasiLattice::initializeCoordinate_lowercovers(){
	for(int i = 0; i != power; i++){
		coordinate_lowercovers.push_back(lattice->lowerCover(coordinate_irreducibles[i]));
	}
}

void productQuasiLattice::initializeGroundBases(){
	for(int i = 0; i != power; i++){
		map<int, vector<int>> ithBase;
		for(int j = 0; j !=  coordinate_irreducibles[i].size(); j++){
			int e = coordinate_irreducibles[i][j];
			vector<int> ethBase;
			for(int k = 0; k != power; k++){
				if(i == k)
					ethBase.push_back(e);
				else{
					vector<int> allowedpair;
					for(int l = 0; l != projections[k].size(); l++){
						int f = projections[k][l];
						if(allowed[i][k][e][f])
							allowedpair.push_back(f);
					}
					ethBase.push_back(lattice->minimum(allowedpair));
				}
			}
			ithBase[e] = ethBase;
		}
		groundBases.push_back(ithBase);
	}
}

bool productQuasiLattice::compare(int i, int a, int j, int b){ // Only For irreducible a and b
	return lattice->compare(a,groundBases[j][b][i]);
}

void productQuasiLattice::initializeIndicesConvertors(){
		for(int i = 0; i != power; i++){
		map<int,int> ithConvertor;
		for(int a = 0; a != coordinate_irreducibles[i].size(); a++){
			int e = coordinate_irreducibles[i][a];
			ithConvertor[e] = int2indices.size();
			int2indices.push_back(std::make_pair(i,e));
		}
		indices2int.push_back(ithConvertor);
	}
}

Graph productQuasiLattice::computeIrreducibleGraph(){
	//construction of graph
	Graph irreducibleGraph; //node i represents int2indices[i]
	for(int e = 0; e != int2indices.size(); e++){
		int i = int2indices[e].first;
		int a = int2indices[e].second;
		int itr_a = coordinate_irreducibles2iterator[i][a];
		Edges iaEdges;
		/*
		int lower = coordinate_lowercovers[i][itr_a];
		if(lower != -1){
			iaEdges.push_back(Edge(e, indices2int[i][lower], 0));
		}*/
		for(int k = 0; k != power; k++){
			vector<int> kthLowerCover;
			if(k != i)
				kthLowerCover = lattice->joinRepresentation(groundBases[i][a][k], coordinate_irreducibles[k]);
			else
				kthLowerCover = lattice->joinRepresentation(coordinate_lowercovers[i][itr_a], coordinate_irreducibles[i]);//This if statement may not be necessary; i -> i will be removed in scc decomposition and scc lowercover
			for(int j = 0; j != kthLowerCover.size(); j++){
				iaEdges.push_back(Edge(e,indices2int[k][kthLowerCover[j]],0));
			}
		}
		irreducibleGraph.push_back(iaEdges);
	}
	return irreducibleGraph;
}

std::pair<vector<vector<int>>, vector<map<int,int>>> productQuasiLattice::SCCdecomposited(const Graph& irreducibleGraph){
	vector<vector<int>> scc;
	vector<map<int,int>> indices2scc(power, map<int,int>());
	stronglyConnectedComponents(irreducibleGraph, scc);
	for(int i = 0; i != scc.size(); i++){
		for(int j = 0; j != scc[i].size(); j++){
			int k = int2indices[scc[i][j]].first;
			int a = int2indices[scc[i][j]].second;
			indices2scc[k][a] = i;
		}
	}
	return std::make_pair(scc, indices2scc);
}

std::vector<std::set<int>> productQuasiLattice::SCClowercovers(const vector<vector<int>>& scc, vector<map<int,int>>& indices2int ,const Graph& irreducibleGraph){
	vector<set<int>> res(scc.size());
	for(int i = 0; i != scc.size(); i++){
		for(int j = 0; j != scc[i].size(); j++){
			int node = scc[i][j];
			Edges edges = irreducibleGraph[node];
			for(int k = 0; k != edges.size(); k++){
				int dst = edges[k].dst;
				int coord = int2indices[dst].first;
				int elem = int2indices[dst].second;
				int dstComp =  indices2int[coord][elem];
				if(dstComp != i){
					res[i].insert(dstComp);
				}
			}
		}		
	}
	return res;
}

void productQuasiLattice::reduceLowercovers(std::vector<std::set<int>>& lowcovers){
	//calculate should be removed elements
	vector<set<int>> willRemove;
	for(int i = 0; i != lowcovers.size(); i++){
		set<int> ithWillRemove;
		//pick i -> j, i -> k; if j -> k exists, reduce i -> k
		for(auto itr1 = lowcovers[i].begin(); itr1 != lowcovers[i].end(); itr1++){
			for(auto itr2 = lowcovers[i].begin(); itr2 != lowcovers[i].end(); itr2++){
				int j = *itr1;
				int k = *itr2;
				if(j == k)
					continue;
				if(lowcovers[j].find(k) != lowcovers[j].end())
					ithWillRemove.insert(k);

			}
		}
		willRemove.push_back(ithWillRemove);
	}
	//Removing
	for(int i = 0; i != lowcovers.size(); i++){
		for(auto itr = willRemove[i].begin(); itr != willRemove[i].end(); itr++){
			lowcovers[i].erase(*itr);
		}
	}
}

void productQuasiLattice::output2graphviz(string filename, const vector<set<int>>& sccLowercover){
	std::ofstream outfile(filename + ".txt");
	outfile << "digraph dolicas {" << endl;
	outfile << "  node[label = \"\", shape = circle]" << endl;
	rep(i, sccLowercover.size()){
		outfile << "  " << i << ";" << endl;
	}
	rep(i, sccLowercover.size()){
		/*if(sccLowercover[i] != -1)
			outfile << "  " << i << " -> " << sccLowercover[i] << ";" << endl;*/
		for(auto itr = sccLowercover[i].begin(); itr != sccLowercover[i].end(); itr++){
			outfile << "  " << i << " -> " << *itr << ";" << endl;
		}
	}
	outfile << "}" << endl; 
	
	string command = "dot -T png " + filename +".txt -o " + filename + ".png";
	system(command.c_str());
}

void productQuasiLattice::graphicRepresentation(const string& filename){
	//Strongly connected component decomposition
	Graph irreducibleGraph = computeIrreducibleGraph();
	auto hoge = SCCdecomposited(irreducibleGraph);
	vector<vector<int>> scc = hoge.first;
	vector<map<int,int>> indices2scc = hoge.second;
	//Re-spanning edeges
	vector<set<int>> sccLowercover = SCClowercovers(scc, indices2scc, irreducibleGraph);
	//reduce reduntant edges
	reduceLowercovers(sccLowercover);
	//output for graphviz
	output2graphviz(filename, sccLowercover);
	
}

productModularLattice::productModularLattice(modularLattice* lat,int n, std::function<bool(int,int, int, int)> oracle) : productQuasiLattice(lat, n, oracle){
	mlattice = lat;
}

std::set<std::vector<int>> productModularLattice::SCCcollinear(const std::vector<std::vector<int>>& scc, std::vector<std::map<int,int>> indices2scc){
	set<vector<int>> res;
	for(int i = 0; i != power; i++){
		vector<vector<int>> ithCollinears = mlattice->colinearSets(coordinate_irreducibles[i]);
		for(int j = 0; j != ithCollinears.size(); j++){
			int itr1,itr2,itr3; itr1 = ithCollinears[j][0]; itr2 = ithCollinears[j][1]; itr3 = ithCollinears[j][2];
			int scc1,scc2,scc3; 
			scc1 = indices2scc[i][coordinate_irreducibles[i][itr1]];
			scc2 = indices2scc[i][coordinate_irreducibles[i][itr2]];
			scc3 = indices2scc[i][coordinate_irreducibles[i][itr3]];
			vector<int> temp; temp.push_back(scc1); temp.push_back(scc2); temp.push_back(scc3);
			std::sort(temp.begin(), temp.end());
			res.insert(temp);
		}
	}
	return res;
}

string int2string(int n, bool flag){
	string hoge[100] = {"deepskyblue", "seagreen", "indigo", "maroon", "black", "gold", "red", "lightsteelblue", "deeppink", "lawngreen", "grey"};
	int colorNo = 11;
	if(!flag)
		return "";
	else
		return hoge[n%colorNo];

}

void productModularLattice::output2graphviz(std::string filename, const std::vector<std::set<int>>& sccLowercover, const std::set<std::vector<int>> sccCollinears, bool colormode){

	std::ofstream outfile(filename + ".txt");
	outfile << "digraph dolicas {" << endl;
	outfile << "  node[label = \"\", shape = circle]" << endl;
	rep(i, sccLowercover.size()){
		outfile << "  " << i << ";" << endl;
	}
	rep(i, sccLowercover.size()){
		/*if(sccLowercover[i] != -1)
			outfile << "  " << i << " -> " << sccLowercover[i] << ";" << endl;*/
		for(auto itr = sccLowercover[i].begin(); itr != sccLowercover[i].end(); itr++){
			outfile << "  " << i << " -> " << *itr << ";" << endl;
		}
	}
	// new edge output for modular lattice
	int counter = 0;
	for(auto itr = sccCollinears.begin(); itr != sccCollinears.end(); itr++){
		outfile << "  " << (*itr)[0] << " -> " << (*itr)[1] << " -> " << (*itr)[2] << " [dir = none, style = \"dashed\", color = " << int2string(counter, colormode) << "];" << endl;
		outfile << "  {rank = same;" << (*itr)[0] << "; " << (*itr)[1] << "; " << (*itr)[2] << ";}" << endl;
		counter++;
	}


	outfile << "}" << endl; 
	
	string command = "dot -T png " + filename +".txt -o " + filename + ".png";
	system(command.c_str());
}

void productModularLattice::graphicRepresentation(const string& filename, bool colormode){
	//Strongly connected component decomposition
	Graph irreducibleGraph = computeIrreducibleGraph();
	auto hoge = SCCdecomposited(irreducibleGraph);
	vector<vector<int>> scc = hoge.first;
	vector<map<int,int>> indices2scc = hoge.second;
	//Re-spanning edeges
	vector<set<int>> sccLowercover = SCClowercovers(scc, indices2scc, irreducibleGraph);
	//reduce reduntant edges
	reduceLowercovers(sccLowercover);
	//colinear relationship for scc
	set<vector<int>> sccCollinear = SCCcollinear(scc, indices2scc);
	int a = 0;
	//output for graphviz
	output2graphviz(filename, sccLowercover, sccCollinear, colormode);
}