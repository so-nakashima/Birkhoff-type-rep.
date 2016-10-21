#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#include<map>
#include<iterator>
#include<fstream>
#include "lattice.h"

#define rep(i,n) for(int i = 0; i != n; i++)


int main(){

	std::ifstream file("testlattice1.txt");
	lattice l(file);
	std::set<std::string> s,t;
	s.insert("a");
	s.insert("b");
	t.insert("c");
	std::set<std::string> hoge = l.join(s,t);

	return 0;
}