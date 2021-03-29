#pragma once

#include "Loop.h"
#include "ScreenAnalogCoef.h"
#include "ScreenSetAnalogPl.h"	
#include "ScreenAnalogTestIO.h"

extern ScreenAnalogCoef sAnalogCoef;	
extern ScreenSetAnalogPl sSetAnalogPl;
extern ScreenAnalogTestIO sAnalogTestIO;

class ScreenAnalogPl : public BaseScreen {
	void _write(uint16_t Reg, uint16_t Val) {
		WriteBuf_t temp;
		temp.AdrReg = Reg;
		temp.Value = Val;
		temp.Adress = AnalogBl.Adress;
		write(temp);
	}

	class WindowZero : public BaseWindow {

		Label l1 = Label(this, 20, 0, this->GetW()-40, 60, this->name, Fonts::TimesNewRoman, FontForms::Bold,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Bottom);
		Graphics line1 = Graphics(this, 50, 65, this->GetW()-100 , 5, 0x0000, Figure::rect, 3, true);

		Label label = Label(this, 50, 100, this->GetW()-100, this->GetH()-230, "Вы действительно хотите записать нули?", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);

		Button bOK = Button(this, 100, this->GetH()-100, 150, 65, RA8875_GREEN, "Да", 10);
		Button bClose = Button(this, this->GetW() - 250, this->GetH() - 100, 150, 65, RA8875_RED, "Закрыть", 10);

	public:
		WindowZero(void) : BaseWindow("Запись нулей", &Screens) {
			this->bClose.addCallBack([&]() {
				this->Close();
			});
			this->bOK.addCallBack([&]() {
				WriteBuf_t temp;
				temp.AdrReg = 102;
				temp.Value = 102;
				temp.Adress = AnalogBl.Adress;
				write(temp);
				this->Close();
			});
		}
	} Zero;

    Button settZero	    = Button(this, 165, 100, 470, 60, 0x7BEF, "Уставки нулей", 0);
	Button coeff	    = Button(this, 165, 170, 470, 60, 0x7BEF, "Коэффициенты", 0);
	Button sett         = Button(this, 165, 240, 470, 60, 0x7BEF, "Уставки", 0);
    Button testIO         = Button(this, 165, 310, 470, 60, 0x7BEF, "Тест IO", 0);
    


public:

	ScreenAnalogPl(void) : BaseScreen(&Screens, "Аналоговая плата") {
		this->settZero.addCallBack([&]() {
			this->Zero.Open();
		});
		this->coeff.addCallBack([]() { Screens.JumpScreen(&sAnalogCoef); });
		this->sett.addCallBack([]() { Screens.JumpScreen(&sSetAnalogPl); });
		this->testIO.addCallBack([]() { Screens.JumpScreen(&sAnalogTestIO); });
    }
};

