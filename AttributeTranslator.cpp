#include <string>
#include <vector>
#include "RadixTree.h"
#include <fstream>
#include "provided.h"
#include"AttributeTranslator.h"
using namespace std;


AttributeTranslator::AttributeTranslator(){

}

AttributeTranslator::~AttributeTranslator(){

}

//we need to first check for the source attribute-value pair as a string (prefix before the second ','(inclusive)) in the map: if return type!=nullptr then push back the target as an attvalpair of that pointer's vector; else, first insert an empty vector with this source atvalpair, then push back the target to the new vector in the map
bool AttributeTranslator::Load(std::string filename){
	string line;
	ifstream file;
	file.open(filename);
	if(!file) return false;
	vector<AttValPair> tmpmp;
	while(getline(file,line)){
		if (line == "") continue;				//white lines? 
		string curstr = line;
		int cnt = 0,i=0;
		while(cnt<2){
			if(curstr[i]==',') cnt++;
			i++;
		}
		string pref = curstr.substr(0,i), suff = curstr.substr(i,-1);
		int j=0;
		while(suff[j]!=',') j++;
		string att = suff.substr(0,j), val=suff.substr(j+1,-1);
		vector<AttValPair>* ptr = mp.search(pref);
		if(!ptr){
			mp.insert(pref,tmpmp);
		}
		AttValPair tmp; tmp.attribute = att,tmp.value=val;
		ptr=mp.search(pref);
		if(find(ptr->begin(),ptr->end(),tmp)==ptr->end()) ptr->push_back(tmp);
	}
	file.close();
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
	string key = source.attribute+','+source.value+',';
	vector<AttValPair>* res = mp.search(key);
	vector<AttValPair> empty;
	if(!res) return empty;
	return *res;
}
