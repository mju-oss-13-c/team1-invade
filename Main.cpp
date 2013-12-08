// Engine setup
#include <Engine.h>
#include <Trimath.h>
#include <GUI.h>

// Main game functions
#include <Game.h>
#include <Server.h>

// Functions
bool ChangeWindow(bool fullscreen);

/* Main */
void MenuCallBacks()
{
	CallBack(MENU_QUIT)
	{
		game.quit=true;
	}
	CallBack(MENU_START)
	{
		//SetCursorPos(width/2,heigth/2);
		menu=false;
		mode=true;
	}
	CallBack(MENU_HELP)
	{
		//SetCursorPos(width/2,heigth/2);
		help=true;
		menu=false;
	}
	CallBack(MENU_CREDITS)
	{
		//SetCursorPos(width/2,heigth/2);
		credits=true;
		menu=false;
	}
	CallBack(MENU_SET)
	{
		//SetCursorPos(width/2,heigth/2);
		settings=true;
		menu=false;
	}
	CallBack(MENU_MULTI)
	{
		//SetCursorPos(width/2,heigth/2);
		multi=true;
		menu=false;
	}
	// Internet
	if (Inet)
	{
		if (InternetGetConnectedState(NULL,0))
			game.internet=true;
		else
			game.internet=false;
	}
	else
	{
		game.internet=false;
	}
	// Auto-update
	if (game.internet)
	{
		/*HINTERNET Session=InternetOpen(Title,0,NULL,NULL,INTERNET_FLAG_ASYNC);
		HINTERNET Url=InternetOpenUrl(Session,"http://www.google.com/",NULL,0,0,0);
		if (Url==NULL)
			game.update=false;
		else
			game.update=true;
		InternetCloseHandle(Url);
		InternetCloseHandle(Session);*/
		/*if (InternetOpenUrl(Inet,"http://www.google.nl/"///"http://sourceforge.net/projects/tritank/files/Releases/1.1/Tritank%201.1.exe/download"
			,NULL,0,NULL,NULL)==NULL)
			game.update=true;
		else
			game.update=false;*/
	}
	else
	{
		game.update=false;
	}
}

void OptionCallBacks()
{
	CallBack(OPTION_BACK)
	{
		ShowCursor(false);
		if (game.smooth)
		{
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glEnable(GL_BLEND);
		}
		RunResize(width,heigth);
		option=false;
		run=true;
	}
	CallBack(OPTION_QUIT)
	{
		option=false;
		mode=true;
	}
}

void RunSetup();

void RunCallBacks()
{
	if (key[VK_RETURN] && (game.stop||game.win||game.lost))
	{
		RunSetup();
		
	}else if (key[VK_ESCAPE])
	{
		run=false;
		optionset=true;
		ShowCursor(true);
	}
}

void SubCallBacks()
{
		CallBack(SEL_TKONOFF){
			if (strcmp(game.tkonoff,"TeamKill On")==0)
				strcpy(game.tkonoff,"TeamKill Off");
			else if (strcmp(game.tkonoff,"TeamKill Off")==0)
				strcpy(game.tkonoff,"TeamKill On");
		}
	// Global GUI
	CallBack(MENU_BACK)
	{
		if (help)
		{
			help=false;
			menuset=true;
		}
		else if (credits)
		{
			credits=false;
			menuset=true;
		}
		else if (settings)
		{
			settings=false;
			menuset=true;
		}
		else if (multi)
		{
			multi=false;
			menuset=true;
		}
		else if (mode)
		{
			mode=false;
			menuset=true;
		}
	}
	if (settings)
	{
		CallBack(SET_DIF)
		{
			if (strcmp(game.difficulty,"Hard")==0)
				strcpy(game.difficulty,"Easy");
			else if (strcmp(game.difficulty,"Easy")==0)
				strcpy(game.difficulty,"Normal");
			else
				strcpy(game.difficulty,"Hard");
		}
		CallBack(SET_SMO)
		{
			game.smooth=!game.smooth;
		}
	}
	else if (multi)
	{
		// Check if there's a connection
		if (Inet)
		{
			if (InternetGetConnectedState(NULL,0))
			{
				game.internet=true;
				// Check server
				if (InternetConnect(Inet,"",INTERNET_DEFAULT_HTTPS_PORT,"","",INTERNET_SERVICE_HTTP,0,0))
				{
					game.online=true;
				}
				else
				{
					game.online=false;
				}
			}
			else
			{
				game.internet=false;
			}
		}
		else
		{
			game.internet=false;
		}
		// Servers
		CallBack(MUL_LIST)
		{
			if (game.online)
			{
			}
		}
	}
	else if (mode)
	{
		CallBack(SEL_TYPE)
		{
			if (strcmp(game.type,"Survival")==0)
				strcpy(game.type,"Battle");
			else if (strcmp(game.type,"Battle")==0)
				strcpy(game.type,"Time battle");
			else if (strcmp(game.type,"Time battle")==0)
				strcpy(game.type,"CTEF");
			else if (strcmp(game.type,"CTEF")==0)
				strcpy(game.type,"CTF");
			else if (strcmp(game.type,"CTF")==0)
				strcpy(game.type,"Survival");
		}
		CallBack(SEL_EP)
		{
			if (AENEMIES<MAXENEMIES)
				AENEMIES++;
		}
		CallBack(SEL_EM)
		{
			if (AENEMIES>1)
				AENEMIES--;
		}
		CallBack(SEL_MP)
		{
			if (AMATES<MAXMATES)
				AMATES++;
		}
		CallBack(SEL_MM)
		{
			if (AMATES>0)
				AMATES--;
		}
		CallBack(SEL_SP)
		{
			if (ASQUARES<MAXSQUARES)
				ASQUARES++;
		}
		CallBack(SEL_SM)
		{
			if (ASQUARES>0)
				ASQUARES--;
		}
		CallBack(SEL_TP)
		{
			if (game.time<MAXGTIME)
				game.time+=6000;
		}
		CallBack(SEL_TM)
		{
			if (game.time>6000)
				game.time-=6000;
		}
		CallBack(SEL_MAP)
		{
			if (strcmp(game.type,"CTF")!=0)
			{
				if (strcmp(game.map,"Random")==0)
					strcpy(game.map,"Cubic");
				else if (strcmp(game.map,"Cubic")==0)
					strcpy(game.map,"Plaza");
				else if (strcmp(game.map,"Plaza")==0)
					strcpy(game.map,"Parallel");
				else if (strcmp(game.map,"Parallel")==0)
					strcpy(game.map,"Stars");
				else if (strcmp(game.map,"Stars")==0)
					strcpy(game.map,"Random");
			}
			else
			{
				if (strcmp(game.ctfmap,"Diagonal")==0)
					strcpy(game.ctfmap,"Grid");
				else if (strcmp(game.ctfmap,"Grid")==0)
					strcpy(game.ctfmap,"Street");
				else if (strcmp(game.ctfmap,"Street")==0)
					strcpy(game.ctfmap,"Diagonal");
			}
		}
		CallBack(SEL_MAXSCP)
		{
			if (game.maxscore<10)
				game.maxscore++;
		}
		CallBack(SEL_MAXSCM)
		{
			if (game.maxscore>1)
				game.maxscore--;
		}
		CallBack(SEL_START)
		{
			mode=false;
			runset=true;
		}
	}
}

