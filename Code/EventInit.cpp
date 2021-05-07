/*
 * EventInit.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: ans0l
 */

#include "ScreenEvents.h"

std::string ListEvent[100] = {};

void EventInit(void) {
	ListEvent[NumberCrash::PanelOn] = "Панель включена";
	ListEvent[10] = "Обрыв связи: ";
	ListEvent[11] = "Связь восстановлена: ";
	ListEvent[12] = "Неисправность: ";
	ListEvent[21] = "Неисправность батареи";
	ListEvent[31] = "Неисправность БКИ";

	ListEvent[41] = "Неисправность ШОТ";
	ListEvent[42] = "Авария ШОТ";
	ListEvent[43] = "Авария O3";
	ListEvent[44] = "Напряжение ECI не в норме";
	ListEvent[45] = "Напряжение ECII не в норме";
	ListEvent[46] = "Напряжение AБ ниже нормы";
	ListEvent[47] = "Авария O7";

	ListEvent[48] = "Отсутствие напряжения на вводе";
	ListEvent[49] = "Обрыв связи с АБ";
	ListEvent[50] = "Авар. откл. выключателя в цепи АБ";
	ListEvent[51] = "Авар. откл. выключателя линии и доп. цепей";
	ListEvent[52] = "Авария I3";
	ListEvent[53] = "Авар. откл. выключателя ввода";
	ListEvent[54] = "Авария I1";

	ListEvent[55] = "Rиз < ";
	ListEvent[56] = "Напряжение ECI не в норме(пред.)";
	ListEvent[57] = "Напряжение ECII не в норме(пред.)";
	ListEvent[58] = "Напряжение AБ не в норме(пред.)";
}
