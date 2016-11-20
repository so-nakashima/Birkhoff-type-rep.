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
using std::cout;

void readMatrix(istream& in, vector<vector<int>>& res);
vector<vector<int>> int2vector(int i);
bool isSubspacesStable(int i, int j, const vector<vector<int>>& mat, int itrx, int itry);
bool isOrthogonal(vector<int> vec1, vector<int> vec2, const vector<vector<int>>& mat, int itrx, int itry);

const int module = 2;

void check(){
	vector<vector<int>> mat;
	std::ifstream inMatrix("matrix\\matrix1.txt");
	readMatrix(inMatrix, mat);

	cout << isSubspacesStable(1,1, mat, 0, 0) << endl; 

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

vector<vector<int>> int2vector(int i){ // return bases of subspaces indicated by int i
	vector<vector<int>> res;
	vector<int> temp;
	switch (i)
	{
	case 0:
		temp.push_back(0); temp.push_back(0); res.push_back(temp);
		break;
	case 1:
		temp.push_back(0); temp.push_back(1); res.push_back(temp);
		break;
	case 2:
		temp.push_back(1); temp.push_back(1); res.push_back(temp);
		break;
	case 3:
		temp.push_back(0); temp.push_back(1); res.push_back(temp); temp.clear();
		temp.push_back(1); temp.push_back(0); res.push_back(temp);
		break;
	default:
		std::cout << "Error in converting integer to subspace" << endl;
		break;
	}
	return res;
}

bool isOrthogonal(vector<int> vec1, vector<int> vec2, const vector<vector<int>>& mat, int itrx, int itry){
	int sum = 0;
	rep(i, vec1.size()){
		rep(j, vec2.size()){
			sum += vec1[i] * vec2[j] * mat[i + itrx][j + itry];
			sum %= module;
		}
	}
	return sum == 0;
}

bool isSubspacesStable(int i, int j, const vector<vector<int>>& mat, int itrx, int itry){ // check whether subspace i and j are stable, bilinear function are given by mat and (itrx, itry) (coordinate of most upperleft)
	vector<vector<int>> subspace1 = int2vector(i);
	vector<vector<int>> subspace2 = int2vector(j);
	bool res = true;
	rep(k, subspace1.size()){
		rep(l, subspace2.size()){
			if(!isOrthogonal(subspace1[k], subspace2[l], mat, itrx, itry))
				res = false;
		}
	}
	return res;
}