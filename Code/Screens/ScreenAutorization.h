/*
 * ScreenAutorization.h
 *
 *  Created on: Dec 3, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

using namespace VA;

class ScreenAutorization : public BaseScreen {
	uint16_t pass = 0;

	class WindowInfo : public BaseWindow {

		Label label = Label(this, 0, 0, this->GetW(), this->GetH()-170, "", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
		Button bClose = Button(this, 59, this->GetH()-100, 150, 65, 0x031f, "Закрыть", 10);


	public:
		WindowInfo(void) : BaseWindow("", &Screens, 522, 70, 268, 340) {
			this->bClose.addCallBack([&]() {
				this->Close();
			});
		}

		void Open(std::string text) {
			label.SetText(text);
			this->BaseWindow::Open();
		}
	} Info;

	class WindowAutors : public BaseWindow {

		Label l1 = Label(this, 20, 0, this->GetW()-40, 60, this->name, Fonts::TimesNewRoman, FontForms::Bold,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Bottom);
		Graphics line1 = Graphics(this, 50, 65, this->GetW()-100 , 5, 0x0000, Figure::rect, 3, true);

		Label label = Label(this, 50, 100, this->GetW()-100, this->GetH()-230,
				"Ананьев А.С.\nБутенко В.А.\n Луценко Г.А.\n Мозговая О.Л.", Fonts::TimesNewRoman, FontForms::Italic,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);

		Button bClose = Button(this, this->GetW() - 380, this->GetH() - 100, 150, 65, RA8875_RED, "Закрыть", 10);

	public:
		WindowAutors(void) : BaseWindow("Авторы:", &Screens) {
			this->bClose.addCallBack([&]() {
				this->Close();
			});
		}
	} Autors;

public:

	Button bOpen	= Button(this, 300, 100, 200, 75, 0x031f, "Открыть доступ");
	Button bClose	= Button(this, 300, 200, 200, 75, 0x031f, "Закрыть доступ");
	Display disp	= Display(nullptr, 500, 0, 1, 1, &this->pass, 4, 0, 0, 9999);

	Button bAutors	= Button(this, 300, 300, 200, 75, 0x031f, "Авторы");

	ScreenAutorization(void)
		: BaseScreen(&Screens, "Авторизация")
	{

		this->bAutors.addCallBack([&]() {
			this->Autors.Open();
		});

		this->bOpen.addCallBack([&]() {
			Screens.kbr.Open(&this->disp);
		});
		this->bClose.addCallBack([&]() {
			Screens.CloseLevelAcces();
			this->Info.Open("Доступ закрыт");
		});
		this->disp.addCallBack([&]() {
			Screens.OpenLevelAcces(this->pass) ? this->Info.Open("Доступ открыт") : this->Info.Open("Неверный пароль");
		});

		Screens.InsufficientLavelAccess.bAutorization.addCallBack([&]() {
			Screens.JumpScreen(this);
			this->bOpen.CallBack();
		});
	}
    void Loop(void) override {
    	this->bAutors.SetShowed(Screens.GetLevelAcces() == LevelsAcces::Admin);
		this->bAutors.SetEnabled(Screens.GetLevelAcces() == LevelsAcces::Admin);
    }
};


