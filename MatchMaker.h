#include <vector>
#include <string>
#include "RadixTree.h"
#include "provided.h"
using namespace std;

class AttributeTranslator;
class MemberDatabase;
struct AttValPair;
struct EmailCount;

class MatchMaker{
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email,int threshold) const;
private:
	const MemberDatabase* mb=nullptr;
	const AttributeTranslator* mat=nullptr;
};