// Menu
void RenderFrame()
{
	glLineWidth(2.5f);
	// Frame
	glColor3d(0.25,1.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(-9.0,6.0);glVertex2d(-9.0,-7.5);
	glVertex2d(-9.0,-7.5);glVertex2d(-5.0,-7.5);
	glEnd();
}

void MenuSetup()
{
	// Mouse
	//SetCursorPos(width/2,heigth/2);
	// OpenGL
}

void Menu()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PrintText("Tritank",-2.5,7.5,MENUTITLE);
	PushButton("Singleplayer",-8.0,4.0,pushcol,MENU_START);
	PushButton("Multiplayer",-8.0,2.5,pushcol,MENU_MULTI);
	PushButton("Options",-8.0,1.0,pushcol,MENU_SET);
	PushButton("Help",-8.0,-0.5,pushcol,MENU_HELP);
	PushButton("Credits",-8.0,-2.0,pushcol,MENU_CREDITS);
	PushButton("Quit",-8.0,-3.5,pushcol,MENU_QUIT);
	// Auto-update
	if (game.update)
	{
		PrintText("A newer version of Tritank is available!",-8.0,-4.5,MENUTEXT);
		PrintText("Go to https://sourceforge.net/projects/tritank/files/Releases/ now.",-8.0,-5.1,MENUTEXT);
	}
	MenuCallBacks();
	RenderFrame();
	SwapBuffers(hDC);
}

void Help()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PushButton("Back",-10.0,9.0,pushcol2,MENU_BACK);PrintText("Help",-5.0,8.5,MENUSUBT);
	PrintText("Controls:",-8.0,7.0,MENUSUB);
	PrintText("Use the arrows to move and rotate, use A and D for switching weapons and W for shooting.",-8.0,6.5,MENUTEXT);
	PrintText("When playing, press the escape key to pause or to return to the menu.",-8.0,6.0,MENUTEXT);
	SubCallBacks();
	SwapBuffers(hDC);
}

void RenderSetting()
{
	glColor3d(1.0,0.5,0.1);
	glBegin(GL_LINES);
	glVertex2d(-9.5,-8.0);glVertex2d(-9.5,7.5);
	glEnd();
}
void Settings()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PushButton("Back",-10.0,9.0,pushcol2,MENU_BACK);PrintText("Options",-5.0,8.5,MENUSUBT);
	// Difficulty
	PrintText("Difficulty:",-9.0,7.0,MENUDATA);PrintText(game.difficulty,-6.75,7.0,MENUDATA);
	PushButton("Change",-4.0,6.75,pushcol1,SET_DIF);
	// Graphics
	PrintText("Smooth:",-9.0,5.5,MENUDATA);
	if (game.smooth)
		PrintText("On",-7.5,5.5,MENUDATA);
	else
		PrintText("Off",-7.5,5.5,MENUDATA);
	PushButton("Change",-4.0,5.25,pushcol1,SET_SMO);
	// Power
	PrintText("Mode:",-9.0,4.0,MENUDATA);
	if (game.fullscreen)
		PrintText("Fullscreen",-7.9,4.0,MENUDATA);
	else
		PrintText("Windowed",-7.9,4.0,MENUDATA);
	PushButton("Change",-4.0,3.75,pushcol1,SET_WIN);
	SubCallBacks();
	RenderSetting();
	SwapBuffers(hDC);
}

void Multi()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PushButton("Back",-10.0,9.0,pushcol2,MENU_BACK);PrintText("Multiplayer",-5.0,8.5,MENUSUBT);
	PrintText("Multiplayer is yet in development. The server is planned to be online in 2012, you can try now:",-9.0,7.0,MENUTEXT);
	PushButton("Browse serverlist",-8.0,5.5,pushcol,MUL_LIST);
	if (game.internet)
	{
		PrintText("You are connected to the internet.",-9.0,4.75,MENUTEXT);
		if (game.online)
			PrintText("The server is online.",-9.0,4.25,MENUTEXT);
		else
			PrintText("The server is not yet online.",-9.0,4.25,MENUTEXT);
	}
	else
	{
		PrintText("Can't connect to the internet. Please check your internet connection.",-9.0,4.75,MENUTEXT);
	}
	SubCallBacks();
	SwapBuffers(hDC);
}

void Credits()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PushButton("Back",-10.0,9.0,pushcol2,MENU_BACK);PrintText("Credits",-5.0,8.5,MENUSUBT);
	PrintText("Tritank is coded by Dardan (David) with C++ and uses the OpenGL API.",-8.0,7.5,MENUTEXT);
	PrintText("For any questions, suggestions etc. go to the forum/discussion page:",-8.0,7.0,MENUTEXT);
	PrintText("https://sourceforge.net/p/tritank/discussion/",-8.0,6.25,MENUDATA);
	PrintText("Version:",-8.0,5.0,MENUTEXT);PrintValue((double)VERSION/10.0,false,-6.75,4.95,MENUDATA);
	PrintText("Build:",-8.0,4.25,MENUTEXT);PrintText(BUILDDATA,-6.75,4.2,MENUDATA);
	SubCallBacks();
	SwapBuffers(hDC);
}

