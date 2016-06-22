#ifndef CONTROLE_XINPUT_H
#define CONTROLE_XINPUT_H
#include "include/xinput.h"
//Adicionar C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libxinput1_2.a nos parâmetros do linker
#include <limits.h>
class Controle_XINPUT {
	int _numerocontrole;
	int _resultadoconexao;
	XINPUT_STATE _estadocontrole;
	XINPUT_BATTERY_INFORMATION _estadobateria;
	public:
		Controle_XINPUT(int numerocontrole);
		~Controle_XINPUT();
		int NumeroControle();
		XINPUT_STATE GetState();
		bool IsConnected();
		void Vibrar(int Left=0, int Right=0);
		XINPUT_GAMEPAD GetGamepadState();
		int EstadoBotoes();
		
		//Este método precisa da versão 1.4 da libxinput.a. Vide https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputgetbatteryinformation(v=vs.85).aspx
		int EstadoBateria();
		
		//Esses três métodos são apenas para remover a deadzone da visualização na tela
		int EstadoThumb(short sThumb, int _DEADZONE)
		{
			if(sThumb>_DEADZONE
				||sThumb<-_DEADZONE)
				return sThumb;
			else
				return 0;
		}
		int EstadoThumbL(bool IsX)
		{
			short _sThumbL;
			if(IsX)
				_sThumbL = _estadocontrole.Gamepad.sThumbLX;
			else
				_sThumbL = _estadocontrole.Gamepad.sThumbLY;
			return EstadoThumb(_sThumbL,XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		int EstadoThumbR(bool IsX)
		{
			short _sThumbR;
			if(IsX)
				_sThumbR = _estadocontrole.Gamepad.sThumbRX;
			else
				_sThumbR = _estadocontrole.Gamepad.sThumbRY;
			return EstadoThumb(_sThumbR,XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
};
Controle_XINPUT::Controle_XINPUT(int numerocontrole)
{
	_numerocontrole=numerocontrole-1;
}
Controle_XINPUT::~Controle_XINPUT()
{
}
int Controle_XINPUT::NumeroControle()
{
	return _numerocontrole+1;
}
XINPUT_STATE Controle_XINPUT::GetState()
{
	ZeroMemory(&_estadocontrole,sizeof(XINPUT_STATE));
	
	_resultadoconexao = XInputGetState(_numerocontrole,&_estadocontrole);
	/*
	No caso de programas como ScpDriver, que emulam o controle de PS3 como de XBox 360, estes armazenam uma lista dos 4 últimos controles conectados, o que engana o XInput,
	fazendo-o acreditar que os controles ainda estão conectados (retornando ERROR_SUCCESS para _resultadoconexao)
	*/
	
	return _estadocontrole;
}
bool Controle_XINPUT::IsConnected()
{
	return (_resultadoconexao==ERROR_SUCCESS);
}
void Controle_XINPUT::Vibrar(int Left, int Right)
{
	XINPUT_VIBRATION Vibration;
	ZeroMemory(&Vibration,sizeof(XINPUT_VIBRATION));
	Vibration.wLeftMotorSpeed=Left;
	Vibration.wRightMotorSpeed=Right;
	XInputSetState(_numerocontrole,&Vibration);
}
XINPUT_GAMEPAD Controle_XINPUT::GetGamepadState()
{
	return _estadocontrole.Gamepad;
}
int Controle_XINPUT::EstadoBotoes()
{
	return GetGamepadState().wButtons;
}
int Controle_XINPUT::EstadoBateria()
{
	XInputGetBatteryInformation(_numerocontrole,BATTERY_DEVTYPE_GAMEPAD,&_estadobateria);
	return _estadobateria.BatteryLevel;
}
#endif
