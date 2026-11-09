#include "estruturas.hpp"
#include <iostream>
#include <bitset>

using namespace std;

bool GetBit(uint32_t data, uint8_t position) {
	return (data >> position) & 1;
}

uint16_t GetBit(uint32_t data, uint8_t position, uint8_t size) {
	if (size > 16) return 0;
	return ((data >> position) & (uint16_t(~0) >> (16 - size)));
}

void BitUnitTest() {
	cout << endl << "-GET BIT UNIT TEST-" << endl;
	cout << "Result -> " << (GetBit(23, 4) ? "True" : "False") << " BITSET(" << (bitset<8>(GetBit(23, 4))) << ")" << " Expected -> True (1)" << endl;
	cout << "Result -> " << (GetBit(13, 1) ? "True" : "False") << " BITSET(" << (bitset<8>(GetBit(13, 1))) << ")" << " Expected -> False (0)" << endl;
	cout << "Result -> " << (bitset<8>(GetBit(82, 3, 4))) << " Expected -> 00001010" << endl;
	cout << "Result -> " << (bitset<8>(GetBit(82, 0, 3))) << " Expected -> 00000010" << endl;
	cout << "Result -> " << (bitset<16>(GetBit(65535, 0, 16))) << " Expected -> 1111111111111111" << endl;
}