void Select()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PushButton("Back",-10.0,9.0,pushcol2,MENU_BACK);PrintText("Game mode",-5.0,8.5,MENUSUBT);
	// Type
	PushButton(game.type,-8.5,6.5,pushcol1,SEL_TYPE);
	PushButton(game.tkonoff,0,3.0,pushcol1,SEL_TKONOFF);
	if (strcmp(game.type,"Battle")==0)
	{
		PrintText("Face to face on the battlefield.",-4.0,6.7,MENUTEXT);
		PrintText("Enemies:",-8.5,5.2,MENUDATA);PrintValue(AENEMIES,true,-6.0,5.2,MENUDATA);
		PushButton("+",-5.5,5.0,pushcol1,SEL_EP);PushButton("-",-4.5,5.0,pushcol1,SEL_EM);
		PrintText("Teammates:",-8.5,4.1,MENUDATA);PrintValue(AMATES,true,-6.0,4.1,MENUDATA);
		PushButton("+",-5.5,3.9,pushcol1,SEL_MP);PushButton("-",-4.5,3.9,pushcol1,SEL_MM);
		PrintText("Map:",-8.5,3.0,MENUDATA);PushButton(game.map,-5.5,2.8,pushcol1,SEL_MAP);//PushButton("TeamKill Off",-4.5,3.9,pushcol1,SEL_MM);
		if (strcmp(game.map,"Random")==0)
		{
			PrintText("Buildings:",-8.5,1.9,MENUDATA);PrintValue(ASQUARES,true,-6.0,1.9,MENUDATA);
			PushButton("+",-5.5,1.7,pushcol1,SEL_SP);PushButton("-",-4.5,1.7,pushcol1,SEL_SM);
			PrintText("Play in a randomly generated map.",-8.5,1.0,MENUTEXT);
		}
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		PrintText("Beat the enemy with your strategy!",-4.0,6.7,MENUTEXT);
	}
	else if (strcmp(game.type,"CTEF")==0)
	{
		PrintText("'Conquer the enemy front'.",-4.0,6.7,MENUTEXT);
	}
	else if (strcmp(game.type,"Time battle")==0)
	{
		PrintText("Kill the most before the time runs out!",-4.0,6.7,MENUTEXT);
		PrintText("Enemies:",-8.5,5.2,MENUDATA);PrintValue(AENEMIES,true,-6.0,5.2,MENUDATA);
		PushButton("+",-5.5,5.0,pushcol1,SEL_EP);PushButton("-",-4.5,5.0,pushcol1,SEL_EM);
		PrintText("Teammates:",-8.5,4.1,MENUDATA);PrintValue(AMATES,true,-6.0,4.1,MENUDATA);
		PushButton("+",-5.5,3.9,pushcol1,SEL_MP);PushButton("-",-4.5,3.9,pushcol1,SEL_MM);
		PrintText("Time (min.):",-8.5,3.0,MENUDATA);PrintValue(game.time/6000,true,-6.0,3.0,MENUDATA);
		PushButton("+",-5.5,2.8,pushcol1,SEL_TP);PushButton("-",-4.5,2.8,pushcol1,SEL_TM);
		PrintText("Map:",-8.5,1.9,MENUDATA);PushButton(game.map,-5.5,1.7,pushcol1,SEL_MAP);
		if (strcmp(game.map,"Random")==0)
		{
			PrintText("Buildings:",-8.5,0.8,MENUDATA);PrintValue(ASQUARES,true,-6.0,0.8,MENUDATA);
			PushButton("+",-5.5,0.6,pushcol1,SEL_SP);PushButton("-",-4.5,0.6,pushcol1,SEL_SM);
			PrintText("Play in a randomly generated map.",-8.5,-0.1,MENUTEXT);
		}
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		PrintText("Good old 'Capture the flag'!",-4.0,6.7,MENUTEXT);
		PrintText("Map:",-8.5,5.2,MENUDATA);PushButton(game.ctfmap,-5.5,5.0,pushcol1,SEL_MAP);
		PrintText("Max. points:",-8.5,4.1,MENUDATA);PrintValue(game.maxscore,true,-6.0,4.1,MENUDATA);
		PushButton("+",-5.5,3.9,pushcol1,SEL_MAXSCP);PushButton("-",-4.5,3.9,pushcol1,SEL_MAXSCM);
	}
	// Start!
	PushButton("Start",-8.5,-2.0,pushcol,SEL_START);
	SubCallBacks();
	SwapBuffers(hDC);
}

// Options
void OptionSetup()
{
	// Mouse
	ShowCursor(true);
	//SetCursorPos(width/2,heigth/2);
	// Data
	// OpenGL
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	Resize(width,heigth);
}

void Option()
{
	ShowCursor(true);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	PrintText("Pause",-5.0,8.5,MENUSUBT);
	PushButton("Return",-8.0,6.5,pushcol,OPTION_BACK);
	PushButton("Quit",-8.0,5.0,pushcol,OPTION_QUIT);
	OptionCallBacks();
	SwapBuffers(hDC);
}

