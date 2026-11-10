#pragma once

#include <cstdint>

enum participant

struct Personal {
	uint16_t participante;
	uint16_t local_socioeconomico;
};

struct Score {
	uint16_t p1;
	uint16_t p2;
};

struct Participant {
	Personal personal;
	Score score;
};

bool Bit::GetBit(uint32_t data, uint8_t position);

uint32_t Bit::GetBit(uint32_t data, uint8_t position, uint8_t size);

void Bit::BitUnitTest();