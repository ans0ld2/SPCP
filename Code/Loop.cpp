
#include "Loop.h"

#include "ScreenGlobal.h"
#include "ScreenMenu.h"
#include "ScreenSysSett.h"
#include "ScreenSetTime.h"
#include "ScreenCOM.h"
#include "ScreenAutorization.h"
#include "ScreenCrash.h"
#include "ScreenEvents.h"
#include "ScreenZVU.h"
#include "ScreenSettZVU.h"
#include "ScreenBattery.h"
#include "ScreenMain.h"
#include "ScreenContrlInsulation.h"
#include "ScreenBKI.h"
#include "ScreenAnalogPl.h"
#include "ScreenAnalogCoef.h"
#include "ScreenSetAnalogPl.h"
#include "ScreenSetBKI.h"

Memory_un Memory[17000] = {};
uint16_t Buf[4000] = {};

bool CrashBattery = true;
bool exch = false;

using namespace VA;

GUI Screens(11);

ScreenGlobal Global;									//0
ScreenMenu Menu;										//1
ScreenSysSett SystemSett;								//2
ScreenSetTime SetTime;									//3
ScreenCOM COMSett;										//4
ScreenAutorization Autorization;						//5
ScreenCrash sCrash;										//6
ScreenEvents sEvents;									//7
ScreenZVU sZVU;											//8
ScreenSettZVU sSettZVU;									//9
ScreenBattery sBatteryControl;							//10
ScreenMain sMain;										//11
ScreenContrlInsulation sContrlInsulation;				//12
ScreenBKI sBKI;											//13
ScreenAnalogPl	sAnalogPl;								//14
ScreenAnalogCoef sAnalogCoef;							//15
ScreenSetAnalogPl sSetAnalogPl;							//16
ScreenSetBKI sSetBKI;									//17
ScreenAnalogTestIO sAnalogTestIO;						//18

WindowReboot Reboot;

EEPROM_AT25640 eeprom(&hspi1, &Memory->U, NSS1_GPIO_Port, NSS1_Pin, EEPROM_Polarity::LOW);

Modbus Modbus1;
Modbus Modbus2;

#include "DeviceB118.h"
#include "DeviceDCXJ.h"
#include "AnalogBlock.h"
#include "DeviceBKI.h"

DeviceB118 B118[2] = {
		DeviceB118(ModeDevice::V220),
		DeviceB118(ModeDevice::V60),
};
AnalogBlock AnalogBl;
DeviceDCXJ DCXJ;

DeviceBKI BKI;



void Setup(void) {

	eeprom.Reads(0, rMemory::StartAdress);

	if(Memory[0].U != 0x112 || Memory[3].U != 0x163) {
		uint16_t Buf1[] = { 55, 5, 0, 0, 192, 0, 100, 96, 1, 100 };
		uint16_t Buf2[] = { 0, 2600, 2310, 1900, 1050, 1000, 100, 2800, 2420, 2000, 1050, 1000, 100 };

		eeprom.Writes(10, sizeof(Buf1)/2, Buf1);
		eeprom.Writes(100, sizeof(Buf2)/2, Buf2);

		Memory[0].U = 0x112;
		Memory[3].U = 0x163;
		eeprom.Write(&Memory[0].U);
		eeprom.Write(&Memory[3].U);

		EraseEvent();
	}
	
	Screens.Init();
	Screens.SetBackLight(Memory[eMemory::Backlight].U);
	Screens.SetTimeOut(Memory[eMemory::TimeOut].U);

	ModbusInitStruct ModbusInit;

	ModbusInit.Adress 		= Memory[eMemory::SlaveIdCOM1].U;
	ModbusInit.huart		= &huart4;
	ModbusInit.Memory		= &Memory[1000].U;
	ModbusInit.NRegMax		= sizeof(Memory)/2 - (ModbusInit.Memory - &Memory->U);
	ModbusInit.Interface	= ModbusInterface::RS485;
	ModbusInit.Dir_Port		= DIR4_GPIO_Port;
	ModbusInit.Dir_Pin		= DIR4_Pin;
	ModbusInit.Dir_Polarity = VA_MODBUS_POLARITY_LOW;
	ModbusInit.WaitSlave	= 300;
	ModbusInit.CountRepeat	= 3;
	Modbus1.Init(&ModbusInit, ModbusRegime::Slave, &htim7);
	Modbus1.SetBaudRate(Memory[eMemory::BaudRateCOM1].U*100);
	Modbus1.SetParity((UART_Parity)Memory[eMemory::ParityCOM1].U);

	ModbusInit.huart		= &huart1;   // 9600 Odd 1stop
	ModbusInit.Dir_Port		= DIR1_GPIO_Port;
	ModbusInit.Dir_Pin		= DIR1_Pin;
	Modbus2.Init(&ModbusInit, ModbusRegime::Master);
	Modbus2.SetBaudRate(9600);
	Modbus2.SetParity(UART_Parity::Odd);

	sSettZVU.addElement(&sZVU.regime);
	sSettZVU.addElement(&sZVU.condition);
	sSettZVU.addElement(&sZVU.selectedRegime);

	for (uint8_t i = 0; i < sizeof(sZVU.selectedCondition)/sizeof(sZVU.selectedCondition[0]); i++) {
		sSettZVU.addElement(&sZVU.selectedCondition[i]);
	}

	EventInit();
	DCXJ.Enable = false;
}

