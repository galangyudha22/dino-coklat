#include <sl.h>
#include "entities.h"
#include <vector>
#include <random>
#include <string>

using namespace std;
bool isJump(Dinoku, Ground);

bool isCollision(Dinoku, Wood);

int main()
{
	slWindow(800, 400, "Dicok", false);

	

	int dinoku = slLoadTexture("Dinoku.png");
	int backgrnd = slLoadTexture("bg.png");
	int woodimg = slLoadTexture("wood.png");
	int dalanimg = slLoadTexture("dalan.png");
	int jump = slLoadWAV("jump.wav");
	int text = slLoadFont("yts.ttf");
	//int sound = slLoadWAV("backsoundd.wav");

	

	random_device rd;

	double gravitasi = -0.2;
	bool isJump = false;
	double score = 0;
	

	
	//iniliasisasi  objek
	Ground dalan;
	dalan.posX = 400;
	dalan.posY = 10;

	Dinoku dino;
	dino.posX = 150;
	dino.posY = 90;
	dino.velX = 0;
	dino.velY = 0;
	dino.radius = 10;

	background backg;
	backg.posX = 400;
	backg.posY = 300;
	backg.velX = 0;
	backg.velY = 0;

	Wood wood;
	wood.posX = 850;
	wood.posY = 75;
	wood.velX = 0;
	wood.velY = 0;
	wood.radius = 10;

	bool mainMenu = true;
	bool gameover = false;
	while (!slShouldClose())
	{
		slSetBackColor(0, 0, 0);
		slSprite(backgrnd, backg.posX, backg.posY, 1240, 840);
		slSprite(dalanimg, dalan.posX, dalan.posY, 16000, 100);
		
		if (mainMenu)
		{
			slSetFont(text, 20);
			slSetTextAlign(SL_ALIGN_CENTER);
			slText(400, 200, "press 'space' to start");
			if (slGetKey(' '))
			{
				mainMenu = false;
			}
		}




		else if (!gameover)
		{
			slSprite(dinoku, dino.posX, dino.posY, 60, 60);
			slSprite(woodimg, wood.posX, wood.posY, 60, 60);
			//slSoundLoop(backsoundd);

			slSetFont(text, 20);
			slSetTextAlign(SL_ALIGN_LEFT);
			slText(50, 20, std::to_string(score).c_str());


			dalan.posX -= 10;

			if (dalan.posX <= 40)
			{
				dalan.posX = 6000;
			}

			backg.posX -= 0.1;

			if (backg.posX <= 180)
			{
				backg.posX = 370;
			}


			dino.velY += gravitasi;
			dino.posY += dino.velY;
			if (dino.posY < 90)
			{
				dino.posY = 90;
			}
			if (slGetKey(' ') && !isJump)
			{
				dino.velY = 8;
				slSoundPlay(jump);
				isJump = true;
			}
			if (dino.posY < 92 && dino.velY < 0)
			{
				isJump = false;
			}


			wood.posX -= 4;

			if (wood.posX < -50)
			{
				wood.posX = 850;
				score++;
			}

			if (isCollision(dino, wood))
				gameover = true;
			slSoundStopAll;

			


			
		}
		else
		{
			slSetForeColor(1, 0.5, 0.5, 1);
			slSetTextAlign(SL_ALIGN_CENTER);
			slText(400, 200, "AHAHA LOSE");
			slText(400, 170, "Press 'space' to restart");
			if (slGetKey(' '))
			{
				//slsoundloop = true;
				gameover = false;
				wood.posX = 850;
				score = 0;
				slSetForeColor(1, 1, 1, 1);
			}
		}


		slRender();
		
	}
	slClose();

	return 0;
}

bool isCollision(Dinoku d, Wood w)
{
	double dx = d.posX - w.posX;
	double dy = d.posY - w.posY;
	double distance = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
	if (distance <= d.radius + w.radius)
		return true;

	return false;
}