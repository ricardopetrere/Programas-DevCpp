/*
Escreva um programa que faça com que oito bolinhas de cores variadas se movimentem do centro para a borda da tela até à distância de 200 pixels.
Atingida essa distância as bolinhas devem circular em torno do centro, inicialmente, no sentido anti-horário.
Ao pressionar a barra de espaços o sentido deve ser invertido, ou seja para horário se estiver anit-horário, e vice-versa.

Vejam o programa modelo que postei na sessão "Definir Materiais" aqui do SIGA. Este programa modelo tem o nome Struct03 e está no arquivo compactado Struct03.zip
*/

/*
Fazer com que, depois de um certo, dê "spawn" em mais 8 bolas para cada uma das 8 bolas
Sugestão: criar variáveis x_origem e y_origem, que, enquanto as bolas iniciais estiverem sendo expandidas, troque os dois pares de x e y. Quando as bolas iniciais pararem de expandir, só passar a trocar x e y, a partir de x_origem e y_origem
*/
#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

//http://www.asciitable.com/
#define ESC 27
char tecla=0;

typedef struct TBola
{
	int x;
	int y;
	int raio;
	int cor;
};

int main()
{
	srand(time(NULL));
	initwindow(500,500);
	TBola bolas[8];
	TBola bolas_secundarias[64];
	int raio=10;
	int raio2=5;
	
	int centro_x = getmaxx()/2;
	int centro_y = getmaxy()/2;
	
	int n2;
	for(n2=0;n2<8;n2++)
	{
		bolas[n2].x = centro_x;
		bolas[n2].y = centro_y;
		bolas[n2].raio = raio;
		bolas[n2].cor = rand()%15+1;
		for(int n3=0;n3<8;n3++)
		{
			bolas_secundarias[n2*8+n3].raio=raio2;
			bolas_secundarias[n2*8+n3].cor=rand()%15+1;
		}
	}
	
	int pg=1;
	bool expandindo_bolas=true;
	int passo_grau=-1;
	int grau=0;
	
	int mov=0;
	int passo_mov=5;
	
	int passo_grau2=-1;
	int grau2=0;
	int passo3=1;
	int distancia_bolas2=50;
	
	while(tecla!=ESC)
	{
		pg = (pg==1) ? pg=2 : pg=1;
		setactivepage(pg);
		cleardevice();
		if(expandindo_bolas)
		{
			for(n2=0;n2<8;n2++)
			{
				bolas[n2].x= centro_x + int(mov*cos((n2*45)*M_PI/180));
				bolas[n2].y= centro_y + int(mov*sin((n2*45)*M_PI/180));
				
				setcolor(bolas[n2].cor);
				setfillstyle(SOLID_FILL,bolas[n2].cor);
				fillellipse(bolas[n2].x,bolas[n2].y,bolas[n2].raio,bolas[n2].raio);
			}
			mov+=passo_mov;
			if(mov>=200)
			{
				mov=200;
				expandindo_bolas=false;
			}
		}
		else
		{
			setcolor(WHITE);
			circle(centro_x,centro_y,mov);
			
			for(n2=0;n2<8;n2++)
			{
				bolas[n2].x= centro_x + int(mov*cos((n2*45 + grau)*M_PI/180));
				bolas[n2].y= centro_y + int(mov*sin((n2*45 + grau)*M_PI/180));
								
				setcolor(bolas[n2].cor);
				setfillstyle(SOLID_FILL,bolas[n2].cor);
				fillellipse(bolas[n2].x,bolas[n2].y,bolas[n2].raio,bolas[n2].raio);
				
				for(int n=0;n<8;n++)
				{
					int n3=n2*8+n;
					bolas_secundarias[n3].x=bolas[n2].x+int(distancia_bolas2*cos((n*45 + grau2)*M_PI/180));
					bolas_secundarias[n3].y=bolas[n2].y+int(distancia_bolas2*sin((n*45 + grau2)*M_PI/180));
					setcolor(bolas_secundarias[n3].cor);
					setfillstyle(SOLID_FILL,bolas_secundarias[n3].cor);
					fillellipse(bolas_secundarias[n3].x,bolas_secundarias[n3].y,bolas_secundarias[n3].raio,bolas_secundarias[n3].raio);
				}
				grau2+=passo_grau2;
				grau2=grau2%360;
			}
			grau+=passo_grau;
			grau=grau%360;

			if(mov<50||mov>200)
			{
				passo3=-passo3;
			}
			mov+=passo3;
			
			if(GetKeyState(VK_SPACE)&0x80)
			{
				passo_grau=-passo_grau;
				while(GetKeyState(VK_SPACE)&0x80);
			}
			if(GetKeyState(VK_RBUTTON)&0x80)
			{
				passo_grau2=-passo_grau2;
				while(GetKeyState(VK_RBUTTON)&0x80);
			}
		}		
		setvisualpage(pg);
		
		fflush(stdin);
		if(kbhit())
			tecla=getch();
		delay(30);
	}
	closegraph();
	return 0;
}
