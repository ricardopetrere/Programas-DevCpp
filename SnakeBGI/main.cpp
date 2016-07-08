#include <graphics.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <time.h>

#define COLUNAS			(20)
#define LINHAS 			(20)
#define ESCALA			(2)
#define TILE			(8*ESCALA)
#define MEIO_TILE		(TILE/2)
#define CELULA			(2*TILE)
#define LARGURA			(COLUNAS*CELULA)
#define ALTURA			(LINHAS*CELULA)
#define CENTROX_TELA	((GetSystemMetrics(SM_XVIRTUALSCREEN)+GetSystemMetrics(SM_CXVIRTUALSCREEN)/2))
#define CENTROY_TELA	((GetSystemMetrics(SM_YVIRTUALSCREEN)+GetSystemMetrics(SM_CYVIRTUALSCREEN)/2))
#define CHAR_VAZIO		('\0')
#define CHAR_SNAKE		('X')
#define CHAR_POINT		('.')

using namespace std;

int pg=1;
bool sair=false;
char matriz[LINHAS][COLUNAS];

enum movimentos {
	UP=0,RIGHT=1,DOWN=2,LEFT=3
};
movimentos mov_atual=RIGHT;

typedef struct TPosicao
{
	int i,j;
	
};
bool operator==(const TPosicao& _a, const TPosicao& _b)
{
	return _a.i==_b.i&&_a.j==_b.j;
}
TPosicao &GeraTPosicao(int i, int j)
{
	TPosicao retorno;
	retorno.i=i;
	retorno.j=j;
	return retorno;
	
//	TPosicao* retorno = (struct TPosicao*)(malloc(sizeof(struct TPosicao)));
//	retorno->i=i;
//	retorno->j=j;
//	return *retorno;
}
TPosicao &GeraTPosicao(TPosicao _base)
{
	TPosicao retorno = _base;
//	retorno.i=_base.i;
//	retorno.j=_base.j;
	return retorno;
}
TPosicao ponto;
typedef struct TSnake
{
	vector<TPosicao> posicoes;
	int qtd_posicoes;
//	TPosicao* _frente;
//	TPosicao* _traseira;
	void InsereTPosicao(TPosicao &pos)
	{
		posicoes.push_back(pos);
//		_frente = &pos;
//		if(qtd_posicoes==0)
//			_traseira=&pos;
		qtd_posicoes++;
		matriz[pos.i][pos.j] = CHAR_SNAKE;
	}
	void Mover()
	{
		int n=0;
		matriz[posicoes[n].i][posicoes[n].j]=CHAR_VAZIO;
		for(;n<qtd_posicoes-1;n++)
		{
			posicoes[n].i=posicoes[n+1].i;
			posicoes[n].j=posicoes[n+1].j;
		}
		switch(mov_atual)
		{
			case UP:
				posicoes[n].i=posicoes[n-1].i-1;
				posicoes[n].j=posicoes[n-1].j;
				break;
			case RIGHT:
				posicoes[n].i=posicoes[n-1].i;
				posicoes[n].j=posicoes[n-1].j+1;
				break;
			case DOWN:
				posicoes[n].i=posicoes[n-1].i+1;
				posicoes[n].j=posicoes[n-1].j;
				break;
			case LEFT:
				posicoes[n].i=posicoes[n-1].i;
				posicoes[n].j=posicoes[n-1].j-1;
				break;
		}
		if(matriz[posicoes[n].i][posicoes[n].j]==CHAR_SNAKE)
			sair=true;
		else
			matriz[posicoes[n].i][posicoes[n].j]=CHAR_SNAKE;
	}
	void Desenhar()
	{
		setfillstyle(SOLID_FILL,WHITE);
		int n=0;
		for(;n<qtd_posicoes-1;n++)
		{
			int x0,y0,x1,y1;
			if(posicoes[n].j<posicoes[n+1].j)
			{
				x0=(posicoes[n].j)*CELULA+MEIO_TILE;
				x1=(posicoes[n+1].j)*CELULA+TILE+MEIO_TILE;
			}
			else
			{
				x0=(posicoes[n+1].j)*CELULA+MEIO_TILE;
				x1=(posicoes[n].j)*CELULA+TILE+MEIO_TILE;
			}
			if(posicoes[n].i<posicoes[n+1].i)
			{
				y0=(posicoes[n].i)*CELULA+MEIO_TILE;
				y1=(posicoes[n+1].i)*CELULA+TILE+MEIO_TILE;
			}
			else
			{
				y0=(posicoes[n+1].i)*CELULA+MEIO_TILE;
				y1=(posicoes[n].i)*CELULA+TILE+MEIO_TILE;
			}
//			std::cout<<n<<std::endl<<x0<<std::endl<<y0<<std::endl<<std::endl;
//			std::cout<<n<<std::endl<<x1<<std::endl<<y1<<std::endl<<std::endl;
			bar(x0,y0,x1,y1);
		}
	}
	TPosicao Frente()
	{
		return posicoes[qtd_posicoes-1];
//		return *_frente;
	}
	TPosicao Traseira()
	{
		return posicoes[0];
//		return *_traseira;
	}
};
TSnake s;

char ProximaCasa(TPosicao base)
{
	switch(mov_atual)
	{
		case UP:
			return matriz[base.i-1][base.j];
		case RIGHT:
			return matriz[base.i][base.j+1];
		case DOWN:
			return matriz[base.i+1][base.j];
		case LEFT:
			return matriz[base.i][base.j-1];
	}
}

