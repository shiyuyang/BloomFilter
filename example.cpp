#include "BloomFilter.h"
#include <iostream>

int main() {
	std::string a = "asdasdasdasdasdasdad";
	std::string b = "asdasdbsdasdasdasdad";
	BloomFilter fillter = BloomFilter(380, 8);
	fillter.Add(a);
	bool is_contain = false;
	is_contain = fillter.Test(b);
	std::cout << "is_contain = " << is_contain << std::endl;
	is_contain = fillter.Test(a);
	std::cout << "is_contain = " << is_contain << std::endl;
	return 0;
}