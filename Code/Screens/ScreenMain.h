/*
 * ScreenMain.h
 *
 *  Created on: Feb 2, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"
#include "AnalogBlock.h"
#include "DeviceBKI.h"
#include "ScreenAnalogPl.h"
#include "ScreenSetAnalogPl.h"

using namespace VA;

extern AnalogBlock AnalogBl;
extern DeviceBKI BKI;
extern ScreenAnalogPl	sAnalogPl;
extern ScreenSetAnalogPl sSetAnalogPl;

class ScreenMain : public BaseScreen {


	Graphics Vline1 	= Graphics(this, 180, 65, 2, 285, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 380, 65, 2, 285, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline3 	= Graphics(this, 520, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);

	Graphics Hline1 	= Graphics(this, 0, 135, 800, 5, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 205, 520, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline3 	= Graphics(this, 0, 275, 520, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline4 	= Graphics(this, 0, 350, 520, 2, RA8875_BLACK, Figure::rect, 0, true);


	Label lVoltage		 = Label(this, 180, 65, 200, 70, "Напряжение",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lCurrent 		= Label(this, 380, 65, 140, 70, "Ток",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lControlIns 	= Label(this, 520, 65, 280, 70, "Контроль изоляции",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);



	Label lBusI		= Label(this, 0, 135, 180, 70, "Шина ±ЕСI",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lBusII	= Label(this, 0, 205, 180, 70, "Шина ±ЕСII",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lAB		= Label(this, 0, 275, 180, 70, "АБ",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);


	 Display BusIVolt 	= Display(this, 200, 145, 100, 50, &AnalogBl.Mem.AI2, 4, 1, 0, 00, nullptr);
	 Display BusICurr 	= Display(this, 400, 145, 80, 50, &AnalogBl.Mem.AI3, 4, 1, 0, 00, nullptr);
	 Display BusIIVolt 	= Display(this, 200, 215, 100, 50, &AnalogBl.Mem.AI11, 4, 1, 0, 00, nullptr);
	 Display BusIICurr 	= Display(this, 400, 215, 80, 50, &AnalogBl.Mem.AI13, 4, 1, 0, 00, nullptr);
	 Display AB_Volt 	= Display(this, 200, 285, 100, 50, &AnalogBl.Mem.AI12, 4, 1, 0, 00, nullptr);
	 Display AB_Curr 	= Display(this, 400, 285, 80, 50, &AnalogBl.Mem.AI1, 4, 1, 0, 00, nullptr);


	Label Units[10] = {
		Label(this, 310, 135, 50, 70, "В", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 490, 135, 50, 70, "А", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 310, 205, 50, 70, "В", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 490, 205, 50, 70, "А", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 310, 275, 50, 70, "В", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 490, 275, 50, 70, "А", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 760, 135, 50, 70, "В", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 760, 195, 50, 70, "В", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 740, 265, 50, 70, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 740, 335, 50, 70, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		};

	Label lInsul[4] = {
		Label(this, 525, 135, 120, 70, "+UЕС = ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY),
		Label(this, 525, 195, 120, 70, "-UЕС = ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY),
		Label(this, 515, 265, 120, 70, "+Rиз = ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY),
		Label(this, 515, 335, 120, 70, "-Rиз = ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY),
	};

	Display dispCont[4] = {
			Display(this, 640, 145, 100, 50, &BKI.Mem.U1Plus, 4, 1, 0, 00, nullptr),
			Display(this, 640, 205, 100, 50, &BKI.Mem.U1Minus, 4, 1, 0, 00, nullptr),
			Display(this, 630, 275, 100, 50, &BKI.Mem.R1Plus, 4, 1, 0, 00, nullptr),
			Display(this, 630, 345, 100, 50, &BKI.Mem.R1Minus, 4, 1, 0, 00, nullptr),
	};

	Button butAnalog	= Button(this, 80, 360, 350, 50, 0x7BEF, "Аналоговая плата", 0);
	Button butAnSet		= Button(this, 80, 360, 350, 50, 0x7BEF, "Уставки", 0);
public:
	Indicator bki = Indicator(this, 760, 66, 24, 24, true);

	ScreenMain(void) : BaseScreen(&Screens, "Основной экран") {

		this->butAnalog.addCallBack([]() { Screens.JumpScreen(&sAnalogPl); });
		this->butAnSet.addCallBack([]() { Screens.JumpScreen(&sSetAnalogPl); });

		BusICurr.SetSigned(true);
		BusIICurr.SetSigned(true);
		AB_Curr.SetSigned(true);
	}
    void Loop(void) override {
    	this->butAnalog.SetShowed(Screens.GetLevelAcces() == LevelsAcces::Admin);
    	this->butAnalog.SetEnabled(Screens.GetLevelAcces() == LevelsAcces::Admin);
    	this->butAnSet.SetShowed(Screens.GetLevelAcces() == LevelsAcces::User);
    	this->butAnSet.SetEnabled(Screens.GetLevelAcces() == LevelsAcces::User);
    }
};




