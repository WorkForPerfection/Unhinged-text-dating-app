#include <string>
#include <vector>
#include "RadixTree.h"					//shouldn't include it?
using namespace std;

struct AttValPair;

class AttributeTranslator{
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	RadixTree<vector<AttValPair>> mp;
};



