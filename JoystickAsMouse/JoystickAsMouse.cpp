#include <windows.h>
#include <iostream>
#include "xinput.h"//poderia ser <xinput.h>, mas eu achei melhor deixar .h e .a na pasta do executável
using namespace std;

XINPUT_STATE estado_controle;
int mascaraDPAD=(XINPUT_GAMEPAD_DPAD_UP|XINPUT_GAMEPAD_DPAD_DOWN|XINPUT_GAMEPAD_DPAD_LEFT|XINPUT_GAMEPAD_DPAD_RIGHT);
int mascaraBotoes=(XINPUT_GAMEPAD_A|XINPUT_GAMEPAD_B|XINPUT_GAMEPAD_X|XINPUT_GAMEPAD_Y);
INPUT in_mouse;
INPUT in_keyboard;
size_t in_size=sizeof(INPUT);
bool LButtonPressed=false;
bool RButtonPressed=false;
bool ESCPressed=false;
bool BackPressed=false;

#define TAXA_MOV_MOUSE	50

int EstadoDPAD()
{
	return estado_controle.Gamepad.wButtons&mascaraDPAD;
}
int EstadoBotoes()
{
	return estado_controle.Gamepad.wButtons&mascaraBotoes;
}
int EstadoThumbLX()
{
	if(estado_controle.Gamepad.sThumbLX>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		||estado_controle.Gamepad.sThumbLX<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return estado_controle.Gamepad.sThumbLX;
	else
		return 0;
}
int EstadoThumbLY()
{
	if(estado_controle.Gamepad.sThumbLY>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		||estado_controle.Gamepad.sThumbLY<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return estado_controle.Gamepad.sThumbLY;
	else
		return 0;
}
int EstadoThumbRX()
{
	if(estado_controle.Gamepad.sThumbRX>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		||estado_controle.Gamepad.sThumbRX<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return estado_controle.Gamepad.sThumbRX;
	else
		return 0;
}
int EstadoThumbRY()
{
	if(estado_controle.Gamepad.sThumbRY>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		||estado_controle.Gamepad.sThumbRY<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return estado_controle.Gamepad.sThumbRY;
	else
		return 0;
}

void BASE_SendInput(INPUT _in)
{
	SendInput(1,&_in,in_size);
}
void BASE_SendInputKeyboard(int _VKey, int _KEYEVENTF)
{
	ZeroMemory(&in_keyboard,in_size);
	in_keyboard.type = INPUT_KEYBOARD;
	in_keyboard.ki.wScan=0;
	in_keyboard.ki.time=0;
	in_keyboard.ki.dwExtraInfo=0;
	in_keyboard.ki.wVk=_VKey;
	in_keyboard.ki.dwFlags=_KEYEVENTF;
	BASE_SendInput(in_keyboard);
}
void BASE_SendInputMouse(int _MOUSEEVENTF, int _dx, int _dy, int _mouseData)
{
	ZeroMemory(&in_mouse,in_size);
	in_mouse.type  = INPUT_MOUSE;
	in_mouse.mi.dwFlags = _MOUSEEVENTF;
	in_mouse.mi.dx = _dx;
	in_mouse.mi.dy = _dy;
	in_mouse.mi.mouseData=_mouseData;
	BASE_SendInput(in_mouse);
}
void BASE_SendInputKeyboardKey(int _VKey, bool &_KeyPressed, bool _KeyValue, int _KEYEVENTF)
{
	//https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/
	_KeyPressed=_KeyValue;
	BASE_SendInputKeyboard(_VKey,_KEYEVENTF);
}
void BASE_SendInputMouseButton(bool &_ButtonPressed, bool _ButtonValue, int _MOUSEEVENTF)
{
	//http://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application
	_ButtonPressed=_ButtonValue;
	BASE_SendInputMouse(_MOUSEEVENTF,0,0,0);
}
bool BASE_PressKey(int _VKey, bool &_KeyPressed)
{
	if(GetKeyState(_VKey)&0x80)
	{
		_KeyPressed=true;
	}
	else
	{
		if(_KeyPressed)
		{
			_KeyPressed=false;
			return true;
		}
		_KeyPressed=false;
	}
	return false;
}
bool BASE_ConverteClickGamepadtoKeyboardKey(int _XINPUT_MASK, int _VKey, bool &_KeyPressed)
{
	if(estado_controle.Gamepad.wButtons&_XINPUT_MASK)
	{
		BASE_SendInputKeyboardKey(_VKey,_KeyPressed,true,0);
	}
	else
	{
		if(_KeyPressed)
		{
			BASE_SendInputKeyboardKey(_VKey,_KeyPressed,false,KEYEVENTF_KEYUP);
			return true;
		}
		_KeyPressed=false;
	}
	return false;
}
bool BASE_ConverteClickGamepadtoMouseClick(int _XINPUT_MASK,bool &_ButtonPressed, int _MOUSEEVENTF_DOWN, int _MOUSEEVENTF_UP)
{
	if(estado_controle.Gamepad.wButtons&_XINPUT_MASK)
	{
		BASE_SendInputMouseButton(_ButtonPressed,true,_MOUSEEVENTF_DOWN);
	}
	else
	{
		if(_ButtonPressed)
		{
			BASE_SendInputMouseButton(_ButtonPressed,false,_MOUSEEVENTF_UP);
			return true;
		}
		_ButtonPressed=false;
	}
	return false;
}

bool CheckESC()
{
	return BASE_PressKey(VK_ESCAPE,ESCPressed);
}
bool CheckGamepadBack()
{
	return BASE_ConverteClickGamepadtoKeyboardKey(XINPUT_GAMEPAD_BACK,VK_ESCAPE,ESCPressed);
}
bool CheckBack()
{
	return BASE_ConverteClickGamepadtoKeyboardKey(XINPUT_GAMEPAD_B,VK_BACK,BackPressed);
}
bool CheckLeftClick()
{
	return BASE_ConverteClickGamepadtoMouseClick(XINPUT_GAMEPAD_A,LButtonPressed,MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_LEFTUP);
}
bool CheckRightClick()
{
	return BASE_ConverteClickGamepadtoMouseClick(XINPUT_GAMEPAD_Y,RButtonPressed,MOUSEEVENTF_RIGHTDOWN,MOUSEEVENTF_RIGHTUP);
}
//#include <math.h>
//double RetornaValorLogaritmico(int valor, int base,int minimo=0)
//{
//	double retorno;
//	if(valor>0)
//	{
//		cout<<valor-minimo<<endl;
//		retorno = (log((double)(valor-minimo))/log((double)base));
//	}
//	else if(valor==0)
//	{
//		
//		retorno = 0;
//	}
//	else
//	{
//		cout<<-valor+minimo<<endl;
//		retorno = -(log((double)(-valor+minimo))/log((double)base));
//	}
//	cout<<retorno<<endl;
//	return retorno;
//}

void MoverMouse()
{
	int lx=EstadoThumbLX();
	int ly=EstadoThumbLY();
	
	if(lx>0)
		lx-=XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	else if(lx<0)
		lx+=XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	if(ly>0)
		ly-=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	else if(ly<0)
		ly+=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	
	int dx=(lx/(double)SHRT_MAX)*TAXA_MOV_MOUSE;
	int dy=-(ly/(double)SHRT_MAX)*TAXA_MOV_MOUSE;
	
	BASE_SendInputMouse(MOUSEEVENTF_MOVE,dx,dy,0);
}
void Rolar()
{
	int ry=EstadoThumbRY();
	
	if(ry>0)
		ry-=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	else if(ry<0)
		ry+=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	
	//https://social.msdn.microsoft.com/Forums/vstudio/en-US/ad2d3e85-7527-49dc-ac1c-a2b031b119ba/how-can-i-simulate-the-scroll-mouse?forum=vcgeneral
	int dy=(ry/(double)SHRT_MAX)*120;
	
	BASE_SendInputMouse(MOUSEEVENTF_WHEEL,0,0,dy);
}
void ChecarJoystick()
{
	CheckLeftClick();
	CheckRightClick();
	CheckBack();
	MoverMouse();
	Rolar();
}
int main()
{
	while(!CheckGamepadBack()&&!CheckESC())
	{
		XInputGetState(0,&estado_controle);
//		std::cout<<estado_controle.dwPacketNumber<<std::endl;
		ChecarJoystick();
		Sleep(50);
	}
	return 0;
}
