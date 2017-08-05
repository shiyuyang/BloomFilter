#include "BloomFilter.h"


int main() {
	std::string a = "asdasdasdasdasdasdad";
	std::string b = "asdasdbsdasdasdasdad";
	BloomFilter fillter = BloomFilter(380, 8);
	fillter.Add(a);
	bool is_contain = fillter.Test(b);
	is_contain = fillter.Test(a);
	return 0;
}