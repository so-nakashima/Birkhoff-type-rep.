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

using std::string;
using std::istream;
using std::vector;
using std::set;


productDistributiveLattice::productDistributiveLattice(const distributiveLattice* lat, int n, std::function<bool(int,int, std::set<std::string>, std::set<std::string>)> oracle)
	: power(n), lattice(lat){
		
}



//Followings are NOT my codes

