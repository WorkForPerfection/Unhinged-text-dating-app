#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <vector>
using namespace std;


/*
struct AttValPair {
    AttValPair(std::string att, std::string val)
     : attribute(att), value(val){}

    AttValPair(){}

    std::string attribute;
    std::string value;

    bool operator==(const AttValPair& rhs) const {
        return (attribute == rhs.attribute  &&  value == rhs.value);
    }

    bool operator!=(const AttValPair& rhs) const {
        return !(*this == rhs);
    }
};
*/


PersonProfile::PersonProfile(string name, string email){
	mname = name;
	memail = email;
}

PersonProfile::~PersonProfile(){

}

string PersonProfile::GetName() const{
	return mname;
}

string PersonProfile::GetEmail() const{
	return memail;
}

void PersonProfile::AddAttValPair(const AttValPair& attval){
	mlist.push_back(attval);
	mp.insert(attval.attribute,attval.value);
}

int PersonProfile::GetNumAttValPairs() const{
	return mlist.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
	int n = attribute_num;
	if(n<0 || n>=mlist.size()) return false;
	attval = mlist[n];
	return true;
}


