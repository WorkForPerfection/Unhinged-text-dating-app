#include<vector>
#include<string>
#include"RadixTree.h"		
using namespace std;

class PersonProfile;
struct AttValPair;

//the PP struct is used to temporarily hold info
class MemberDatabase{
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;				//put all member's email addresses (who has the input AttValPair in their profile) in the vector 
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	struct PP{
		string name,email;
		vector<AttValPair> atlist;
		void clearPP(){
			name = ""; email="";
			atlist.clear();
		}
	};
	RadixTree<vector<string>> mp;
	RadixTree<PersonProfile> mp2;
};