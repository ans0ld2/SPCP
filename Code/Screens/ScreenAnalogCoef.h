#pragma once

#include "Loop.h"
#include "AnalogBlock.h"

extern AnalogBlock AnalogBl;

class ScreenAnalogCoef : public BaseScreen {

	void _write(uint16_t Reg, uint16_t Val) {

		WriteBuf_t temp;

		temp.AdrReg = Reg;
		temp.Value = Val;
		temp.Adress = AnalogBl.Adress;
		write(temp);

		temp.AdrReg = 103;
		temp.Value = 103;
		write(temp);
	}


    Label label[8] = {
		Label(this, 65, 90, 135, 65, "Вход Х1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 140, 135, 65, "Вход Х2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 190, 135, 65, "Вход Х3", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 65, 240, 135, 65, "Вход Х11", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 290, 135, 65, "Вход Х12", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 340, 135, 65, "Вход Х13", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 210, 55, 160, 65, "Значение", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 375, 55, 135, 65, "Коэф-т", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

    Display dValue[6] 			= {
		 Display(this, 210, 100, 100, 40, &AnalogBl.Mem.AI1, 4, 1, 0, 32000, nullptr),
		 Display(this, 210, 150, 100, 40, &AnalogBl.Mem.AI2, 4, 1, 0, 32000, nullptr),
		 Display(this, 210, 200, 100, 40, &AnalogBl.Mem.AI3, 4, 1, 0, 32000, nullptr),
		 Display(this, 210, 250, 100, 40, &AnalogBl.Mem.AI11, 4, 1, 0, 32000, nullptr),
		 Display(this, 210, 300, 100, 40, &AnalogBl.Mem.AI12, 4, 1, 0, 32000, nullptr),
		 Display(this, 210, 350, 100, 40, &AnalogBl.Mem.AI13, 4, 1, 0, 32000, nullptr),

	};
    Display dCoef[6] 			= {
		 Display(this, 375, 100, 100, 40, &AnalogBl.Mem.K1, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 375, 150, 100, 40, &AnalogBl.Mem.K2, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 375, 200, 100, 40, &AnalogBl.Mem.K3, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 375, 250, 100, 40, &AnalogBl.Mem.K11, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 375, 300, 100, 40, &AnalogBl.Mem.K12, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 375, 350, 100, 40, &AnalogBl.Mem.K13, 4, 0, 0, 32000, &Screens.kbr),
	};

public:

	ScreenAnalogCoef(void) : BaseScreen(&Screens, "Коэффициенты") {
		this->dCoef[0].addCallBack([&]() {
			this->_write(25, *this->dCoef[0].GetPValue());
		});
		this->dCoef[1].addCallBack([&]() {
			this->_write(26, *this->dCoef[1].GetPValue());
		});
		this->dCoef[2].addCallBack([&]() {
			this->_write(27, *this->dCoef[2].GetPValue());
		});
		this->dCoef[3].addCallBack([&]() {
			this->_write(28, *this->dCoef[3].GetPValue());
		});
		this->dCoef[4].addCallBack([&]() {
			this->_write(29, *this->dCoef[4].GetPValue());
		});
		this->dCoef[5].addCallBack([&]() {
			this->_write(30, *this->dCoef[5].GetPValue());
		});
		this->dValue[0].SetSigned(true);
		this->dValue[2].SetSigned(true);
		this->dValue[5].SetSigned(true);
	}
};

