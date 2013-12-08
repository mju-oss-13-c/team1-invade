void FireYou(const unsigned int name)
{
	// Check if aloud
	if (you.wait>0)
		return;
	else
		you.wait=bulletdata[name].wait;
	// Check bullets
	if (DATABULLETS[0][name]>0)
	{
		loopi(loop1,MAXBULLETS[name])
		{
			if (!bullet[0][name][loop1].alive)
			{
				bullet[0][name][loop1].alive=true;
				bullet[0][name][loop1].xpos=you.xpos+cos(you.ang/180.0*PI);
				bullet[0][name][loop1].ypos=you.ypos+sin(you.ang/180.0*PI);
				bullet[0][name][loop1].ang=you.ang+ (bulletdata[name].dev>0 ? (bulletdata[name].dev-(rand()%((bulletdata[name].dev*2+1)*10)/10.0)) : 0);
				bullet[0][name][loop1].xdir=cos(bullet[0][name][loop1].ang/180.0*PI);
				bullet[0][name][loop1].ydir=sin(bullet[0][name][loop1].ang/180.0*PI);
				you.xdir-=cos(you.ang/180.0*PI)*bulletdata[name].kickback;
				you.ydir-=sin(you.ang/180.0*PI)*bulletdata[name].kickback;
				DATABULLETS[0][name]--;
				return;
			}
		}
	}
}

void FireEnemies(unsigned int player,const unsigned int name)
{
	// Check if aloud
	if (enemy[player].wait>0)
		return;
	else
		enemy[player].wait=bulletdata[name].wait;
	// Check bullets
	if (DATABULLETS[player+1][name]>0)
	{
		loopi(loop2,MAXBULLETS[name])
		{
			if (!bullet[player+1][name][loop2].alive)
			{
				bullet[player+1][name][loop2].alive=true;
				bullet[player+1][name][loop2].xpos=enemy[player].xpos+cos(enemy[player].ang/180.0*PI);
				bullet[player+1][name][loop2].ypos=enemy[player].ypos+sin(enemy[player].ang/180.0*PI);
				bullet[player+1][name][loop2].ang=enemy[player].ang+ (bulletdata[name].dev>0 ? (bulletdata[name].dev-(rand()%((bulletdata[name].dev*2+1)*10)/10.0)) : 0);
				bullet[player+1][name][loop2].xdir=cos(bullet[player+1][name][loop2].ang/180.0*PI);
				bullet[player+1][name][loop2].ydir=sin(bullet[player+1][name][loop2].ang/180.0*PI);
				enemy[player].xdir-=cos(enemy[player].ang/180.0*PI)*bulletdata[name].kickback;
				enemy[player].ydir-=sin(enemy[player].ang/180.0*PI)*bulletdata[name].kickback;
				DATABULLETS[player+1][name]--;
				return;
			}
		}
	}
}

void FireMates(unsigned int player,const unsigned int name)
{
	// Check if aloud
	if (mate[player].wait>0)
		return;
	else
		mate[player].wait=bulletdata[name].wait;
	// Check bullets
	if (DATABULLETS[player+ENEMIES+1][name]>0)
	{
		loopi(loop2,MAXBULLETS[name])
		{
			if (!bullet[player+ENEMIES+1][name][loop2].alive)
			{
				bullet[player+ENEMIES+1][name][loop2].alive=true;
				bullet[player+ENEMIES+1][name][loop2].xpos=mate[player].xpos+cos(mate[player].ang/180.0*PI);
				bullet[player+ENEMIES+1][name][loop2].ypos=mate[player].ypos+sin(mate[player].ang/180.0*PI);
				bullet[player+ENEMIES+1][name][loop2].ang=mate[player].ang+ (bulletdata[name].dev>0 ? (bulletdata[name].dev-(rand()%((bulletdata[name].dev*2+1)*10)/10.0)) : 0);
				bullet[player+ENEMIES+1][name][loop2].xdir=cos(bullet[player+ENEMIES+1][name][loop2].ang/180.0*PI);
				bullet[player+ENEMIES+1][name][loop2].ydir=sin(bullet[player+ENEMIES+1][name][loop2].ang/180.0*PI);
				mate[player].xdir-=cos(mate[player].ang/180.0*PI)*bulletdata[name].kickback;
				mate[player].ydir-=sin(mate[player].ang/180.0*PI)*bulletdata[name].kickback;
				DATABULLETS[player+ENEMIES+1][name]--;
				return;
			}
		}
	}
}

void MoveYou()
{
	if (you.alive)
	{
		// Moving
		if (key[VK_RIGHT])
		{
			you.ang-=1.0;
		}
		else if (key[VK_LEFT])
		{
			you.ang+=1.0;
		}
		if (you.ang==361.0)
			you.ang=1.0;
		else if (you.ang==0.0)
			you.ang=360.0;
		if (key[VK_UP])
		{
			you.xdir=cos(you.ang/180.0*PI)*you.speed;
			you.ydir=sin(you.ang/180.0*PI)*you.speed;
		}
		else if (key[VK_DOWN])
		{
			you.xdir=-cos(you.ang/180.0*PI)*you.speed;
			you.ydir=-sin(you.ang/180.0*PI)*you.speed;
		}
		else
		{
			you.xdir=0.0;
			you.ydir=0.0;
		}
		// Shooting
		if (shootswitch)
		{
			if (DATABULLETS[0][0]==0&&DATABULLETS[0][1]==0&&DATABULLETS[0][2]==0&&DATABULLETS[0][3]==0&&DATABULLETS[0][4]==0&&DATABULLETS[0][5]==0&&DATABULLETS[0][6]==0)
				shootswitch=false;
			if (shootswitch)
			{
				if (key[0x44])
				{
					if (you.weapon==BULLETTYPES-1)
						you.weapon=0;
					else
						you.weapon++;
					while (DATABULLETS[0][you.weapon]<=0)
					{
						if (you.weapon==BULLETTYPES-1)
							you.weapon=0;
						else
							you.weapon++;
					}
					shootswitch=false;
				}
				else if (key[0x41])
				{
					if (you.weapon==0)
						you.weapon=BULLETTYPES-1;
					else
						you.weapon--;
					while (DATABULLETS[0][you.weapon]==0)
					{
						if (you.weapon==0)
							you.weapon=BULLETTYPES-1;
						else
							you.weapon--;
					}
					shootswitch=false;
				}
			}
		}
		else
		{
			if (!key[0x41]&&!key[0x44])
				shootswitch=true;
		}
		// Auto-switch
		bool noammo=true;
		if (DATABULLETS[0][0]==0&&DATABULLETS[0][1]==0&&DATABULLETS[0][2]==0&&DATABULLETS[0][3]==0&&DATABULLETS[0][4]==0&&DATABULLETS[0][5]==0&&DATABULLETS[0][6]==0)
			noammo=false;
		while (DATABULLETS[0][you.weapon]==0&&shootswitch)
		{
			if (you.weapon==BULLETTYPES-1)
				you.weapon=0;
			else
				you.weapon++;
		}
		// Firing
		if (you.wait>0)
			you.wait--;
		if (key[0x57])
			FireYou(you.weapon);
		// Initial position
		you.xpos+=you.xdir;
		you.ypos+=you.ydir;
	}
}

void MoveEnemies()
{
	loopi(loop1,ENEMIES)
	{
		// Computing actions
		if (enemy[loop1].alive)
		{
			if (aienemy[loop1].wait>0)
				aienemy[loop1].wait--;
			if (aienemy[loop1].wait2>0)
				aienemy[loop1].wait2--;
			// Select target
			if (aienemy[loop1].attack==MAXMATES+MAXENEMIES+2)
				aienemy[loop1].attack=rand()%(MATES+1);
			if (aienemy[loop1].attack!=0&&!mate[aienemy[loop1].attack-1].alive)
			{
				loopi(loop2,MATES)
				{
					if (mate[loop2].alive)
						aienemy[loop1].attack=loop2+1;
				}
				if (rand()%3==1)
					aienemy[loop1].attack=0;
			}
			else if (aienemy[loop1].attack==0&&!you.alive)
			{
				loopi(loop2,MATES)
				{
					if (mate[loop2].alive)
						aienemy[loop1].attack=loop2+1;
				}
			}
			loopi(loop2,MATES)
			{
				if (mate[loop2].alive&&distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)<=12.0)
					aienemy[loop1].attack=loop2+1;
			}
			if (you.alive&&distance(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos)<=12.0)
				aienemy[loop1].attack=0;
			// You tactics
			if (aienemy[loop1].attack==0&&you.alive&&flag[0].owner!=loop1&&flag[0].prim!=loop1)
			{
				if (aienemy[loop1].wait==0)
				{
					if (rand()%4==1)
					{
						aienemy[loop1].forward=false;
						aienemy[loop1].back=true;
					}
					else if (strcmp(game.type,"CTEF")==0&&rand()%5==1)
					{
						aienemy[loop1].forward=aienemy[loop1].back=false;
					}
					else
					{
						aienemy[loop1].forward=true;
						aienemy[loop1].back=false;
					}
					aienemy[loop1].wait=rand()%201+80+rand()%41;
				}
				enemy[loop1].ang=direction(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos);
				// Selecting the weapon
				if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=6.0&&DATABULLETS[loop1+1][MINI]>0)
				{
					enemy[loop1].weapon=MINI;
				}
				else if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=10.0&&you.lives<=15&&DATABULLETS[loop1+1][ROCKET]>0)
				{
					enemy[loop1].weapon=ROCKET;
				}
				else if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=13.0&&DATABULLETS[loop1+1][CANNON]>0)
				{
					enemy[loop1].weapon=CANNON;
				}
				else if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=16.0&&DATABULLETS[loop1+1][SHELL]>0)
				{
					enemy[loop1].weapon=SHELL;
				}
				else if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=23.0&&DATABULLETS[loop1+1][RIFLE]>0)
				{
					enemy[loop1].weapon=RIFLE;
				}
				else if (DATABULLETS[loop1+1][ANTI]>0)
				{
					enemy[loop1].weapon=ANTI;
				}
				else
				{
					loopi(loop2,BULLETTYPES)
					{
						if (DATABULLETS[loop1+1][loop2]>0)
							enemy[loop1].weapon=loop2;
					}
				}
				// Determine shots
				if (you.alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos))/PI*180.0)&&
					enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos))/PI*180.0))
					aienemy[loop1].shoot=true;
				loopi(loop2,ENEMIES)
				{
					if (loop1!=loop2&&enemy[loop2].alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0)&&
						enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0))
						aienemy[loop1].shoot=false;
				}
			}
			// Mate tactics
			else if (mate[aienemy[loop1].attack-1].alive&&flag[0].owner!=loop1&&flag[0].prim!=loop1)
			{
				if (aienemy[loop1].wait==0)
				{
					if (rand()%4==1)
					{
						aienemy[loop1].forward=false;
						aienemy[loop1].back=true;
					}
					else if (strcmp(game.type,"CTEF")==0&&rand()%5==1)
					{
						aienemy[loop1].forward=aienemy[loop1].back=false;
					}
					else
					{
						aienemy[loop1].forward=true;
						aienemy[loop1].back=false;
					}
					aienemy[loop1].wait=rand()%201+80+rand()%41;
				}
				enemy[loop1].ang=direction(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos);
				// Selecting the weapon
				if (distance(mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=5.0&&DATABULLETS[loop1+1][MINI]>0)
				{
					enemy[loop1].weapon=MINI;
				}
				else if (distance(mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=10.0&&mate[aienemy[loop1].attack-1].lives<=15&&DATABULLETS[loop1+1][ROCKET]>0)
				{
					enemy[loop1].weapon=ROCKET;
				}
				else if (distance(mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=13.0&&DATABULLETS[loop1+1][CANNON]>0)
				{
					enemy[loop1].weapon=CANNON;
				}
				else if (distance(mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=16.0&&DATABULLETS[loop1+1][SHELL]>0)
				{
					enemy[loop1].weapon=SHELL;
				}
				else if (distance(mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=23.0&&DATABULLETS[loop1+1][RIFLE]>0)
				{
					enemy[loop1].weapon=RIFLE;
				}
				else if (DATABULLETS[loop1+1][ANTI]>0)
				{
					enemy[loop1].weapon=ANTI;
				}
				else
				{
					loopi(loop2,BULLETTYPES)
					{
						if (DATABULLETS[loop1+1][loop2]>0)
							enemy[loop1].weapon=loop2;
					}
				}
				// Determine shots
				if (mate[aienemy[loop1].attack-1].alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos))/PI*180.0)&&
					enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos))/PI*180))
					aienemy[loop1].shoot=true;
				loopi(loop2,ENEMIES)
				{
					if (loop1!=loop2&&enemy[loop2].alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0)&&
						enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0))
						aienemy[loop1].shoot=false;
				}
			}
			// Random moving
			else
			{
				if (strcmp(game.type,"CTEF")==0)
				{
					aienemy[loop1].forward=true;
					aienemy[loop1].back=false;
					if (enemy[loop1].ang<-90.0)
					{
						aienemy[loop1].left=true;
						aienemy[loop1].right=false;
					}
					else if (enemy[loop1].ang>-90.0)
					{
						aienemy[loop1].left=false;
						aienemy[loop1].right=true;
					}
					else
					{
						aienemy[loop1].left=aienemy[loop1].right=false;
					}
					if (enemy[loop1].lives<30)
					{
						loopi(loop2,THEALTH)
						{
							if (ithealth[loop2].spawned&&distance(enemy[loop1].xpos,enemy[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny)<=6.0)
							{
								if (enemy[loop1].ang<direction(enemy[loop1].xpos,enemy[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny))
								{
									aienemy[loop1].left=true;
									aienemy[loop1].right=false;
								}
								else if (enemy[loop1].ang>direction(enemy[loop1].xpos,enemy[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny))
								{
									aienemy[loop1].left=false;
									aienemy[loop1].right=true;
								}
								else
								{
									aienemy[loop1].left=aienemy[loop1].right=false;
								}
								aienemy[loop1].forward=true;
								aienemy[loop1].back=false;
							}
						}
					}
					aienemy[loop1].shoot=false;
				}
				else if (strcmp(game.type,"CTF")==0&&!game.stop)
				{
					aienemy[loop1].forward=true;
					aienemy[loop1].back=false;
					if (!flag[0].taken)
						enemy[loop1].ang=direction(enemy[loop1].xpos,enemy[loop1].ypos,flag[0].xpos,flag[0].ypos);
					else
						enemy[loop1].ang=direction(enemy[loop1].xpos,enemy[loop1].ypos,flag[1].xpos,flag[1].ypos);
					// Shooting
					aienemy[loop1].shoot=false;
					if (flag[0].prim==loop1&&you.alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos))/PI*180.0)&&
					enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,you.xpos,you.ypos))/PI*180.0)||
					flag[0].prim==loop1&&mate[aienemy[loop1].attack-1].alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos))/PI*180.0)&&
					enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[aienemy[loop1].attack-1].xpos,mate[aienemy[loop1].attack-1].ypos))/PI*180))
						aienemy[loop1].shoot=true;
					loopi(loop2,ENEMIES)
					{
						if (loop1!=loop2&&enemy[loop2].alive&&enemy[loop1].ang>=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)-(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0)&&
							enemy[loop1].ang<=direction(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)+(atan(1.0/distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos))/PI*180.0))
							aienemy[loop1].shoot=false;
					}
				}
				else
				{
					if (aienemy[loop1].wait==0)
					{
						if (rand()%3==1)
						{
							aienemy[loop1].forward=false;
							aienemy[loop1].back=true;
						}
						else if (rand()%4==1)
						{
							aienemy[loop1].forward=true;
							aienemy[loop1].back=false;
						}
						else
						{
							aienemy[loop1].forward=aienemy[loop1].back=false;
						}
						aienemy[loop1].wait=rand()%201+80+rand()%41;
					}
					if (aienemy[loop1].wait2==0)
					{
						if (rand()%3==1)
						{
							aienemy[loop1].left=true;
							aienemy[loop1].right=false;
						}
						else if (rand()%3==1)
						{
							aienemy[loop1].left=false;
							aienemy[loop1].right=true;
						}
						else
						{
							aienemy[loop1].left=aienemy[loop1].right=false;
						}
						aienemy[loop1].wait2=rand()%51+7+rand()%7;
					}
					aienemy[loop1].shoot=false;
				}
			}
			// Final actions
			if (aienemy[loop1].right)
			{
				enemy[loop1].ang-=1.0;
			}
			else if (aienemy[loop1].left)
			{
				enemy[loop1].ang+=1.0;
			}
			if (enemy[loop1].ang==361.0)
				enemy[loop1].ang=1.0;
			else if (enemy[loop1].ang==0.0)
				enemy[loop1].ang=360.0;
			if (aienemy[loop1].forward)
			{
				enemy[loop1].xdir=cos(enemy[loop1].ang/180.0*PI)*enemy[loop1].speed;
				enemy[loop1].ydir=sin(enemy[loop1].ang/180.0*PI)*enemy[loop1].speed;
			}
			else if (aienemy[loop1].back)
			{
				enemy[loop1].xdir=-cos(enemy[loop1].ang/180.0*PI)*enemy[loop1].speed;
				enemy[loop1].ydir=-sin(enemy[loop1].ang/180.0*PI)*enemy[loop1].speed;
			}
			else
			{
				enemy[loop1].xdir=0.0;
				enemy[loop1].ydir=0.0;
			}
			if (!enemy[loop1].wait==0)
				enemy[loop1].wait--;
			if (aienemy[loop1].shoot)
				FireEnemies(loop1,enemy[loop1].weapon);
			// Initial position
			enemy[loop1].xpos+=enemy[loop1].xdir;
			enemy[loop1].ypos+=enemy[loop1].ydir;
		}
	}
}

