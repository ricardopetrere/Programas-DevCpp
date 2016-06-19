#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<iostream>
using namespace std;

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC    	27

int main()
{
  int driver, mode;
  char tecla;
  int  x, y, passo, passox, passoy, raio;
  POINT P;
  HWND hwnd;

  tecla = 0;
  x = 100;
  y = 100;
  raio = 18; 
  passo = 5; // incremento do centro do circulo
  passox = passo;
  passoy = passo;

  detectgraph(&driver, &mode);
  initgraph(&driver, &mode, "");

  hwnd = GetForegroundWindow(); 

  cleardevice();
  setcolor (LIGHTRED);
  rectangle(10, 10, 400, 400);
  setfillstyle(1, YELLOW);
  setcolor (YELLOW);
  while(tecla != ESC) {
    setfillstyle(1, BLACK);
    setcolor (BLACK);
    fillellipse(x, y, raio, raio);

    if(GetKeyState(VK_LEFT)&0x80)   x = x - passox;
    if(GetKeyState(VK_RIGHT)&0x80)  x = x + passox;
    if(GetKeyState(VK_UP)&0x80)     y = y - passoy;
    if(GetKeyState(VK_DOWN)&0x80)   y = y + passoy;
    if(GetKeyState(VK_SPACE)&0x80) {
        setfillstyle(1, LIGHTRED);
        setcolor(LIGHTRED);
        fillellipse(rand()%380+15, rand()%380+15, 5, 5);
    }
    if(GetKeyState(VK_LBUTTON)&0x80) {
        setfillstyle(1, LIGHTBLUE);
        setcolor(LIGHTBLUE);
        if (GetCursorPos(&P))
          if (ScreenToClient(hwnd, &P))
            fillellipse(P.x, P.y, 5, 5);
//        cout << P.x << " / " << P.y << endl;
//        fillellipse(rand()%380+15, rand()%380+15, 5, 5);
    }

    fflush(stdin);    
    if (kbhit()){
      tecla = getch();
    }
    
    if (x >= 400-raio)
      x = 400-raio;
    if (x <= 10+raio+1)
      x = 10+raio+1;
    if (y >= 400-raio)
      y = 400-raio;
    if (y <= 10+raio+1)
      y = 10+raio+1;

    setfillstyle(1, YELLOW);
    setcolor (YELLOW);
    fillellipse(x, y, raio, raio);
    delay(50);  
  }

  closegraph();
  return(0);
}
