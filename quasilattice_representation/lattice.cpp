#include<iostream>
#include "lattice.h"
#include<vector>
#include<string>
#include<math.h>
#include<map>
#include<iterator>


using std::string;
using std::istream;
using std::vector;

std::vector<std::string> split(const std::string &str, char sep);

istream& lattice::read(istream& in){
	string str;
	int n;
	in >> n;
	getline(in, str);
	for(int i = 0; i != n; i++){
		if(!std::getline(in, str))
			throw "Reading error in lattice::read";
		vector<string> v = split(str, ' ');
		_ASSERT(0 < v.size() && v.size() <= 2);
		if(labels.find(v[0]) != labels.end())
			throw "Some element is defined twice";
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