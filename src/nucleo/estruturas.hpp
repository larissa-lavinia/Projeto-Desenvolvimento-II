#pragma once

#include <cstdint>

struct Dados {
	uint32_t participante;
	uint32_t local_socioeconomico;
};

struct Gabarito {
	uint16_t p1;
	uint16_t p2;
};

struct Inscrito {
	Dados dados;
	Gabarito gabarito;
};

bool GetBit(uint32_t data, uint8_t position);

uint16_t GetBit(uint32_t data, uint8_t position, uint8_t size);

void BitUnitTest();