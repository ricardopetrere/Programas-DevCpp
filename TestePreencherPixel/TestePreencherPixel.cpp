#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define ESC 27
char tecla=0;
int largura=500;
int altura=500;
int pg=1;

HWND window;
POINT P;

int cor_atual=0;
char buf[3];

int main()
{
	initwindow(largura,altura,"TestePreencherPixel",(getmaxwidth()-largura),(getmaxheight()-altura)/2);
	window = GetForegroundWindow();
	int cor_elipse=COLOR(80,80,80);
	int raio_elipse=150;
	double valor;
	while(tecla!=ESC)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		if(GetAsyncKeyState(VK_UP))//&0x80)
		{
			cor_atual++;
		}
		if(GetAsyncKeyState(VK_DOWN))//&0x80)
		{
			cor_atual--;
		}
		cor_atual=(cor_atual+16)%16;
		setfillstyle(SOLID_FILL,cor_elipse);
		fillellipse(0,0,raio_elipse,raio_elipse);
		setbkcolor(cor_elipse);
		setfillstyle(SOLID_FILL,cor_atual);
		outtextxy(0,0,"LBUTTON: putpixel");
		outtextxy(0,20,"RBUTTON: floodfill");
//		moveto(0,0);
//		moveto(0,40);
		outtextxy(0,40,"0 a 15: cor de fundo");
//		moveto(0,20);
//		moveto(0,60);
		outtextxy(0,60,"Cor atual: ");
		
		itoa(cor_atual,buf,10);
		outtextxy(70,60,buf);
		bar(0,80,49,129);
		setvisualpage(pg);
		
		GetCursorPos(&P);
		if(GetAsyncKeyState(VK_LBUTTON))//&0x80)
		{
			if(GetForegroundWindow()==window)
			{
				if(ScreenToClient(window,&P))
				{
					valor = sqrt(pow(P.x,2)+pow(P.y,2));
					if(valor>raio_elipse)
					{
						putpixel(P.x-1,P.y-1,cor_atual);
						putpixel(P.x-1,P.y,cor_atual);
						putpixel(P.x-1,P.y+1,cor_atual);
						
						putpixel(P.x,P.y-1,cor_atual);
						putpixel(P.x,P.y,cor_atual);
						putpixel(P.x,P.y+1,cor_atual);
						
						putpixel(P.x+1,P.y-1,cor_atual);
						putpixel(P.x+1,P.y,cor_atual);
						putpixel(P.x+1,P.y+1,cor_atual);
					}
				}
			}
		}
		else if(GetAsyncKeyState(VK_RBUTTON))
		{
			if(GetForegroundWindow()==window)
			{
				if(ScreenToClient(window,&P))
				{
					floodfill(P.x,P.y,cor_atual);
				}
			}
		}
		else
			delay(100);
		if(kbhit())
			tecla=getch();
	}
	closegraph();
	return 0;
}
