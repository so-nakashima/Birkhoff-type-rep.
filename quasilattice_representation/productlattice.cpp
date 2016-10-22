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

#define rep(i,n) for(int i = 0; i != n; i++)

using std::string;
using std::istream;
using std::vector;
using std::set;
using std::map;


productDistributiveLattice::productDistributiveLattice(distributiveLattice* lat, int n, std::function<bool(int,int, std::set<std::string>, std::set<std::string>)> oracle)
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
		//construction of projections and minimums
		for(int i = 0; i != power; i++){
			set<set<string>> ithproj;
			set<string> ithmin;
			bool flag = true;
			for(auto itr = lattice->elements.begin(); itr != lattice->elements.end(); itr++){
				if(allowed[i][i][*itr][*itr] && flag){
					ithproj.insert(*itr);
					ithmin = *itr;
					flag = false;
				}
				else if(allowed[i][i][*itr][*itr]){
					ithmin = lattice->meet(ithmin, *itr);
					ithproj.insert(*itr);
				}
			}
			projections.push_back(ithproj);
			minimum.push_back(ithmin);
		}
		/*
		//construction for groundBases
		for(int i = 0; i != power; i++){
			map<string, vector<set<string>>> ithBase;
			for(auto itr = lattice->labels.begin(); itr != lattice->labels.end(); itr++){
				vector<set<string>> base;
				set<string> singleton; singleton.insert(*itr);
				set<string> ideal = lattice->principal_ideal(singleton);
				if(allowed[i][i][ideal][ideal]){
					for(int j = 0; j != power; j++){
						if(j == i){
							set<string> temp; temp.insert(*itr);
							base.push_back(temp);
						}
						else{
							set<string> jthComp;
							bool flag = true;
							for(auto itrelem = lattice->elements.begin(); itrelem != lattice->elements.end(); itrelem++){
								if(allowed[i][j][ideal][*itrelem] && flag){
									jthComp = *itrelem;
									flag = false;
								}
								else if(allowed[i][j][ideal][*itrelem]){
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
		*/
}

std::pair<bool, std::vector<std::set<std::string>>> productDistributiveLattice::calculateBase(int i, std::string a){
	set<string> sing; sing.insert(a);
	set<string> ideal = lattice->principal_ideal(sing);
	return std::make_pair(allowed[i][i][ideal][ideal], groundBases[i][a]);
}

bool productDistributiveLattice::compare(int i, string s1, int j, string s2){
	auto hoge = calculateBase(j, s2);
	assert(hoge.first);
	return hoge.second[i].find(s1)	!= hoge.second[i].end();
}