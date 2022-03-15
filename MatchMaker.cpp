#include <vector>
#include <string>
#include "RadixTree.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "MatchMaker.h"
#include "provided.h"
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;


// struct EmailCount {
//     EmailCount(std::string em, int ct)
//      : email(em), count(ct)
//     {}

//     std::string email;
//     int count;
// };


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){
	mb=&mdb;
	mat=&at;
}

MatchMaker::~MatchMaker(){
	mb=nullptr;
	mat=nullptr;
}

//only members with number of compatible matches >= threshold can have an EmailCount variable created for him & added to the vector 
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email,int threshold) const{
	set<string> compatibles;
	set<string> candidates;
	vector<EmailCount> res,empty;				//return emtpy whenever input is invalid
	const PersonProfile* ptr = mb->GetMemberByEmail(email);
	if(!ptr) return empty;
	AttValPair att;
	for(int i=0;i<ptr->GetNumAttValPairs();++i){
		bool ok = ptr->GetAttVal(i,att);	if(!ok) return empty;
		vector<AttValPair> match = mat->FindCompatibleAttValPairs(att);	
		//this for loop runs in constant time since we assume there is a constant upperbound that an AVP is compatible to
		for(AttValPair it:match){
			compatibles.insert(it.attribute+","+it.value);
		}
	}
	//now match is the total number of compatible pairs acceptable for this person
	for(auto it:compatibles){
		int i = 0; while(it[i]!=',') i++;
		AttValPair curpair; curpair.attribute=it.substr(0,i);curpair.value=it.substr(i+1,-1);
		vector<string> cur = mb->FindMatchingMembers(curpair);
		for (int i = 0; i < cur.size(); ++i) {
			string curstr = cur[i];
			candidates.insert(curstr);
		}
	}
// for(auto it:candidates) cout<<it<<endl;
// return empty;
	//now candidates contain all potential people who have at least one compatible trait with the target person
	for(string mail:candidates){
		int cnt=0;
		const PersonProfile* currentperson = mb->GetMemberByEmail(mail);			//this person is guaranteed to exist
		if(!currentperson || currentperson==ptr) continue;
		for(int i=0;i<currentperson->GetNumAttValPairs();i++){
			currentperson->GetAttVal(i,att);
			string key = att.attribute+","+att.value;
			if(compatibles.find(key)!=compatibles.end()) cnt++;
		}
//if(mail=="ScoElliso714@sky.com") cout<<mail<<" "<<cnt<<endl; 
		if(cnt>=threshold){
			EmailCount ec(currentperson->GetEmail(),cnt);
			res.push_back(ec);
		}
	}
//return empty;
	sort(res.begin(),res.end(),[](const EmailCount& e1, const EmailCount& e2){return e1.count==e2.count?e1.email<e2.email:e1.count>e2.count;});	
	return res;
}