void MoveMates()
{
	loopi(loop1,MATES)
	{
		// Computing actions
		if (mate[loop1].alive)
		{
			if (aimate[loop1].wait>0)
				aimate[loop1].wait--;
			if (aimate[loop1].wait2>0)
				aimate[loop1].wait2--;
			// Select target
			if (aimate[loop1].attack==MAXMATES+MAXENEMIES+2)
				aimate[loop1].attack=rand()%ENEMIES;
			if (!enemy[aimate[loop1].attack].alive)
			{
				loopi(loop2,ENEMIES)
				{
					if (enemy[loop2].alive)
						aimate[loop1].attack=loop2;
				}
			}
			loopi(loop2,ENEMIES)
			{
				if (enemy[loop2].alive&&distance(mate[loop1].xpos,mate[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)<=12.0)
					aimate[loop1].attack=loop2;
			}
			// Enemy tactics
			if (enemy[aimate[loop1].attack].alive&&flag[1].owner!=loop1+1&&flag[1].prim!=loop1)
			{
				if (aimate[loop1].wait==0)
				{
					if (rand()%4==1)
					{
						aimate[loop1].forward=false;
						aimate[loop1].back=true;
					}
					else if (strcmp(game.type,"CTEF")==0&&rand()%5==1)
					{
						aimate[loop1].forward=aimate[loop1].back=false;
					}
					else
					{
						aimate[loop1].forward=true;
						aimate[loop1].back=false;
					}
					aimate[loop1].wait=rand()%201+80+rand()%41;
				}
				mate[loop1].ang=direction(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos);
				// Selecting the weapon
				if (distance(enemy[aimate[loop1].attack-1].xpos,enemy[aimate[loop1].attack-1].ypos,mate[loop1].xpos,mate[loop1].ypos)<=5.0&&DATABULLETS[loop1+ENEMIES+1][MINI]>0)
				{
					mate[loop1].weapon=MINI;
				}
				else if (distance(enemy[aimate[loop1].attack-1].xpos,enemy[aimate[loop1].attack-1].ypos,mate[loop1].xpos,mate[loop1].ypos)<=10.0&&enemy[aimate[loop1].attack-1].lives<=15&&DATABULLETS[loop1+ENEMIES+1][ROCKET]>0)
				{
					mate[loop1].weapon=ROCKET;
				}
				else if (distance(enemy[aimate[loop1].attack-1].xpos,enemy[aimate[loop1].attack-1].ypos,mate[loop1].xpos,mate[loop1].ypos)<=13.0&&DATABULLETS[loop1+ENEMIES+1][CANNON]>0)
				{
					mate[loop1].weapon=CANNON;
				}
				else if (distance(enemy[aimate[loop1].attack-1].xpos,enemy[aimate[loop1].attack-1].ypos,mate[loop1].xpos,mate[loop1].ypos)<=16.0&&DATABULLETS[loop1+ENEMIES+1][SHELL]>0)
				{
					mate[loop1].weapon=SHELL;
				}
				else if (distance(enemy[aimate[loop1].attack-1].xpos,enemy[aimate[loop1].attack-1].ypos,mate[loop1].xpos,mate[loop1].ypos)<=23.0&&DATABULLETS[loop1+ENEMIES+1][RIFLE]>0)
				{
					mate[loop1].weapon=RIFLE;
				}
				else if (DATABULLETS[loop1+ENEMIES+1][ANTI]>0)
				{
					mate[loop1].weapon=ANTI;
				}
				else
				{
					loopi(loop2,BULLETTYPES)
					{
						if (DATABULLETS[loop1+ENEMIES+1][loop2]>0)
							mate[loop1].weapon=loop2;
					}
				}
				// Determine shots
				if (enemy[aimate[loop1].attack].alive&&mate[loop1].ang>=direction(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos)-(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos))/PI*180.0)&&
					mate[loop1].ang<=direction(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos)+(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos))/PI*180.0))
					aimate[loop1].shoot=true;
				if (you.alive&&mate[loop1].ang>=direction(mate[loop1].xpos,mate[loop1].ypos,you.xpos,you.ypos)-(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,you.xpos,you.ypos))/PI*180.0)&&
					mate[loop1].ang<=direction(mate[loop1].xpos,mate[loop1].ypos,you.xpos,you.ypos)+(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,you.xpos,you.ypos))/PI*180.0))
					aimate[loop1].shoot=false;
				loopi(loop2,MATES)
				{
					if (loop1!=loop2&&mate[loop2].alive&&mate[loop1].ang>=direction(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)-(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos))/PI*180.0)&&
						mate[loop1].ang<=direction(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)+(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos))/PI*180.0))
						aimate[loop1].shoot=false;
				}
			}
			// Random moving
			else
			{
				if (strcmp(game.type,"CTEF")==0)
				{
					aimate[loop1].forward=true;
					aimate[loop1].back=false;
					if (mate[loop1].ang<90.0)
					{
						aimate[loop1].left=true;
						aimate[loop1].right=false;
					}
					else if (mate[loop1].ang>90.0)
					{
						aimate[loop1].left=false;
						aimate[loop1].right=true;
					}
					else
					{
						aimate[loop1].left=aimate[loop1].right=false;
					}
					if (mate[loop1].lives<30)
					{
						loopi(loop2,THEALTH)
						{
							if (ithealth[loop2].spawned&&distance(mate[loop1].xpos,mate[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny)<=6.0)
							{
								if (mate[loop1].ang<direction(mate[loop1].xpos,mate[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny))
								{
									aimate[loop1].left=true;
									aimate[loop1].right=false;
								}
								else if (mate[loop1].ang>direction(mate[loop1].xpos,mate[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny))
								{
									aimate[loop1].left=false;
									aimate[loop1].right=true;
								}
								else
								{
									aimate[loop1].left=aimate[loop1].right=false;
								}
								aimate[loop1].forward=true;
								aimate[loop1].back=false;
							}
						}
					}
					aimate[loop1].shoot=false;
				}
				else if (strcmp(game.type,"CTF")==0&&!game.stop)
				{
					aimate[loop1].forward=true;
					aimate[loop1].back=false;
					if (!flag[1].taken)
						mate[loop1].ang=direction(mate[loop1].xpos,mate[loop1].ypos,flag[1].xpos,flag[1].ypos);
					else
						mate[loop1].ang=direction(mate[loop1].xpos,mate[loop1].ypos,flag[0].xpos,flag[0].ypos);
					// Shooting
					aimate[loop1].shoot=false;
					if (flag[1].prim==loop1&&enemy[aimate[loop1].attack].alive&&enemy[loop1].ang>=direction(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos)-(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos))/PI*180.0)&&
					mate[loop1].ang<=direction(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos)+(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,enemy[aimate[loop1].attack].xpos,enemy[aimate[loop1].attack].ypos))/PI*180))
						aimate[loop1].shoot=true;
					loopi(loop2,MATES)
					{
						if (loop1!=loop2&&mate[loop2].alive&&mate[loop1].ang>=direction(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)-(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos))/PI*180.0)&&
							mate[loop1].ang<=direction(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)+(atan(1.0/distance(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos))/PI*180.0))
							aimate[loop1].shoot=false;
					}
				}
				else
				{
					if (aimate[loop1].wait==0)
					{
						if (rand()%3==1)
						{
							aimate[loop1].forward=false;
							aimate[loop1].back=true;
						}
						else if (rand()%4==1)
						{
							aimate[loop1].forward=true;
							aimate[loop1].back=false;
						}
						else
						{
							aimate[loop1].forward=aimate[loop1].back=false;
						}
						aimate[loop1].wait=rand()%201+80+rand()%41;
					}
					if (aimate[loop1].wait2==0)
					{
						if (rand()%3==1)
						{
							aimate[loop1].left=true;
							aimate[loop1].right=false;
						}
						else if (rand()%3==1)
						{
							aimate[loop1].left=false;
							aimate[loop1].right=true;
						}
						else
						{
							aimate[loop1].left=aimate[loop1].right=false;
						}
						aimate[loop1].wait2=rand()%51+7+rand()%7;
					}
					aimate[loop1].shoot=false;
				}
			}
		}
		// Final actions
		if (mate[loop1].alive)
		{
			if (aimate[loop1].right)
			{
				mate[loop1].ang-=1.0;
			}
			else if (aimate[loop1].left)
			{
				mate[loop1].ang+=1.0;
			}
			if (mate[loop1].ang==361.0)
				mate[loop1].ang=1.0;
			else if (mate[loop1].ang==0.0)
				mate[loop1].ang=360.0;
			if (aimate[loop1].forward)
			{
				mate[loop1].xdir=cos(mate[loop1].ang/180.0*PI)*mate[loop1].speed;
				mate[loop1].ydir=sin(mate[loop1].ang/180.0*PI)*mate[loop1].speed;
			}
			else if (aimate[loop1].back)
			{
				mate[loop1].xdir=-cos(mate[loop1].ang/180.0*PI)*mate[loop1].speed;
				mate[loop1].ydir=-sin(mate[loop1].ang/180.0*PI)*mate[loop1].speed;
			}
			else
			{
				mate[loop1].xdir=0.0;
				mate[loop1].ydir=0.0;
			}
			if (!mate[loop1].wait==0)
				mate[loop1].wait--;
			if (aimate[loop1].shoot)
				FireMates(loop1,mate[loop1].weapon);
			// Initial position
			mate[loop1].xpos+=mate[loop1].xdir;
			mate[loop1].ypos+=mate[loop1].ydir;
		}
	}
}

