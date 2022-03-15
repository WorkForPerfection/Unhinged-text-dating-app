#include <vector>
#include <string>
#include "RadixTree.h"		//not include this?
#include "provided.h"
#include "PersonProfile.h"
#include "MemberDatabase.h"
#include <fstream>
using namespace std;

MemberDatabase::MemberDatabase(){

}

MemberDatabase::~MemberDatabase(){

}

//We don't care about the time complexity of loading information
bool MemberDatabase::LoadDatabase(std::string filename){
	string line;
	ifstream file;
	file.open(filename);
	if(!file) return false;
	int cnt = 1;
	PP tmp;					
	vector<string> empty;
	//we use a cnt variable to keep track of where we are in the input
	while(getline(file,line)){
		if(line=="") {
			cnt=0;
			PersonProfile myprof(tmp.name,tmp.email);
			mp2.insert(myprof.GetEmail(),myprof);
			PersonProfile* ptr = mp2.search(myprof.GetEmail());
			for(int i=0;i<tmp.atlist.size();++i){
				ptr->AddAttValPair(tmp.atlist[i]);
			}
			tmp.clearPP();
		}
		else{
			if(cnt==1){
				tmp.name = line;
			}
			else if (cnt==2) tmp.email = line;
			else if (cnt>3){
				string curstr = line;
				int i=0; while(i<curstr.length() && curstr[i]!=',') i++;
				string att = curstr.substr(0,i), val = curstr.substr(i+1,-1);
				AttValPair pair1; pair1.attribute = att; pair1.value = val;
				tmp.atlist.push_back(pair1);
				vector<string>* ptr = mp.search(curstr);				
				if(!ptr){mp.insert(curstr,empty);}
				ptr = mp.search(curstr);
				ptr->push_back(tmp.email);
			}
		}
		cnt++;
	}
	file.close();
	return true;
}

//Assuming key length is a constant this costs O(1), as we have proven in the implementation of RadixTree
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
	vector<string> empty;
	string key = input.attribute+","+input.value;
	vector<string>* ptr = mp.search(key);
	if(!ptr) return empty;
	return *ptr;
} 

//this costs O(1)
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
	PersonProfile* tmp = mp2.search(email);
	if(!tmp) return nullptr;
	return tmp;
}