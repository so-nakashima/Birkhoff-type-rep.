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
using std::map;


productDistributiveLattice::productDistributiveLattice(const distributiveLattice* lat, int n, std::function<bool(int,int, std::set<std::string>, std::set<std::string>)> oracle)
	: power(n), lattice(lat){
		for(int i = 0; i != power; i++){
			vector<map<set<string>,map<set<string>,bool>>> oraclecopy_bind1;
			for(int j = 0; j != power; j++){
				map<set<string>,map<set<string>,bool>> oraclecopy_bind2;
				for(auto itr1 = lattice->elements.begin(); itr1 != lattice->elements.end(); itr1++){
					for(auto itr2 = lattice->elements.begin(); itr2 != lattice->elements.end(); itr2++)
						oraclecopy_bind2[*itr1][*itr2] = oracle(i, j, *itr1, *itr2);
				}
				oraclecopy_bind1.push_back(oraclecopy_bind2);
			}
			allowed.push_back(oraclecopy_bind1);
		}
}



//Followings are NOT my codes

