/* Core definitions/headers */
// System headers
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <time.h>
#pragma comment (lib,"wininet.lib")

// Input/Output
#include <iostream>
#include <fstream>
using namespace std;

// OpenGL
#include <gl/gl.h>
#pragma comment (lib,"opengl32.lib")

// Windows
WNDCLASSEX wcex;
HINSTANCE hInstance;
HWND hWnd;
HDC hDC;
HGLRC hRC;
MSG msg;
HINTERNET Inet;
#define TRI_ICON 101
OSVERSIONINFO WinData;

// Global definitions
#define Window "Wnd"
#define Title "Tritank 1.0"
#define VERSION 10
#define BUILDDATA "Fighter's release"
bool key[256],init,lmouse,rmouse;
unsigned int width,heigth,mx,my,maxwidth,maxheigth,owidth,oheigth,wxpos,wypos;

/* OpenGL */
// Init
bool EnableOpenGL(HWND hWnd,HDC*hDC,HGLRC*hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    if (!(*hDC=GetDC(hWnd)))
	{
		MessageBox(NULL,"Unable to create a device context. Program will now close.","Error",NULL);
		return false;
	}
    ZeroMemory(&pfd,sizeof(pfd));
    pfd.nSize=sizeof(pfd);
    pfd.nVersion=1;
    pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    pfd.iPixelType=PFD_TYPE_RGBA;
    pfd.cColorBits=24;
    pfd.cDepthBits=16;
    pfd.iLayerType=PFD_MAIN_PLANE;
    if (!(iFormat=ChoosePixelFormat(*hDC,&pfd)))
	{
		MessageBox(NULL,"Unable to find a suitable pixel format. Program will now close.","Error",NULL);
		return false;
	}
    if (!SetPixelFormat(*hDC,iFormat,&pfd))
	{
		MessageBox(NULL,"Unable to initialize the pixel formats. Program will now close.","Error",NULL);
		return false;
	}
    if (!(*hRC=wglCreateContext(*hDC)))
	{
		MessageBox(NULL,"Unable to create a rendering context. Program will now close.","Error",NULL);
		return false;
	}
    if (!wglMakeCurrent(*hDC,*hRC))
	{
		MessageBox(NULL,"Unable to activate the rendering context. Program will now close.","Error",NULL);
		return false;
	}
	return true;
}

void DisableOpenGL(HWND hWnd,HDC hDC,HGLRC hRC)
{
	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))
			MessageBox(NULL,"Unable release the device context and rendering context.","Shutdown error",NULL);
		if (!wglDeleteContext(hRC))
			MessageBox(NULL,"Unable to release rendering context.","Shutdown error",NULL);
		hRC=NULL;
	}
	if (hDC&&!ReleaseDC(hWnd,hDC))
	{
		MessageBox(NULL,"Unable to release device context.","Shutdown error",NULL);
		hDC=NULL;
	}
}

// Resize
void Resize(int w,int h)
{
	width=w;heigth=h;
	glViewport(0,0,width,heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0,10.0,-10.0,10.0,0.0,1.0);
}

void RunResize(int w,int h)
{
	width=w;heigth=h;
	glViewport(0,0,width,heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0,20.0,-20.0,20.0,0.0,1.0);
}

/* Game objects */
// Player
struct Player
{
	// Position
	double xpos,ypos;
	double xdir,ydir;
	double speed;
	double ang;
	double xfriction,yfriction;
	bool blockx,blocky;
	// Properties
	bool alive;
	int lives;
	unsigned int weapon,spawntime;
	// Variables
	unsigned int wait;
};

Player you;
#define MAXENEMIES 10
Player enemy[MAXENEMIES];
unsigned int ENEMIES;
#define MAXMATES 9
Player mate[MAXMATES];
unsigned int MATES;

struct AI
{
	unsigned int wait,wait2;
	unsigned int attack;
	bool forward,back,right,left,shoot;
};
AI aienemy[MAXENEMIES];
AI aimate[MAXMATES];

