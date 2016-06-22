#include "include/graphics.h"
#include <stdlib.h>
#include <iostream>
#include "controle_xinput.h"

#define MASK_KEYDOWN 	(0x80)
#define RAIO			(10)
#define DIAMETRO		(2*RAIO)

struct TImagem
{
	void* bmp;
	void* mask;
	void CarregarImagens(int left, int top, int right, int bottom, char caminho_mask[50], char caminho_bitmap[50])
	{
		int tamanho=imagesize(left,top,right,bottom);
		
		readimagefile(caminho_mask,left,top,right,bottom);
		mask=malloc(tamanho);
		getimage(left,top,right,bottom,mask);
		
		readimagefile(caminho_bitmap,left,top,right,bottom);
		bmp=malloc(tamanho);
		getimage(left,top,right,bottom,bmp);
	}
	void Desenhar(int x, int y)
	{
		putimage(x,y,mask,AND_PUT);
		putimage(x,y,bmp,OR_PUT);
	}
};
struct TPosicao
{
	int x;
	int y;
};
int largura=500;
int altura=500;
int quarto_largura=largura/4;
int pg=1;
char buf_int[11];
HWND Window;
bool F1Pressed=false;
bool F2Pressed=false;
bool F3Pressed=false;
bool F4Pressed=false;

TPosicao pos_up;
TPosicao pos_down;
TPosicao pos_left;
TPosicao pos_right;

TPosicao pos_A;
TPosicao pos_B;
TPosicao pos_X;
TPosicao pos_Y;

TPosicao pos_back;
TPosicao pos_start;
TPosicao pos_L3;
TPosicao pos_R3;

TPosicao pos_LB;
TPosicao pos_RB;

TPosicao pos_LT;
TPosicao pos_RT;

using namespace std;

