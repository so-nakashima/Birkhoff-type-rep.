#include<iostream>
#include "lattice.h"
#include<vector>
#include<string>
#include<math.h>
#include<map>
#include<iterator>
#include<algorithm>
#include<assert.h>
#include<queue>


using std::string;
using std::istream;
using std::vector;
using std::set;

std::vector<std::string> split(const std::string &str, char sep);
int ipow(int base, int exp);
set<string> bit2stringset(int n, const distributiveLattice* lat);

istream& distributiveLattice::read(istream& in){
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

distributiveLattice::distributiveLattice(istream& in){
	read(in);
	for(int i = 0; i != ipow(2, labels.size()); i++){
		set<string> candidate = bit2stringset(i);
		if(valid(candidate))
			elements.insert(candidate);
	}
}

set<string> distributiveLattice::bit2stringset(int n){
	set<string> res;
	auto itr = labels.begin();
	for(int i = 0; i != labels.size(); i++, itr++){
		if(n % 2 == 1)
			res.insert(*itr);
		n /= 2;
	}
	return res;
}

bool distributiveLattice::valid(set<string> elem){
	auto itr = elem.begin();
	for(itr; itr != elem.end(); itr++){
		string base = *itr;
		if(labels.find(base) == labels.end() ||(order[base] != "__BOTTOM" && elem.find(order[base]) == elem.end()))
			return false;
	}
	return true;
}

std::set<std::string> distributiveLattice::join(std::set<std::string> s1, std::set<std::string> s2){
	/*
	if(!valid(s1) || !valid(s2))
		throw "Taking lattice::join of invalid representations of elements";
		*/
	assert( valid(s1) && valid(s2));
	set<string> res;
	std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.begin()));
	return res;
}

std::set<std::string> distributiveLattice::meet(std::set<std::string> s1, std::set<std::string> s2){
	/*
	if(!valid(s1) || !valid(s2))
		throw "Taking lattice::meet of invalid representations of elements";
		*/
	assert( valid(s1) && valid(s2));
	set<string> res;
	std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),std::inserter(res, res.begin()));
	return res;
}

bool distributiveLattice::compare(std::set<std::string> s1, std::set<std::string> s2){
	assert(valid(s1) && valid(s2));
	bool flag = true;
	for(auto itr = s1.begin(); itr != s1.end(); itr++){
		if(s2.find(*itr) == s2.end()){
			flag = false;
			break;
		}
	}
	return flag;
}

std::set<std::string> distributiveLattice::principal_ideal(std::set<std::string> s){
	 set<string> visited;
	 std::queue<string> processing;
	 set<string> res = s;
	 for(auto itr = s.begin(); itr != s.end(); itr++){
		 processing.push(*itr);
		 visited.insert(*itr);
	 }
	 while(!processing.empty()){
		 string now = processing.front();
		 processing.pop();
		 string next = order[now];
		 if(next != "__BOTTOM" && visited.find(next) == visited.end()){
			 processing.push(next);
			 res.insert(next);
		 }
	 }
	 return res;
}

//Followings are NOT my program

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

int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}