// Run
void RunSetup()
{
	// Mouse
	ShowCursor(false);
//	SetCursorPos(width/2,heigth/2);
	// Game
	game.stop=false;
	if (strcmp(game.type,"Time battle")==0)
	{
		game.elapsed=game.time;
		game.score=game.escore=0;
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		game.score=game.escore=0;
	}
	// Players
	you.xpos=18.5-rand()%18*2;you.ypos=-14.0;
	you.xdir=0.0;you.ydir=0.0;
	you.ang=90.0;
	if (strcmp(game.type,"CTF")!=0)
		you.speed=0.05;
	else
		you.speed=0.075;
	you.alive=true;
	if (strcmp(game.type,"CTEF")==0)
		you.lives=15;
	else if (strcmp(game.type,"CTF")==0)
		you.lives=25;
	else
		you.lives=40;
	you.weapon=SHELL;
	you.wait=0;
	if (strcmp(game.type,"CTEF")==0||strcmp(game.type,"Time battle")==0)
		you.spawntime=500;
	if (strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)
	{
		ENEMIES=AENEMIES;
		MATES=AMATES;
	}
	else if (strcmp(game.type,"CTEF")==0)
	{
		if (strcmp(game.difficulty,"Hard")==0)
		{
			ENEMIES=MAXENEMIES;
			MATES=ENEMIES-4;
		}
		else if (strcmp(game.difficulty,"Normal")==0)
		{
			ENEMIES=rand()%(MAXENEMIES/3)+MAXENEMIES/2;
			MATES=ENEMIES-1;
		}
		else if (strcmp(game.difficulty,"Easy")==0)
		{
			ENEMIES=rand()%(MAXENEMIES/3)+MAXENEMIES/3;
			MATES=ENEMIES+rand()%2+1;
		}
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		if (strcmp(game.difficulty,"Hard")==0)
		{
			ENEMIES=MAXENEMIES-rand()%2;
			MATES=rand()%(MAXMATES/2)+MAXENEMIES/4+1;
		}
		else if (strcmp(game.difficulty,"Normal")==0)
		{
			ENEMIES=rand()%(MAXENEMIES/4)+MAXENEMIES/2;
			MATES=rand()%(MAXMATES/4)+MAXMATES/2;
		}
		else if (strcmp(game.difficulty,"Easy")==0)
		{
			ENEMIES=rand()%(MAXENEMIES/2)+MAXMATES/4+1;
			MATES=MAXMATES-rand()%2;
		}
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		if (strcmp(game.difficulty,"Hard")==0)
		{
			ENEMIES=MAXENEMIES-rand()%3-2;
			MATES=ENEMIES/2;
		}
		else if (strcmp(game.difficulty,"Normal")==0)
		{
			ENEMIES=MAXENEMIES-rand()%2-3;
			MATES=ENEMIES-1;
		}
		else if (strcmp(game.difficulty,"Easy")==0)
		{
			MATES=MAXMATES/2+rand()%3;
			ENEMIES=MATES/3*2;
		}
	}
	loopi(loop1,ENEMIES)
	{
		enemy[loop1].xpos=18.5-rand()%18*2;
		enemy[loop1].ypos=18.5;
		enemy[loop1].xdir=0.0;
		enemy[loop1].ydir=0.0;
		enemy[loop1].ang=90.0;
		if (strcmp(game.type,"CTF")!=0)
			enemy[loop1].speed=0.05;
		else
			enemy[loop1].speed=0.075;
		enemy[loop1].alive=true;
		if (strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)
		{
			if (strcmp(game.difficulty,"Hard")==0)
				enemy[loop1].lives=50;
			else if (strcmp(game.difficulty,"Normal")==0)
				enemy[loop1].lives=40;
			else if (strcmp(game.difficulty,"Easy")==0)
				enemy[loop1].lives=30;
		}
		else if (strcmp(game.type,"CTEF")==0)
		{
			enemy[loop1].lives=15;
		}
		else if (strcmp(game.type,"Survival")==0)
		{
			enemy[loop1].lives=40;
		}
		else if (strcmp(game.type,"CTF")==0)
		{
			enemy[loop1].lives=25;
		}
		enemy[loop1].weapon=SHELL;
		enemy[loop1].wait=0;
		if (strcmp(game.type,"CTEF")==0||strcmp(game.type,"Time battle")==0)
			enemy[loop1].spawntime=500;
		// AI
		aienemy[loop1].wait=aienemy[loop1].wait2=0;
		aienemy[loop1].attack=MAXMATES+MAXENEMIES+2;
	}
	loopi(loop1,MATES)
	{
		mate[loop1].xpos=18.5-rand()%18*2;
		mate[loop1].ypos=-14.0;
		mate[loop1].xdir=0.0;
		mate[loop1].ydir=0.0;
		mate[loop1].ang=90.0;
		if (strcmp(game.type,"CTF")!=0)
			mate[loop1].speed=0.05;
		else
			mate[loop1].speed=0.075;
		mate[loop1].alive=true;
		mate[loop1].lives=you.lives;
		mate[loop1].weapon=SHELL;
		mate[loop1].wait=0;
		if (strcmp(game.type,"CTEF")==0||strcmp(game.type,"Time battle")==0)
			mate[loop1].spawntime=500;
		// AI
		aimate[loop1].wait=aimate[loop1].wait2=0;
		aimate[loop1].attack=MAXMATES+MAXENEMIES+2;
	}
	// Bullets
	if (strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)
	{
		loopi(loop1,MATES+ENEMIES+1)
		{
			DATABULLETS[loop1][CANNON]=50;
			DATABULLETS[loop1][RIFLE]=80;
			DATABULLETS[loop1][ROCKET]=30;
			DATABULLETS[loop1][ANTI]=25;
			DATABULLETS[loop1][SHELL]=50;
			DATABULLETS[loop1][MINI]=100;
			DATABULLETS[loop1][CTFCAN]=0;
		}
	}
	else if (strcmp(game.type,"CTEF")==0)
	{
		loopi(loop1,MATES+ENEMIES+1)
		{
			DATABULLETS[loop1][CANNON]=15;
			DATABULLETS[loop1][RIFLE]=50;
			DATABULLETS[loop1][SHELL]=10;
			DATABULLETS[loop1][ROCKET]=DATABULLETS[loop1][ANTI]=DATABULLETS[loop1][MINI]=DATABULLETS[loop1][CTFCAN]=0;
		}
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		loopi(loop1,MATES+ENEMIES+1)
		{
			DATABULLETS[loop1][CANNON]=25+(rand()%11-5);
			DATABULLETS[loop1][RIFLE]=50+(rand()%51-25);
			DATABULLETS[loop1][ROCKET]=10+(rand()%11-5);
			DATABULLETS[loop1][ANTI]=15+(rand()%11-5);
			DATABULLETS[loop1][SHELL]=20+(rand()%11-5);
			DATABULLETS[loop1][MINI]=100-rand()%21;
			DATABULLETS[loop1][CTFCAN]=0;
		}
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		loopi(loop1,MATES+ENEMIES+1)
		{
			DATABULLETS[loop1][CANNON]=DATABULLETS[loop1][RIFLE]=DATABULLETS[loop1][ROCKET]=DATABULLETS[loop1][ANTI]=DATABULLETS[loop1][SHELL]=DATABULLETS[loop1][MINI]=0;
			DATABULLETS[loop1][CTFCAN]=50;
		}
	}
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,BULLETTYPES)
		{
			loopi(loop3,MAXBULLETS[loop2])
			{
				bullet[loop1][loop2][loop3].alive=false;
			}
		}
	}
	// World
	if ((strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)&&strcmp(game.map,"Random")==0)
	{
		SQUARES=ASQUARES;
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		SQUARES=rand()%(MAXSQUARES-4)+5;
	}
	else if (strcmp(game.type,"CTEF")==0)
	{
		SQUARES=0;
	}
	else if (strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)
	{
		if (strcmp(game.map,"Cubic")==0)
			SQUARES=1;
		else if (strcmp(game.map,"Plaza")==0)
			SQUARES=8;
		else if (strcmp(game.map,"Parallel")==0)
			SQUARES=6;
		else if (strcmp(game.map,"Stars")==0)
			SQUARES=25;
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		if (strcmp(game.ctfmap,"Grid")==0)
			SQUARES=6;
		else if (strcmp(game.ctfmap,"Diagonal")==0)
			SQUARES=10;
		else if (strcmp(game.ctfmap,"Street")==0)
			SQUARES=2;
	}
	if (strcmp(game.type,"Survival")==0)
	{
		loopi(loop1,SQUARES)
		{
			cube[loop1].xpos=rand()%24001/1000.0-12.0;
			cube[loop1].ypos=rand()%22001/1000.0-8.5;
			cube[loop1].sizex=rand()%2501/1000.0+0.5;
			cube[loop1].sizey=rand()%2501/1000.0+0.5;
			cube[loop1].ang=0.0;
		}
	}
	else if (strcmp(game.type,"Battle")==0||strcmp(game.type,"Time battle")==0)
	{
		if (strcmp(game.map,"Cubic")==0)
		{
			cube[0].xpos=0.0;
			cube[0].ypos=2.25;
			cube[0].sizex=2.5;
			cube[0].sizey=2.5;
			cube[0].ang=0.0;
		}
		else if (strcmp(game.map,"Plaza")==0)
		{
			cube[0].xpos=9.0;
			cube[0].ypos=-6.75;
			cube[0].sizex=1.0;
			cube[0].sizey=1.0;
			cube[0].ang=0.0;
			cube[1].xpos=9.0;
			cube[1].ypos=2.25;
			cube[1].sizex=1.0;
			cube[1].sizey=1.0;
			cube[1].ang=0.0;
			cube[2].xpos=9.0;
			cube[2].ypos=11.25;
			cube[2].sizex=1.0;
			cube[2].sizey=1.0;
			cube[2].ang=0.0;
			cube[3].xpos=0.0;
			cube[3].ypos=11.25;
			cube[3].sizex=1.0;
			cube[3].sizey=1.0;
			cube[3].ang=0.0;
			cube[4].xpos=-9.0;
			cube[4].ypos=11.25;
			cube[4].sizex=1.0;
			cube[4].sizey=1.0;
			cube[4].ang=0.0;
			cube[5].xpos=-9.0;
			cube[5].ypos=2.25;
			cube[5].sizex=1.0;
			cube[5].sizey=1.0;
			cube[5].ang=0.0;
			cube[6].xpos=-9.0;
			cube[6].ypos=-6.75;
			cube[6].sizex=1.0;
			cube[6].sizey=1.0;
			cube[6].ang=0.0;
			cube[7].xpos=0.0;
			cube[7].ypos=-6.75;
			cube[7].sizex=1.0;
			cube[7].sizey=1.0;
			cube[7].ang=0.0;
		}
		else if (strcmp(game.map,"Parallel")==0)
		{
			loopi(loop1,SQUARES)
			{
				cube[loop1].xpos=loop1*6.0-15.0;
				cube[loop1].ypos=(double)loop1*2.0-2.75;
				cube[loop1].sizex=0.75;
				cube[loop1].sizey=7.5;
				cube[loop1].ang=0.0;
			}
		}
		else if (strcmp(game.map,"Stars")==0)
		{
			loopi(loop1,SQUARES)
			{
				cube[loop1].xpos=rand()%30001/1000.0-15.0;
				cube[loop1].ypos=rand()%25001/1000.0-10.0;
				cube[loop1].sizex=0.05;
				cube[loop1].sizey=0.05;
				cube[loop1].ang=0.0;
			}
		}
	}
	else if (strcmp(game.type,"CTF")==0)
	{
		flag[0].taken=false;flag[0].wait=0;
		flag[1].taken=false;flag[1].wait=0;
		if (strcmp(game.ctfmap,"Grid")==0)
		{
			//Cubes
			cube[0].xpos=10.0;
			cube[0].ypos=-4.75;
			cube[0].sizex=2.0;
			cube[0].sizey=1.0;
			cube[0].ang=0.0;
			cube[1].xpos=10.0;
			cube[1].ypos=9.25;
			cube[1].sizex=2.0;
			cube[1].sizey=1.0;
			cube[1].ang=0.0;
			cube[2].xpos=0.0;
			cube[2].ypos=9.25;
			cube[2].sizex=2.0;
			cube[2].sizey=1.0;
			cube[2].ang=0.0;
			cube[3].xpos=-10.0;
			cube[3].ypos=9.25;
			cube[3].sizex=2.0;
			cube[3].sizey=1.0;
			cube[3].ang=0.0;
			cube[4].xpos=-10.0;
			cube[4].ypos=-4.75;
			cube[4].sizex=2.0;
			cube[4].sizey=1.0;
			cube[4].ang=0.0;
			cube[5].xpos=0.0;
			cube[5].ypos=-4.75;
			cube[5].sizex=2.0;
			cube[5].sizey=1.0;
			cube[5].ang=0.0;
			// Flags
			flag[0].spawnx=flag[0].xpos=-15.0;flag[0].spawny=flag[0].ypos=0.0;
			flag[1].spawnx=flag[1].xpos=15.0;flag[1].spawny=flag[1].ypos=0.0;
		}
		else if (strcmp(game.ctfmap,"Diagonal")==0)
		{
			// Cubes
			loopi(loop1,SQUARES)
			{
				cube[loop1].xpos=rand()%7*4-12.0;
				cube[loop1].ypos=rand()%6*4-7.5;
				cube[loop1].sizex=rand()%11/100.0+0.5;
				cube[loop1].sizey=rand()%11/100.0+0.5;
				cube[loop1].ang=0.0;
			}
			// Flags
			flag[0].spawnx=flag[0].xpos=16.0;flag[0].spawny=flag[0].ypos=-11.5;
			flag[1].spawnx=flag[1].xpos=-16.0;flag[1].spawny=flag[1].ypos=16.0;
		}
		else if (strcmp(game.ctfmap,"Street")==0)
		{
			// Cubes
			cube[0].xpos=14.0;
			cube[0].ypos=2.25;
			cube[0].sizex=5;
			cube[0].sizey=15;
			cube[0].ang=0.0;
			cube[1].xpos=-14.0;
			cube[1].ypos=2.25;
			cube[1].sizex=5;
			cube[1].sizey=15;
			cube[1].ang=0.0;
			// Flags
			flag[0].spawnx=flag[0].xpos=0.0;flag[0].spawny=flag[0].ypos=-13.0;
			flag[1].spawnx=flag[1].xpos=0.0;flag[1].spawny=flag[1].ypos=17.25;
		}
	}
	if (strcmp(game.type,"CTF")==0)
	{
		flag[0].prim=rand()%ENEMIES;
		flag[1].prim=rand()%MATES;
	}
	else
	{
		flag[0].prim=ENEMIES+1;
		flag[1].prim=MATES+2;
	}
	flag[1].owner=MATES+2;
	flag[0].owner=ENEMIES+1;
	// Items
	if (strcmp(game.type,"CTEF")==0)
	{
		THEALTH=rand()%(MAXITEMS-2)+3;
		TARIFLE=TMINI=TCANNON=TSHELL=TROCKET=0;
		loopi(loop1,THEALTH)
		{
			ithealth[loop1].add=5;
			ithealth[loop1].wait=rand()%701+300;
			ithealth[loop1].spawned=true;
			ithealth[loop1].spawnx=rand()%61/2.0-15.0;
			ithealth[loop1].spawny=rand()%41/2.0-8.0;
		}
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		THEALTH=0;
		TARIFLE=rand()%3;
		TMINI=rand()%3;
		TCANNON=2+rand()%3;
		TSHELL=2+rand()%3;
		TROCKET=rand()%3;
		loopi(loop1,TARIFLE)
		{
			itarifle[loop1].add=10;
			itarifle[loop1].wait=rand()%1251+750;
			itarifle[loop1].spawned=true;
			itarifle[loop1].spawnx=(rand()%8)*4-18.0;
			itarifle[loop1].spawny= rand()%2==0 ? -12.5 : 17.0;
		}
		loopi(loop1,TMINI)
		{
			itmini[loop1].add=20;
			itmini[loop1].wait=rand()%1251+750;
			itmini[loop1].spawned=true;
			itmini[loop1].spawnx=(rand()%8)*4-17.5;
			itmini[loop1].spawny= rand()%2==0 ? -12.5 : 17.0;
		}
		loopi(loop1,TCANNON)
		{
			itcannon[loop1].add=6;
			itcannon[loop1].wait=rand()%751+500;
			itcannon[loop1].spawned=true;
			itcannon[loop1].spawnx=(rand()%8)*4-17.0;
			itcannon[loop1].spawny= rand()%2==0 ? -12.5 : 17.0;
		}
		loopi(loop1,TSHELL)
		{
			itshell[loop1].add=5;
			itshell[loop1].wait=rand()%751+500;
			itshell[loop1].spawned=true;
			itshell[loop1].spawnx=(rand()%8)*4-16.5;
			itshell[loop1].spawny= rand()%2==0 ? -12.5 : 17.0;
		}
		loopi(loop1,TROCKET)
		{
			itrocket[loop1].add=3;
			itrocket[loop1].wait=rand()%1001+1000;
			itrocket[loop1].spawned=true;
			itrocket[loop1].spawnx=(rand()%8)*4-16.0;
			itrocket[loop1].spawny= rand()%2==0 ? -12.5 : 17.0;
		}
	}
	else
	{
		THEALTH=TARIFLE=TMINI=TCANNON=TSHELL=TROCKET=0;
	}
	// Particles
	loopi(loop1,ENEMIES+MATES+1)
	{
		PARTICLES[loop1]=0;
		loopi(loop2,MAXPARTICLES)
		{
			explosion[loop1][loop2].alive=false;
		}
	}
	// OpenGL
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	if (game.smooth)
	{
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
		glEnable(GL_BLEND);
	}
	RunResize(width,heigth);
}

