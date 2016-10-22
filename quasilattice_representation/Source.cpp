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

#define rep(i,n) for(int i = 0; i != n; i++)

using namespace std;

bool oracle(int i, int j, std::set<std::string> s1, std::set<std::string> s2){
	set<string> diff;
	std::set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(diff, diff.begin()));
	return diff.size() == 0;
}

int main(){

	std::ifstream file("testlattice1.txt");
	distributiveLattice l(file);
	std::set<std::string> s,t;
	s.insert("a");
	s.insert("b");
	t.insert("a");
	productDistributiveLattice pl(&l, 2, oracle);

	std::cout << pl.allowed[0][1][s][t] << std::endl;

	return 0;
}