void MoveBullets()
{
	// Bullets
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,BULLETTYPES)
		{
			loopi(loop3,MAXBULLETS[loop2])
			{
				if (bullet[loop1][loop2][loop3].alive)
				{
					bullet[loop1][loop2][loop3].xpos+=bullet[loop1][loop2][loop3].xdir*bulletdata[loop2].speed;
					bullet[loop1][loop2][loop3].ypos+=bullet[loop1][loop2][loop3].ydir*bulletdata[loop2].speed;
				}
			}
		}
	}
}

void RenderBullets()
{
	// Cannons
	glPointSize(4.0f);
	glColor3d(0.8,0.5,0.4);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[CANNON])
		{
			if (bullet[loop1][CANNON][loop2].alive)
			{
				glBegin(GL_POINTS);
				glVertex2d(bullet[loop1][CANNON][loop2].xpos,bullet[loop1][CANNON][loop2].ypos);
				glEnd();
			}
		}
	}
	// Rifles
	glLineWidth(1.0f);
	glColor3d(1.0,1.0,0.5);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[RIFLE])
		{
			if (bullet[loop1][RIFLE][loop2].alive)
			{
				glPushMatrix();
				glTranslated(bullet[loop1][RIFLE][loop2].xpos,bullet[loop1][RIFLE][loop2].ypos,0.0);
				glRotated(bullet[loop1][RIFLE][loop2].ang,0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2d(-0.4,0.0);
				glVertex2d(0.0,0.0);
				glEnd();
				glPopMatrix();
			}
		}
	}
	// Anti-air
	glLineWidth(2.0f);
	glColor3d(0.5,0.8,0.8);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[ANTI])
		{
			if (bullet[loop1][ANTI][loop2].alive)
			{
				glPushMatrix();
				glTranslated(bullet[loop1][ANTI][loop2].xpos,bullet[loop1][ANTI][loop2].ypos,0.0);
				glRotated(bullet[loop1][ANTI][loop2].ang,0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2d(-0.65,0.0);
				glVertex2d(0.0,0.0);
				glEnd();
				glPopMatrix();
			}
		}
	}
	// Heavy cannons
	glColor3d(0.6,0.6,0.6);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[ROCKET])
		{
			if (bullet[loop1][ROCKET][loop2].alive)
			{
				glPushMatrix();
				glTranslated(bullet[loop1][ROCKET][loop2].xpos,bullet[loop1][ROCKET][loop2].ypos,0.0);
				glRotated(bullet[loop1][ROCKET][loop2].ang,0.0,0.0,1.0);
				glBegin(GL_TRIANGLES);
				glVertex2d(0.0,0.0);
				glVertex2d(-0.4,0.1);
				glVertex2d(-0.4,-0.1);
				glEnd();
				glPopMatrix();
			}
		}
	}
	// Artillery shell
	glColor3d(0.4,0.5,0.4);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[SHELL])
		{
			if (bullet[loop1][SHELL][loop2].alive)
			{
				glPushMatrix();
				glTranslated(bullet[loop1][SHELL][loop2].xpos,bullet[loop1][SHELL][loop2].ypos,0.0);
				glRotated(bullet[loop1][SHELL][loop2].ang,0.0,0.0,1.0);
				glBegin(GL_POLYGON);
				glVertex2d(-0.1,0.06);
				glVertex2d(0.0,0.0);
				glVertex2d(-0.1,-0.06);
				glVertex2d(-0.25,-0.08);
				glVertex2d(-0.25,0.08);
				glEnd();
				glPopMatrix();
			}
		}
	}
	// Minigun
	glPointSize(2.0f);
	glColor3d(0.9,0.9,1.0);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[MINI])
		{
			if (bullet[loop1][MINI][loop2].alive)
			{
				glBegin(GL_POINTS);
				glVertex2d(bullet[loop1][MINI][loop2].xpos,bullet[loop1][MINI][loop2].ypos);
				glEnd();
			}
		}
	}
	// CTFCannon
	glLineWidth(1.5f);
	glColor3d(0.25,1.0,0.5);
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,MAXBULLETS[CTFCAN])
		{
			if (bullet[loop1][CTFCAN][loop2].alive)
			{
				glPushMatrix();
				glTranslated(bullet[loop1][CTFCAN][loop2].xpos,bullet[loop1][CTFCAN][loop2].ypos,0.0);
				glRotated(bullet[loop1][CTFCAN][loop2].ang,0.0,0.0,1.0);
				glBegin(GL_LINES);
				glVertex2d(-0.3,0.0);
				glVertex2d(0.0,0.0);
				glEnd();
				glPopMatrix();
			}
		}
	}
}

void MoveParticles()
{
	loopi(loop1,ENEMIES+MATES+1)
	{
		loopi(loop2,PARTICLES[loop1])
		{
			if (explosion[loop1][loop2].alive&&explosion[loop1][loop2].a>0.0)
			{
				explosion[loop1][loop2].xpos+=explosion[loop1][loop2].xdir*explosion[loop1][loop2].speed;
				explosion[loop1][loop2].ypos+=explosion[loop1][loop2].ydir*explosion[loop1][loop2].speed;
				explosion[loop1][loop2].a-=(rand()%10+1.0)/(200.0-rand()%51);
			}
		}
	}
}

void RenderParticles()
{
	// Init
	if (!game.smooth)
		glEnable(GL_BLEND);
	loopi(loop1,ENEMIES+MATES+1)
	{
		loopi(loop2,PARTICLES[loop1])
		{
			if (explosion[loop1][loop2].alive&&explosion[loop1][loop2].a>0.0)
			{
				glPointSize(explosion[loop1][loop2].size);
				glColor4d(explosion[loop1][loop2].r,explosion[loop1][loop2].g,explosion[loop1][loop2].b,explosion[loop1][loop2].a);
				glBegin(GL_POINTS);
				glVertex2d(explosion[loop1][loop2].xpos,explosion[loop1][loop2].ypos);
				glEnd();
			}
		}
	}
	if (!game.smooth)
		glDisable(GL_BLEND);
}

