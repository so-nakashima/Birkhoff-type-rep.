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