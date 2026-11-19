#pragma once

#include <cstdint>

struct Personal {
	uint16_t participante;
	uint16_t local_socioeconomico;
};

struct AreaScore {
	uint16_t p1;	// 01° - 16°
	uint16_t p2;	// 17° - 32°
	uint16_t p3;	// 33° - 45° + 3 bits
};

struct Score {
	AreaScore Mat;
	AreaScore Cienc_Ex;
	AreaScore Cienc_Hu;
	AreaScore Lin;
};

struct Participant {
	Personal personal;
	Score score;
};


namespace Bit {
	bool GetBit(uint16_t data, uint8_t position);

	uint16_t GetBit(uint16_t data, uint8_t position, uint8_t size);

	void SetBit(uint16_t& data, uint8_t position, bool value);

	void SetBit(uint16_t& data, uint8_t position, uint8_t size, uint16_t value);

	void BitUnitTest();
}

namespace Data {
	uint8_t GetSex(const uint16_t& personalData);

	uint8_t GetSex(const uint16_t& personalData);

	uint8_t GetSchoolType(const uint16_t& personalData);

	uint8_t GetTrainee(const uint16_t& personalData);

	uint8_t GetSchoolSituation(const uint16_t& personalData);

	uint8_t GetRace(const uint16_t& personalData);

	uint8_t GetNationality(const uint16_t& personalData);

	uint8_t GetAge(const uint16_t& personalData);

	uint16_t GetCity(const uint16_t& locationData);

	uint8_t GetIncome(const uint16_t& economicData);

	uint8_t GetWifi(const uint16_t& economicData);

	void SetSex(uint16_t& personalData, bool value);

	void SetSex(uint16_t& personalData, bool value);

	void SetSchoolType(uint16_t& personalData, bool value);

	void SetTrainee(uint16_t& personalData, bool value);

	void SetSchoolSituation(uint16_t& personalData, uint8_t value);

	void SetRace(uint16_t& personalData, uint8_t value);

	void SetNationality(uint16_t& personalData, uint8_t value);

	void SetAge(uint16_t& personalData, uint8_t value);

	void SetCity(uint16_t& locationData, uint16_t value);

	void SetIncome(uint16_t& economicData, bool value);

	void SetWifi(uint16_t& economicData, bool value);
}