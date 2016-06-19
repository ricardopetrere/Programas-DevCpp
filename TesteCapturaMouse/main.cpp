#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define ESC 27
char tecla=0;
int largura=800;
int altura=600;
int centro_x;
int centro_y;
int pg=1;
int raio_circulo=200;
int offset_linhasxy = 50;

POINT P;
HWND hwnd;
HWND console;

//char* ConverteDoubleParaChar7(double valor)
//{
//	char* retorno;
//	strcpy(retorno,"       ");
//	_snprintf(retorno,7,"%f",valor);
//	return retorno;
//}

int main()
{
	console = GetConsoleWindow();
	ShowWindow(console,SW_HIDE);
	initwindow(largura,altura,"Teste de Captura do Mouse",(getmaxwidth()-largura)/2,(getmaxheight()-altura)/2);
	hwnd = GetForegroundWindow();
	centro_x = getmaxx()/2;
	centro_y = getmaxy()/2;

	while(tecla!=ESC)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		cleardevice();
		
		setcolor(GREEN);
		//Círculo
		circle(centro_x,centro_y,raio_circulo);
		//Eixos X e Y
		line(centro_x-raio_circulo-offset_linhasxy,centro_y,centro_x+raio_circulo+offset_linhasxy,centro_y);
		line(centro_x,centro_y-raio_circulo-offset_linhasxy,centro_x,centro_y+raio_circulo+offset_linhasxy);
		
		if(GetCursorPos(&P))
		{
			if (ScreenToClient(hwnd, &P))
			{
				if((P.x>=0&&P.x<=largura)&&((P.y>=0&&P.y<=altura)))
				{
					double dx = (P.x-centro_x);
					double dy = (centro_y-P.y);
					double _atan = atan2(dy,dx)*180/M_PI;
					if(_atan<0)//_atan vai de -180 a 180
					{
						_atan+=360;//Para visualizar melhor
					}
//					double _cos = round(cos(_atan*M_PI/180)*1000)/1000;
					double _cos = cos(_atan*M_PI/180);
//					double _sin = round(sin(_atan*M_PI/180)*1000)/1000;
					double _sin = sin(_atan*M_PI/180);
					setcolor(WHITE);
					line(centro_x,centro_y,centro_x+raio_circulo*_cos,centro_y-raio_circulo*_sin);
					setcolor(RED);
					line(centro_x+raio_circulo*_cos,centro_y,centro_x+raio_circulo*_cos,centro_y-raio_circulo*_sin);
					line(centro_x,centro_y-raio_circulo*_sin,centro_x+raio_circulo*_cos,centro_y-raio_circulo*_sin);
					rectangle(P.x+10,P.y,P.x+140,P.y+50);
					
					
					char mensagem[18];
					char* temp_valor;
					strcpy(temp_valor,"       ");
					
					//Ângulo
					strcpy(mensagem,"");
					strcat(mensagem,"Ângulo:  ");
					
					_snprintf(temp_valor,7,"%f",_atan);
//					temp_valor=ConverteDoubleParaChar7(_atan);
					
					strcat(mensagem,temp_valor);
					strcat(mensagem,"°");
					outtextxy(P.x+15,P.y+2,mensagem);
					
					//Cosseno
					strcpy(mensagem,"");
					strcat(mensagem,"Cosseno: ");
					
					_snprintf(temp_valor,7+(_cos<0),"%f",_cos);
//					strcpy(temp_valor,ConverteDoubleParaChar7(_cos));
					
					strcat(mensagem,temp_valor);
					outtextxy(P.x+15,P.y+18,mensagem);
					
					//Seno
					strcpy(mensagem,"");
					strcat(mensagem,"Seno:    ");
					
					_snprintf(temp_valor,7+(_sin<0),"%f",_sin);
//					strcpy(temp_valor,ConverteDoubleParaChar7(_sin));
					
					strcat(mensagem,temp_valor);
					outtextxy(P.x+15,P.y+34,mensagem);
					
//					cout << "Ângulo: " << _atan << endl;
//					cout << "Cos: " << _cos << " Sin: " << _sin << endl;
//					delay(100);
				}
			}
		}
		
		setvisualpage(pg);
		if(kbhit())
			tecla=getch();
		delay(100);
	}
	ShowWindow(console,SW_RESTORE);
//	cout << "Fim de programa";
	closegraph();
	return 0;
}
