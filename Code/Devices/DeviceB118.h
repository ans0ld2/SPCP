/*
 * DeviceB118.h
 *
 *  Created on: Dec 6, 2020
 *      Author: anan2
 */

#pragma once

#include "BaseDevice.h"

 enum class ModeDevice {
		V220,
		V110,
		V60,
		V36
	};

class DeviceB118 : public BaseDevice {

	static uint16_t mAdress;

public:
	ModeDevice Mode;
	uint16_t* pRegime = nullptr;
	struct MemEEP_B118 {
		uint16_t Umax;
		uint16_t Uset;
		uint16_t Umin;
		uint16_t Imax;
		uint16_t Iset;
		uint16_t Imin;
	}* pSettings[2];
	uint16_t* pPusk;

	DeviceB118(ModeDevice Mode = ModeDevice::V220) : BaseDevice(this->mAdress++, FunctionWrite::F6) {
		this->Mode = Mode;
		if (this->Mode == ModeDevice::V220) {
			this->pRegime = &Memory[eMemory::RegimeB118].U;
		}
		else if (this->Mode == ModeDevice::V60) {
			this->pRegime = &Memory[eMemory::RegimeB118M].U;
		}

		this->pSettings[0] = (MemEEP_B118*)(this->pRegime + 1);
		this->pSettings[1] = (MemEEP_B118*)(this->pRegime + 7);
		if (this->Mode == ModeDevice::V220) {
			this->pPusk = &Memory[rMemory::PuskB118].U;
		}
		else if (this->Mode == ModeDevice::V60) {
			this->pPusk = &Memory[rMemory::PuskB118M].U;
		}

		RegistersExchange temp;
		temp.FirstReg = 0;
		temp.NReg = 8;
		temp.pBuff = (uint16_t*)&this->Mem;
		this->Exchange.push_back(temp);

		this->Name = "Блок Б130-" + std::to_string(this->Adress - 0);

	}

	struct Memory_t {
		uint16_t Uout;
		uint16_t Iout;
		uint16_t Imax;
		uint16_t Umax;
		uint16_t Umin;
		struct B118_State_s {
			uint16_t State		: 1;
			uint16_t Mode		: 1;
			uint16_t Protect	: 1;
			uint16_t Crash		: 1;
		} State;
		uint16_t Ufloat;
		uint16_t Boost;
	} Mem;
};


uint16_t DeviceB118::mAdress = 1;