bool TeclaEstaPressionada(int Virtual_Key)
{
	return (GetKeyState(Virtual_Key)&MASK_KEYDOWN)>0&&GetForegroundWindow()==Window;
}
char* ConvertInt(int i)
{
	return itoa(i,buf_int,10);
}
void SetValoresPosicao(TPosicao &_pos, int x, int y)
{
	_pos.x=x;
	_pos.y=y;
}
void DesenharBola(TPosicao _pos)
{
	fillellipse(_pos.x,_pos.y,RAIO,RAIO);
}
int main()
{
	initwindow(largura,altura,"Teste Controles XINPUT",(getmaxwidth()-largura)/2,(getmaxheight()-altura)/2);
	TImagem imagem_controle;
	
	SetValoresPosicao(pos_LB,190,110);
	SetValoresPosicao(pos_up,190,130);
	SetValoresPosicao(pos_down,190,170);
	SetValoresPosicao(pos_left,170,150);
	SetValoresPosicao(pos_right,210,150);
	
	SetValoresPosicao(pos_RB,410,110);
	SetValoresPosicao(pos_Y,410,130);
	SetValoresPosicao(pos_A,410,170);
	SetValoresPosicao(pos_X,390,150);
	SetValoresPosicao(pos_B,430,150);
	
	SetValoresPosicao(pos_back,250,150);
	SetValoresPosicao(pos_L3,250,210);
	SetValoresPosicao(pos_start,350,150);
	SetValoresPosicao(pos_R3,350,210);
	
	Controle_XINPUT controle1=Controle_XINPUT(1);
	Controle_XINPUT controle2=Controle_XINPUT(2);
	Controle_XINPUT controle3=Controle_XINPUT(3);
	Controle_XINPUT controle4=Controle_XINPUT(4);
	Controle_XINPUT* controle_atual=&controle1;
	
	imagem_controle.CarregarImagens(120,80,479,319,"controle_xinput_m.bmp","controle_xinput_b.bmp");
//	Window=GetActiveWindow();
	Window=GetForegroundWindow();
	while(!TeclaEstaPressionada(VK_ESCAPE))
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		cleardevice();
		setfillstyle(SOLID_FILL,RED);
		imagem_controle.Desenhar(120,80);
		outtextxy(0,0,"Instruções:");
		outtextxy(0,20,"1 a 4: Seleciona o controle.");
		outtextxy(0,40,"F1: Vibrar Esquerda");
		outtextxy(0,60,"F2: Vibrar Direita");
		outtextxy(0,80,"F3: Vibrar Ambos");
		outtextxy(0,100,"F4: Parar Vibração");
		if(TeclaEstaPressionada('1'))
		{
			if(controle_atual!=&controle1)
			{
				controle_atual=&controle1;
			}
		}
		else if(TeclaEstaPressionada('2'))
		{
			if(controle_atual!=&controle2)
			{
				controle_atual=&controle2;
			}
		}
		else if(TeclaEstaPressionada('3'))
		{
			if(controle_atual!=&controle3)
			{
				controle_atual=&controle3;
			}
		}
		else if(TeclaEstaPressionada('4'))
		{
			if(controle_atual!=&controle4)
			{
				controle_atual=&controle4;
			}
		}
//		cout<<"X: "<<mousex()<<endl<<"Y: "<<mousey()<<endl<<endl;
		controle_atual->GetState();
		
		outtextxy(0,200,"Controle nº:");
		outtextxy(0,220,ConvertInt(controle_atual->NumeroControle()));
		
		outtextxy(0,250,"dwPacketNumber");
		outtextxy(0,270,ConvertInt(controle_atual->GetState().dwPacketNumber));
		
		outtextxy(0,300,"wButtons: ");
		outtextxy(0,320,ConvertInt(controle_atual->EstadoBotoes()));
		moveto(50,320);
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_DPAD_UP)
		{
			DesenharBola(pos_up);
			outtext("UP, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_DPAD_DOWN)
		{
			DesenharBola(pos_down);
			outtext("DOWN, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_DPAD_LEFT)
		{
			DesenharBola(pos_left);
			outtext("LEFT, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			DesenharBola(pos_right);
			outtext("RIGHT, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_A)
		{
			DesenharBola(pos_A);
			outtext("A, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_B)
		{
			DesenharBola(pos_B);
			outtext("B, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_X)
		{
			DesenharBola(pos_X);
			outtext("X, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_Y)
		{
			DesenharBola(pos_Y);
			outtext("Y, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_BACK)
		{
			DesenharBola(pos_back);
			outtext("BACK, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_START)
		{
			DesenharBola(pos_start);
			outtext("START, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_LEFT_THUMB)
		{
			DesenharBola(pos_L3);
			outtext("L3, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_RIGHT_THUMB)
		{
			DesenharBola(pos_R3);
			outtext("R3, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			DesenharBola(pos_LB);
			outtext("LB, ");
		}
		if(controle_atual->EstadoBotoes()&XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			DesenharBola(pos_RB);
			outtext("RB, ");
		}
		bar(pos_LB.x-RAIO,pos_LB.y-RAIO,pos_LB.x+RAIO,pos_LB.y-RAIO-(controle_atual->GetGamepadState().bLeftTrigger/(double)UCHAR_MAX)*2*DIAMETRO);
		bar(pos_RB.x-RAIO,pos_RB.y-RAIO,pos_RB.x+RAIO,pos_RB.y-RAIO-(controle_atual->GetGamepadState().bRightTrigger/(double)UCHAR_MAX)*2*DIAMETRO);
		
		if(controle_atual->GetGamepadState().sThumbLX>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			bar(pos_L3.x+RAIO,pos_L3.y-RAIO,pos_L3.x+RAIO+(controle_atual->GetGamepadState().sThumbLX/(double)SHRT_MAX)*2*DIAMETRO,pos_L3.y+RAIO);
		}
		else if(controle_atual->GetGamepadState().sThumbLX<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			bar(pos_L3.x-RAIO,pos_L3.y-RAIO,pos_L3.x-RAIO+(controle_atual->GetGamepadState().sThumbLX/(double)SHRT_MAX)*2*DIAMETRO,pos_L3.y+RAIO);
		}
		if(controle_atual->GetGamepadState().sThumbRX>XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			bar(pos_R3.x+RAIO,pos_R3.y-RAIO,pos_R3.x+RAIO+(controle_atual->GetGamepadState().sThumbRX/(double)SHRT_MAX)*2*DIAMETRO,pos_R3.y+RAIO);
		}
		else if(controle_atual->GetGamepadState().sThumbRX<-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			bar(pos_R3.x-RAIO,pos_R3.y-RAIO,pos_R3.x-RAIO+(controle_atual->GetGamepadState().sThumbRX/(double)SHRT_MAX)*2*DIAMETRO,pos_R3.y+RAIO);
		}
		
		if(controle_atual->GetGamepadState().sThumbLY>XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			bar(pos_L3.x-RAIO,pos_L3.y-RAIO,pos_L3.x+RAIO,pos_L3.y-RAIO-(controle_atual->GetGamepadState().sThumbLY/(double)SHRT_MAX)*2*DIAMETRO);
		}
		else if(controle_atual->GetGamepadState().sThumbLY<-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			bar(pos_L3.x-RAIO,pos_L3.y+RAIO,pos_L3.x+RAIO,pos_L3.y+RAIO-(controle_atual->GetGamepadState().sThumbLY/(double)SHRT_MAX)*2*DIAMETRO);
		}
		if(controle_atual->GetGamepadState().sThumbRY>XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			bar(pos_R3.x-RAIO,pos_R3.y-RAIO,pos_R3.x+RAIO,pos_R3.y-RAIO-(controle_atual->GetGamepadState().sThumbRY/(double)SHRT_MAX)*2*DIAMETRO);
		}
		else if(controle_atual->GetGamepadState().sThumbRY<-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			bar(pos_R3.x-RAIO,pos_R3.y+RAIO,pos_R3.x+RAIO,pos_R3.y+RAIO-(controle_atual->GetGamepadState().sThumbRY/(double)SHRT_MAX)*2*DIAMETRO);
		}
		
		outtextxy(0*quarto_largura,350,"bLeftTrigger: ");
		outtextxy(0*quarto_largura,370,ConvertInt(controle_atual->GetGamepadState().bLeftTrigger));
		
		outtextxy(1*quarto_largura,350,"bRightTrigger: ");
		outtextxy(1*quarto_largura,370,ConvertInt(controle_atual->GetGamepadState().bRightTrigger));
		
		outtextxy(0*quarto_largura,400,"sThumbLX: ");
		outtextxy(0*quarto_largura,420,ConvertInt(controle_atual->EstadoThumbL(true)));
		outtextxy(0*quarto_largura+quarto_largura/2,420,ConvertInt(controle_atual->GetGamepadState().sThumbLX));
		
		outtextxy(1*quarto_largura,400,"sThumbLY: ");
		outtextxy(1*quarto_largura,420,ConvertInt(controle_atual->EstadoThumbL(false)));
		outtextxy(1*quarto_largura+quarto_largura/2,420,ConvertInt(controle_atual->GetGamepadState().sThumbLY));
		
		outtextxy(2*quarto_largura,400,"sThumbRX: ");
		outtextxy(2*quarto_largura,420,ConvertInt(controle_atual->EstadoThumbR(true)));
		outtextxy(2*quarto_largura+quarto_largura/2,420,ConvertInt(controle_atual->GetGamepadState().sThumbRX));
		
		outtextxy(3*quarto_largura,400,"sThumbRY: ");
		outtextxy(3*quarto_largura,420,ConvertInt(controle_atual->EstadoThumbR(false)));
		outtextxy(3*quarto_largura+quarto_largura/2,420,ConvertInt(controle_atual->GetGamepadState().sThumbRY));
		
		outtextxy(0,450,"BatteryLevel: ");
		outtextxy(0,470,ConvertInt(controle_atual->EstadoBateria()));
		switch(controle_atual->EstadoBateria())
		{
			case BATTERY_LEVEL_EMPTY:
				outtextxy(20,470," - BATTERY_LEVEL_EMPTY");
				break;
			case BATTERY_LEVEL_LOW:
				outtextxy(20,470," - BATTERY_LEVEL_LOW");
				break;
			case BATTERY_LEVEL_MEDIUM:
				outtextxy(20,470," - BATTERY_LEVEL_MEDIUM");
				break;
			case BATTERY_LEVEL_FULL:
				outtextxy(20,470," - BATTERY_LEVEL_FULL");
				break;
		}
		
		if(TeclaEstaPressionada(VK_F1))
		{
			F1Pressed=true;
		}
		else if(F1Pressed)
		{
			controle_atual->Vibrar(SHRT_MAX);
			F1Pressed=false;
		}
		
		if(TeclaEstaPressionada(VK_F2))
		{
			F2Pressed=true;
		}
		else if(F2Pressed)
		{
			controle_atual->Vibrar(0,SHRT_MAX);
			F2Pressed=false;
		}
		
		if(TeclaEstaPressionada(VK_F3))
		{
			F3Pressed=true;
		}
		else if(F3Pressed)
		{
			controle_atual->Vibrar(SHRT_MAX,SHRT_MAX);
			F3Pressed=false;
		}
		
		if(TeclaEstaPressionada(VK_F4))
		{
			F4Pressed=true;
		}
		else if(F4Pressed)
		{
			controle_atual->Vibrar();
			F4Pressed=false;
		}
		
		setvisualpage(pg);
		delay(50);
	}
	closegraph();
	return 0;
}
