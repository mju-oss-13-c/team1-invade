/* Object/Definitions */
// Pushbutton
double pushcol[3]={0.0,0.0,1.0};
double pushcol1[3]={0.0,0.5,0.0};
double pushcol2[3]={1.0,0.0,0.0};
#define PUSHBUTTONS 26
#define MENU_QUIT 0
#define MENU_START 1
#define OPTION_BACK 2
#define OPTION_QUIT 3
#define MENU_HELP 4
#define MENU_BACK 5
#define MENU_CREDITS 6
#define MENU_MULTI 7
#define MENU_SET 8
#define SET_DIF 9
#define SET_SMO 10
#define SET_WIN 11
#define MUL_LIST 12
#define SEL_TYPE 13
#define SEL_START 14
#define SEL_EP 15
#define SEL_EM 16
#define SEL_MP 17
#define SEL_MM 18
#define SEL_SP 19
#define SEL_SM 20
#define SEL_MAP 21
#define SEL_TP 22
#define SEL_TM 23
#define SEL_MAXSCP 24
#define SEL_MAXSCM 25
#define SEL_TKONOFF 26

// Input
double inputcol[3]={1.0,1.0,1.0};
#define INPUTBARS 1

// Fonts
#define TEXTTYPES 8
// Core
#define MENUPUSH 0
#define MENUINPUT 1
// Rest
#define MENUSUB 2
#define MENUDATA 3
#define MENUMSG 4
#define MENUTEXT 5
#define MENUTITLE 6
#define MENUSUBT 7

// GUI structures
struct Button
{
	bool clicked,touched,toggle;
};
Button push[PUSHBUTTONS];

struct bar
{
	int loop,sloop;
	float time;
	bool clicked,aloud;
	char curtext[100];
	float wait;
};
bar input[INPUTBARS];

struct Font
{
	HFONT font,oldfont;
	unsigned int base;
	int height,width,thickness;
	bool italic,underline,strike;
	const char*type;
	double color[3];
};
Font text[TEXTTYPES];

// GUI
#define CallBack(name) if (push[name].clicked)
#define TextRead(name) if (input[name].clicked)
bool toggle;

