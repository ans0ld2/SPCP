/*
 * ScreenContrlInsulation.h
 *
 *  Created on: Feb 6, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"
#include "DeviceBKI.h"


using namespace VA;

extern DeviceBKI BKI;

class ScreenContrlInsulation : public BaseScreen {

	uint16_t Value[6] = {0}; 	// значения сопротивлений изоляции
				// номер фидера

/*-----------------------Вертикальные линии -------------------------------------------------------------------*/
	Graphics Vline1 	= Graphics(this, 210, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 415, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline3 	= Graphics(this, 620, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Горизонтальные линии ----------------------------------------------------------------*/
	Graphics Hline1 	= Graphics(this, 0,	185, 620, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 300, 620, 2, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Кнопки переключения------------------------------------------------------------------*/
	Button left		= Button(this, 648, 170, 120, 55, 0x7BEF, "<<", 0);
	Button right 	= Button(this, 648, 250, 120, 55, 0x7BEF, ">>", 0);

	//Button SetBKI 	= Button(this, 648, 250, 120, 55, 0x7BEF, ">>", 0);

/*----------------------------------------------------------------------------------------------------------------*/
	Label lfider[3] = {
		Label(this, 5, 85, 300, 85, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 5, 205, 300, 85, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 5, 320, 300, 85, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

/*----------------------------------------------------------------------------------------------------------------*/
	Label section[6] = {
		[0] = Label(this, 235, 65, 200, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[1] = Label(this, 235, 185, 200, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[2] = Label(this, 235, 300, 200, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		[3] = Label(this, 440, 65, 200, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[4] = Label(this, 440, 185, 200, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[5] = Label(this, 440, 300, 200, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),

	};

/*-----------------------Дисплеии вывода значения сопротивления Полюсов------------------------------------------------------------------*/
	Display disp[6] = {
			//---------- +
		Display(this, 235, 126, 100,50, &Value[0], 4, 1, 0, 1000, nullptr),
		Display(this, 235, 242, 100,50, &Value[1], 4, 1, 0, 1000, nullptr),
		Display(this, 235, 357, 100,50, &Value[2], 4, 1, 0, 1000, nullptr),
			//---------- -
		Display(this, 440, 126, 100,50, &Value[3], 4, 1, 0, 1000, nullptr),
		Display(this, 440, 242, 100,50, &Value[4], 4, 1, 0, 1000, nullptr),
		Display(this, 440, 357, 100,50, &Value[5], 4, 1, 0, 1000, nullptr)
	};

/*-----------------------Дисплеии вывода значения сопротивления Полюсов------------------------------------------------------------------*/

	Label Units[6] = {
		Label(this, 355, 136, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 367, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 560, 136, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 367, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

public:

	uint32_t Max = 32; 						// количество фидеров
	uint32_t Min = 3; 						// количество фидеров на экране
	uint32_t counter = 3; 			 		// номер фидера

	ScreenContrlInsulation(void) : BaseScreen(&Screens, "Блок контроля изоляции") {
		this->left.addCallBack([&]() {
			if(this->counter >= this->Min + 3) {
				this->counter -= 3;
			}
			else { this->counter = this->Min; }
			});
			this->right.addCallBack([&]() {
			if(this->counter < (this->Max - 3)) {
				this->counter += 3;
			}
			else { this->counter = this->Max; }
			});
	}

	void Loop(void) override;

	void JumpTo(void) override {
		//this->counter = BKI.Mem.Nfider;
	}
};

