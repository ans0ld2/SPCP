/*
 * ScreenSetBKI.h
 *
 *  Created on: Feb 10, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"
#include "DeviceBKI.h"

using namespace VA;

extern DeviceBKI BKI;

class ScreenSetBKI : public BaseScreen {

	void _write(uint16_t Reg, uint16_t Val) {
		WriteBuf_t temp;
		temp.AdrReg = Reg;
		temp.Value = Val;
		temp.Adress = BKI.Adress;
		write(temp);
	}

	Label label[4] = {
		Label(this, 75, 110, 350, 65, "Количество фидеров, шт.", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 75, 170, 350, 65, "Колибровочній коэф-т", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 75, 230, 350, 65, "Rиз (предупред), кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 75, 290, 350, 65, "Rиз (авария), кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

	Display disp[4] 			= {
		 Display(this, 450, 120, 100, 40, &BKI.Mem.Nfider, 2, 0, 3, 32, &Screens.kbr),
		 Display(this, 450, 180, 100, 40, &BKI.Mem.KalibrK, 4, 0, 0, 9999, &Screens.kbr),
		 Display(this, 450, 240, 100, 40, &Memory[eMemory::warnInsulation].U, 4, 0, 0, 9999, &Screens.kbr),
		 Display(this, 450, 300, 100, 40, &BKI.Mem.LevelR, 4, 0, 0, 9999, &Screens.kbr),
	};



public:

	ScreenSetBKI(void) : BaseScreen(&Screens, "Параметры БКИ: ") {
		this->disp[0].addCallBack([&]() {
			this->_write(148, *this->disp[0].GetPValue());
		});
		this->disp[1].addCallBack([&]() {
			this->_write(149, *this->disp[1].GetPValue());
		});
		this->disp[2].addCallBack([&]() {
			eeprom.Write(&Memory[eMemory::warnInsulation].U);
		});
		this->disp[3].addCallBack([&]() {
			this->_write(152, *this->disp[3].GetPValue());
		});
	}

	void Loop(void) override {
//		if(Memory[eMemory::warnInsulation].U <= BKI.Mem.LevelR) {
//			Memory[eMemory::warnInsulation].U = BKI.Mem.LevelR + 10;
//		}
	}

	void JumpTo(void) override {

	}
};
