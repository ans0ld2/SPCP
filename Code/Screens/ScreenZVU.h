/*
 * ScreenZVU.h
 *
 *  Created on: Dec 4, 2020
 *      Author: ans0ld
 */

#pragma once 

#include "Loop.h"
#include  "ScreenSettZVU.h"

#include "DeviceB118.h"

using namespace VA;

extern ScreenSettZVU sSettZVU;
extern DeviceB118 B118[2];

class ScreenZVU: public BaseScreen
{

    const std::vector<std::string> labelZVU = { "ЕCI", "ECII" };

    class WindowPusk: public BaseWindow
    {

        Label l1 = Label(this, 20, 0, this->GetW() - 40, 60, this->name,
                         Fonts::TimesNewRoman, FontForms::Bold,
                         VALabelScale::S2, VALabelAlignX::CenterX,
                         VALabelAlignY::Bottom);
        Graphics line1 = Graphics(this, 50, 65, this->GetW() - 100, 5, 0x0000,
                                  Figure::rect, 3, true);

        Label label = Label(this, 50, 100, this->GetW() - 100,
                            this->GetH() - 230,
                            "Вы действительно хотите запустить ЗВУ?",
                            Fonts::TimesNewRoman, FontForms::Normal,
                            VALabelScale::S2, VALabelAlignX::CenterX,
                            VALabelAlignY::CenterY);

        Button bOK = Button(this, 100, this->GetH() - 100, 150, 65,
                            RA8875_GREEN, "Да", 10);
        Button bClose = Button(this, this->GetW() - 250, this->GetH() - 100,
                               150, 65, RA8875_RED, "Закрыть", 10);

    public:
        WindowPusk(void) :
                BaseWindow("Запуск ЗВУ", &Screens)
        {
            this->bClose.addCallBack([&]() {
                this->Close();
            });
            this->bOK.addCallBack([&]() {
                WriteBuf_t temp;
                temp.AdrReg = 5;
                temp.Value = 0;
                if(sSettZVU.chosenDevise == 0) {
                    Memory[rMemory::PuskB118].U = 0;
                    temp.Adress = B118[0].Adress;
                }
                else {
                    Memory[rMemory::PuskB118M].U = 0;
                    temp.Adress = B118[1].Adress;
                }
                write(temp);

                this->Close();
            });
        }
    } Pusk;
public:

    /*----------------------------------------------------------------------------------------------------- */
    Label regime = Label(this, 0, 0, 160, 60, "Режим:", Fonts::TimesNewRoman,
                         FontForms::Normal, VALabelScale::S2,
                         VALabelAlignX::Right, VALabelAlignY::Top, 0x00);
    Label condition = Label(this, 0, 0, 160, 60, "Состояние:",
                            Fonts::TimesNewRoman, FontForms::Normal,
                            VALabelScale::S2, VALabelAlignX::Right,
                            VALabelAlignY::Bottom, 0x00);

    Label selectedRegime = Label(this, 170, 0, 160, 60, "Подзаряд",
                                 Fonts::TimesNewRoman, FontForms::Normal,
                                 VALabelScale::S2, VALabelAlignX::Left,
                                 VALabelAlignY::Top, 0x00);
    Label selectedCondition[1] = { Label(this, 170, 0, 20, 60, "Г",
                                         Fonts::TimesNewRoman,
                                         FontForms::Normal, VALabelScale::S2,
                                         VALabelAlignX::Left,
                                         VALabelAlignY::Bottom, 0x00), };

    /*----------------------------------------------------------------------------------------------------- */

    Button bStop = Button(this, 215, 130, 140, 80, RA8875_RED, "СТОП", 5);
    Button bStart = Button(this, 25, 130, 140, 80, RA8875_GREEN, "ПУСК", 5);

//	Label lSelfStart  = Label(this, 40, 185, 280, 40, "Самозапуск", Fonts::TimesNewRoman, FontForms::Normal,
//	        VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY, 0x0);

//Indicator SelfStart = Indicator(this, 280, 185, 75, 40, false);