/* Functions */
void InitGUI()
{
	// Core
	text[MENUPUSH].type="Courier New";
	text[MENUPUSH].thickness=FW_HEAVY;
	text[MENUPUSH].italic=false;
	text[MENUPUSH].strike=false;
	text[MENUPUSH].underline=false;
	text[MENUPUSH].height=heigth/18;
	text[MENUPUSH].width=width/60;
	text[MENUPUSH].color[0]=0.0;text[MENUPUSH].color[1]=1.0;text[MENUPUSH].color[2]=1.0;
	text[MENUINPUT].type="Courier New";
	text[MENUINPUT].thickness=FW_LIGHT;
	text[MENUINPUT].italic=false;
	text[MENUINPUT].strike=false;
	text[MENUINPUT].underline=false;
	text[MENUINPUT].height=heigth/25;
	text[MENUINPUT].width=width/80;
	text[MENUINPUT].color[0]=0.0;text[MENUINPUT].color[1]=0.0;text[MENUINPUT].color[2]=0.0;
	// Rest
	text[MENUSUB].type="Courier New";
	text[MENUSUB].thickness=FW_NORMAL;
	text[MENUSUB].italic=false;
	text[MENUSUB].strike=false;
	text[MENUSUB].underline=false;
	text[MENUSUB].height=heigth/20;
	text[MENUSUB].width=width/90;
	text[MENUSUB].color[0]=1.0;text[MENUSUB].color[1]=1.0;text[MENUSUB].color[2]=0.0;
	text[MENUDATA].type="Courier New";
	text[MENUDATA].thickness=FW_LIGHT;
	text[MENUDATA].italic=false;
	text[MENUDATA].strike=false;
	text[MENUDATA].underline=false;
	text[MENUDATA].height=heigth/25;
	text[MENUDATA].width=width/100;
	text[MENUDATA].color[0]=1.0;text[MENUDATA].color[1]=1.0;text[MENUDATA].color[2]=1.0;
	text[MENUMSG].type="Courier New";
	text[MENUMSG].thickness=FW_BOLD;
	text[MENUMSG].italic=false;
	text[MENUMSG].strike=false;
	text[MENUMSG].underline=false;
	text[MENUMSG].height=heigth/30;
	text[MENUMSG].width=width/100;
	text[MENUMSG].color[0]=0.5;text[MENUMSG].color[1]=0.5;text[MENUMSG].color[2]=0.5;
	text[MENUTEXT].type="Courier New";
	text[MENUTEXT].thickness=FW_NORMAL;
	text[MENUTEXT].italic=false;
	text[MENUTEXT].strike=false;
	text[MENUTEXT].underline=false;
	text[MENUTEXT].height=heigth/30;
	text[MENUTEXT].width=width/110;
	text[MENUTEXT].color[0]=0.75;text[MENUTEXT].color[1]=0.75;text[MENUTEXT].color[2]=0.5;
	text[MENUTITLE].type="Courier New";
	text[MENUTITLE].thickness=FW_SEMIBOLD;
	text[MENUTITLE].italic=false;
	text[MENUTITLE].strike=false;
	text[MENUTITLE].underline=false;
	text[MENUTITLE].height=heigth/8;
	text[MENUTITLE].width=width/30;
	text[MENUTITLE].color[0]=1.0;text[MENUTITLE].color[1]=0.25;text[MENUTITLE].color[2]=0.1;
	text[MENUSUBT].type="Courier New";
	text[MENUSUBT].thickness=FW_NORMAL;
	text[MENUSUBT].italic=false;
	text[MENUSUBT].strike=false;
	text[MENUSUBT].underline=false;
	text[MENUSUBT].height=heigth/10;
	text[MENUSUBT].width=width/50;
	text[MENUSUBT].color[0]=0.25;text[MENUSUBT].color[1]=0.25;text[MENUSUBT].color[2]=1.0;
	loopi(loop1,TEXTTYPES)
	{
		text[loop1].base=glGenLists(96);
		text[loop1].font=CreateFont(text[loop1].height,text[loop1].width,0,0,text[loop1].thickness,text[loop1].italic,text[loop1].underline,text[loop1].strike,
			ANSI_CHARSET,OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY|CLEARTYPE_QUALITY|ANTIALIASED_QUALITY,FF_MODERN|FIXED_PITCH,text[MENUPUSH].type);
		text[loop1].oldfont=(HFONT)SelectObject(hDC,text[loop1].font);
		wglUseFontBitmaps(hDC,32,96,text[loop1].base);
		SelectObject(hDC,text[loop1].oldfont);
		DeleteObject(text[loop1].font);
	}
	loopi(loop1,INPUTBARS)
	{
		input[loop1].loop=-1;
		input[loop1].sloop=-1;
		input[loop1].wait=100.0f;
	}
	loopi(loop1,PUSHBUTTONS)
	{
		push[loop1].clicked=push[loop1].touched=push[loop1].toggle=false;
	}
}

void CleanGUI()
{
	loopi(loop1,TEXTTYPES)
	{
		glDeleteLists(text[loop1].base,96);
	}
}