void Run()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0,0.0,-1.0);
	MoveYou();
	MoveEnemies();
	MoveMates();
	MoveBullets();
	MoveParticles();
	Collisions();
	RenderItems();
	RenderParticles();
	RenderBullets();
	RenderPlayers();
	RenderFlags();
	RenderMap();
	RenderMenu();
	RunCallBacks();
	SwapBuffers(hDC);
}

bool GraphicsInit()
{
	// OpenGL
	if (!EnableOpenGL(hWnd,&hDC,&hRC))
	{
		MessageBox(hWnd,"Unable to set up OpenGL. Program will now close.","Error",NULL);
		return false;
	}
	glClearColor(0,0,0,1);
	Resize(width,heigth);
	// Structures
	InitGUI();
	ShowCursor(false);
	ShowCursor(true);
	return true;
}

// Game
bool GameInit()
{
	// Application setup
	timer.TimerInit();
	maxwidth=GetSystemMetrics(SM_CXSCREEN);
	maxheigth=GetSystemMetrics(SM_CYSCREEN);
	srand((unsigned int)time(0));
	Inet=InternetOpen(Title,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,INTERNET_FLAG_ASYNC);
	WinData.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&WinData);
	game.firstrun=true;
	FILE*user;
	if (WinData.dwMajorVersion==6)
	{
		user=fopen("C:/ProgramData/Tritank/userfile.txt","r");
		if (user)
		{
			game.firstrun=false;
		}
		else
		{
			if (!CreateDirectory("C:/ProgramData/Tritank",NULL))
			{
				MessageBox(hWnd,"Unable to create the directory. Make sure the path 'C:/ProgramData/' exists. Program will now close.","Error",NULL);
				return false;
			}
		}
	}
	else if (WinData.dwMajorVersion==5)
	{
		user=fopen("C:/Documents and Settings/All Users/Application Data/Tritank/userfile.txt","r");
		if (user)
		{
			game.firstrun=false;
		}
		else
		{
			if (!CreateDirectory("C:/Documents and Settings/All Users/Application Data/Tritank/",NULL))
			{
				MessageBox(hWnd,"Unable to create the directory. Make sure the path 'C:/Documents and Settings/All Users/Application Data/' exists. Program will now close.","Error",NULL);
				return false;
			}
		}
	}
	else
	{
		MessageBox(hWnd,"You're not running Windows XP/Vista/7. Program will now close.","Error",NULL);
		return false;
	}
	// Game setup
	game.focus=true;
	game.difficulty=new char[15]();
	game.type=new char[15]();
	game.tkonoff = new char[15]();
	strcpy(game.tkonoff, "TeamKill On");
	game.map=new char[15]();
	game.ctfmap=new char[15]();
	if (!game.firstrun)
	{
		// Reading...
		char lines[16][15];
		loopi(loop1,16)
		{
			while (fgets(lines[loop1],sizeof(lines[loop1]),user)!=NULL)
			{
				if(lines[loop1][strlen(lines[loop1])-1]=='\n')
					break;
			}
		}
		fclose(user);
		// Data transfer
		if (atoi(lines[0])!=VERSION)
		{
			game.firstrun=true;
			if (WinData.dwMajorVersion==6)
				remove("C:/ProgramData/Tritank/userfile.txt");
			else
				remove("C:/Documents and Settings/All Users/Application Data/Tritank/userfile.txt");
		}
		else
		{
			lines[1][strlen(lines[1])-1]='\0';
			strcpy(game.difficulty,lines[1]);
			lines[2][strlen(lines[2])-1]='\0';
			strcpy(game.type,lines[2]);
			lines[3][strlen(lines[3])-1]='\0';
			strcpy(game.map,lines[3]);
			lines[4][strlen(lines[4])-1]='\0';
			strcpy(game.ctfmap,lines[4]);
			game.smooth= lines[5][0]=='0' ? false : true;
			game.fullscreen= lines[6][0]=='0' ? false : true;
			game.time=atoi(lines[7]);
			owidth=atoi(lines[8]);oheigth=atoi(lines[9]);
			wxpos=atoi(lines[10]);wypos=atoi(lines[11]);
			AENEMIES=atoi(lines[12]);AMATES=atoi(lines[13]);ASQUARES=atoi(lines[14]);
			game.maxscore=atoi(lines[15]);
			if (game.fullscreen)
			{
				width=maxwidth;heigth=maxheigth;
			}
			else
			{
				width=owidth;heigth=oheigth;
			}
		}
	}
	if (game.firstrun)
	{
		// Default data
		strcpy(game.difficulty,"Normal");
		strcpy(game.type,"Survival");
		strcpy(game.map,"Random");
		strcpy(game.ctfmap,"Diagonal");
		game.smooth=false;
		game.fullscreen=true;
		game.time=6000;
		owidth=500;oheigth=500;
		wxpos=0;wypos=0;
		AENEMIES=1;AMATES=0;ASQUARES=0;
		width=maxwidth;heigth=maxheigth;
		game.maxscore=5;
	}
	// Loop constants
	MAXBULLETS[CANNON]=7;
	MAXBULLETS[RIFLE]=20;
	MAXBULLETS[ROCKET]=2;
	MAXBULLETS[ANTI]=1;
	MAXBULLETS[SHELL]=4;
	MAXBULLETS[MINI]=30;
	MAXBULLETS[CTFCAN]=10;
	// Game constants
	bulletdata[CANNON].damage=8;
	bulletdata[CANNON].speed=0.15;
	bulletdata[CANNON].kickback=0.1;
	bulletdata[CANNON].wait=50;
	bulletdata[CANNON].dev=1;
	bulletdata[RIFLE].damage=2;
	bulletdata[RIFLE].speed=0.3;
	bulletdata[RIFLE].kickback=0.01;
	bulletdata[RIFLE].wait=15;
	bulletdata[RIFLE].dev=2;
	bulletdata[ROCKET].damage=16;
	bulletdata[ROCKET].speed=0.2;
	bulletdata[ROCKET].kickback=0.35;
	bulletdata[ROCKET].wait=200;
	bulletdata[ROCKET].dev=0;
	bulletdata[ANTI].damage=10;
	bulletdata[ANTI].speed=0.5;
	bulletdata[ANTI].kickback=0.35;
	bulletdata[ANTI].wait=175;
	bulletdata[ANTI].dev=0;
	bulletdata[SHELL].damage=10;
	bulletdata[SHELL].speed=0.2;
	bulletdata[SHELL].kickback=0.15;
	bulletdata[SHELL].wait=80;
	bulletdata[SHELL].dev=1;
	bulletdata[MINI].damage=1;
	bulletdata[MINI].speed=0.45;
	bulletdata[MINI].kickback=0.05;
	bulletdata[MINI].wait=5;
	bulletdata[MINI].dev=4;
	bulletdata[CTFCAN].damage=5;
	bulletdata[CTFCAN].speed=0.4;
	bulletdata[CTFCAN].kickback=0.05;
	bulletdata[CTFCAN].wait=30;
	bulletdata[CTFCAN].dev=0;
	return true;
}

