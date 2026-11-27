#include "estruturas.hpp"
#include <iostream>
#include <bit>
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
	data = (value << position) | (data & ~(uint16_t(1) << position));
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
	SetBit(testValue, 3, 0);
	cout << "Result -> " << (bitset<8>(testValue)) << " Expected -> 00010100" << endl;
}

uint8_t PersonalData::GetSex(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 0);
}

uint8_t PersonalData::GetSchoolType(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 1);
}

uint8_t PersonalData::GetTrainee(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 2);
}

uint8_t PersonalData::GetSchoolSituation(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 3, 2);
}

uint8_t PersonalData::GetRace(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 5, 3);
}

uint8_t PersonalData::GetNationality(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 8, 3);
}

uint8_t PersonalData::GetAge(const uint16_t& personalData) {
	return Bit::GetBit(personalData, 11, 5);
}

uint8_t PersonalData::GetFatherOcup(const uint16_t& soceconomicData) {
	return Bit::GetBit(soceconomicData, 0, 3);
}

uint8_t PersonalData::GetMotherOcup(const uint16_t& soceconomicData) {
	return Bit::GetBit(soceconomicData, 3, 3);
}

uint8_t PersonalData::GetWealth(const uint16_t& soceconomicData) {
	return Bit::GetBit(soceconomicData, 6, 5);
}

uint8_t PersonalData::GetHouseQnt(const uint16_t& soceconomicData) {
	return Bit::GetBit(soceconomicData, 11, 5);
}

void PersonalData::SetSex(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 0, value);
}

void PersonalData::SetSchoolType(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 1, value);
}

void PersonalData::SetTrainee(uint16_t& personalData, bool value) {
	Bit::SetBit(personalData, 2, value);
}

void PersonalData::SetSchoolSituation(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 3, 2, value);
}

void PersonalData::SetRace(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 5, 3, value);
}

void PersonalData::SetNationality(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 8, 3, value);
}

void PersonalData::SetAge(uint16_t& personalData, uint8_t value) {
	Bit::SetBit(personalData, 11, 5, value);
}

void PersonalData::SetFatherOcup(uint16_t& soceconomicData, uint8_t value) {
	Bit::SetBit(soceconomicData, 0, 3, value);
}

void PersonalData::SetMotherOcup(uint16_t& soceconomicData, uint8_t value) {
	Bit::SetBit(soceconomicData, 3, 3, value);
}

void PersonalData::SetWealth(uint16_t& soceconomicData, uint8_t value) {
	Bit::SetBit(soceconomicData, 6, 5, value);
}

void PersonalData::SetHouseQnt(uint16_t& soceconomicData, uint8_t value) {
	Bit::SetBit(soceconomicData, 11, 5, value);
}

uint8_t ScoreData::GetExam(const Score& scoreData, Area area) {
	return std::popcount(scoreData.exam[area].p1) + std::popcount(scoreData.exam[area].p2) + std::popcount(scoreData.exam[area].p3);
}

uint16_t ScoreData::GetEssay(const Score& scoreData) {
	return scoreData.essay;
}

void ScoreData::SetExam(Score& scoreData, Area area, uint16_t p1, uint16_t p2, uint16_t p3) {
	scoreData.exam[area].p1 = p1;
	scoreData.exam[area].p2 = p2;
	scoreData.exam[area].p3 = p3;
}

void ScoreData::GetEssay(Score& scoreData, uint16_t value) {
	scoreData.essay = value;
}