double x,y;
double x2[MAXENEMIES];double y2[MAXENEMIES];
double x3[MAXMATES];double y3[MAXMATES];

struct Object
{
	double xpos,ypos;
	double sizex,sizey;
	double ang;
};
#define MAXSQUARES 25
Object cube[MAXSQUARES];
unsigned int SQUARES,ASQUARES;

struct
{
	double xpos,ypos;
	double spawnx,spawny;
	unsigned int wait,owner,prim;
	bool taken;
}flag[2];

struct Items
{
	double spawnx,spawny;
	bool spawned;
	unsigned int add,wait;
};
#define MAXITEMS 10
unsigned int THEALTH,TARIFLE,TCANNON,TSHELL,TMINI,TROCKET;
Items ithealth[MAXITEMS];
Items itarifle[MAXITEMS];
Items itmini[MAXITEMS];
Items itcannon[MAXITEMS];
Items itshell[MAXITEMS];
Items itrocket[MAXITEMS];

struct Bullet
{
	// Position
	double xpos,ypos;
	double xdir,ydir;
	double ang;
	// Properties
	char Team;
	bool alive;
};
#define ALLOCBULLETS 30
#define MAXCANNON 30
#define MAXSHELL 25
#define MAXMINI 100
#define MAXRIFLE 75
#define MAXROCKET 15
#define BULLETTYPES 7
// Types
#define CANNON 0
#define RIFLE 1
#define ROCKET 2
#define ANTI 3
#define SHELL 4
#define MINI 5
#define CTFCAN 6
// Structures
unsigned int MAXBULLETS[BULLETTYPES];
unsigned int DATABULLETS[MAXENEMIES+MAXMATES+1][BULLETTYPES];

struct Properties
{
	double speed;
	double kickback;
	int dev;
	unsigned int damage;
	unsigned int wait;
};
Bullet bullet[MAXMATES+MAXENEMIES+1][BULLETTYPES][ALLOCBULLETS];
Properties bulletdata[BULLETTYPES];

struct Particles
{
	double xpos,ypos;
	double xdir,ydir;
	double r,g,b,a;
	double speed;
	float size;
	bool alive;
};
#define MAXPARTICLES 20
unsigned int PARTICLES[MAXMATES+MAXENEMIES+1];
Particles explosion[MAXMATES+MAXENEMIES+1][MAXPARTICLES];

struct
{
	bool win,lost,smooth,fullscreen,inter,stop;
	bool internet,online,update;
	bool firstrun,focus,quit;
	char*difficulty;
	char*type;
	char*map;
	char*tkonoff;
	char*ctfmap;
	unsigned int time,elapsed;
	unsigned int score,escore,maxscore;
}game;

// Timer
class Timer
{
public:
	void TimerInit();
	float GetTime();
	float starttime,oneframe;
private:
  __int64 frequency,start,elapsed;
  float resolution;
  unsigned long ms_start,ms_elapsed;
  bool timer;
};

void Timer::TimerInit()
{
	ZeroMemory(&timer,sizeof(timer));
	oneframe=10;
	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&frequency))
	{
		timer=false;
		ms_start=GetTickCount();
		resolution=1.0f/1000.0f;
		frequency=1000;
		ms_elapsed=ms_start;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		timer=true;
		resolution=(float)(1.0/(double)frequency);
		elapsed=start;
	}
}

float Timer::GetTime()
{
	__int64 time;
	if (timer)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time);	
		return ((float)(time-start)*resolution)*1000.0f;
	}
	else
	{
		return((float)(GetTickCount()-ms_start)*resolution)*1000.0f;
	}
}

Timer timer;

/* Gameplay definitions*/
#define MAXGTIME 90000
unsigned int loop1,loop2,loop3,loop4,AENEMIES,AMATES;
bool shootswitch=true;
bool menuset=true,menu=false,runset=false,run=false,optionset=false,option=false;
bool help=false,credits=false,settings=false,multi=false,mode=false;