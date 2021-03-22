/*
 * Screen1.h
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "Loop.h"
#include "ScreenEvents.h"
#include "ScreenCrash.h"
#include "ScreenSysSett.h"
#include "ScreenZVU.h"
#include "ScreenBattery.h"
#include "ScreenMain.h"
#include "ScreenBKI.h"
#include "ScreenAnalogPl.h"

using namespace VA;

extern ScreenCrash sCrash;
extern ScreenEvents sEvents;
extern ScreenSysSett SystemSett;
extern ScreenZVU sZVU;
extern ScreenBattery sBatteryControl;
extern ScreenMain sMain;
extern ScreenBKI sBKI;
extern ScreenAnalogPl	sAnalogPl;

class ScreenMenu : public BaseScreen {

public:

	Button lookCrash	 = Button(this, 60, 100, 360, 90, 0x7BEF, "Просмотр аварий", 0);
	Button lookEvent	 = Button(this, 60, 210, 360, 70, 0x7BEF, "Просмотр событий", 0);
	Button systemSetting = Button(this, 60, 295, 360, 70, 0x7BEF, "Системные настройки", 0);


	Button butZVU	 = Button(this, 465, 100, 310, 90, 0x7BEF, "ЗВУ", 0);
	//Button butDCXJ	 = Button(this, 465, 295, 310, 70, 0x7BEF, "Контроль  АКБ", 0);
	Button butMain	 = Button(this, 465, 210, 310, 70, 0x7BEF, "Основной экран", 0);
	Button butBKI	 = Button(this, 465, 295, 310, 70, 0x7BEF, "БКИ", 0);
	//Button butAnalog = Button(this, 575, 295, 200, 70, 0x7BEF, "Аналоговая плата", 0);

	ScreenMenu(void):BaseScreen(&Screens, "Меню") {

		this->systemSetting.addCallBack([]() { Screens.JumpScreen(&SystemSett); });
		this->lookCrash.addCallBack([]() { Screens.JumpScreen(&sCrash); });
		this->lookEvent.addCallBack([]() { Screens.JumpScreen(&sEvents); });
		this->butZVU.addCallBack([]() { Screens.JumpScreen(&sZVU); });
		//this->butDCXJ.addCallBack([]() { Screens.JumpScreen(&sBatteryControl); });
		this->butMain.addCallBack([]() { Screens.JumpScreen(&sMain); });
		this->butBKI.addCallBack([]() { Screens.JumpScreen(&sBKI); });
		//this->butAnalog.addCallBack([]() { Screens.JumpScreen(&sAnalogPl); });
	}

};