void LoopTask(void *argument) {

	while(true) {
		Memory[rMemory::VoltageB118].U = sZVU.OutputVoltage;
		Memory[rMemory::CurrentB118].U = sZVU.OutputCurrent;
		Memory[rMemory::Crash].U = !Global.indCrash.state;
		sBatteryControl.Max = Memory[eMemory::N_SectionDCXJ].U;

		bool state = true;		// состояние индикатора на глобале
		bool errCon = false;	// ошибка по связи
		bool errWarn = false;	// предупредительная авария
		bool errZVU = false;

		for(uint16_t i = 0; i < BaseDevice::Devices.size(); i++) {
			if(BaseDevice::Devices[i]->ErrorConnection) {
				sCrash.addCrash((NumberCrash)(11 + i));
				state = false;
				errCon = true;
			}
			else {
				sCrash.delCrash((NumberCrash)(11 + i));
			}
		}

		for(uint16_t i = 0; i < 2; i++) {
			if(B118[i].Mem.State.Crash || B118[i].Mem.State.Protect) {
				sCrash.addCrash((NumberCrash)(91 + i));
				state = false;
				errZVU = true;
			}
			else {
				sCrash.delCrash((NumberCrash)(91 + i));
			}
		}
		if(!CrashBattery) 	{
			sCrash.addCrash(NumberCrash::BatteryCrash);
			state = false;
		}
		else sCrash.delCrash(NumberCrash::BatteryCrash);

		if (exch) {
			uint16_t* status = (uint16_t*)&AnalogBl.Mem.sAnalogIO;
			if((*status) & (1 << (0))){
				sCrash.addCrash(NumberCrash::CrashO1);
				state = false;
			}
			else {
				sCrash.delCrash(NumberCrash::CrashO1);
			}
			if((*status) & (1 << (1))){
				sCrash.addCrash(NumberCrash::CrashO2);
				state = false;
			}
			else {
				sCrash.delCrash(NumberCrash::CrashO2);
			}
	//		if((*status) & (1 << (2))){
	//			sCrash.addCrash(NumberCrash::CrashO3);
	//			state = false;
	//		}
	//		else {
	//			sCrash.delCrash(NumberCrash::CrashO3);
	//		}
			if((*status) & (1 << (3))){
				sCrash.addCrash(NumberCrash::CrashO4);
				state = false;
			}
			else {
				sCrash.delCrash(NumberCrash::CrashO4);
			}
			if((*status) & (1 << (4))){
				sCrash.addCrash(NumberCrash::CrashO5);
				state = false;
			}
			else {
				sCrash.delCrash(NumberCrash::CrashO5);
			}
			if((*status) & (1 << (5))){
				sCrash.addCrash(NumberCrash::CrashO6);
				state = false;
			}
			else {
				sCrash.delCrash(NumberCrash::CrashO6);
			}
	//		if((*status) & (1 << (6))){
	//			sCrash.addCrash(NumberCrash::CrashO7);
	//			state = false;
	//		}
	//		else {
	//			sCrash.delCrash(NumberCrash::CrashO7);
	//		}

	//-------------------------------------------------------//
	//		if((*status) & (1 << (8))){
	//			sCrash.addCrash(NumberCrash::CrashI1);
	//			state = false;
	//		}
	//		else {
	//			sCrash.delCrash(NumberCrash::CrashI1);
	//		}
			if((*status) & (1 << (9))){
				sCrash.addCrash(NumberCrash::CrashI2);
				state = false;
			}
			else sCrash.delCrash(NumberCrash::CrashI2);

	//		if((*status) & (1 << (10))){
	//			sCrash.addCrash(NumberCrash::CrashI3);
	//			state = false;
	//		}
	//		else sCrash.delCrash(NumberCrash::CrashI3);

			if((*status) & (1 << (11))){
				sCrash.addCrash(NumberCrash::CrashI4);
				state = false;
			}
			else sCrash.delCrash(NumberCrash::CrashI4);

			if((*status) & (1 << (12))){
				sCrash.addCrash(NumberCrash::CrashI5);
				state = false;
			}
			else sCrash.delCrash(NumberCrash::CrashI5);

			if((*status) & (1 << (13))){
				sCrash.addCrash(NumberCrash::CrashI6);
				state = false;
			}
			else sCrash.delCrash(NumberCrash::CrashI6);

			if((*status) & (1 << (14))){
				sCrash.addCrash(NumberCrash::CrashI7);
				state = false;
			}
			else sCrash.delCrash(NumberCrash::CrashI7);

			if(!BKI.ErrorConnection) {
				if((BKI.Mem.R1Minus < Memory[eMemory::warnInsulation].U || BKI.Mem.R1Minus < Memory[eMemory::warnInsulation].U)
						&& Memory[eMemory::warnInsulation].U != 0 ){
					sCrash.addCrash(NumberCrash::WarnInsul);
					state = false;
					errWarn = true;
				}
				else sCrash.delCrash(NumberCrash::WarnInsul);

				if(HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin)) {
					sCrash.addCrash(NumberCrash::CrashInsul);
					state = false;
				}
				else sCrash.delCrash(NumberCrash::CrashInsul);
			}
			else {
				sCrash.delCrash(NumberCrash::WarnInsul);
				sCrash.delCrash(NumberCrash::CrashInsul);
			}

			if(!AnalogBl.ErrorConnection) {
		// ---- Предупредительные аварии
				if(( AnalogBl.Mem.AI2 < Memory[eMemory::MinSetWarnEC1].U*10 ||
						AnalogBl.Mem.AI2 > Memory[eMemory::MaxSetWarnEC1].U*10)
						&& (Memory[eMemory::MinSetWarnEC1].U || Memory[eMemory::MaxSetWarnEC1].U) != 0){
					sCrash.addCrash(NumberCrash::WarnEC1);
					state = false;
					errWarn = true;
				}
				else sCrash.delCrash(NumberCrash::WarnEC1);
				//--------------------------------------------------------------
				if(( AnalogBl.Mem.AI11 < Memory[eMemory::MinSetWarnEC2].U*10 ||
						AnalogBl.Mem.AI11 > Memory[eMemory::MaxSetWarnEC2].U*10)
						&& (Memory[eMemory::MinSetWarnEC2].U || Memory[eMemory::MaxSetWarnEC2].U) != 0){
					sCrash.addCrash(NumberCrash::WarnEC2);
					state = false;
					errWarn = true;
				}
				else sCrash.delCrash(NumberCrash::WarnEC2);
				//--------------------------------------------------------------

				if( AnalogBl.Mem.AI12 < Memory[eMemory::MinSetWarnAB].U*10
						&& Memory[eMemory::MinSetWarnAB].U != 0){
					sCrash.addCrash(NumberCrash::WarnAB);
					state = false;
					errWarn = true;
				}
				else sCrash.delCrash(NumberCrash::WarnAB);


				uint16_t * status = (uint16_t *)&AnalogBl.Mem.sAnalogIO;
				WriteBuf_t temp;
				temp.Adress = AnalogBl.Adress;
				temp.AdrReg = 24;
				temp.Value  = *status;
				if(!(*status & (1 << 3)) && errZVU){
					*status |= (1 << 3);
					temp.Value  = *status;
					write(temp);
				}
				else if ((*status & (1 << 3)) && !errZVU ) {
					*status &= ~(1 << 3);
					temp.Value  = *status;
					write(temp);
				}
	//			if((*status & (1 << 2)) && !CrashBattery){
	//				*status &= ~(1 << 2);
	//				temp.Value  = *status;
	//				write(temp);
	//			}
	//			else if (!(*status & (1 << 2)) && CrashBattery ) {
	//				*status |= (1 << 2);
	//				temp.Value  = *status;
	//				write(temp);
	//			}

			}
			else {
				sCrash.delCrash(NumberCrash::WarnEC1);
				sCrash.delCrash(NumberCrash::WarnEC2);
				sCrash.delCrash(NumberCrash::WarnAB);
			}
		}
		Global.indCrash.state = state;
		if (HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin) || !HAL_GPIO_ReadPin(OUT2_GPIO_Port,OUT2_Pin)){
			errWarn = true;
		}


		HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, errWarn ? GPIO_PIN_SET : GPIO_PIN_RESET);	//Предупредительная авария
		HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, errCon ? GPIO_PIN_RESET : GPIO_PIN_SET);	//Система управления не в норме


		taskYIELD();
		osDelay(50);
	}

}

