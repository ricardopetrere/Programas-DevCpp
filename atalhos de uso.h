/*
Colocar nos parâmetros de linker do projeto:

-lbgi
-lgdi32
-lcomdlg32
-luuid
-loleaut32
-lole32
*/
/*
Esqueleto de programa:

#include <graphics.h>
#include <stdlib.h>

#define ESC 27
char tecla=0;
int largura=500;
int altura=500;
int pg=1;

int main()
{
	initwindow(largura,altura,"",(getmaxx()-largura)/2,(getmaxy()-altura)/2);

	while(tecla!=ESC)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		cleardevice();
		
		
		setvisualpage(pg);
		if(kbhit())
			tecla=getch();
		delay(50);
	}
	closegraph();
	return 0;
}
*/
/*
Modelo de uso do GetKeyState:

if(GetKeyState(VK_)&0x80)//0x80 é a máscara para tecla pressionada no momento (KeyDown)
		{
			
		}
*/
/*
Ao usar áudio (função PlaySound()), adicionar nos parâmetros de linker do projeto:
-lwinmm
*/
/*
Ao usar rede no código (ex: programas que utilizam a biblioteca rede.h), adicionar nos parâmetros do linker do projeto os caminhos dos seguintes arquivos:

"C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libws2_32.a"
"C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libmswsock.a"
"C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib/libadvapi32.a"
*/
/*
Ao usar comandos para joysticks XInput (ex: Controles de XBox 360), adicionar nos parâmetros do linker do projeto o caminho do arquivo:
"C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libxinput1_4.a"

No código:
#include <xinput.h>
*/