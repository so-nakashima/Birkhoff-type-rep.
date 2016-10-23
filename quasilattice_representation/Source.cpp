#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#include<map>
#include<iterator>
#include<fstream>
#include "lattice.h"
//#include "productlattice.h"

#define rep(i,n) for(int i = 0; i != n; i++)

using namespace std;

int main(){
	
	std::ifstream file("testlattice1.txt");
	quasiLattice l(file);

	

	//productDistributiveLattice pl(&l, 3, oracle);
	//auto hoge = pl.calculateBase(1, "b");
	//auto fuga = l.principal_ideal(s);
	 
	//bool flag = pl.compare(2, "a", 1, "b");
	vector<int> vec;
	for(int i = 0; i != 6; i++){
		vec.push_back(i);
	}
	vec[1] = 0;
	auto hoge = l.joinIrreducibles(vec);
	return 0;
}