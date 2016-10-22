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
		//construction for allowed
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
		//construction for groundBases
		for(int i = 0; i != power; i++){
			map<string, vector<set<string>>> ithBase;
			for(auto itr = lattice->labels.begin(); itr != lattice->labels.end(); itr++){
				vector<set<string>> base;
				set<string> singleton; singleton.insert(*itr);
				if(allowed[i][i][singleton][singleton]){
					for(int j = 0; j != power; j++){
						if(j == i){
							set<string> temp; temp.insert(*itr);
							base.push_back(temp);
						}
						else{
							set<string> jthComp;
							bool flag = true;
							for(auto itrelem = lattice->elements.begin(); itrelem != lattice->elements.end(); itrelem++){
								if(allowed[i][j][singleton][*itrelem] && flag){
									jthComp = *itrelem;
									flag = false;
								}
								else if(allowed[i][j][singleton][*itrelem]){
									set<string> forCopy;
									std::set_intersection(jthComp.begin(), jthComp.end(), itrelem->begin(), itrelem-> end(), inserter(forCopy, forCopy.begin()));
									jthComp = forCopy;
								}
							}
							base.push_back(jthComp);
						}
					}
				}
				ithBase[*itr] = base;
			}
			groundBases.push_back(ithBase);
		}
}

std::pair<bool, std::vector<std::set<std::string>>> productDistributiveLattice::calculateBase(int i, std::string a){
	set<string> sing; sing.insert(a);
	return std::make_pair(allowed[i][i][sing][sing], groundBases[i][a]);
}