    Button leftZVU = Button(this, 20, 240, 90, 70, 0x031f, "<", 0);

    Label numZVU = Label(this, 110, 240, 160, 70, "", Fonts::TimesNewRoman,
                         FontForms::Bold, VALabelScale::S2,
                         VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);

    Button rightZVU = Button(this, 275, 240, 90, 70, 0x031f, ">", 0);

    Button bSettingZVU = Button(this, 16, 345, 350, 60, 0x7BEF, "Уставки ЗВУ");

    /*----------------------------------------------------------------------------------------------------- */
    Graphics vline = Graphics(this, 380, 62, 5, 356, 0x00, Figure::rect, 0,
                              true);
    Graphics hline = Graphics(this, 380, 240, 420, 5, 0x00, Figure::rect, 0,
                              true);

    /*----------------------------------------------------------------------------------------------------- */

    Label inputVolt = Label(this, 400, 80, 200, 80, "Выходное напряжение",
                            Fonts::TimesNewRoman, FontForms::Normal,
                            VALabelScale::S2, VALabelAlignX::Left,
                            VALabelAlignY::CenterY, 0x00);

    Display numInputVolt = Display(this, 640, 85, 100, 60, &this->OutputVoltage,
                                   4, 1, 0, 00, nullptr);

    /*----------------------------------------------------------------------------------------------------- */
    Label inputCurrent = Label(this, 400, 168, 300, 50, "Выходной ток",
                               Fonts::TimesNewRoman, FontForms::Normal,
                               VALabelScale::S2, VALabelAlignX::Left,
                               VALabelAlignY::CenterY, 0x00);

    Display numInputCurrent = Display(this, 640, 160, 100, 60,
                                      &this->OutputCurrent, 4, 1, 0, 00,
                                      nullptr);

    /*----------------------------------------------------------------------------------------------------- */

    Label targetVolt = Label(this, 400, 260, 200, 80, "Напряжение задания",
                             Fonts::TimesNewRoman, FontForms::Normal,
                             VALabelScale::S2, VALabelAlignX::Left,
                             VALabelAlignY::CenterY, 0x00);

    Display numTargetVolt = Display(this, 640, 265, 100, 60, &this->TargetVolt,
                                    4, 1, 0, 00, nullptr);

    /*----------------------------------------------------------------------------------------------------- */

    Label targetCurrent = Label(this, 400, 348, 200, 50, "Токоограничение",
                                Fonts::TimesNewRoman, FontForms::Normal,
                                VALabelScale::S2, VALabelAlignX::Left,
                                VALabelAlignY::CenterY, 0x00);

    Display numTargetCurrent = Display(this, 640, 340, 100, 60,
                                       &this->TargetCurrent, 4, 1, 0, 00,
                                       nullptr);
    /*----------------------------------------------------------------------------------------------------- */

    Label unit[4] = { Label(this, 755, 85, 40, 60, "B", Fonts::TimesNewRoman,
                            FontForms::Normal, VALabelScale::S2,
                            VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00),
                      Label(this, 755, 160, 40, 60, "A", Fonts::TimesNewRoman,
                            FontForms::Normal, VALabelScale::S2,
                            VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00),
                      Label(this, 755, 265, 40, 60, "B", Fonts::TimesNewRoman,
                            FontForms::Normal, VALabelScale::S2,
                            VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00),
                      Label(this, 755, 340, 40, 60, "%", Fonts::TimesNewRoman,
                            FontForms::Normal, VALabelScale::S2,
                            VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00) };

    uint16_t TargetCurrent;
    uint16_t TargetVolt;

    uint16_t OutputVoltage;
    uint16_t OutputCurrent;
    uint8_t count = 0;