int main()
{
	srand(time(NULL));
	s.InsereTPosicao(GeraTPosicao(2,2));
	s.InsereTPosicao(GeraTPosicao(2,3));
	s.InsereTPosicao(GeraTPosicao(2,4));
	
	initwindow(LARGURA,ALTURA,"Snake BGI",CENTROX_TELA-(LARGURA/2),CENTROY_TELA-(ALTURA/2));
	
	bool posponto=false;
	int tentativas=0;
	ponto.i=-1;
	ponto.j=-1;
	
	bool pensarduasvezes=false;
	
//	delay(5000);
	while(!sair)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		cleardevice();
		if(ProximaCasa(s.Frente())==CHAR_POINT)
		{
			if
			(
				(ponto.i==0&&mov_atual==UP)
				||(ponto.j==COLUNAS-1&&mov_atual==RIGHT)
				||(ponto.i==LINHAS-1&&mov_atual==DOWN)
				||(ponto.j==0&&mov_atual==LEFT)
			)
			{
				delay(0);
			}
			s.InsereTPosicao(ponto);
			if
			(
				(mov_atual==UP&&s.Frente().i==0)
				||
				(mov_atual==RIGHT&&s.Frente().j==COLUNAS-1)
				||
				(mov_atual==DOWN&&s.Frente().i==LINHAS-1)
				||
				(mov_atual==LEFT&&s.Frente().j==0)
				||ProximaCasa(s.Frente())==CHAR_SNAKE
			)
			{
				pensarduasvezes=true;
			}
			posponto=false;
		}
		else if(!pensarduasvezes)
		{
			s.Mover();
			if
			(
				(mov_atual==UP&&s.Frente().i==0)
				||
				(mov_atual==RIGHT&&s.Frente().j==COLUNAS-1)
				||
				(mov_atual==DOWN&&s.Frente().i==LINHAS-1)
				||
				(mov_atual==LEFT&&s.Frente().j==0)
				||ProximaCasa(s.Frente())==CHAR_SNAKE
			)
			{
				pensarduasvezes=true;
			}
		}
		else if(pensarduasvezes)
		{
//			pensarduasvezes=false;
		}
		
		TPosicao _F=s.Frente();
//		cout<<_F.i<<endl<<_F.j<<endl<<endl;
		if(_F.j<0||_F.j>=COLUNAS
			||_F.i<0||_F.i>=LINHAS)
		{
			sair=true;
		}
		while(!posponto)
		{
			ponto.i=rand()%LINHAS;
			ponto.j=rand()%COLUNAS;
			if(matriz[ponto.i][ponto.j]==CHAR_VAZIO)
			{
				matriz[ponto.i][ponto.j]=CHAR_POINT;
				posponto=true;
				tentativas=0;
			}
			else
				tentativas++;
			if(tentativas>ALTURA*COLUNAS)//fim de jogo
			{
				posponto=true;
				sair=true;
				delay(5000);
			}
		}
		
		s.Desenhar();
		if(ponto.i>=0&&ponto.j>=0)
		{
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,WHITE);
			fillellipse((ponto.j*CELULA)+TILE,(ponto.i*CELULA)+TILE,MEIO_TILE,MEIO_TILE);
		}
		
		if(GetKeyState(VK_RCONTROL)&0x80)
		{
			setcolor(GREEN);
			for(int n=0;n<LINHAS;n++)
			{
				line(0,n*CELULA,COLUNAS*CELULA,n*CELULA);
			}
			for(int n=0;n<COLUNAS;n++)
			{
				line(n*CELULA,0,n*CELULA,LINHAS*CELULA);
			}
			setfillstyle(SOLID_FILL,RED);
			bar(s.posicoes[s.qtd_posicoes-1].j*CELULA,s.posicoes[s.qtd_posicoes-1].i*CELULA
				,(s.posicoes[s.qtd_posicoes-1].j*CELULA)+CELULA,(s.posicoes[s.qtd_posicoes-1].i*CELULA)+CELULA);
			
			setfillstyle(SOLID_FILL,WHITE);
			if(matriz[ponto.i][ponto.j]==CHAR_POINT)
				bar(ponto.j*CELULA,ponto.i*CELULA,(ponto.j*CELULA)+CELULA,(ponto.i*CELULA)+CELULA);
		}
		setvisualpage(pg);
		
		delay(1000/10);
		
		if(GetKeyState(VK_UP)&0x80&&mov_atual!=DOWN)
		{
			mov_atual=UP;
			pensarduasvezes=false;
		}
		if(GetKeyState(VK_RIGHT)&0x80&&mov_atual!=LEFT)
		{
			mov_atual=RIGHT;
			pensarduasvezes=false;
		}
		if(GetKeyState(VK_DOWN)&0x80&&mov_atual!=UP)
		{
			mov_atual=DOWN;
			pensarduasvezes=false;
		}
		if(GetKeyState(VK_LEFT)&0x80&&mov_atual!=RIGHT)
		{
			mov_atual=LEFT;
			pensarduasvezes=false;
		}
		
		if(GetKeyState(VK_ESCAPE)&0x80)
		{
			sair=true;
		}
	}
	delay(2000);
	closegraph();
	return 0;
}
