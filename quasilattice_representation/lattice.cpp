#include<iostream>
#include "lattice.h"
#include<vector>
#include<string>
#include<math.h>
#include<map>
#include<iterator>
#include<algorithm>
#include<assert.h>


using std::string;
using std::istream;
using std::vector;
using std::set;

std::vector<std::string> split(const std::string &str, char sep);

istream& lattice::read(istream& in){
	string str;
	int n;
	in >> n;
	getline(in, str);
	for(int i = 0; i != n; i++){
		if(!std::getline(in, str)){
			assert(0 && "reading error");
		}
		vector<string> v = split(str, ' ');
		_ASSERT(0 < v.size() && v.size() <= 2);
		/*if(labels.find(v[0]) != labels.end()){
			 std::cout << "Some element is defined twice" << std::endl;
		}*/
		assert(labels.find(v[0]) == labels.end());
		labels.insert(v[0]);
		if(v.size() == 1)
			order[v[0]] = "__BOTTOM";
		else
			order[v[0]] = v[1];
		
	}
	return in;
};

lattice::lattice(istream& in){
	read(in);
}

bool lattice::valid(set<string> elem){
	auto itr = elem.begin();
	for(itr; itr != elem.end(); itr++){
		string base = *itr;
		if(labels.find(base) == labels.end() ||(order[base] != "__BOTTOM" && elem.find(order[base]) == elem.end()))
			return false;
	}
	return true;
}

std::set<std::string> lattice::join(std::set<std::string> s1, std::set<std::string> s2){
	/*
	if(!valid(s1) || !valid(s2))
		throw "Taking lattice::join of invalid representations of elements";
		*/
	assert( valid(s1) && valid(s2));
	set<string> res;
	std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.begin()));
	return res;
}

std::set<std::string> lattice::meet(std::set<std::string> s1, std::set<std::string> s2){
	/*
	if(!valid(s1) || !valid(s2))
		throw "Taking lattice::meet of invalid representations of elements";
		*/
	assert( valid(s1) && valid(s2));
	set<string> res;
	std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.begin()));
	return res;
}

std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> v;        // 分割結果を格納するベクター
    auto first = str.begin();              // テキストの最初を指すイテレータ
    while( first != str.end() ) {         // テキストが残っている間ループ
        auto last = first;                      // 分割文字列末尾へのイテレータ
        while( last != str.end() && *last != sep )       // 末尾 or セパレータ文字まで進める
            ++last;
        v.push_back(std::string(first, last));       // 分割文字を出力
        if( last != str.end() )
            ++last;
        first = last;          // 次の処理のためにイテレータを設定
    }
    return v;
}