void GameMain()
{
	if (menuset)
	{
		MenuSetup();
		menuset=false;
		menu=true;
	}
	else if (menu)
	{
		Menu();
	}
	else if (help)
	{
		Help();
	}
	else if (credits)
	{
		Credits();
	}
	else if (settings)
	{
		Settings();
	}
	else if (multi)
	{
		Multi();
	}
	else if (mode)
	{
		Select();
	}
	else if (optionset)
	{
		OptionSetup();
		optionset=false;
		option=true;
	}
	else if (option)
	{
		Option();
	}
	else if (runset)
	{
		RunSetup();
		runset=false;
		run=true;
	}
	else if (run)
	{
		Run();
	}
}

void GameQuit()
{
	// Change data files
	ofstream userfile;
	if (WinData.dwMajorVersion==6)
		userfile.open ("C:/ProgramData/Tritank/userfile.txt");
	else
		userfile.open ("C:/Documents and Settings/All Users/Application Data/Tritank/userfile.txt");
	if (userfile.is_open())
	{
		userfile << VERSION << '\n';
		userfile << game.difficulty << '\n';
		userfile << game.type << '\n';
		userfile << game.map << '\n';
		userfile << game.ctfmap << '\n';
		userfile << (unsigned int)game.smooth << '\n';
		userfile << (unsigned int)game.fullscreen << '\n';
		userfile << game.time << '\n';
		userfile << owidth << '\n';
		userfile << oheigth << '\n';
		userfile << wxpos << '\n';
		userfile << wypos << '\n';
		userfile << AENEMIES << '\n';
		userfile << AMATES << '\n';
		userfile << ASQUARES << '\n';
		userfile << game.maxscore << '\n';
		userfile.close();
	}
	else
	{
		MessageBox(hWnd,"Unable to open the core files for writing.","Shutdown error",NULL);
	}
	// Closing off...
	InternetCloseHandle(Inet);
	CleanGUI();
	DisableOpenGL(hWnd,hDC,hRC);
	if (hWnd&&!DestroyWindow(hWnd))
		hWnd=NULL;
	if (!UnregisterClass(wcex.lpszClassName,hInstance))
		hInstance=NULL;
}

