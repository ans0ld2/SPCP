/*
 * ScreenConrlInsulation.cpp
 *
 *  Created on: 17 мар. 2021 г.
 *      Author: ans0l
 */


#include "ScreenContrlInsulation.h"
#include "ScreenBKI.h"


extern ScreenBKI sBKI;

void ScreenContrlInsulation::Loop(void) {
		if (BKI.ErrorConnection){
			Screens.JumpScreen(&sBKI);
		}
		uint8_t number;
			for(uint8_t i = 0; i < 3; i++) {

				number = this->counter + i - 3;
				this->lfider[i].SetText("Сопротивление\n" + std::to_string(number + 1) + "-го фидера");

				this->Value[i] = BKI.Mem.Fider[number].Plus;
				this->Value[i + 3] = BKI.Mem.Fider[number].Minus;
			}
	}
