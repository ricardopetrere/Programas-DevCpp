#include <graphics.h>
#include <stdlib.h>
#include <iostream>
//#include <windows.h>
#include <Mmsystem.h>

//#define SND_FILENAME 0x20000
//#define SND_LOOP 8 
//#define SND_ASYNC 1 

#define ESC 27
char tecla=0;

int largura=450;
int altura=600;

int pg=1;

int largura_borda = 25;//A borda total terá 50px
int raio_circulo = 10;

//Formas:http://i.imgur.com/9Z0oJXe.png
enum Formas_Tetris {I_BLOCK,J_BLOCK,L_BLOCK,O_BLOCK,S_BLOCK,T_BLOCK,Z_BLOCK};
//Cores das formas:
//I_BLOCK=CYAN,J_BLOCK=BLUE,L_BLOCK=BROWN,O_BLOCK=YELLOW,S_BLOCK=LIGHTGREEN,T_BLOCK=MAGENTA,Z_BLOCK=RED

int x,y;

using namespace std;

int main()
{
	initwindow(largura,altura,"Tetris with BGI",(getmaxwidth()-largura)/2,(getmaxheight()-altura)/2);
	
	x=largura/2;
	y=100;
//	PlaySound("C:\\Users\\Ricardo\\Desktop\\ProgII\\TetrisBGI\\audios\\BUI.wav",NULL,SND_FILENAME||SND_ASYNC|SND_NOSTOP);
	
//	readimagefile("imagens/1.png",0,0,50,50);
//	int Tamanho = imagesize(0, 0, 50, 50);
//	void* fig;
//	fig = malloc(Tamanho);
//	getimage(0, 0, 50, 50, fig);
	
	while(tecla!=ESC)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		cleardevice();
		
		//Borda
		setfillstyle(SOLID_FILL,BLUE);
		bar(0,0,largura,altura);
		setfillstyle(SOLID_FILL,BLACK);
		bar(largura_borda,largura_borda,largura-largura_borda,altura-largura_borda);
		
		//Validações de movimento
		if(GetKeyState(VK_LEFT)&0x80)
		{
			x-=1;
		}
		if(GetKeyState(VK_RIGHT)&0x80)
		{
			x+=1;
		}
		if(GetKeyState(VK_UP)&0x80)
		{
			y-=1;
		}
		if(GetKeyState(VK_DOWN)&0x80)
		{
			y+=1;
		}
		if(x<raio_circulo)x=raio_circulo;
		if(x>largura-raio_circulo)x=largura-raio_circulo;
		if(y<raio_circulo)y=raio_circulo;
		if(y>altura-raio_circulo)y=altura-raio_circulo;
		
		//Validação da peça escolhida
		setcolor(BLACK);		
//		if(tecla==73||tecla==105)//I
		if(GetKeyState(73)&0x80)
		{
			setfillstyle(SOLID_FILL,CYAN);
			fillellipse(x,y,raio_circulo,raio_circulo);
//			putimage(x,y+2*raio_circulo,fig,1);
		}
//		else if(tecla==74||tecla==106)//J
		else if(GetKeyState(74)&0x80)
		{
			setfillstyle(SOLID_FILL,BLUE);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
//		else if(tecla==76||tecla==108)//L
		else if(GetKeyState(76)&0x80)
		{
			setfillstyle(SOLID_FILL,BROWN);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
//		else if(tecla==79||tecla==111)//O
		else if(GetKeyState(79)&0x80)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
//		else if(tecla==83||tecla==115)//S
		else if(GetKeyState(83)&0x80)
		{
			setfillstyle(SOLID_FILL,LIGHTGREEN);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
//		else if(tecla==84||tecla==116)//T
		else if(GetKeyState(84)&0x80)
		{
			setfillstyle(SOLID_FILL,MAGENTA);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
//		else if(tecla==90||tecla==122)//Z
		else if(GetKeyState(90)&0x80)
		{
			setfillstyle(SOLID_FILL,RED);
			fillellipse(x,y,raio_circulo,raio_circulo);
		}
		
		//Validação do ESC
		if(GetKeyState(VK_ESCAPE)&0x80)
		{
			tecla=ESC;
		}
		
		setvisualpage(pg);
		delay(20);
	}
	closegraph();
	return 0;
}
