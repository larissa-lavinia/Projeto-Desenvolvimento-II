#include "estruturas.hpp"
#include <iostream>
#include <bitset>

using namespace std;

bool Bit::GetBit(uint16_t data, uint8_t position) {
	return (data >> position) & 1;
}

uint16_t Bit::GetBit(uint16_t data, uint8_t position, uint8_t size) {
	if (size > 16) return 0;
	return ((data >> position) & (uint16_t(~0) >> (16 - size)));
}

void Bit::SetBit(uint16_t& data, uint8_t position, bool value) {
	data = (value << position) | (data & (uint16_t(~1) << position));
}

void Bit::SetBit(uint16_t& data, uint8_t position, uint8_t size, uint16_t value) {
	if (size > 16) return;
	data = (value << position) | (data & ~((uint16_t(~0) >> (16 - size)) << position));
}

void Bit::BitUnitTest() {
	cout << endl << "-GET BIT UNIT TEST-" << endl;
	cout << "Result -> " << (GetBit(23, 4) ? "True" : "False") << " BITSET(" << (bitset<8>(GetBit(23, 4))) << ")" << " Expected -> True (1)" << endl;
	cout << "Result -> " << (GetBit(13, 1) ? "True" : "False") << " BITSET(" << (bitset<8>(GetBit(13, 1))) << ")" << " Expected -> False (0)" << endl;
	cout << "Result -> " << (bitset<8>(GetBit(82, 3, 4))) << " Expected -> 00001010" << endl;
	cout << "Result -> " << (bitset<8>(GetBit(82, 0, 3))) << " Expected -> 00000010" << endl;
	cout << "Result -> " << (bitset<16>(GetBit(65535, 0, 16))) << " Expected -> 1111111111111111" << endl;

	uint16_t testValue = 0b0110101;
	cout << "Original Value -> " << (bitset<8>(testValue)) << endl;
	SetBit(testValue, 3, 3, 0b011);
	cout << "Result -> " << (bitset<8>(testValue)) << " Expected -> 00011101" << endl;
	SetBit(testValue, 0, 0);
	cout << "Result -> " << (bitset<8>(testValue)) << " Expected -> 00011100" << endl;
}

uint8_t Data::GetSex(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 0);
}

uint8_t Data::GetSchoolType(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 1);
}

uint8_t Data::GetTrainee(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 2);
}

uint8_t Data::GetSchoolSituation(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 3, 2);
}

uint8_t Data::GetRace(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 5, 3);
}

uint8_t Data::GetNationality(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 8, 3);
}

uint8_t Data::GetAge(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 11, 5);
}

uint16_t Data::GetCity(const uint16_t& locationData) {
	return Bit::GetBit(locationData, 0, 13);
}

uint8_t Data::GetIncome(const uint16_t& economicData) {
	return Bit::GetBit(economicData, 13);
}

uint8_t Data::GetWifi(const uint16_t& economicData) {
	return Bit::GetBit(economicData, 14);
}

void Data::SetSex(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 0, value);
}

void Data::SetSchoolType(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 1, value);
}

void Data::SetTrainee(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 2, value);
}

void Data::SetSchoolSituation(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 3, 2, value);
}

void Data::SetRace(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 5, 3, value);
}

void Data::SetNationality(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 8, 3, value);
}

void Data::SetAge(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 11, 5, value);
}

void Data::SetCity(uint16_t& locationData, uint16_t value) {
	Bit::SetBit(locationData, 0, 13, value);
}

void Data::SetIncome(uint16_t& economicData, bool value) {
	Bit::SetBit(economicData, 13, value);
}

void Data::SetWifi(uint16_t& economicData, bool value) {
	Bit::SetBit(economicData, 14, value);
}