void PrintText(char*Text,double x,double y,const unsigned int texttype)
{
	if (Text==NULL)
		return;
	glColor3dv(text[texttype].color);
	glRasterPos2d(x,y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(text[texttype].base-32);
	glCallLists(strlen(Text),GL_UNSIGNED_BYTE,Text);
	glPopAttrib();
}

void PrintValue(double value,bool integer,double x,double y,const unsigned int texttype)
{
	char Text[7];
	if (integer)
		sprintf(Text,"%d",(int)value);
	else
		sprintf(Text,"%5.1f",value);
	if (value=NULL)
		return;
	glColor3dv(text[texttype].color);
	glRasterPos2d(x,y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(text[texttype].base-32);
	glCallLists(strlen(Text),GL_UNSIGNED_BYTE,Text);
	glPopAttrib();
}

void PushButton(char*Text,double x,double y,double color[4],const unsigned int name)
{
	double pwidth=strlen(Text)*(double)text[MENUPUSH].width*(20.0/(double)width)+0.4;
	if (mx>=width-((20.0-(x+10.0))*((double)width/20.0))&&
		mx<=width-((20.0-(x+pwidth+10.0))*((double)width/20.0))&&
		my<=(20.0-(y+10.0))*((double)heigth/20.0)&&
		my>=(20.0-(y+11.0))*((double)heigth/20.0))
	{
		push[name].touched=true;
		if (lmouse&&!push[name].toggle)
			push[name].clicked=push[name].toggle=true;
		else if (lmouse&&push[name].clicked)
			push[name].clicked=false;
		else if (!lmouse)
			push[name].toggle=false;
	}
	else
	{
		push[name].touched=false;
		push[name].clicked=false;
	}
	if (push[name].touched)
		glColor3d(0.8,0.8,0.8);
	else
		glColor3dv(color);
	glBegin(GL_QUADS);
	glVertex2d(x,y);
	glVertex2d(x,y+1.0);
	glVertex2d(x+pwidth,y+1.0);
	glVertex2d(x+pwidth,y);
	glEnd();
	PrintText(Text,x+0.2,y+0.25,MENUPUSH);
}

void InputBar(double x,double y,double pwidth,double color[4],bool text,const unsigned int name)
{
	if (mx>=width-((20.0-(x+10.0))*((double)width/20.0))&&
		mx<=width-((20.0-(x+pwidth+10.0))*((double)width/20.0))&&
		my<=(20.0-(y+10.0))*((double)heigth/20.0)&&
		my>=(20.0-(y+11.0))*((double)heigth/20.0))
	{
		if (lmouse)
			input[name].clicked=true;
	}
	else
	{
		input[name].clicked=false;
	}
	if (input[name].clicked)
		glColor3d(0.7,0.7,0.7);
	else
		glColor3dv(color);
	glBegin(GL_QUADS);
	glVertex2d(x,y);
	glVertex2d(x,y+1.0);
	glVertex2d(x+pwidth,y+1.0);
	glVertex2d(x+pwidth,y);
	glEnd();
	if ((double)strlen(input[name].curtext)*0.249+0.349>=pwidth)
		input[name].aloud=false;
	else
		input[name].aloud=true;
	if (input[name].clicked)
	{
		if (input[name].time==0)
			input[name].time=timer.GetTime();
		if (timer.GetTime()-input[name].time>=input[name].wait)
		{
			if (input[name].aloud)
			{
				if (key[0x30]||key[0x31]||key[0x32]||key[0x33]||key[0x34]||key[0x35]||key[0x36]||key[0x37]||key[0x38]||key[0x39]||
					key[0x41]||key[0x42]||key[0x43]||key[0x44]||key[0x45]||key[0x46]||key[0x47]||key[0x48]||key[0x49]||
					key[0x4A]||key[0x4B]||key[0x4C]||key[0x4D]||key[0x4E]||key[0x4F]||
					key[0x50]||key[0x51]||key[0x52]||key[0x53]||key[0x54]||key[0x55]||key[0x56]||key[0x57]||key[0x58]||key[0x59]||
					key[0x5A]||
					key[VK_OEM_1]||key[VK_OEM_PERIOD]||key[VK_OEM_2]||key[VK_SPACE]||key[VK_OEM_6]||key[VK_OEM_4]||
					key[VK_OEM_3]||key[VK_OEM_PLUS]||key[VK_OEM_MINUS]||key[VK_OEM_COMMA])
				{
					input[name].loop++;
					input[name].sloop++;
					// Numbers
					if (key[0x30]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='0';
					else if (key[0x31]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='1';
					else if (key[0x32]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='2';
					else if (key[0x33]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='3';
					else if (key[0x34]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='4';
					else if (key[0x35]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='5';
					else if (key[0x36]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='6';
					else if (key[0x37]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='7';
					else if (key[0x38])
						input[name].curtext[input[name].loop]='8';
					else if (key[0x39]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='9';
					// Letters
					else if (key[0x41])
						input[name].curtext[input[name].loop]='a';
					else if (key[0x42])
						input[name].curtext[input[name].loop]='b';
					else if (key[0x43])
						input[name].curtext[input[name].loop]='c';
					else if (key[0x44])
						input[name].curtext[input[name].loop]='d';
					else if (key[0x45])
						input[name].curtext[input[name].loop]='e';
					else if (key[0x46])
						input[name].curtext[input[name].loop]='f';
					else if (key[0x47])
						input[name].curtext[input[name].loop]='g';
					else if (key[0x48])
						input[name].curtext[input[name].loop]='h';
					else if (key[0x49])
						input[name].curtext[input[name].loop]='i';
					else if (key[0x4A])
						input[name].curtext[input[name].loop]='j';
					else if (key[0x4B])
						input[name].curtext[input[name].loop]='k';
					else if (key[0x4C])
						input[name].curtext[input[name].loop]='l';
					else if (key[0x4D])
						input[name].curtext[input[name].loop]='m';
					else if (key[0x4E])
						input[name].curtext[input[name].loop]='n';
					else if (key[0x4F])
						input[name].curtext[input[name].loop]='o';
					else if (key[0x50])
						input[name].curtext[input[name].loop]='p';
					else if (key[0x51])
						input[name].curtext[input[name].loop]='q';
					else if (key[0x52])
						input[name].curtext[input[name].loop]='r';
					else if (key[0x53])
						input[name].curtext[input[name].loop]='s';
					else if (key[0x54])
						input[name].curtext[input[name].loop]='t';
					else if (key[0x55])
						input[name].curtext[input[name].loop]='u';
					else if (key[0x56])
						input[name].curtext[input[name].loop]='v';
					else if (key[0x57])
						input[name].curtext[input[name].loop]='w';
					else if (key[0x58])
						input[name].curtext[input[name].loop]='x';
					else if (key[0x59])
						input[name].curtext[input[name].loop]='y';
					else if (key[0x5A])
						input[name].curtext[input[name].loop]='z';
					// Symbols
					else if (key[VK_OEM_1]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]=';';
					else if (key[VK_OEM_1]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]=':';
					else if (key[VK_OEM_PERIOD])
						input[name].curtext[input[name].loop]='.';
					else if (key[VK_OEM_COMMA])
						input[name].curtext[input[name].loop]=',';
					else if (key[VK_OEM_2])
						input[name].curtext[input[name].loop]='/';
					else if (key[VK_SPACE])
						input[name].curtext[input[name].loop]=' ';
					else if (key[0x31]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='!';
					else if (key[0x32]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='@';
					else if (key[0x33]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='#';
					else if (key[0x34]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='$';
					else if (key[0x35]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='%';
					else if (key[0x36]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='^';
					else if (key[0x37]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='&';
					else if (key[VK_OEM_3]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='`';
					else if (key[VK_OEM_3]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='~';
					// Brackets
					else if (key[0x30]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]=')';
					else if (key[0x39]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='(';
					else if (key[VK_OEM_4]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='[';
					else if (key[VK_OEM_4]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='{';
					else if (key[VK_OEM_6]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]=']';
					else if (key[VK_OEM_6]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='}';
					// Math
					else if (key[VK_OEM_PLUS]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='=';
					else if (key[VK_OEM_PLUS]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='+';
					else if (key[VK_OEM_MINUS]&&!key[VK_SHIFT])
						input[name].curtext[input[name].loop]='-';
					else if (key[VK_OEM_MINUS]&&key[VK_SHIFT])
						input[name].curtext[input[name].loop]='_';
				}
			}
			if (key[VK_LEFT]&&input[name].loop>=0)
			{
				input[name].loop--;
			}
			else if (key[VK_RIGHT]&&(double)input[name].loop*0.249+0.349<=pwidth)
			{
				input[name].loop++;
			}
			if (key[VK_BACK])
			{
				if (input[name].loop>=0)
				{
					input[name].curtext[input[name].loop]=NULL;
					input[name].loop--;
					input[name].sloop--;
				}
			}
			input[name].time=0;
		}
		glColor3d(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex2d(x+((double)input[name].loop+1.0)*0.249+0.1-(input[name].sloop-input[name].loop)*0.249,y+0.2);
		glVertex2d(x+((double)input[name].loop+1.0)*0.249+0.1-(input[name].sloop-input[name].loop)*0.249,y+0.8);
		glEnd();
	}
	PrintText(input[name].curtext,x+0.1,y+0.25,MENUINPUT);
}