void Collisions()
{
	/* Players */
	// Initialization
	you.xfriction=you.yfriction=1.0;
	you.blocky=you.blockx=false;
	x=you.xdir;y=you.ydir;
	loopi(loop1,ENEMIES)
	{
		enemy[loop1].blocky=enemy[loop1].blockx=false;
		enemy[loop1].xfriction=enemy[loop1].yfriction=1.0;
		x2[loop1]=enemy[loop1].xdir;y2[loop1]=enemy[loop1].ydir;
	}
	loopi(loop1,MATES)
	{
		mate[loop1].blocky=mate[loop1].blockx=false;
		mate[loop1].xfriction=mate[loop1].yfriction=1.0;
		x3[loop1]=mate[loop1].xdir;y3[loop1]=mate[loop1].ydir;
	}
	// Cubes
	loopi(loop1,SQUARES)
	{
		if (you.xpos>=cube[loop1].xpos-cube[loop1].sizex-1.0&&you.xpos<=cube[loop1].xpos+cube[loop1].sizex+1.0&&
			you.ypos>=cube[loop1].ypos-cube[loop1].sizey-1.0&&you.ypos<=cube[loop1].ypos+cube[loop1].sizey+1.0)
		{
			if (direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(cube[loop1].sizex+1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
				direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0))
			{
				you.blocky=true;
				if (you.ydir<0.0)
				{
					you.ydir=0.0;you.xfriction= you.xfriction==0.75 ? you.xfriction : 0.75;
					if (you.ypos<cube[loop1].ypos+cube[loop1].sizey+1.0)
						you.ydir=(cube[loop1].ypos+cube[loop1].sizey+1.0)-you.ypos;
				}
			}
			else if (direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0)&&
				direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(cube[loop1].sizex+1.0,-cube[loop1].sizey-1.0,0.0,0.0))
			{
				you.blocky=true;
				if (you.ydir>0.0)
				{
					you.ydir=0.0;you.xfriction= you.xfriction==0.75 ? you.xfriction : 0.75;
					if (you.ypos>cube[loop1].ypos-cube[loop1].sizey-1.0)
						you.ydir=(cube[loop1].ypos-cube[loop1].sizey-1.0)-you.ypos;
				}
			}
			else if (direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
				direction(you.xpos,you.ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0))
			{
				you.blockx=true;
				if (you.xdir>0.0)
				{
					you.xdir=0.0;you.yfriction= you.yfriction==0.75 ? you.yfriction : 0.75;
					if (you.xpos>cube[loop1].xpos-cube[loop1].sizex-1.0)
						you.xdir=(cube[loop1].xpos-cube[loop1].sizex-1.0)-you.xpos;
				}
			}
			else
			{
				you.blockx=true;
				if (you.xdir<0.0)
				{
					you.xdir=0.0;you.yfriction= you.yfriction==0.75 ? you.yfriction : 0.75;
					if (you.xpos<cube[loop1].xpos+cube[loop1].sizex+1.0)
						you.xdir=(cube[loop1].xpos+cube[loop1].sizex+1.0)-you.xpos;
				}
			}
		}
	}
	loopi(loop1,SQUARES)
	{
		loopi(loop2,ENEMIES)
		{
			if (enemy[loop2].xpos>=cube[loop1].xpos-cube[loop1].sizex-1.0&&enemy[loop2].xpos<=cube[loop1].xpos+cube[loop1].sizex+1.0&&
				enemy[loop2].ypos>=cube[loop1].ypos-cube[loop1].sizey-1.0&&enemy[loop2].ypos<=cube[loop1].ypos+cube[loop1].sizey+1.0)
			{
				if (direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(cube[loop1].sizex+1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
					direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0))
				{
					enemy[loop2].blocky=true;
					if (enemy[loop2].ydir<0.0)
					{
						enemy[loop2].ydir=0.0;enemy[loop2].xfriction= enemy[loop2].xfriction==0.75 ? enemy[loop2].xfriction : 0.75;
						if (enemy[loop2].ypos<cube[loop1].ypos+cube[loop1].sizey+1.0)
							enemy[loop2].ydir=(cube[loop1].ypos+cube[loop1].sizey+1.0)-enemy[loop2].ypos;
					}
				}
				else if (direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0)&&
					direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(cube[loop1].sizex+1.0,-cube[loop1].sizey-1.0,0.0,0.0))
				{
					enemy[loop2].blocky=true;
					if (enemy[loop2].ydir>0.0)
					{
						enemy[loop2].ydir=0.0;enemy[loop2].xfriction= enemy[loop2].xfriction==0.75 ? enemy[loop2].xfriction : 0.75;
						if (enemy[loop2].ypos>cube[loop1].ypos-cube[loop1].sizey-1.0)
							enemy[loop2].ydir=(cube[loop1].ypos-cube[loop1].sizey-1.0)-enemy[loop2].ypos;
					}
				}
				else if (direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
					direction(enemy[loop2].xpos,enemy[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0))
				{
					enemy[loop2].blockx=true;
					if (enemy[loop2].xdir>0.0)
					{
						enemy[loop2].xdir=0.0;enemy[loop2].yfriction= enemy[loop2].yfriction==0.75 ? enemy[loop2].yfriction : 0.75;
						if (enemy[loop2].xpos>cube[loop1].xpos-cube[loop1].sizex-1.0)
							enemy[loop2].xdir=(cube[loop1].xpos-cube[loop1].sizex-1.0)-enemy[loop2].xpos;
					}
				}
				else
				{
					enemy[loop2].blockx=true;
					if (enemy[loop2].xdir<0.0)
					{
						enemy[loop2].xdir=0.0;enemy[loop2].yfriction= enemy[loop2].yfriction==0.75 ? enemy[loop2].yfriction : 0.75;
						if (enemy[loop2].xpos<cube[loop1].xpos+cube[loop1].sizex+1.0)
							enemy[loop2].xdir=(cube[loop1].xpos+cube[loop1].sizex+1.0)-enemy[loop2].xpos;
					}
				}
			}
		}
		loopi(loop2,MATES)
		{
			if (mate[loop2].xpos>=cube[loop1].xpos-cube[loop1].sizex-1.0&&mate[loop2].xpos<=cube[loop1].xpos+cube[loop1].sizex+1.0&&
				mate[loop2].ypos>=cube[loop1].ypos-cube[loop1].sizey-1.0&&mate[loop2].ypos<=cube[loop1].ypos+cube[loop1].sizey+1.0)
			{
				if (direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(cube[loop1].sizex+1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
					direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0))
				{
					mate[loop2].blocky=true;
					if (mate[loop2].ydir<0.0)
					{
						mate[loop2].ydir=0.0;mate[loop2].xfriction= mate[loop2].xfriction==0.75 ? mate[loop2].xfriction : 0.75;
						if (mate[loop2].ypos<cube[loop1].ypos+cube[loop1].sizey+1.0)
							mate[loop2].ydir=(cube[loop1].ypos+cube[loop1].sizey+1.0)-mate[loop2].ypos;
					}
				}
				else if (direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0)&&
					direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(cube[loop1].sizex+1.0,-cube[loop1].sizey-1.0,0.0,0.0))
				{
					mate[loop2].blocky=true;
					if (mate[loop2].ydir>0.0)
					{
						mate[loop2].ydir=0.0;mate[loop2].xfriction= mate[loop2].xfriction==0.75 ? mate[loop2].xfriction : 0.75;
						if (mate[loop2].ypos>cube[loop1].ypos-cube[loop1].sizey-1.0)
							mate[loop2].ydir=(cube[loop1].ypos-cube[loop1].sizey-1.0)-mate[loop2].ypos;
					}
				}
				else if (direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)>=direction(-cube[loop1].sizex-1.0,cube[loop1].sizey+1.0,0.0,0.0)&&
					direction(mate[loop2].xpos,mate[loop2].ypos,cube[loop1].xpos,cube[loop1].ypos)<=direction(-cube[loop1].sizex-1.0,-cube[loop1].sizey-1.0,0.0,0.0))
				{
					mate[loop2].blockx=true;
					if (mate[loop2].xdir>0.0)
					{
						mate[loop2].xdir=0.0;mate[loop2].yfriction= mate[loop2].yfriction==0.75 ? mate[loop2].yfriction : 0.75;
						if (mate[loop2].xpos>cube[loop1].xpos-cube[loop1].sizex-1.0)
							mate[loop2].xdir=(cube[loop1].xpos-cube[loop1].sizex-1.0)-mate[loop2].xpos;
					}
				}
				else
				{
					mate[loop2].blockx=true;
					if (mate[loop2].xdir<0.0)
					{
						mate[loop2].xdir=0.0;mate[loop2].yfriction= mate[loop2].yfriction==0.75 ? mate[loop2].yfriction : 0.75;
						if (mate[loop2].xpos<cube[loop1].xpos+cube[loop1].sizex+1.0)
							mate[loop2].xdir=(cube[loop1].xpos+cube[loop1].sizex+1.0)-mate[loop2].xpos;
					}
				}
			}
		}
	}
	// Borders
	if (you.xpos<=-18.5)
	{
		you.blockx=true;
		if (you.xdir<=0.0)
		{
			you.xdir=0.0;you.yfriction= you.yfriction==0.5 ? you.yfriction : 0.5;
			you.xpos=-18.5;
		}
	}
	else if (you.xpos>=18.5)
	{
		you.blockx=true;
		if (you.xdir>=0.0)
		{
			you.xdir=0.0;you.yfriction= you.yfriction==0.5 ? you.yfriction : 0.5;
			you.xpos=18.5;
		}
	}
	if (you.ypos<=-14.0)
	{
		you.blocky=true;
		if (you.ydir<=0.0)
		{
			you.ydir=0.0;you.xfriction= you.xfriction==0.5 ? you.xfriction : 0.5;
			you.ypos=-14.0;
		}
	}
	else if (you.ypos>=18.5)
	{
		you.blocky=true;
		if (you.ydir>=0.0)
		{
			you.ydir=0.0;you.xfriction= you.xfriction==0.5 ? you.xfriction : 0.5;
			you.ypos=18.5;
		}
	}
	loopi(loop1,ENEMIES)
	{
		if (enemy[loop1].xpos<=-18.5)
		{
			enemy[loop1].blockx=true;
			if (enemy[loop1].xdir<=0.0)
			{
				enemy[loop1].xdir=0.0;enemy[loop1].yfriction= enemy[loop1].yfriction==0.5 ? enemy[loop1].yfriction : 0.5;
				enemy[loop1].xpos=-18.5;
			}
		}
		else if (enemy[loop1].xpos>=18.5)
		{
			enemy[loop1].blockx=true;
			if (enemy[loop1].xdir>=0.0)
			{
				enemy[loop1].xdir=0.0;enemy[loop1].yfriction= enemy[loop1].yfriction==0.5 ? enemy[loop1].yfriction : 0.5;
				enemy[loop1].xpos=18.5;
			}
		}
		if (enemy[loop1].ypos<=-14.0)
		{
			enemy[loop1].blocky=true;
			if (enemy[loop1].ydir<=0.0)
			{
				enemy[loop1].ydir=0.0;enemy[loop1].xfriction= enemy[loop1].xfriction==0.5 ? enemy[loop1].xfriction : 0.5;
				enemy[loop1].ypos=-14.0;
			}
		}
		else if (enemy[loop1].ypos>=18.5)
		{
			enemy[loop1].blocky=true;
			if (enemy[loop1].ydir>=0.0)
			{
				enemy[loop1].ydir=0.0;enemy[loop1].xfriction= enemy[loop1].xfriction==0.5 ? enemy[loop1].xfriction : 0.5;
				enemy[loop1].ypos=18.5;
			}
		}
	}
	loopi(loop1,MATES)
	{
		if (mate[loop1].xpos<=-18.5)
		{
			mate[loop1].blockx=true;
			if (mate[loop1].xdir<=0.0)
			{
				mate[loop1].xdir=0.0;mate[loop1].yfriction= mate[loop1].yfriction==0.5 ? mate[loop1].yfriction : 0.5;
				mate[loop1].xpos=-18.5;
			}
		}
		else if (mate[loop1].xpos>=18.5)
		{
			mate[loop1].blockx=true;
			if (mate[loop1].xdir>=0.0)
			{
				mate[loop1].xdir=0.0;mate[loop1].yfriction= mate[loop1].yfriction==0.5 ? mate[loop1].yfriction : 0.5;
				mate[loop1].xpos=18.5;
			}
		}
		if (mate[loop1].ypos<=-14.0)
		{
			mate[loop1].blocky=true;
			if (mate[loop1].ydir<=0.0)
			{
				mate[loop1].ydir=0.0;mate[loop1].xfriction= mate[loop1].xfriction==0.5 ? mate[loop1].xfriction : 0.5;
				mate[loop1].ypos=-14.0;
			}
		}
		else if (mate[loop1].ypos>=18.5)
		{
			mate[loop1].blocky=true;
			if (mate[loop1].ydir>=0.0)
			{
				mate[loop1].ydir=0.0;mate[loop1].xfriction= mate[loop1].xfriction==0.5 ? mate[loop1].xfriction : 0.5;
				mate[loop1].ypos=18.5;
			}
		}
	}
	// Players
	loopi(loop1,ENEMIES)
	{
		if (you.alive&&enemy[loop1].alive)
		{
			// You-Enemy
			if (distance(you.xpos,you.ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=2.0)
			{
				if (!you.blockx&&!enemy[loop1].blockx)
				{
					you.xdir+=(x2[loop1]-x)*0.75;
					enemy[loop1].xdir+=(x-x2[loop1])*0.75;
				}
				else
				{
					you.xdir=0.0;enemy[loop1].xdir=0.0;
				}
				if (!you.blocky&&!enemy[loop1].blocky)
				{
					you.ydir+=(y2[loop1]-y)*0.75;
					enemy[loop1].ydir+=(y-y2[loop1])*0.75;
				}
				else
				{
					you.ydir=0.0;enemy[loop1].ydir=0.0;
				}
			}
		}
	}
	loopi(loop1,MATES)
	{
		if (you.alive&&mate[loop1].alive)
		{
			// You-Mate
			if (distance(you.xpos,you.ypos,mate[loop1].xpos,mate[loop1].ypos)<=2.0)
			{
				if (!you.blockx&&!mate[loop1].blockx)
				{
					you.xdir+=(x3[loop1]-x)*0.75;
					mate[loop1].xdir+=(x-x3[loop1])*0.75;
				}
				else
				{
					you.xdir=0.0;mate[loop1].xdir=0.0;
				}
				if (!you.blocky&&!mate[loop1].blocky)
				{
					you.ydir+=(y3[loop1]-y)*0.75;
					mate[loop1].ydir+=(y-y3[loop1])*0.75;
				}
				else
				{
					you.ydir=0.0;mate[loop1].ydir=0.0;
				}
			}
		}
	}
	loopi(loop1,ENEMIES)
	{
		loopi(loop2,ENEMIES)
		{
			if (loop1!=loop2&&enemy[loop1].alive&&enemy[loop2].alive)
			{
				// Enemy-Enemy
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,enemy[loop2].xpos,enemy[loop2].ypos)<=2.0)
				{
					if (!enemy[loop1].blockx&&!enemy[loop2].blockx)
					{
						enemy[loop1].xdir+=(x2[loop2]-x2[loop1])*0.75;
						enemy[loop2].xdir+=(x2[loop1]-x2[loop2])*0.75;
					}
					else
					{
						enemy[loop2].xdir=0.0;enemy[loop1].xdir=0.0;
					}
					if (!enemy[loop1].blocky&&!enemy[loop2].blocky)
					{
						enemy[loop1].ydir+=(y2[loop2]-y2[loop1])*0.75;
						enemy[loop2].ydir+=(y2[loop1]-y2[loop2])*0.75;
					}
					else
					{
						enemy[loop2].ydir=0.0;enemy[loop1].ydir=0.0;
					}
				}
			}
		}
		loopi(loop2,MATES)
		{
			if (enemy[loop1].alive&&mate[loop2].alive)
			{
				// Enemy-Mate
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)<=2.0)
				{
					if (!enemy[loop1].blockx&&mate[loop2].blockx)
					{
						enemy[loop1].xdir+=(x3[loop2]-x2[loop1])*0.75;
						mate[loop2].xdir+=(x2[loop1]-x3[loop2])*0.75;
					}
					else
					{
						mate[loop2].xdir=0.0;enemy[loop1].xdir=0.0;
					}
					if (!enemy[loop1].blocky&&mate[loop2].blocky)
					{
						enemy[loop1].ydir+=(y3[loop2]-y2[loop1])*0.75;
						mate[loop2].ydir+=(y2[loop1]-y3[loop2])*0.75;
					}
					else
					{
						mate[loop2].ydir=0.0;enemy[loop1].ydir=0.0;
					}
				}
			}
		}
	}
	loopi(loop1,MATES)
	{
		loopi(loop2,MATES)
		{
			if (loop1!=loop2&&mate[loop1].alive&&mate[loop2].alive)
			{
				// Mate-Mate
				if (distance(mate[loop1].xpos,mate[loop1].ypos,mate[loop2].xpos,mate[loop2].ypos)<=2.0)
				{
					if (!mate[loop1].blockx&&!mate[loop2].blockx)
					{
							mate[loop1].xdir+=(x3[loop2]-x3[loop1])*0.75;
						mate[loop2].xdir+=(x3[loop1]-x3[loop2])*0.75;
					}
						else
					{
						mate[loop2].xdir=0.0;mate[loop1].xdir=0.0;
					}
					if (!mate[loop1].blocky&&!mate[loop2].blocky)
					{
						mate[loop1].ydir+=(y3[loop2]-y3[loop1])*0.75;
						mate[loop2].ydir+=(y3[loop1]-y3[loop2])*0.75;
					}
					else
					{
						mate[loop2].ydir=0.0;mate[loop1].ydir=0.0;
					}
				}
			}
		}
	}
	// Final position
	if (you.alive)
	{
		you.xpos-=x;you.ypos-=y;
		you.xpos+=you.xdir*you.xfriction;
		you.ypos+=you.ydir*you.yfriction;
	}
	loopi(loop1,ENEMIES)
	{
		if (enemy[loop1].alive)
		{
			enemy[loop1].xpos-=x2[loop1];
			enemy[loop1].ypos-=y2[loop1];
			enemy[loop1].xpos+=enemy[loop1].xdir*enemy[loop1].xfriction;
			enemy[loop1].ypos+=enemy[loop1].ydir*enemy[loop1].yfriction;
		}
	}
	loopi(loop1,MATES)
	{
		if (mate[loop1].alive)
		{
			mate[loop1].xpos-=x3[loop1];
			mate[loop1].ypos-=y3[loop1];
			mate[loop1].xpos+=mate[loop1].xdir*mate[loop1].xfriction;
			mate[loop1].ypos+=mate[loop1].ydir*mate[loop1].yfriction;
		}
	}
	/* Bullets */
	loopi(loop1,ENEMIES)
	{
		loopi(loop2,BULLETTYPES)
		{
			// You hit enemy
			loopi(loop3,MAXBULLETS[loop2])
			{
				if (enemy[loop1].alive&&distance(bullet[0][loop2][loop3].xpos,bullet[0][loop2][loop3].ypos,enemy[loop1].xpos,enemy[loop1].ypos)<=1.0&&bullet[0][loop2][loop3].alive)
				{
					enemy[loop1].lives-=bulletdata[loop2].damage;
					bullet[0][loop2][loop3].alive=false;
				}
			}
			// Enemy hit you
			loopi(loop3,MAXBULLETS[loop2])
			{
				if (you.alive&&distance(bullet[loop1+1][loop2][loop3].xpos,bullet[loop1+1][loop2][loop3].ypos,you.xpos,you.ypos)<=1.0&&bullet[loop1+1][loop2][loop3].alive)
				{
					you.lives-=bulletdata[loop2].damage;
					bullet[loop1+1][loop2][loop3].alive=false;
				}
				// Enemy hit enemy
				loopi(loop4,ENEMIES)
				{
					if (loop1!=loop4&&enemy[loop4].alive&&
						distance(bullet[loop1+1][loop2][loop3].xpos,bullet[loop1+1][loop2][loop3].ypos,enemy[loop4].xpos,enemy[loop4].ypos)<=1.0
						&&bullet[loop1+1][loop2][loop3].alive)
					{
						enemy[loop4].lives-=bulletdata[loop2].damage;
						bullet[loop1+1][loop2][loop3].alive=false;
					}
				}
			}
		}
	}
	loopi(loop1,MATES)
	{
		if(strcmp("TeamKill Off", game.tkonoff)==0)
			break;
		loopi(loop2,BULLETTYPES)
		{
			// You hit mate
			loopi(loop3,MAXBULLETS[loop2])
			{
				if (mate[loop1].alive&&distance(bullet[0][loop2][loop3].xpos,bullet[0][loop2][loop3].ypos,mate[loop1].xpos,mate[loop1].ypos)<=1.0&&bullet[0][loop2][loop3].alive)
				{
					mate[loop1].lives-=bulletdata[loop2].damage;
					bullet[0][loop2][loop3].alive=false;
				}
			}
			loopi(loop3,MAXBULLETS[loop2])
			{
				// Mate hit you
				if (you.alive&&distance(bullet[loop1+ENEMIES+1][loop2][loop3].xpos,bullet[loop1+ENEMIES+1][loop2][loop3].ypos,you.xpos,you.ypos)<=1.0&&bullet[loop1+ENEMIES+1][loop2][loop3].alive)
				{
					you.lives-=bulletdata[loop2].damage;
					bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
				}
				// Mate hit mate
				loopi(loop4,MATES)
				{
					if (loop1!=loop4&&mate[loop4].alive&&bullet[loop1+ENEMIES+1][loop2][loop3].alive&&
						distance(bullet[loop1+ENEMIES+1][loop2][loop3].xpos,bullet[loop1+ENEMIES+1][loop2][loop3].ypos,mate[loop4].xpos,mate[loop4].ypos)<=1.0)
					{
						mate[loop4].lives-=bulletdata[loop2].damage;
						bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
					}
				}
			}
		}
	}
	loopi(loop1,MATES)
	{
		loopi(loop2,BULLETTYPES)
		{
			loopi(loop4,ENEMIES)
			{
				// Mate hit enemy
				loopi(loop3,MAXBULLETS[loop2])
				{
					if (enemy[loop4].alive&&distance(bullet[loop1+ENEMIES+1][loop2][loop3].xpos,bullet[loop1+ENEMIES+1][loop2][loop3].ypos,enemy[loop4].xpos,enemy[loop4].ypos)<=1.0
						&&bullet[loop1+ENEMIES+1][loop2][loop3].alive)
					{
						enemy[loop4].lives-=bulletdata[loop2].damage;
						bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
					}
				}
				// Enemy hit mate
				loopi(loop3,MAXBULLETS[loop2])
				{
					if (mate[loop1].alive&&distance(bullet[loop4+1][loop2][loop3].xpos,bullet[loop4+1][loop2][loop3].ypos,mate[loop1].xpos,mate[loop1].ypos)<=1.0
						&&bullet[loop4+1][loop2][loop3].alive)
					{
						mate[loop1].lives-=bulletdata[loop2].damage;
						bullet[loop4+1][loop2][loop3].alive=false;
					}
				}
			}
		}
	}
	// Cubes
	loopi(loop1,SQUARES)
	{
		loopi(loop2,MATES+ENEMIES+1)
		{
			loopi(loop3,BULLETTYPES)
			{
				loopi(loop4,MAXBULLETS[loop3])
				{
					if (bullet[loop2][loop3][loop4].xpos>=cube[loop1].xpos-cube[loop1].sizex&&bullet[loop2][loop3][loop4].xpos<=cube[loop1].xpos+cube[loop1].sizex&&
						bullet[loop2][loop3][loop4].ypos>=cube[loop1].ypos-cube[loop1].sizey&&bullet[loop2][loop3][loop4].ypos<=cube[loop1].ypos+cube[loop1].sizey
						&&bullet[loop2][loop3][loop4].alive)
					{
						bullet[loop2][loop3][loop4].alive=false;
					}
				}
			}
		}
	}
	// Borders
	loopi(loop1,MATES+ENEMIES+1)
	{
		loopi(loop2,BULLETTYPES)
		{
			loopi(loop3,MAXBULLETS[loop2])
			{
				if (bullet[loop1][loop2][loop3].xpos<=-19.5&&bullet[loop1][loop2][loop3].alive||bullet[loop1][loop2][loop3].xpos>=19.5&&bullet[loop1][loop2][loop3].alive
					||bullet[loop1][loop2][loop3].ypos<=-15.0&&bullet[loop1][loop2][loop3].alive||bullet[loop1][loop2][loop3].ypos>=19.5&&bullet[loop1][loop2][loop3].alive)
				{
					bullet[loop1][loop2][loop3].alive=false;
				}
			}
		}
	}
	/* Flags */
	if (strcmp(game.type,"CTF")==0)
	{
		flag[1].taken=false;
		flag[1].owner=MATES+2;
		if (distance(you.xpos,you.ypos,flag[1].xpos,flag[1].ypos)<=1.25&&!flag[1].taken&&you.alive)
		{
			flag[1].taken=true;
			if (flag[1].wait==0)
				flag[1].wait=300;
			flag[1].xpos=you.xpos;flag[1].ypos=you.ypos;
			flag[1].owner=0;
		}
		else
		{
			loopi(loop1,MATES)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,flag[1].xpos,flag[1].ypos)<=1.25&&!flag[1].taken&&mate[loop1].alive)
				{
					flag[1].taken=true;
					if (flag[1].wait==0)
						flag[1].wait=300;
					flag[1].xpos=mate[loop1].xpos;flag[1].ypos=mate[loop1].ypos;
					flag[1].owner=loop1+1;
					break;
				}
			}
			if (flag[1].owner==MATES+2&&flag[1].xpos!=flag[1].spawnx||flag[1].ypos!=flag[1].spawny)
			{
				if (flag[1].wait>0)
				{
					flag[1].wait--;
				}
				else
				{
					flag[1].xpos=flag[1].spawnx;
					flag[1].ypos=flag[1].spawny;
				}
			}
		}
		flag[0].taken=false;
		flag[0].owner=ENEMIES+1;
		loopi(loop1,ENEMIES)
		{
			if (distance(enemy[loop1].xpos,enemy[loop1].ypos,flag[0].xpos,flag[0].ypos)<=1.25&&!flag[0].taken&&enemy[loop1].alive)
			{
				flag[0].taken=true;
				if (flag[0].wait==0)
					flag[0].wait=300;
				flag[0].xpos=enemy[loop1].xpos;flag[0].ypos=enemy[loop1].ypos;
				flag[0].owner=loop1;
				break;
			}
		}
		if (flag[0].owner==ENEMIES+1&&flag[0].xpos!=flag[0].spawnx||flag[0].ypos!=flag[0].spawny)
		{
			if (flag[0].wait>0)
			{
				flag[0].wait--;
			}
			else
			{
				flag[0].xpos=flag[0].spawnx;
				flag[0].ypos=flag[0].spawny;
			}
		}
		// Returning
		if (distance(you.xpos,you.ypos,flag[0].xpos,flag[0].ypos)<=1.25&&flag[0].wait>0&&you.alive)
		{
			flag[0].wait=0;
			flag[0].xpos=flag[0].spawnx;
			flag[0].ypos=flag[0].spawny;
		}
		else
		{
			loopi(loop1,MATES)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,flag[0].xpos,flag[0].ypos)<=1.25&&flag[0].wait>0&&mate[loop1].alive)
				{
					flag[0].wait=0;
					flag[0].xpos=flag[0].spawnx;
					flag[0].ypos=flag[0].spawny;
					break;
				}
			}
		}
		loopi(loop1,ENEMIES)
		{
			if (distance(enemy[loop1].xpos,enemy[loop1].ypos,flag[1].xpos,flag[1].ypos)<=1.25&&flag[1].wait>0&&enemy[loop1].alive)
			{
				flag[1].wait=0;
				flag[1].xpos=flag[1].spawnx;
				flag[1].ypos=flag[1].spawny;
				break;
			}
		}
		// Scoring
		if (flag[0].taken&&!flag[1].taken&&flag[1].wait==0)
		{
			if (distance(flag[0].xpos,flag[0].ypos,flag[1].xpos,flag[1].ypos)<=1.25)
			{
				flag[0].taken=false;
				flag[0].xpos=flag[0].spawnx;
				flag[0].ypos=flag[0].spawny;
				flag[0].owner=ENEMIES+1;
				game.escore++;
			}
		}
		if (flag[1].taken&&!flag[0].taken&&flag[0].wait==0)
		{
			if (distance(flag[0].xpos,flag[0].ypos,flag[1].xpos,flag[1].ypos)<=1.25)
			{
				flag[1].taken=false;
				flag[1].xpos=flag[1].spawnx;
				flag[1].ypos=flag[1].spawny;
				flag[1].owner=MATES+2;
				game.score++;
			}
		}
	}
	/* Items */
	if (strcmp(game.type,"CTEF")==0)
	{
		loopi(loop1,THEALTH)
		{
			if (distance(you.xpos,you.ypos,ithealth[loop1].spawnx,ithealth[loop1].spawny)<=1.25&&ithealth[loop1].spawned)
			{
				ithealth[loop1].spawned=false;
				you.lives+=ithealth[loop1].add;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,THEALTH)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny)<=1.25&&ithealth[loop2].spawned)
				{
					ithealth[loop2].spawned=false;
					enemy[loop1].lives+=ithealth[loop2].add;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,THEALTH)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,ithealth[loop2].spawnx,ithealth[loop2].spawny)<=1.25&&ithealth[loop2].spawned)
				{
					ithealth[loop2].spawned=false;
					mate[loop1].lives+=ithealth[loop2].add;
				}
			}
		}
	}
	else if (strcmp(game.type,"Survival")==0)
	{
		loopi(loop1,TARIFLE)
		{
			if (distance(you.xpos,you.ypos,itarifle[loop1].spawnx,itarifle[loop1].spawny)<=1.25&&itarifle[loop1].spawned)
			{
				itarifle[loop1].spawned=false;
				DATABULLETS[0][RIFLE]+=itarifle[loop1].add;
				if (DATABULLETS[0][RIFLE]>MAXRIFLE)
					DATABULLETS[0][RIFLE]=MAXRIFLE;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,TARIFLE)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,itarifle[loop2].spawnx,itarifle[loop2].spawny)<=1.25&&itarifle[loop2].spawned)
				{
					itarifle[loop2].spawned=false;
					DATABULLETS[loop1+1][RIFLE]+=itarifle[loop2].add;
					if (DATABULLETS[loop1+1][RIFLE]>MAXRIFLE)
						DATABULLETS[loop1+1][RIFLE]=MAXRIFLE;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,TARIFLE)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,itarifle[loop2].spawnx,itarifle[loop2].spawny)<=1.25&&itarifle[loop2].spawned)
				{
					itarifle[loop2].spawned=false;
					DATABULLETS[loop1+ENEMIES+1][RIFLE]+=itarifle[loop2].add;
					if (DATABULLETS[loop1+ENEMIES+1][RIFLE]>MAXRIFLE)
						DATABULLETS[loop1+ENEMIES+1][RIFLE]=MAXRIFLE;
				}
			}
		}
		loopi(loop1,TMINI)
		{
			if (distance(you.xpos,you.ypos,itmini[loop1].spawnx,itmini[loop1].spawny)<=1.25&&itmini[loop1].spawned)
			{
				itmini[loop1].spawned=false;
				DATABULLETS[0][MINI]+=itmini[loop1].add;
				if (DATABULLETS[0][MINI]>MAXMINI)
					DATABULLETS[0][MINI]=MAXMINI;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,TMINI)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,itmini[loop2].spawnx,itmini[loop2].spawny)<=1.25&&itmini[loop2].spawned)
				{
					itmini[loop2].spawned=false;
					DATABULLETS[loop1+1][MINI]+=itmini[loop2].add;
					if (DATABULLETS[loop1+1][MINI]>MAXMINI)
						DATABULLETS[loop1+1][MINI]=MAXMINI;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,TMINI)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,itmini[loop2].spawnx,itmini[loop2].spawny)<=1.25&&itmini[loop2].spawned)
				{
					itmini[loop2].spawned=false;
					DATABULLETS[loop1+ENEMIES+1][MINI]+=itmini[loop2].add;
					if (DATABULLETS[loop1+ENEMIES+1][MINI]>MAXMINI)
						DATABULLETS[loop1+ENEMIES+1][MINI]=MAXMINI;
				}
			}
		}
		loopi(loop1,TCANNON)
		{
			if (distance(you.xpos,you.ypos,itcannon[loop1].spawnx,itcannon[loop1].spawny)<=1.25&&itcannon[loop1].spawned)
			{
				itcannon[loop1].spawned=false;
				DATABULLETS[0][CANNON]+=itcannon[loop1].add;
				if (DATABULLETS[0][CANNON]>MAXCANNON)
					DATABULLETS[0][CANNON]=MAXCANNON;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,TCANNON)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,itcannon[loop2].spawnx,itcannon[loop2].spawny)<=1.25&&itcannon[loop2].spawned)
				{
					itcannon[loop2].spawned=false;
					DATABULLETS[loop1+1][CANNON]+=itcannon[loop2].add;
					if (DATABULLETS[loop1+1][CANNON]>MAXCANNON)
						DATABULLETS[loop1+1][CANNON]=MAXCANNON;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,TCANNON)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,itcannon[loop2].spawnx,itcannon[loop2].spawny)<=1.25&&itcannon[loop2].spawned)
				{
					itcannon[loop2].spawned=false;
					DATABULLETS[loop1+ENEMIES+1][CANNON]+=itcannon[loop2].add;
					if (DATABULLETS[loop1+ENEMIES+1][CANNON]>MAXCANNON)
						DATABULLETS[loop1+ENEMIES+1][CANNON]=MAXCANNON;
				}
			}
		}
		loopi(loop1,TSHELL)
		{
			if (distance(you.xpos,you.ypos,itshell[loop1].spawnx,itshell[loop1].spawny)<=1.25&&itshell[loop1].spawned)
			{
				itshell[loop1].spawned=false;
				DATABULLETS[0][SHELL]+=itshell[loop1].add;
				if (DATABULLETS[0][SHELL]>MAXSHELL)
					DATABULLETS[0][SHELL]=MAXSHELL;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,TSHELL)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,itshell[loop2].spawnx,itshell[loop2].spawny)<=1.25&&itshell[loop2].spawned)
				{
					itshell[loop2].spawned=false;
					DATABULLETS[loop1+1][SHELL]+=itshell[loop2].add;
					if (DATABULLETS[loop1+1][SHELL]>MAXSHELL)
						DATABULLETS[loop1+1][SHELL]=MAXSHELL;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,TSHELL)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,itshell[loop2].spawnx,itshell[loop2].spawny)<=1.25&&itshell[loop2].spawned)
				{
					itshell[loop2].spawned=false;
					DATABULLETS[loop1+ENEMIES+1][SHELL]+=itshell[loop2].add;
					if (DATABULLETS[loop1+ENEMIES+1][SHELL]>MAXSHELL)
						DATABULLETS[loop1+ENEMIES+1][SHELL]=MAXSHELL;
				}
			}
		}
		loopi(loop1,TROCKET)
		{
			if (distance(you.xpos,you.ypos,itrocket[loop1].spawnx,itrocket[loop1].spawny)<=1.25&&itrocket[loop1].spawned)
			{
				itrocket[loop1].spawned=false;
				DATABULLETS[0][ROCKET]+=itrocket[loop1].add;
				if (DATABULLETS[0][ROCKET]>MAXROCKET)
					DATABULLETS[0][ROCKET]=MAXROCKET;
			}
		}
		loopi(loop1,ENEMIES)
		{
			loopi(loop2,TROCKET)
			{
				if (distance(enemy[loop1].xpos,enemy[loop1].ypos,itrocket[loop2].spawnx,itrocket[loop2].spawny)<=1.25&&itrocket[loop2].spawned)
				{
					itrocket[loop2].spawned=false;
					DATABULLETS[loop1+1][ROCKET]+=itrocket[loop2].add;
					if (DATABULLETS[loop1+1][ROCKET]>MAXROCKET)
						DATABULLETS[loop1+1][ROCKET]=MAXROCKET;
				}
			}
		}
		loopi(loop1,MATES)
		{
			loopi(loop2,TROCKET)
			{
				if (distance(mate[loop1].xpos,mate[loop1].ypos,itrocket[loop2].spawnx,itrocket[loop2].spawny)<=1.25&&itrocket[loop2].spawned)
				{
					itrocket[loop2].spawned=false;
					DATABULLETS[loop1+ENEMIES+1][ROCKET]+=itrocket[loop2].add;
					if (DATABULLETS[loop1+ENEMIES+1][ROCKET]>MAXROCKET)
						DATABULLETS[loop1+ENEMIES+1][ROCKET]=MAXROCKET;
				}
			}
		}
	}
	/* Particles */
	if (!you.alive)
	{
		if (PARTICLES[0]==0)
			PARTICLES[0]=rand()%(MAXPARTICLES/2+1)+MAXPARTICLES/2;
		loopi(loop2,PARTICLES[0])
		{
			if (!explosion[0][loop2].alive)
			{
				explosion[0][loop2].alive=true;
				explosion[0][loop2].xpos=you.xpos;
				explosion[0][loop2].ypos=you.ypos;
				explosion[0][loop2].xdir=cos(rand()%721/2.0/180.0*PI);
				explosion[0][loop2].ydir=sin(rand()%721/2.0/180.0*PI);
				explosion[0][loop2].speed=rand()%10/100.0+0.01;
				explosion[0][loop2].size=rand()%50/10.0f+1.0f;
				explosion[0][loop2].r=rand()%11/10.0;
				explosion[0][loop2].g=rand()%11/10.0;
				explosion[0][loop2].b=rand()%11/10.0;
				explosion[0][loop2].a=1.0;
			}
		}
	}
	loopi(loop1,ENEMIES)
	{
		if (!enemy[loop1].alive)
		{
			if (PARTICLES[loop1+1]==0)
				PARTICLES[loop1+1]=rand()%11+10;
			loopi(loop2,PARTICLES[loop1+1])
			{
				if (!explosion[loop1+1][loop2].alive)
				{
					explosion[loop1+1][loop2].alive=true;
					explosion[loop1+1][loop2].xpos=enemy[loop1].xpos;
					explosion[loop1+1][loop2].ypos=enemy[loop1].ypos;
					explosion[loop1+1][loop2].xdir=cos(rand()%721/2.0/180.0*PI);
					explosion[loop1+1][loop2].ydir=sin(rand()%721/2.0/180.0*PI);
					explosion[loop1+1][loop2].speed=rand()%10/100.0+0.01;
					explosion[loop1+1][loop2].size=rand()%50/10.0f+1.0f;
					explosion[loop1+1][loop2].r=rand()%11/10.0;
					explosion[loop1+1][loop2].g=rand()%11/10.0;
					explosion[loop1+1][loop2].b=rand()%11/10.0;
					explosion[loop1+1][loop2].a=1.0;
				}
			}
		}
	}
	loopi(loop1,MATES)
	{
		if (!mate[loop1].alive)
		{
			if (PARTICLES[loop1+ENEMIES+1]==0)
				PARTICLES[loop1+ENEMIES+1]=rand()%11+10;
			loopi(loop2,PARTICLES[loop1+ENEMIES+1])
			{
				if (!explosion[loop1+ENEMIES+1][loop2].alive)
				{
					explosion[loop1+ENEMIES+1][loop2].alive=true;
					explosion[loop1+ENEMIES+1][loop2].xpos=mate[loop1].xpos;
					explosion[loop1+ENEMIES+1][loop2].ypos=mate[loop1].ypos;
					explosion[loop1+ENEMIES+1][loop2].xdir=cos(rand()%721/2.0/180.0*PI);
					explosion[loop1+ENEMIES+1][loop2].ydir=sin(rand()%721/2.0/180.0*PI);
					explosion[loop1+ENEMIES+1][loop2].speed=rand()%10/100.0+0.01;
					explosion[loop1+ENEMIES+1][loop2].size=rand()%50/10.0f+1.0f;
					explosion[loop1+ENEMIES+1][loop2].r=rand()%11/10.0;
					explosion[loop1+ENEMIES+1][loop2].g=rand()%11/10.0;
					explosion[loop1+ENEMIES+1][loop2].b=rand()%11/10.0;
					explosion[loop1+ENEMIES+1][loop2].a=1.0;
				}
			}
		}
	}
	/* Rules, checking and stats */
	// Interrupted?
	game.inter=true;
	loopi(loop1,BULLETTYPES)
	{
		if (you.alive&&DATABULLETS[0][loop1]>0)
			game.inter=false;
	}
	loopi(loop1,MATES)
	{
		loopi(loop2,BULLETTYPES)
		{
			if (mate[loop1].alive&&DATABULLETS[loop1+ENEMIES+1][loop2]>0)
				game.inter=false;
		}
	}
	loopi(loop1,ENEMIES)
	{
		loopi(loop2,BULLETTYPES)
		{
			if (enemy[loop1].alive&&DATABULLETS[loop1+1][loop2]>0)
				game.inter=false;
		}
	}
	// Died?
	if (you.lives<=0)
	{
		you.lives=0;
		you.alive=false;
		if (strcmp(game.type,"Time battle")==0&&you.spawntime==500&&!game.stop)
			game.escore++;
	}
	loopi(loop1,ENEMIES)
	{
		if (enemy[loop1].lives<=0)
		{
			enemy[loop1].lives=0;
			enemy[loop1].alive=false;
			if (strcmp(game.type,"Time battle")==0&&enemy[loop1].spawntime==500&&!game.stop)
				game.score++;
		}
	}
	loopi(loop1,MATES)
	{
		if (mate[loop1].lives<=0)
		{
			mate[loop1].lives=0;
			mate[loop1].alive=false;
			if (strcmp(game.type,"Time battle")==0&&mate[loop1].spawntime==500&&!game.stop)
				game.escore++;
		}
	}
}

