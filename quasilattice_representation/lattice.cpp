#include<iostream>
#include "lattice.h"
#include<vector>
#include<string>
#include<math.h>
#include<map>
#include<iterator>
#include<algorithm>


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
	if(!valid(s1) || !valid(s2))
		throw "Taking lattice::join of invalid representation of elements";
	set<string> res;
	std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.begin()));
	return res;
}
//std::set<std::string> meet(std::set<std::string>, std::set<std::string>);

std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> v;        // �������ʂ��i�[����x�N�^�[
    auto first = str.begin();              // �e�L�X�g�̍ŏ����w���C�e���[�^
    while( first != str.end() ) {         // �e�L�X�g���c���Ă���ԃ��[�v
        auto last = first;                      // ���������񖖔��ւ̃C�e���[�^
        while( last != str.end() && *last != sep )       // ���� or �Z�p���[�^�����܂Ői�߂�
            ++last;
        v.push_back(std::string(first, last));       // �����������o��
        if( last != str.end() )
            ++last;
        first = last;          // ���̏����̂��߂ɃC�e���[�^��ݒ�
    }
    return v;
}