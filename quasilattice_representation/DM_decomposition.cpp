#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#include<map>
#include<iterator>
#include<fstream>
#include<set>

#define rep(i,n) for(int i = 0; i != n; i++)

using std::string;
using std::istream;
using std::vector;
using std::set;
using std::pair;
using std::map;
using std::endl;
using std::cin;

void readMatrix(istream& in, vector<vector<int>>& res);

void check(){
	vector<vector<int>> mat;
	std::ifstream inMatrix("matrix\\matrix1.txt");
	readMatrix(inMatrix, mat);

	int x = 0;
	x++;
}

void readMatrix(istream& in, vector<vector<int>>& res){
	int n, m; //number of the rows and collums respectively
	in >> n >> m;
	res.clear();

	rep(i,n){
		vector<int> vectemp;
		rep(j,m){
			int temp; in >> temp;
			vectemp.push_back(temp);
		}
		res.push_back(vectemp);
	}
}