void RenderPlayers()
{
	// Initialization
	glLineWidth(1.5f);
	// You
	if (you.alive)
	{
		glPushMatrix();
		glTranslated(you.xpos,you.ypos,0.0);
		glRotated(you.ang,0.0,0.0,1.0);
		glColor3d(0.2,0.5,0.4);
		glBegin(GL_TRIANGLES);
		glVertex2d(-sin(60.0/180.0*PI),cos(60.0/180.0*PI));
		glVertex2d(-sin(60.0/180.0*PI),-cos(60.0/180.0*PI));
		glVertex2d(1.0,0.0);
		glEnd();
		glColor3d(1.0,1.0,1.0);
		glBegin(GL_LINES);
		loopi(loop2,36)
		{
			glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			glVertex2d(sin(((double)loop2+1.0)*10.0/180.0*PI),cos(((double)loop2+1.0)*10.0/180.0*PI));
		}
		glEnd();
		glPopMatrix();
	}
	// Enemies
	loopi(loop1,ENEMIES)
	{
		if (enemy[loop1].alive)
		{
			glPushMatrix();
			glTranslated(enemy[loop1].xpos,enemy[loop1].ypos,0.0);
			glRotated(enemy[loop1].ang,0.0,0.0,1.0);
			glColor3d(1.0,0.0,0.0);
			glBegin(GL_TRIANGLES);
			glVertex2d(-sin(60.0/180.0*PI),cos(60.0/180.0*PI));
			glVertex2d(-sin(60.0/180.0*PI),-cos(60.0/180.0*PI));
			glVertex2d(1.0,0.0);
			glEnd();
			glColor3d(1.0,1.0,1.0);
			glBegin(GL_LINES);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
				glVertex2d(sin(((double)loop2+1.0)*10.0/180.0*PI),cos(((double)loop2+1.0)*10.0/180.0*PI));
			}
			glEnd();
			glPopMatrix();
		}
	}
	// Mates
	loopi(loop1,MATES)
	{
		if (mate[loop1].alive)
		{
			glPushMatrix();
			glTranslated(mate[loop1].xpos,mate[loop1].ypos,0.0);
			glRotated(mate[loop1].ang,0.0,0.0,1.0);
			glColor3d(0.0,1.0,0.0);
			glBegin(GL_TRIANGLES);
			glVertex2d(-sin(60.0/180.0*PI),cos(60.0/180.0*PI));
			glVertex2d(-sin(60.0/180.0*PI),-cos(60.0/180.0*PI));
			glVertex2d(1.0,0.0);
			glEnd();
			glColor3d(1.0,1.0,1.0);
			glBegin(GL_LINES);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
				glVertex2d(sin(((double)loop2+1.0)*10.0/180.0*PI),cos(((double)loop2+1.0)*10.0/180.0*PI));
			}
			glEnd();
			glPopMatrix();
		}
	}
}