// WndProc
LRESULT CALLBACK WndProc(HWND hWnd,
						 UINT message,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		{
			return 0;
		}
	case WM_QUIT:
		{
			PostQuitMessage(0);
			game.quit=true;
			return 0;
		}break;
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			game.quit=true;
			return 0;
		}break;
	case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:
				return 0;
			case SC_MONITORPOWER:
				return 0;
			default:
				break;
			}
		}break;
	case WM_ACTIVATE:
		{
			if (wParam!=WA_INACTIVE&&!game.focus)
			{
				ShowWindow(hWnd,SW_RESTORE);
				game.focus=true;
			}
			else if (wParam==WA_INACTIVE&&game.focus)
			{
				ShowWindow(hWnd,SW_MINIMIZE);
				game.focus=false;
			}
		}break;
	case WM_LBUTTONDOWN:
		{
			lmouse=true;
			return 0;
		}
	case WM_LBUTTONUP:
		{
			lmouse=false;
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			rmouse=true;
			return 0;
		}
	case WM_RBUTTONUP:
		{
			rmouse=false;
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			mx=LOWORD(lParam);
			my=HIWORD(lParam);
			return 0;
		}
	case WM_SIZE:
		{
			if (run)
			{
				RunResize(LOWORD(lParam),HIWORD(lParam));
				InitGUI();
			}
			else
			{
				Resize(LOWORD(lParam),HIWORD(lParam));
				InitGUI();
			}
			return 0;
		}break;
	case WM_MOUSEWHEEL:
		{
			return 0;
		}
	case WM_KEYDOWN:
		{
			key[wParam]=true;
			return 0;
		}
	case WM_KEYUP:
		{
			key[wParam]=false;
			return 0;
		}
	default:
		{
			return DefWindowProc(hWnd,message,wParam,lParam);
		}
	}
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int iCmdShow)
{
	wcex.cbSize=sizeof(WNDCLASSEX);
    wcex.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    wcex.lpfnWndProc=WndProc;
    wcex.cbClsExtra=0;
    wcex.cbWndExtra=0;
    wcex.hInstance=hInstance;
    wcex.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(TRI_ICON));
    wcex.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground=NULL;
    wcex.lpszMenuName=NULL;
    wcex.lpszClassName=Window;
    wcex.hIconSm=LoadIcon(hInstance,MAKEINTRESOURCE(TRI_ICON));

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"Unable to register the window. Program will now close.",
			"Error",
			NULL);
		game.quit=true;
	}

	init=GameInit();

	if (game.fullscreen)
	{
		if (!(hWnd=CreateWindowEx(
			WS_EX_APPWINDOW,
			wcex.lpszClassName,Title,
			WS_POPUP|WS_VISIBLE|
			WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0,0,width,heigth,
			NULL,NULL,
			hInstance,NULL)))
		{
			MessageBox(NULL,
				"Unable to create the window. Program will now close.",
				"Error",
				NULL);
			game.quit=true;
		}
	}
	else
	{
		if (!(hWnd=CreateWindow(
			wcex.lpszClassName,Title,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE|
			WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0,0,width,heigth,
			NULL,NULL,hInstance,
			NULL)))
		{
			MessageBox(NULL,
				"Unable to create the window. Program will now close.",
				"Error",
				NULL);
			game.quit=true;
		}
	}

	if (!ShowWindow(hWnd,iCmdShow))
	{
		MessageBox(NULL,
			"Unable to display the window. Program will now close.",
			"Error",
			NULL);
		game.quit=true;
	}

	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);

	if (!init||!GraphicsInit())
	{
		game.quit=true;
	}
	while (!game.quit)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (push[SET_WIN].clicked)
		{
			game.fullscreen=!game.fullscreen;
			if (!ChangeWindow(game.fullscreen))
			{
				MessageBox(NULL,"Unable to change the window. Program will now close.","Error",NULL);
				game.quit=true;
			}
			push[SET_WIN].clicked=false;
		}
		else if (game.focus)
		{
			timer.starttime=timer.GetTime();
			GameMain();
			while (timer.GetTime()-timer.starttime<timer.oneframe);
		}
	}
	GameQuit();

	return msg.wParam;
}

// Special function
bool ChangeWindow(bool fullscreen)
{
	// Cleaning up
	DisableOpenGL(hWnd,hDC,hRC);
	if (hWnd&&!DestroyWindow(hWnd))
		hWnd=NULL;
	if (!UnregisterClass(wcex.lpszClassName,hInstance))
		hInstance=NULL;
	// Windows
	if(!RegisterClassEx(&wcex))
		return false;

	if (fullscreen)
	{
		width=maxwidth;heigth=maxheigth;
		if (!(hWnd=CreateWindowEx(
			WS_EX_APPWINDOW,
			wcex.lpszClassName,Title,
			WS_POPUP|WS_VISIBLE|
			WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0,0,maxwidth,maxheigth,
			NULL,NULL,
			hInstance,NULL)))
			return false;
	}
	else
	{
		width=owidth;heigth=oheigth;
		if (!(hWnd=CreateWindow(
			wcex.lpszClassName,Title,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE|
			WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
			0,0,width,heigth,
			NULL,NULL,hInstance,
			NULL)))
			return false;
	}
	if (!ShowWindow(hWnd,SW_SHOW))
		return false;

	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);

	if (!GraphicsInit())
		return false;

	//SetCursorPos(width/2,heigth/2);
	return true;
}