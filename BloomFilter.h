#ifndef _BLOOM_FILTER_H
#define _BLOOM_FILTER_H
#include <bitset>
#include <vector>
#include <cstdint>

class BloomFilter
{
public:
	BloomFilter(uint32_t bits_num, uint32_t hash_times);

	BloomFilter(std::vector<uint64_t> bits, uint32_t hash_times);

	std::vector<uint64_t> SerializeFilter();

	void Add(std::string& key);

	bool Test(std::string& key);
private:
	uint32_t _hash_times;
	std::vector<std::bitset<64>> _bit_sets;
};

#endif