void RenderItems()
{
	glLineWidth(2.0f);
	loopi(loop1,THEALTH)
	{
		if (!ithealth[loop1].spawned)
		{
			if (ithealth[loop1].wait<=0)
			{
				ithealth[loop1].spawned=true;
				ithealth[loop1].wait=rand()%701+300;
			}
			else
			{
				ithealth[loop1].wait--;
			}
		}
		if (ithealth[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(1.0,1.0,1.0);
			glTranslated(ithealth[loop1].spawnx,ithealth[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(1.0,0.0,0.0);
			glBegin(GL_LINES);
			glVertex2d(-0.75,0.0);glVertex2d(0.75,0.0);
			glVertex2d(0.0,-0.75);glVertex2d(0.0,0.75);
			glEnd();
			glPopMatrix();
		}
	}
	glLineWidth(1.0f);
	loopi(loop1,TARIFLE)
	{
		if (!itarifle[loop1].spawned)
		{
			if (itarifle[loop1].wait<=0)
			{
				itarifle[loop1].spawned=true;
				itarifle[loop1].wait=rand()%1251+750;
			}
			else
			{
				itarifle[loop1].wait--;
			}
		}
		if (itarifle[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(0.25,0.25,0.75);
			glTranslated(itarifle[loop1].spawnx,itarifle[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(1.0,1.0,0.5);
			glBegin(GL_LINES);
			glVertex2d(-0.6,-0.6);glVertex2d(0.6,0.6);
			glEnd();
			glPopMatrix();
		}
	}
	glPointSize(2.0f);
	loopi(loop1,TMINI)
	{
		if (!itmini[loop1].spawned)
		{
			if (itmini[loop1].wait<=0)
			{
				itmini[loop1].spawned=true;
				itmini[loop1].wait=rand()%1251+750;
			}
			else
			{
				itmini[loop1].wait--;
			}
		}
		if (itmini[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(0.25,0.25,0.75);
			glTranslated(itmini[loop1].spawnx,itmini[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(0.9,0.9,1.0);
			glBegin(GL_POINTS);
			glVertex2d(0.0,0.0);
			glEnd();
			glPopMatrix();
		}
	}
	glPointSize(4.0f);
	loopi(loop1,TCANNON)
	{
		if (!itcannon[loop1].spawned)
		{
			if (itcannon[loop1].wait<=0)
			{
				itcannon[loop1].spawned=true;
				itcannon[loop1].wait=rand()%751+500;
			}
			else
			{
				itcannon[loop1].wait--;
			}
		}
		if (itcannon[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(0.25,0.25,0.75);
			glTranslated(itcannon[loop1].spawnx,itcannon[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(0.8,0.5,0.4);
			glBegin(GL_POINTS);
			glVertex2d(0.0,0.0);
			glEnd();
			glPopMatrix();
		}
	}
	loopi(loop1,TSHELL)
	{
		if (!itshell[loop1].spawned)
		{
			if (itshell[loop1].wait<=0)
			{
				itshell[loop1].spawned=true;
				itshell[loop1].wait=rand()%751+500;
			}
			else
			{
				itshell[loop1].wait--;
			}
		}
		if (itshell[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(0.25,0.25,0.75);
			glTranslated(itshell[loop1].spawnx,itshell[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(0.4,0.5,0.4);
			glBegin(GL_POLYGON);
			glVertex2d(0.0,0.6);
			glVertex2d(0.2,0.3);
			glVertex2d(0.3,-0.5);
			glVertex2d(-0.3,-0.5);
			glVertex2d(-0.2,0.3);
			glEnd();
			glPopMatrix();
		}
	}
	loopi(loop1,TROCKET)
	{
		if (!itrocket[loop1].spawned)
		{
			if (itrocket[loop1].wait<=0)
			{
				itrocket[loop1].spawned=true;
				itrocket[loop1].wait=rand()%1001+1000;
			}
			else
			{
				itrocket[loop1].wait--;
			}
		}
		if (itrocket[loop1].spawned)
		{
			glPushMatrix();
			glColor3d(0.25,0.25,0.75);
			glTranslated(itrocket[loop1].spawnx,itrocket[loop1].spawny,0.0);
			glScaled(0.25,0.25,0.0);
			glBegin(GL_POLYGON);
			loopi(loop2,36)
			{
				glVertex2d(sin((double)loop2*10.0/180.0*PI),cos((double)loop2*10.0/180.0*PI));
			}
			glEnd();
			glColor3d(0.6,0.6,0.6);
			glBegin(GL_TRIANGLES);
			glVertex2d(0.0,0.75);
			glVertex2d(0.4,-0.4);
			glVertex2d(-0.4,-0.4);
			glEnd();
			glPopMatrix();
		}
	}
}

void RenderFlags()
{
	if (strcmp(game.type,"CTF")!=0)
		return;
	glLineWidth(2.5f);
	glPointSize(5.0f);
	loopi(loop1,2)
	{
		if (loop1==0)
			glColor3d(0.4,1.0,1.0);
		else
			glColor3d(1.0,0.4,0.4);
		glPushMatrix();
		glTranslated(flag[loop1].xpos,flag[loop1].ypos,0.0);
		glBegin(GL_POINTS);
		glVertex2d(0.0,0.0);
		glEnd();
		glBegin(GL_LINES);
		glVertex2d(0.0,0.0);glVertex2d(0.0,1.0);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2d(0.0,1.0);glVertex2d(0.5,1.0);
		glVertex2d(0.5,0.75);glVertex2d(0.0,0.75);
		glEnd();
		glPopMatrix();
	}
}

void RenderMap()
{
	// Initialization
	glLineWidth(2.0f);
	// Borders
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2d(-19.5,-15.0);glVertex2d(-19.5,19.5);
	glVertex2d(-19.5,19.5);glVertex2d(19.5,19.5);
	glVertex2d(19.5,19.5);glVertex2d(19.5,-15.0);
	glVertex2d(19.5,-15.0);glVertex2d(-19.5,-15.0);
	glEnd();
	// Bases
	if (strcmp(game.type,"CTEF")==0)
	{
		glColor3d(1.0,0.3,0.0);
		glBegin(GL_LINES);
		glVertex2d(-19.5,-11.0);glVertex2d(19.5,-11.0);
		glVertex2d(-19.5,15.5);glVertex2d(19.5,15.5);
		glEnd();
	}
	// Map
	glColor3d(0.0,0.0,1.0);
	loopi(loop1,SQUARES)
	{
		glPushMatrix();
		glTranslated(cube[loop1].xpos,cube[loop1].ypos,0.0);
		glRotated(cube[loop1].ang,0.0,0.0,1.0);
		glScaled(cube[loop1].sizex,cube[loop1].sizey,0.0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2d(-1.0,-1.0);
		glVertex2d(-1.0,1.0);
		glVertex2d(1.0,-1.0);
		glVertex2d(1.0,1.0);
		glEnd();
		glPopMatrix();
	}
}

void RenderMenu()
{
	// Box
	glColor3d(0.0,0.0,0.0);
	glBegin(GL_QUADS);
	glVertex2d(-19.5,-19.5);glVertex2d(-19.5,-15.5);
	glVertex2d(19.5,-15.5);glVertex2d(19.5,-19.5);
	glEnd();
	// GUI
	PrintText("Health:",-19.0,-17.0,MENUTEXT);PrintValue(you.lives,true,-16.0,-17.0,MENUDATA);
	PrintText("Weapon:",-19.0,-19.0,MENUTEXT);
	if (you.weapon==CANNON)
		PrintText("Anti-tank cannon",-16.0,-19.0,MENUDATA);
	else if (you.weapon==RIFLE)
		PrintText("Heavy automatic rifle",-16.0,-19.0,MENUDATA);
	else if (you.weapon==ROCKET)
		PrintText("Rocket launcher",-16.0,-19.0,MENUDATA);
	else if (you.weapon==ANTI)
		PrintText("Anti-air cannon",-16.0,-19.0,MENUDATA);
	else if (you.weapon==SHELL)
		PrintText("Light artillery cannon",-16.0,-19.0,MENUDATA);
	else if (you.weapon==MINI)
		PrintText("Minigun",-16.0,-19.0,MENUDATA);
	else if (you.weapon==CTFCAN)
		PrintText("CTF-cannon",-16.0,-19.0,MENUDATA);
	PrintValue(DATABULLETS[0][you.weapon],true,-6.0,-19.0,MENUDATA);
	if (strcmp(game.type,"Time battle")==0||strcmp(game.type,"CTF")==0)
	{
		PrintText("Your team score:",-3.5,-17.0,MENUTEXT);PrintValue(game.score,true,4.0,-17.0,MENUDATA);
		PrintText("Enemy team score:",-3.5,-19.0,MENUTEXT);PrintValue(game.escore,true,4.0,-19.0,MENUDATA);
	}
	// Timer
	if (strcmp(game.type,"Time battle")==0)
	{
		unsigned int ctt=game.elapsed/6000;
		if (ctt>=10)
			PrintValue(ctt,true,15.0,-17.5,MENUSUB);
		else
			PrintValue(ctt,true,15.5,-17.5,MENUSUB);
		PrintText(":",16.0,-17.5,MENUSUB);
		PrintValue(unsigned int(game.elapsed*100/10000)-60*ctt,true,16.5,-17.5,MENUSUB);
	}
	// Winning?
	if (strcmp(game.type,"CTF")==0)
	{
		// One on the other side?
		if (!game.stop)
		{
			game.win=false;
			game.lost=false;
			if (game.score==game.maxscore)
				game.win=true;
			else if (game.escore==game.maxscore)
				game.lost=true;
		}
		if (game.win)
		{
			PrintText("Your team won! Enter To Retry!",-14.0,-1.0,MENUMSG);
			game.stop=true;
		}
		else if (game.lost)
		{
			PrintText("The enemy team won! Enter To Retry!",-14.0,-1.0,MENUMSG);
			game.stop=true;
		}
		// Respawn?
		if (!game.stop)
		{
			if (!you.alive)
			{
				PrintValue((unsigned int)you.spawntime/100+1,true,-0.25,-0.5,MENUMSG);
				you.spawntime--;
			}
			if (you.spawntime<=0)
			{
				you.alive=true;
				you.xpos=18.5-rand()%18*2;you.ypos=-14.0;
				you.xdir=0.0;you.ydir=0.0;
				you.ang=90.0;
				you.lives=25;
				you.weapon=CTFCAN;
				DATABULLETS[0][CTFCAN]=50;
				loopi(loop1,BULLETTYPES)
				{
					loopi(loop2,MAXBULLETS[loop1])
					{
						bullet[0][loop1][loop2].alive=false;
					}
				}
				loopi(loop2,MAXPARTICLES)
				{
					explosion[0][loop2].alive=false;
				}
				you.spawntime=500;
			}
			loopi(loop1,ENEMIES)
			{
				if (!enemy[loop1].alive)
					enemy[loop1].spawntime--;
				if (enemy[loop1].spawntime<=0)
				{
					enemy[loop1].alive=true;
					enemy[loop1].xpos=18.5-rand()%18*2;enemy[loop1].ypos=18.5;
					enemy[loop1].xdir=0.0;enemy[loop1].ydir=0.0;
					enemy[loop1].ang=90.0;
					enemy[loop1].lives=25;
					enemy[loop1].weapon=CTFCAN;
					DATABULLETS[loop1+1][CTFCAN]=50;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,MAXBULLETS[loop2])
						{
							bullet[loop1+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+1][loop2].alive=false;
					}
					enemy[loop1].spawntime=500;
				}
			}
			loopi(loop1,MATES)
			{
				if (!mate[loop1].alive)
					mate[loop1].spawntime--;
				if (mate[loop1].spawntime<=0)
				{
					mate[loop1].alive=true;
					mate[loop1].xpos=18.5-rand()%18*2;mate[loop1].ypos=-14.0;
					mate[loop1].xdir=0.0;mate[loop1].ydir=0.0;
					mate[loop1].ang=90.0;
					mate[loop1].lives=25;
					mate[loop1].weapon=CTFCAN;
					DATABULLETS[loop1+ENEMIES+1][CTFCAN]=50;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,MAXBULLETS[loop2])
						{
							bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+ENEMIES+1][loop2].alive=false;
					}
					mate[loop1].spawntime=500;
				}
			}
		}
		// Stopping?
		game.lost=false;// Using the same bool for recycling memory
		if (!you.alive)
			game.lost=true;
		loopi(loop1,ENEMIES)
		{
			if (!enemy[loop1].alive)
				game.lost=true;
		}
		loopi(loop1,MATES)
		{
			if (!mate[loop1].alive)
				game.lost=true;
		}
		if (game.inter&&!game.stop&&!game.lost)
			PrintText("None of you have ammo left to fight on! Enter To Retry!",-14.0,-1.0,MENUMSG);
	}
	else if (strcmp(game.type,"CTEF")==0)
	{
		// One on the other side?
		if (!game.stop)
		{
			game.win=false;
			game.lost=false;
			if (you.ypos>=16.5&&you.alive)
				game.win=true;
			loopi(loop1,MATES)
			{
				if (mate[loop1].ypos>=16.5&&mate[loop1].alive)
					game.win=true;
			}
			loopi(loop1,ENEMIES)
			{
				if (enemy[loop1].ypos<=-12.0&&enemy[loop1].alive)
					game.lost=true;
			}
		}
		if (game.win)
		{
			PrintText("Your team has conquered the enemy front! Enter To Retry!",-14.0,-1.0,MENUMSG);
			loopi(loop1,ENEMIES)
			{
				if (enemy[loop1].alive)
					enemy[loop1].lives=0;
			}
			game.stop=true;
		}
		else if (game.lost)
		{
			PrintText("The enemy team has conquered your front! Enter To Retry!",-14.0,-1.0,MENUMSG);
			if (you.alive)
				you.lives=0;
			loopi(loop1,MATES)
			{
				if (mate[loop1].alive)
					mate[loop1].lives=0;
			}
			game.stop=true;
		}
		// Respawn?
		if (!game.stop)
		{
			if (!you.alive)
			{
				PrintValue((unsigned int)you.spawntime/100+1,true,-0.25,-0.5,MENUMSG);
				you.spawntime--;
			}
			if (you.spawntime<=0)
			{
				you.alive=true;
				you.xpos=18.5-rand()%18*2;you.ypos=-14.0;
				you.xdir=0.0;you.ydir=0.0;
				you.ang=90.0;
				you.lives=15;
				you.weapon=SHELL;
				DATABULLETS[0][CANNON]=15;
				DATABULLETS[0][RIFLE]=50;
				DATABULLETS[0][ROCKET]=0;
				DATABULLETS[0][ANTI]=0;
				DATABULLETS[0][SHELL]=10;
				DATABULLETS[0][MINI]=0;
				loopi(loop1,BULLETTYPES)
				{
					loopi(loop2,MAXBULLETS[loop1])
					{
						bullet[0][loop1][loop2].alive=false;
					}
				}
				loopi(loop2,MAXPARTICLES)
				{
					explosion[0][loop2].alive=false;
				}
				you.spawntime=500;
			}
			loopi(loop1,ENEMIES)
			{
				if (!enemy[loop1].alive)
					enemy[loop1].spawntime--;
				if (enemy[loop1].spawntime<=0)
				{
					enemy[loop1].alive=true;
					enemy[loop1].alive=true;
					enemy[loop1].xpos=18.5-rand()%18*2;enemy[loop1].ypos=18.5;
					enemy[loop1].xdir=0.0;enemy[loop1].ydir=0.0;
					enemy[loop1].ang=90.0;
					enemy[loop1].lives=15;
					enemy[loop1].weapon=SHELL;
					DATABULLETS[loop1+1][CANNON]=15;
					DATABULLETS[loop1+1][RIFLE]=50;
					DATABULLETS[loop1+1][ROCKET]=0;
					DATABULLETS[loop1+1][ANTI]=0;
					DATABULLETS[loop1+1][SHELL]=10;
					DATABULLETS[loop1+1][MINI]=0;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,MAXBULLETS[loop2])
						{
							bullet[loop1+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+1][loop2].alive=false;
					}
					enemy[loop1].spawntime=500;
				}
			}
			loopi(loop1,MATES)
			{
				if (!mate[loop1].alive)
					mate[loop1].spawntime--;
				if (mate[loop1].spawntime<=0)
				{
					mate[loop1].alive=true;
					mate[loop1].alive=true;
					mate[loop1].xpos=18.5-rand()%18*2;mate[loop1].ypos=-14.0;
					mate[loop1].xdir=0.0;mate[loop1].ydir=0.0;
					mate[loop1].ang=90.0;
					mate[loop1].lives=15;
					mate[loop1].weapon=SHELL;
					DATABULLETS[loop1+ENEMIES+1][CANNON]=15;
					DATABULLETS[loop1+ENEMIES+1][RIFLE]=50;
					DATABULLETS[loop1+ENEMIES+1][ROCKET]=0;
					DATABULLETS[loop1+ENEMIES+1][ANTI]=0;
					DATABULLETS[loop1+ENEMIES+1][SHELL]=10;
					DATABULLETS[loop1+ENEMIES+1][MINI]=0;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,MAXBULLETS[loop2])
						{
							bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+ENEMIES+1][loop2].alive=false;
					}
					mate[loop1].spawntime=500;
				}
			}
		}
		// Stopping?
		game.lost=false;// Using the same bool for recycling memory
		if (!you.alive)
			game.lost=true;
		loopi(loop1,ENEMIES)
		{
			if (!enemy[loop1].alive)
				game.lost=true;
		}
		loopi(loop1,MATES)
		{
			if (!mate[loop1].alive)
				game.lost=true;
		}
		if (game.inter&&!game.stop&&!game.lost)
			PrintText("None of you have ammo left to fight on! Enter To Retry!",-14.0,-1.0,MENUMSG);
	}
	else if (strcmp(game.type,"Time battle")==0)
	{
		if (game.elapsed<=0)
		{
			if (game.score>game.escore)
				PrintText("Time is up! Your team won! Congratulations! Enter To Retry!",-14.0,-1.0,MENUMSG);
			else if (game.score<game.escore)
				PrintText("Time is up! The enemy won! Bad luck. Enter To Retry!",-14.0,-1.0,MENUMSG);
			else
				PrintText("Time is up! It's a tie! This is very rare. Enter To Retry!",-14.0,-1.0,MENUMSG);
			game.stop=true;
		}
		else
		{
			game.elapsed--;
		}
		// Respawn?
		if (!game.stop)
		{
			if (!you.alive)
			{
				PrintValue((unsigned int)you.spawntime/100+1,true,-0.25,-0.5,MENUMSG);
				you.spawntime--;
			}
			if (you.spawntime<=0)
			{
				you.alive=true;
				you.xpos=18.5-rand()%18*2;you.ypos=-14.0;
				you.xdir=0.0;you.ydir=0.0;
				you.ang=90.0;
				you.lives=40;
				you.weapon=SHELL;
				DATABULLETS[0][CANNON]=50;
				DATABULLETS[0][RIFLE]=80;
				DATABULLETS[0][ROCKET]=30;
				DATABULLETS[0][ANTI]=20;
				DATABULLETS[0][SHELL]=50;
				DATABULLETS[0][MINI]=100;
				loopi(loop1,BULLETTYPES)
				{
					loopi(loop2,ALLOCBULLETS)
					{
						bullet[0][loop1][loop2].alive=false;
					}
				}
				loopi(loop2,MAXPARTICLES)
				{
					explosion[0][loop2].alive=false;
				}
				you.spawntime=500;
			}
			loopi(loop1,ENEMIES)
			{
				if (!enemy[loop1].alive)
					enemy[loop1].spawntime--;
				if (enemy[loop1].spawntime<=0)
				{
					enemy[loop1].alive=true;
					enemy[loop1].xpos=18.5-rand()%18*2;enemy[loop1].ypos=18.5;
					enemy[loop1].xdir=0.0;enemy[loop1].ydir=0.0;
					enemy[loop1].ang=90.0;
					if (strcmp(game.difficulty,"Hard")==0)
						enemy[loop1].lives=50;
					else if (strcmp(game.difficulty,"Normal")==0)
						enemy[loop1].lives=40;
					else if (strcmp(game.difficulty,"Easy")==0)
						enemy[loop1].lives=30;
					enemy[loop1].weapon=SHELL;
					DATABULLETS[loop1+1][CANNON]=50;
					DATABULLETS[loop1+1][RIFLE]=80;
					DATABULLETS[loop1+1][ROCKET]=30;
					DATABULLETS[loop1+1][ANTI]=20;
					DATABULLETS[loop1+1][SHELL]=50;
					DATABULLETS[loop1+1][MINI]=100;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,ALLOCBULLETS)
						{
							bullet[loop1+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+1][loop2].alive=false;
					}
					enemy[loop1].spawntime=500;
				}
			}
			loopi(loop1,MATES)
			{
				if (!mate[loop1].alive)
					mate[loop1].spawntime--;
				if (mate[loop1].spawntime<=0)
				{
					mate[loop1].alive=true;
					mate[loop1].alive=true;
					mate[loop1].xpos=18.5-rand()%18*2;mate[loop1].ypos=-14.0;
					mate[loop1].xdir=0.0;mate[loop1].ydir=0.0;
					mate[loop1].ang=90.0;
					mate[loop1].lives=40;
					mate[loop1].weapon=SHELL;
					DATABULLETS[loop1+ENEMIES+1][CANNON]=50;
					DATABULLETS[loop1+ENEMIES+1][RIFLE]=80;
					DATABULLETS[loop1+ENEMIES+1][ROCKET]=30;
					DATABULLETS[loop1+ENEMIES+1][ANTI]=20;
					DATABULLETS[loop1+ENEMIES+1][SHELL]=50;
					DATABULLETS[loop1+ENEMIES+1][MINI]=100;
					loopi(loop2,BULLETTYPES)
					{
						loopi(loop3,ALLOCBULLETS)
						{
							bullet[loop1+ENEMIES+1][loop2][loop3].alive=false;
						}
					}
					loopi(loop2,MAXPARTICLES)
					{
						explosion[loop1+ENEMIES+1][loop2].alive=false;
					}
					mate[loop1].spawntime=500;
				}
			}
		}
		// Stopping?
		game.lost=false;// Using the same bool for recycling memory
		if (!you.alive)
			game.lost=true;
		loopi(loop1,ENEMIES)
		{
			if (!enemy[loop1].alive)
				game.lost=true;
		}
		loopi(loop1,MATES)
		{
			if (!mate[loop1].alive)
				game.lost=true;
		}
		if (game.inter&&!game.stop&&!game.lost)
			PrintText("None of you have ammo left to fight on! Enter To Retry!",-14.0,-1.0,MENUMSG);
	}
	else
	{
		game.win=true;
		loopi(loop1,ENEMIES)
		{
			if (enemy[loop1].alive)
				game.win=false;
		}
		game.lost=true;
		if (you.alive)
		{
			game.lost=false;
			if (game.win)
			{
				PrintText("Your team won! Good job! Enter To Retry!",-11.0,-1.0,MENUMSG);
				game.stop=true;
			}
		}
		loopi(loop1,MATES)
		{
			if (mate[loop1].alive)
			{
				game.lost=false;
				if (game.win)
				{
					PrintText("Your team won! Good job! Enter To Retry!",-11.0,-1.0,MENUMSG);
					game.stop=true;
				}
			}
		}
		loopi(loop1,ENEMIES)
		{
			if (enemy[loop1].alive)
			{
				if (!game.win&&game.lost)
				{
					PrintText("Your team lost! Enter To Retry!",-8.0,-1.0,MENUMSG);
					game.stop=true;
				}
			}
		}
		if (game.win&&game.lost)
		{
			PrintText("Everyone died! Enter To Retry!",-8.0,-1.0,MENUMSG);
			game.stop=true;
		}
		if (game.inter&&!game.stop&&strcmp(game.type,"Battle")==0)
			PrintText("None of you have ammo left to fight on! Enter To Retry!",-14.0,-1.0,MENUMSG);
	}
}