void ExchangeTask(void *argument) {

	while(true) {
		for(uint16_t i = 0; i < BaseDevice::Devices.size(); i++) {
			for(uint16_t n = 0; n < BaseDevice::Devices[i]->Exchange.size(); n++) {
				if(BaseDevice::Devices[i]->Enable) {
					BaseDevice::Devices[i]->ErrorConnection = !Modbus2.ReadsHoldingRegisters(
						BaseDevice::Devices[i]->Adress, BaseDevice::Devices[i]->Exchange[n].FirstReg,
						BaseDevice::Devices[i]->Exchange[n].NReg, BaseDevice::Devices[i]->Exchange[n].pBuff);

					if(BaseDevice::Devices[i] == &BKI){
						if(!BaseDevice::Devices[i]->ErrorConnection)
						{
							sContrlInsulation.Max = BKI.Mem.Nfider;
							if(n == 0) sMain.bki.state = true;
							sMain.bki.state = !sMain.bki.state;
						}
						else {
							sMain.bki.state = false;
						}
					}
					osDelay(300);
				}
			else { BaseDevice::Devices[i]->ErrorConnection = false; }

				if(BaseDevice::Devices[i]->ErrorConnection || !BaseDevice::Devices[i]->Enable) {
					memset(BaseDevice::Devices[i]->Exchange[n].pBuff, 0, BaseDevice::Devices[i]->Exchange[n].NReg*2);
				}
			}
		}
		exch = true;
		WriteBuf_t temp;
		for(uint16_t n = 0; n < 2; n++) {
			if(B118[n].Enable && !B118[n].ErrorConnection) {
				if(B118[n].Mem.State.State != *B118[n].pPusk) {
					temp.Adress = B118[n].Adress;
					temp.AdrReg = 5;
					temp.Value  = *B118[n].pPusk;
					write(temp);
				}
				if(abs(B118[n].Mem.Uout - B118[n].pSettings[*B118[n].pRegime]->Uset) > 10){
					temp.Adress = B118[n].Adress;
					temp.AdrReg = 0;
					temp.Value  = B118[n].pSettings[*B118[n].pRegime]->Uset;
					write(temp);
				}
			}
		}

	uint64_t* ptr = (uint64_t*)&DCXJ.Mem.sCellBattery;
	CrashBattery = true;
	for(uint16_t i = 0; i < 60; i++) {
		if(DCXJ.Enable && DCXJ.ErrorConnection == false) {
			if(i >= sBatteryControl.Max) break;
			if (Memory[eMemory::SettingBatteryDCXJ].U != 0){
				if(abs((int)(Memory[eMemory::SettingBatteryDCXJ].U - DCXJ.Mem.cellVoltage[i]))
					> Memory[eMemory::ToleranceBatteryDCXJ].U) {
				(*ptr) &= ~(1 << i);
				CrashBattery = false;
				}
				else {
					(*ptr) |= (1 << i);
				}
			}

		}
		else break;
	}

		while(osMessageQueueGetCount(WriteBufHandle)) {
			osMessageQueueGet(WriteBufHandle, &temp, NULL, 5);
			if(Modbus2.WriteHoldingRegister(temp.Adress, temp.AdrReg, temp.Value)) {
				osDelay(300);
			}
		}
	}
}

void write(WriteBuf_t temp) {

	osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
}

void ShowDefault(void *argument) {

	while(true) {
		osDelay(5);
		Screens.Touched();
		Screens.Global.Loop();

		if(Screens.GetPtrCurrentScreen() != &sZVU) {
			sZVU.Loop();
		}
		Screens.ShowScreen();
		HAL_IWDG_Refresh(&hiwdg);
	}
}

void EEPROMTask(void *argument) {

	Setup();
	while(true) {
		eeprom.Update();
		taskYIELD();
		osDelay(5);
	}

}
void EraseEvent(void) {
	eeprom.Writes(198, 2, Buf);
	eeprom.Writes(FIRST_REG_EVENT, MAX_COUNT_EVENT * COUNT_REG_EVENT, Buf);
}

void SleepTFT(void *argument) {
	Screens.Sleep();
}

void VA_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	Modbus1.Modbus_TxCpltCallback(huart);
	Modbus2.Modbus_TxCpltCallback(huart);
}

void VA_USART_IRQHandler(UART_HandleTypeDef *huart) {
	Modbus1.Modbus_IRQHandler(huart);
	Modbus2.Modbus_IRQHandler(huart);
}
