#ifndef PERSON_PROFILE_H
#define PERSON_PROFILE_H
#include<vector>
#include<string>
#include "RadixTree.h"						//shouldn't include this?
using namespace std;	

// template<typename ValueType>
// class RadixTree<ValueType>;				//T will be the value type of RadixTree, since keytype is fixed to be string
struct AttValPair;

class PersonProfile{
public:
	PersonProfile(string name, string email);
	~PersonProfile();
	string GetName() const;
	string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	string mname,memail;
	vector<AttValPair> mlist;		//insertion and lookup takes O(1)
	RadixTree<string> mp;			//this helps to map a AttVal pair (written as a string such as "hobby,climbing,") to a vector of AttVal Pairs that are compatible, each also as a string: we can use the Attribute translator class to do this (get a vector of compatibles) in less than O(n) when a new AttPair is inserted into the profile, and store this source-vector<target> pair into the map
};	



#endif