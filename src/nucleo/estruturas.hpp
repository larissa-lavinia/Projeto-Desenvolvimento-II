#pragma once

#include <cstdint>

enum Area {
	Mat, C_Ex, C_Hu, Lin
};

struct Personal {
	uint16_t participante;
	uint16_t socioeconomico;
};

struct AreaScore {
	uint16_t p1;	// 01° - 16°
	uint16_t p2;	// 17° - 32°
	uint16_t p3;	// 33° - 45° + 3 bits
};

struct Score {
	AreaScore exam[4];
	uint16_t essay;
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

namespace PersonalData {
	uint8_t GetSex(const uint16_t& personalData);

	uint8_t GetSchoolType(const uint16_t& personalData);

	uint8_t GetTrainee(const uint16_t& personalData);

	uint8_t GetSchoolSituation(const uint16_t& personalData);

	uint8_t GetRace(const uint16_t& personalData);

	uint8_t GetNationality(const uint16_t& personalData);

	uint8_t GetAge(const uint16_t& personalData);

	uint8_t GetFatherOcup(const uint16_t& soceconomicData);

	uint8_t GetMotherOcup(const uint16_t& soceconomicData);

	uint8_t GetWealth(const uint16_t& soceconomicData);

	uint8_t GetHouseQnt(const uint16_t& soceconomicData);


	void SetSex(uint16_t& personalData, bool value);

	void SetSchoolType(uint16_t& personalData, bool value);

	void SetTrainee(uint16_t& personalData, bool value);

	void SetSchoolSituation(uint16_t& personalData, uint8_t value);

	void SetRace(uint16_t& personalData, uint8_t value);

	void SetNationality(uint16_t& personalData, uint8_t value);

	void SetAge(uint16_t& personalData, uint8_t value);

	void SetFatherOcup(uint16_t& soceconomicData, uint8_t value);

	void SetMotherOcup(uint16_t& soceconomicData, uint8_t value);

	void SetWealth(uint16_t& soceconomicData, uint8_t value);

	void SetHouseQnt(uint16_t& soceconomicData, uint8_t value);
}

namespace ScoreData {
	uint8_t GetExam(const Score& scoreData, Area area);

	uint16_t GetEssay(const Score& scoreData);

	void SetExam(Score& scoreData, Area area, uint16_t p1, uint16_t p2, uint16_t p3);

	void GetEssay(Score& scoreData, uint16_t value);
}