    ScreenZVU(void) :
            BaseScreen(&Screens, "ЗВУ")
    {
        this->bSettingZVU.addCallBack([]() {
            Screens.JumpScreen(&sSettZVU);
        });

        this->bStart.SetLevelAcces(LevelsAcces::User);
        this->bStart.addCallBack([&]() {this->Pusk.Open();});
        this->bStop.addCallBack([]() {
            WriteBuf_t temp;
            temp.AdrReg = 5;
            temp.Value = 1;
            if (sSettZVU.chosenDevise == 0) {
                if (!B118[0].ErrorConnection) {
                    Memory[rMemory::PuskB118].U = 1;
                    temp.Adress = B118[0].Adress;
                    write(temp);
                }

            }
            else {
                if(!B118[1].ErrorConnection) {
                   Memory[rMemory::PuskB118M].U = 1;
                   temp.Adress = B118[1].Adress;
                   write(temp);
                }
            }
        });

        this->leftZVU.addCallBack([&]() {
            if(this->count > 0) {
                count--;
            }
            else {count = labelZVU.size() - 1;}
        });
        this->rightZVU.addCallBack([&]() {
            if(this->count < labelZVU.size() - 1) {
                count++;
            }
            else {count = 0;}
        });

    }

    void Loop(void) override
    {
        UpdateRegime();
        sSettZVU.chosenDevise = this->count;
        this->bStart.SetEnabled(
                ((Memory[rMemory::PuskB118].U != 0 && !B118[0].Mem.State.Crash)
                        && this->count == 0 && !B118[0].ErrorConnection)
                || ((Memory[rMemory::PuskB118M].U != 0 && !B118[1].Mem.State.Crash)
                        && this->count == 1 && !B118[1].ErrorConnection));

        if (this->count == 0) {
            sSettZVU.disp[0].SetPtr(&Memory[eMemory::MaxVoltageRecharge].U);
            sSettZVU.disp[1].SetPtr(&Memory[eMemory::MinVoltageRecharge].U);
            sSettZVU.disp[2].SetPtr(&Memory[eMemory::MaxCurrentRecharge].U);
            sSettZVU.disp[3].SetPtr(&Memory[eMemory::MinCurrentRecharge].U);
            sSettZVU.disp[4].SetPtr(&Memory[eMemory::MaxVoltageBoostCharge].U);
            sSettZVU.disp[5].SetPtr(&Memory[eMemory::MinVoltageBoostCharge].U);
            sSettZVU.disp[6].SetPtr(&Memory[eMemory::MaxCurrentBoostCharge].U);
            sSettZVU.disp[7].SetPtr(&Memory[eMemory::MinCurrentBoostCharge].U);

            sSettZVU.drechargeVoltage.SetPtr(
                    &Memory[eMemory::VoltageRecharge].U);
            sSettZVU.drechargeCurrent.SetPtr(
                    &Memory[eMemory::CurrentRecharge].U);
            sSettZVU.dboostChargeVoltage.SetPtr(
                    &Memory[eMemory::VoltageBoostCharge].U);
            sSettZVU.dboostChargeCurrent.SetPtr(
                    &Memory[eMemory::CurrentBoostCharge].U);
        }

        else {
            sSettZVU.disp[0].SetPtr(&Memory[eMemory::MaxVoltageRechargeM].U);
            sSettZVU.disp[1].SetPtr(&Memory[eMemory::MinVoltageRechargeM].U);
            sSettZVU.disp[2].SetPtr(&Memory[eMemory::MaxCurrentRechargeM].U);
            sSettZVU.disp[3].SetPtr(&Memory[eMemory::MinCurrentRechargeM].U);
            sSettZVU.disp[4].SetPtr(&Memory[eMemory::MaxVoltageBoostChargeM].U);
            sSettZVU.disp[5].SetPtr(&Memory[eMemory::MinVoltageBoostChargeM].U);
            sSettZVU.disp[6].SetPtr(&Memory[eMemory::MaxCurrentBoostChargeM].U);
            sSettZVU.disp[7].SetPtr(&Memory[eMemory::MinCurrentBoostChargeM].U);

            sSettZVU.drechargeVoltage.SetPtr(
                    &Memory[eMemory::VoltageRechargeM].U);
            sSettZVU.drechargeCurrent.SetPtr(
                    &Memory[eMemory::CurrentRechargeM].U);
            sSettZVU.dboostChargeVoltage.SetPtr(
                    &Memory[eMemory::VoltageBoostChargeM].U);
            sSettZVU.dboostChargeCurrent.SetPtr(
                    &Memory[eMemory::CurrentBoostChargeM].U);

        }

        sSettZVU.drechargeVoltage.SetMax(sSettZVU.disp[0].GetValue());
        sSettZVU.drechargeCurrent.SetMax(sSettZVU.disp[2].GetValue());
        sSettZVU.dboostChargeVoltage.SetMax(sSettZVU.disp[4].GetValue());
        sSettZVU.dboostChargeCurrent.SetMax(sSettZVU.disp[6].GetValue());

        sSettZVU.drechargeVoltage.SetMin(sSettZVU.disp[1].GetValue());
        sSettZVU.drechargeCurrent.SetMin(sSettZVU.disp[3].GetValue());
        sSettZVU.dboostChargeVoltage.SetMin(sSettZVU.disp[5].GetValue());
        sSettZVU.dboostChargeCurrent.SetMin(sSettZVU.disp[7].GetValue());

        if (this->count == 0) {
            this->OutputVoltage = B118[0].Mem.Uout;
            this->OutputCurrent = B118[0].Mem.Iout;
            this->TargetCurrent =
                    (Memory[eMemory::RegimeB118].U == 0) ?
                            Memory[eMemory::CurrentRecharge].U :
                            Memory[eMemory::CurrentBoostCharge].U;
            this->TargetVolt =
                    (Memory[eMemory::RegimeB118].U == 0) ?
                            Memory[eMemory::VoltageRecharge].U :
                            Memory[eMemory::VoltageBoostCharge].U;
        } else {
            this->OutputVoltage = B118[1].Mem.Uout;
            this->OutputCurrent = B118[1].Mem.Iout;
            this->TargetCurrent =
                    (Memory[eMemory::RegimeB118M].U == 0) ?
                            Memory[eMemory::CurrentRechargeM].U :
                            Memory[eMemory::CurrentBoostChargeM].U;
            this->TargetVolt =
                    (Memory[eMemory::RegimeB118M].U == 0) ?
                            Memory[eMemory::VoltageRechargeM].U :
                            Memory[eMemory::VoltageBoostChargeM].U;
        }

        this->numZVU.SetText(this->labelZVU[count]);

    }

