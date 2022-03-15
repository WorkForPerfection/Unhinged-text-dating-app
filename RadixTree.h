#ifndef RADIXTREE_H
#define RADIXTREE_H
#include<string>
using namespace std;

//if key already exist, then we should replace value with new value

//struct: contains curstr, parent node, an array of children nodes, boolean isend indicating whether current position is the end of a word

const int maxn = 128;

template <typename ValueType>
class RadixTree {
public:
	 RadixTree();
	 ~RadixTree();
	 void insert(std::string key, const ValueType& value);
	 ValueType* search(std::string key) const;
private:
	struct node{
		string str;
		node* children[maxn];
		node* par=nullptr;
		bool isEndWord=false;
		ValueType* obj=nullptr;										//we return the pointer to the ValuType variable 'obj' of a node only if (isEndWord==true && i==n) when we are searching for the key string
	};
	node* addnode(string mstr, node* mpar){
		node* newn = new node;
		newn->str=mstr;
		for(int i=0;i<maxn;++i) newn->children[i]=nullptr;
	    newn->par=mpar;
		return newn;
	}
	void delallnode(node* curnode){
		if(!curnode) return;
		for(int i=1;i<maxn;++i){
			if(curnode->children[i]) delallnode(curnode->children[i]);
		}		
		if(curnode->obj!=nullptr) delete curnode->obj;
		delete curnode;
	}
	node root;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
	root.str=""; for(int i=0;i<maxn;++i) root.children[i]=nullptr;
}			//root is a dummy node whose str or par will never be accessed

template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
	for(int i=0;i<maxn;++i){
		delallnode(root.children[i]);
	}
}

//potential problem: for any and anyy, we iterate through key and curstr and key first ends, so we 
//returns true onlyif curstr==length and key==n

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
	if(root.children[key[0]]==nullptr){
		node* newnode = addnode(key,&root); newnode->isEndWord=true;	newnode->obj = new ValueType(value);
		root.children[key[0]] = newnode;
		return;
	}
	node* curnode = root.children[key[0]];
	int i = 0;
	int n = key.length();
	while(i<n){
		string curstr = curnode->str;
		int j = 0;
		while(i<n && j<curstr.length()){				//note that we assume k (length of a string) as a constant, so everything done here costs O(1)
			if(key[i]!=curstr[j]){
				string pref = curstr.substr(0,j);
				string suff = curstr.substr(j,-1);
				curnode->str = pref;
				node* original = addnode(suff,curnode);
				node* newnode = addnode(key.substr(i,-1),curnode);
				//copy all the table information in curnode to its inheriter - 'original', then set the table for curnode to point to only two nodes - its direct inheritor and the newnode
				for(int i=0;i<maxn;++i){
					original->children[i]=curnode->children[i];
					curnode->children[i]=nullptr;
				}
				original->isEndWord = curnode->isEndWord; curnode->isEndWord = false;
				original->obj = curnode->obj; curnode->obj = nullptr;
				curnode->children[key[i]]=newnode; curnode->children[suff[0]]=original;
				break;
			}
			i++;j++;
		}
		if(i==n && j==curstr.length()){
			curnode->isEndWord=true; 
			curnode->obj = new ValueType(value); 
			return;				//the current node is the end of this word; so we make isEndWord true
		}
		else if (i==n){
			string pref = curstr.substr(0,j);
			string suff = curstr.substr(j,-1);
			node* newnode = addnode(suff,curnode);
			newnode->obj=curnode->obj; newnode->isEndWord=curnode->isEndWord;
			for(int i=0;i<maxn;++i) newnode->children[i]=curnode->children[i],curnode->children[i]=nullptr;
			curnode->children[suff[0]]=newnode;
			curnode->isEndWord=true;
			curnode->obj = new ValueType(value); 
			curnode->str = pref;
			return;
		}
		else{
			//if not exit, key[i] must be a valid character
			if(curnode->children[key[i]]==nullptr){
				node* newnode = addnode(key.substr(i,-1),curnode); 	
				curnode->children[key[i]] = newnode;
			}
			curnode=curnode->children[key[i]];
		}
	}
}

template<typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const{
	int i=0,n=key.length();
	if(root.children[key[0]]==nullptr) return nullptr;
	node* curnode = root.children[key[0]];
	while(i<n){
		string curstr = curnode->str;
		int j = 0;
		while(i<n && j<curstr.length()){
			if(curstr[j]!=key[i]) return nullptr;
			i++;j++;
		}
		if(i==n && j==curstr.length()){
			if(curnode->isEndWord) return curnode->obj;
			else return nullptr;
		}		
		//when we have i==n and j!=curstr.length(), this word must have not been recorded in the tree (or else we would have splitted this node)
		else if (i==n){
			return nullptr;
		}
		else{
			if(curnode->children[key[i]]==nullptr) return nullptr;
			else curnode=curnode->children[key[i]];
		}
	}
}

#endif