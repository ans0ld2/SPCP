/*
 * DeviceBKI.h
 *
 *  Created on: Feb 10, 2021
 *      Author: ans0l
 */

#pragma once


#include "BaseDevice.h"

class DeviceBKI : public BaseDevice {

	static uint16_t mAdress;

public:

	DeviceBKI(void) : BaseDevice(this->mAdress++, FunctionWrite::F6) {
		RegistersExchange temp;
		temp.FirstReg = 0;
		temp.NReg = 80;
		temp.pBuff = (uint16_t*)&this->Mem;
		this->Exchange.push_back(temp);
		temp.FirstReg = 148;
		temp.NReg = 6;
		temp.pBuff = (uint16_t*)&this->Mem.Nfider;
		this->Exchange.push_back(temp);
		this->Name = "Блок контроля изоляции-" + std::to_string(this->Adress - 47);
	}
	struct Memory_t {
		uint16_t U1Osn;
		uint16_t U1Dop;
		uint16_t _2;
		uint16_t _3;
		uint16_t R1Plus;
		uint16_t R1Minus;
		uint16_t U1Plus;
		uint16_t U1Minus;
		uint16_t _8;
		uint16_t _9;
		uint16_t _10;
		uint16_t _11;
		uint16_t _12;
		uint16_t _13;
		uint16_t _14;
		uint16_t _15;
		struct BKIf_Fider_s {
			uint16_t Plus;
			uint16_t Minus;
		} Fider[64];
		uint16_t Nfider;
		uint16_t KalibrK;
		uint16_t _150;
		uint16_t _151;
		uint16_t LevelR;
		uint16_t En_Sekcion;
	} Mem;
};