    void JumpTo(void) override
    {
        this->Loop();
    }

};

extern ScreenZVU sZVU;

void UpdateRegime(void)
{
    if (sZVU.count == 0) {
        switch (Memory[eMemory::RegimeB118].U) {
            case 0:
                sZVU.selectedRegime.SetText("Подзаряд");
                break;
            case 1:
                sZVU.selectedRegime.SetText("Уск. заряд");
                break;
        }

        sZVU.selectedCondition[0].SetShowed(true);
        if (!B118[0].Enable) {
            sZVU.selectedCondition[0].SetText("О");
        } else if (B118[0].Mem.State.Crash || B118[0].Mem.State.Protect
                   || B118[0].ErrorConnection) {
            sZVU.selectedCondition[0].SetText("А");
        } else if (B118[0].Mem.State.State) {
            sZVU.selectedCondition[0].SetText("Г");
        } else {
            sZVU.selectedCondition[0].SetText("Р");
        }

    } else {
        switch (Memory[eMemory::RegimeB118M].U) {
            case 0:
                sZVU.selectedRegime.SetText("Подзаряд");
                break;
            case 1:
                sZVU.selectedRegime.SetText("Уск. заряд");
                break;
        }

        if (!B118[1].Enable) {
            sZVU.selectedCondition[0].SetText("О");
        } else if (B118[1].Mem.State.Crash || B118[1].Mem.State.Protect
                   || B118[1].ErrorConnection) {
            sZVU.selectedCondition[0].SetText("А");
        } else if (B118[1].Mem.State.State) {
            sZVU.selectedCondition[0].SetText("Г");
        } else {
            sZVU.selectedCondition[0].SetText("Р");
        }
    }

}

