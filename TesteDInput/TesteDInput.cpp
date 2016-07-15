//#include "include/graphics.h"
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "joystick.h"
#define ESC 27
bool sair=false;
int largura=800;
int altura=600;
int pg=1;
Joystick* controle_atual;
DIJOYSTATE2* estado;

//int raio=20;
#define MAX_NUM_JOYSTICK	4
using namespace std;
//int initJoysticks (Joystick *joy[],int joy_vec_size);
//void printJoystick ();

char* ConvertInt(int &i)
{
	char retorno[6];
//	memset(retorno,0,sizeof(i));
	itoa(i,retorno,10);
	return retorno;
}
char* ConvertInt(long &l)
{
	char retorno[10];
	ltoa(l,retorno,10);
	return retorno;
}
char* ConvertInt(unsigned int &i)
{
	char retorno[10];
	itoa(i,retorno,10);
	return retorno;
}
char* ConvertInt(BYTE &b)
{
	char retorno[10];
	itoa(b,retorno,10);
	return retorno;
}

int initJoysticks (Joystick *joy[],int joy_vec_size)
{
	int num_joy;
	
	if(!(num_joy =Joystick::deviceCount())){
		std::cout << "<WARNIG> No joysticks connected!" << std::endl;
		return 0;	
	}
	
	std::cout << "<TRACE> "<< '[' << num_joy << ']' << " joystick(s) founded." << std::endl; 
	
	// Garante que mesmo que encontre mais controles, iniciará o máximo suportado nesse demo
	num_joy = (num_joy > joy_vec_size) ? joy_vec_size:num_joy;
	
	// Inicializa todos os joysticks encontrados
	for (int i =0; i < num_joy; ++i){
		
		try{
			joy[i] = new Joystick(i);
		}
		catch (std::bad_alloc& ba){
			std::cerr << "<ERROR> bad_alloc on [initJoysticks]" << ba.what() << std::endl;
			return 0;
		}
		
		joy[i]->init();
	}
	
	return num_joy;
}
void printJoystick ()
{
	controle_atual->LeDados();
//	joy->LeDados();
//	estado=&joy->state;
	int x_index=100,y_index=40,y_inc=18;
	
	int x2_index=200,y2_index=y_index,x2_inc=10,y2_inc=y_inc;
	int dados_linha=5,offset=(largura-200)/dados_linha;
	outtextxy(x2_index,y2_index,"rgbButtons: ");//0: A, 1: B, 2: X, 3: Y, 4: L1, 5: R1, 6: SELECT, 7: START, 8: L3, 9: R3
	y_index+=y_inc;
	for(unsigned int n=0;n<128;n++)
	{
		outtextxy(x2_index+(n%dados_linha)*offset,y_index+(n/dados_linha)*y_inc,"B");
		outtextxy(x2_index+x2_inc+(n%dados_linha)*offset,y_index+(n/dados_linha)*y_inc,ConvertInt(n));
		outtextxy(x2_index+(4*x2_inc)+(n%dados_linha)*offset,y_index+(n/dados_linha)*y_inc,ConvertInt(estado->rgbButtons[n]));
	}
	
	outtextxy(0,y_index,"lX");
	outtextxy(x_index,y_index,ConvertInt(estado->lX));
	y_index+=y_inc;
	outtextxy(0,y_index,"lY");
	outtextxy(x_index,y_index,ConvertInt(estado->lY));
	y_index+=y_inc;
	outtextxy(0,y_index,"lZ");
	outtextxy(x_index,y_index,ConvertInt(estado->lZ));
	y_index+=y_inc;
	outtextxy(0,y_index,"lRx");
	outtextxy(x_index,y_index,ConvertInt(estado->lRx));
	y_index+=y_inc;
	outtextxy(0,y_index,"lRy");
	outtextxy(x_index,y_index,ConvertInt(estado->lRy));
	y_index+=y_inc;
	outtextxy(0,y_index,"lRz");
	outtextxy(x_index,y_index,ConvertInt(estado->lRz));
	y_index+=y_inc;
	
	outtextxy(0,y_index,"rglSlider");
	outtextxy(x_index,y_index,ConvertInt(estado->rglSlider[0]));
	outtextxy(x_index+50,y_index,ConvertInt(estado->rglSlider[1]));
	y_index+=y_inc;
	
	char buf_dword[4];
	outtextxy(0,y_index,"rgdwPOV");
	itoa((int&)estado->rgdwPOV[0],buf_dword,10);//DPAD no controle. Indica 100x o grau do DPAD (up=0°, etc.), e -1 se nenhuma tecla estiver pressionada
	outtextxy(x_index,y_index,buf_dword);
//	outtextxy(x_index,y_index,ConvertInt((int&)estado->rgdwPOV[0]));
	itoa((int&)estado->rgdwPOV[1],buf_dword,10);
	outtextxy(x_index+50,y_index,buf_dword);
//	outtextxy(x_index+50,y_index,ConvertInt((int&)estado->rgdwPOV[1]));
	y_index+=y_inc;
	itoa((int&)estado->rgdwPOV[2],buf_dword,10);
	outtextxy(x_index,y_index,buf_dword);
//	outtextxy(x_index,y_index,ConvertInt((int&)estado->rgdwPOV[2]));
	itoa((int&)estado->rgdwPOV[3],buf_dword,10);
	outtextxy(x_index+50,y_index,buf_dword);
//	outtextxy(x_index+50,y_index,ConvertInt((int&)estado->rgdwPOV[3]));
	y_index+=y_inc;
	
	outtextxy(0,y_index,"lVX");
	outtextxy(x_index,y_index,ConvertInt(estado->lVX));
	y_index+=y_inc;
	outtextxy(0,y_index,"lVY");
	outtextxy(x_index,y_index,ConvertInt(estado->lVY));
	y_index+=y_inc;
	outtextxy(0,y_index,"lVZ");
	outtextxy(x_index,y_index,ConvertInt(estado->lVZ));
	y_index+=y_inc;
	outtextxy(0,y_index,"lVRx");
	outtextxy(x_index,y_index,ConvertInt(estado->lVRx));
	y_index+=y_inc;
	outtextxy(0,y_index,"lVRy");
	outtextxy(x_index,y_index,ConvertInt(estado->lVRy));
	y_index+=y_inc;
	outtextxy(0,y_index,"lVRz");
	outtextxy(x_index,y_index,ConvertInt(estado->lVRz));
	y_index+=y_inc;
	
	outtextxy(0,y_index,"rglVSlider");
	outtextxy(x_index,y_index,ConvertInt(estado->rglVSlider[0]));
	outtextxy(x_index+50,y_index,ConvertInt(estado->rglVSlider[1]));
	y_index+=y_inc;

	outtextxy(0,y_index,"lAX");
	outtextxy(x_index,y_index,ConvertInt(estado->lAX));
	y_index+=y_inc;
	outtextxy(0,y_index,"lAY");
	outtextxy(x_index,y_index,ConvertInt(estado->lAY));
	y_index+=y_inc;
	outtextxy(0,y_index,"lAZ");
	outtextxy(x_index,y_index,ConvertInt(estado->lAZ));
	y_index+=y_inc;
	outtextxy(0,y_index,"lARx");
	outtextxy(x_index,y_index,ConvertInt(estado->lARx));
	y_index+=y_inc;
	outtextxy(0,y_index,"lARy");
	outtextxy(x_index,y_index,ConvertInt(estado->lARy));
	y_index+=y_inc;
	outtextxy(0,y_index,"lARz");
	outtextxy(x_index,y_index,ConvertInt(estado->lARz));
	y_index+=y_inc;
	
	outtextxy(0,y_index,"rglASlider");
	outtextxy(x_index,y_index,ConvertInt(estado->rglASlider[0]));
	outtextxy(x_index+50,y_index,ConvertInt(estado->rglASlider[1]));
	y_index+=y_inc;

	outtextxy(0,y_index,"lFX");
	outtextxy(x_index,y_index,ConvertInt(estado->lFX));
	y_index+=y_inc;
	outtextxy(0,y_index,"lFY");
	outtextxy(x_index,y_index,ConvertInt(estado->lFY));
	y_index+=y_inc;
	outtextxy(0,y_index,"lFZ");
	outtextxy(x_index,y_index,ConvertInt(estado->lFZ));
	y_index+=y_inc;
	outtextxy(0,y_index,"lFRx");
	outtextxy(x_index,y_index,ConvertInt(estado->lFRx));
	y_index+=y_inc;
	outtextxy(0,y_index,"lFRy");
	outtextxy(x_index,y_index,ConvertInt(estado->lFRy));
	y_index+=y_inc;
	outtextxy(0,y_index,"lFRz");
	outtextxy(x_index,y_index,ConvertInt(estado->lFRz));
	y_index+=y_inc;
	
	outtextxy(0,y_index,"rglFSlider");
	outtextxy(x_index,y_index,ConvertInt(estado->rglFSlider[0]));
	outtextxy(x_index+50,y_index,ConvertInt(estado->rglFSlider[1]));
	y_index+=y_inc;

//	estado=0x0;
}
int main()
{
	Joystick* controles[MAX_NUM_JOYSTICK];
	memset(controles,0,sizeof(*controles[MAX_NUM_JOYSTICK]));
	int qtd_controles = initJoysticks(controles,MAX_NUM_JOYSTICK);
	if(!qtd_controles)
	{
		cout<<"Pressione Enter para sair."<<endl;
		while(!cin.get());
	}
	else
	{
		initwindow(largura,altura,"Teste DINPUT",(getmaxwidth()-largura)/2,(getmaxheight()-altura)/2);
		int id_atual=0;
		char buf_qtd[40];
//		strcpy(buf_qtd,"Quantidade de controles: ");
		itoa(qtd_controles,buf_qtd,10);
		controle_atual = controles[id_atual];
		estado=&controle_atual->state;
		while(!sair)
		{
			pg=(pg==1)?2:1;
			setactivepage(pg);
			
			cleardevice();
			outtextxy(0,0,"Quantidade de controles: ");
			outtextxy(200,0,buf_qtd);
			outtextxy(0,15,"Controle atual: ");
			char* tmp=ConvertInt(id_atual);
			outtextxy(130,15,tmp);
			
			printJoystick();
			
			setvisualpage(pg);
			if(GetKeyState(VK_ESCAPE)&0x80)
			{
				sair=true;
			}
			if(GetKeyState(VK_RIGHT)&0x80)
			{
				id_atual=(id_atual+1)%qtd_controles;
				controle_atual=controles[id_atual];
				estado=&controle_atual->state;
			}
			if(GetKeyState(VK_LEFT)&0x80)
			{
				id_atual=(id_atual-1+qtd_controles)%qtd_controles;
				controle_atual=controles[id_atual];
				estado=&controle_atual->state;
			}
			delay(50);
		}
		estado=0x0;
		controle_atual=0x0;
		closegraph();
//		for(int joynum = 0; joynum < MAX_NUM_JOYSTICK; ++joynum){
//			if(controles[joynum] != NULL)
//				delete controles[joynum];
//		}
	}
	return 0;
}
