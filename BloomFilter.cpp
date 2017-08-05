#include "BloomFilter.h"
#include "MurmurHash3.h"

#define BIT_WIDTH 64 
#define ONE_BYTE 8

uint32_t g_seeds[20] = { 2730761291,
						 3928314409,
						 3169283629,
						 2586501119,
						 2429603003,
						 3172565311,
						 4206904489,
						 2590964639,
						 2323077551,
						 2343428819,
						 3054040553,
						 3048650467,
						 3412998509,
						 3949055303,
						 4122530221,
						 2239582273,
						 2448191089,
						 3730886891,
						 3942007409,
						 2720250623, };

BloomFilter::BloomFilter(uint32_t bits_num, uint32_t hash_times) :_hash_times(hash_times) {
	std::bitset<64> bit_set(0llu);
	_bit_sets.resize(bits_num % BIT_WIDTH == 0 ? bits_num / BIT_WIDTH : bits_num / BIT_WIDTH + 1, bit_set);
}

BloomFilter::BloomFilter(std::vector<uint64_t> bits, uint32_t hash_times) :_hash_times(hash_times) {
	for (auto it = bits.begin(); it != bits.end(); it++) {
		std::bitset<64> bit_set(*it);
		_bit_sets.push_back(bit_set);
	}
}

std::vector<uint64_t> BloomFilter::SerializeFilter()
{
	std::vector<uint64_t> serialized_vec;
	for(auto it = _bit_sets.begin();it != _bit_sets.end(); it++){
		serialized_vec.push_back(it->to_ullong());
	}
	return serialized_vec;
}

void BloomFilter::Add(std::string& key) {
	uint32_t pos = 0;
	for (int i = 0; i < _hash_times; i++) {
		MurmurHash3_x86_32(key.data(), key.size(), g_seeds[i], &pos);
		pos %= _bit_sets.size() * ONE_BYTE;
		_bit_sets[pos / BIT_WIDTH].set(pos % BIT_WIDTH);
	}
}

bool BloomFilter::Test(std::string& key) {
	uint32_t pos = 0;
	for (int i = 0; i < _hash_times; i++) {
		MurmurHash3_x86_32(key.data(), key.size(), g_seeds[i], &pos);
		pos %= _bit_sets.size() * ONE_BYTE;

		if (!_bit_sets[pos / BIT_WIDTH].test(pos % BIT_WIDTH)) {
			return false;
		}
	}
	return true;
}
