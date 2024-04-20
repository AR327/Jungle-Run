#include "iGraphics.h"
#include "bitmap_loader.h"
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define screenWidth 800
#define screenHeight 600
#define _CRT_SECURE_NO_WARNNINGS
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


int submit = 0;
int image1, image2, image3, image4, image5, image9, image10, image11, image12;
int heroImg[3];
int heroImg1[3];
int sum = 60;
int fage = 0;
int pic_x = 0, pic_y = 0;
int pic2_x = 800, pic2_y = 0;
int hero_x = 15, hero_y = 10;
//int mon_x, mon_y = 0;
int flag = 120;
int score = 0;
int herooJump = 0;
int dx = 1;
//int dx = 10;
int fire = 0;
int bullet_x = 193;
int bullet_y = 138;
int Coinx[5], Coiny[5], movingCoin[5];
int i;
int dx1 = 8, dxx = 9;
int k;
int Level = 1;
int check = 0;
int indexNumber = 0;
int mode = 1;
int tempScore;

struct buttonCordinate
{
	int x;
	int y;
} bCordinate[5];



bool musicOn = true;
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
bool CollisonM;


bool highScoreAlreadyUpdated = false;
void updateHighScores();


char a[15];
char c[15];
char button[20][20] = { "bs.bmp", "bh.bmp", "bc.bmp", "bi.bmp", "bq.bmp" };
char homemenu[20] = "MenuPage.bmp";
//char load[20] = "insideload";
//char high[20] = "insidehighscore.bmp";
char about[20] = "Aboutt.bmp";
char quit[20] = "insidequit.bmp";
char back[20] = "back.bmp";
char instruct[20] = "instruct.bmp";
char name[2000];


int gameOver = 0;
int gameState = -1;


//char player[3][200];
vector < int > topScores;


bool validPoint(int mx, int my)
{
	if (mx >= 154 && mx <= 371 && my >= 560 && my <= 570)
	{
		check = 1;
		return true;
	}
}


//coin Initialize
void Initialize(){

	for (i = 0; i < 5; i++)
	{
		Coinx[i] = 800 + rand() % 500;
		//cout << "Coinx" << Coinx << endl;
		k = rand() % 475;
		if (Level == 2)
		{
			if (k <= 300)
				k = k + 300;
		}
		else
		{
			if (k <= 200)
				k = k + 200;
		}
		Coiny[i] = k;
	}

	for (i = 0; i < 5; i++)
	{
		movingCoin[i] = Coinx[i];
	}
}


//Changing Coin's Value
void update(){

	for (i = 0; i < 5; i++)
	{
		movingCoin[i] = movingCoin[i] - 5;
		 
	}
}

struct Monster{
	int x, y, height, width, speed = 5;
	bool hide;
	Monster(){
		hide = false;
		x = 800 + rand() % 500;
		y = 0;
		height = 170;
		width = 220;
	}

	void respawn(){
		x = 800 + rand() % 500;
	}

	void run(){
		x = x - speed;
		if (x <= width*(-1))
			respawn();
	}

	void display(){
		if (!hide)
			iShowImage(x, y, 120, 180, image3);
	}
};
//initialize monster
Monster monster;



bool checkCollision(int Coinx, int Coiny){


	if (hero_x + 100 >= Coinx && hero_x <= Coinx + 30 && hero_y + 256 + herooJump >= Coiny && hero_y + herooJump <= Coiny + 30)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void checkCollisonM()
{
	//checking bullet and monster
	if (fire){
		if (bullet_x >= monster.x && bullet_y <= monster.height){
			monster.hide = true;
			monster.respawn();
			bullet_x = 193;
			bullet_y = 138;
			fire = 0;
		}
	}
	else{
		if (monster.x < -80 || monster.x > screenWidth)
			monster.hide = false;
	}

	//checking hero and monster
	if (hero_x > monster.x){
		flag -= 20;
		monster.respawn();
		//file
		if (flag <= 0)
		{
			gameOver = 1;
			//score = 0;

		}
	}
}


void bulletMove()

{
	if (fire){
		if (bullet_x < screenWidth){
			bullet_x = bullet_x + 5;
		}
		else{
			fire = 0;
		}
	}

}


void iBoldText(double LeftX, double LeftY, char ara[]){
	iText(LeftX - 1, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX - 1, LeftY - 1, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX, LeftY - 1, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
}


void iDraw()
{
	iClear();

	//gameover
	//file
	if (gameOver == 1){

		if (!highScoreAlreadyUpdated){
			updateHighScores();
		}
		iShowBMP2(4, 500, back, 0);
		iText(3, 480, "Press 'b' go to menu page", GLUT_BITMAP_TIMES_ROMAN_10);
		iShowImage(0, 0, screenWidth, screenHeight, image5);
		mode = 1;




	}

	//menupage
	else if (gameState == -1){


		iShowBMP(0, 0, homemenu);
		for (int i = 0; i < 5; i++){
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 0);
		}
	}

	//scores
	else if (gameState == 1){

		fage = 0;
		iShowImage(0, 0, screenWidth, screenHeight, image9);
		//iText(320, 340, "High Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(4, 500, back, 0);
		iText(3, 480, "Press 'b' go to menu page", GLUT_BITMAP_TIMES_ROMAN_10);
		char scores[3][200];
		iSetColor(255, 255, 255);
		//iBoldText(300, 443, "NAME");
		iBoldText(400, 444, "SCORE");
		int l;
		FILE *f;
		f = fopen("highscore.txt", "r");
		if (f != NULL){
			for (l = 0; l < 3; l++)
			{
				//fscanf(f,"%s %s", player[i], scores[i]);
				fscanf(f, "%s", scores[l]);
			}
			fclose(f);
		}
		iSetColor(255, 255, 0);
		//iBoldText(300, 443, player[0]);
		//iBoldText(300, 443, player[1]);
		//iBoldText(300, 443, player[2]);


		iBoldText(405, 405, scores[0]);
		iBoldText(405, 355, scores[1]);
		iBoldText(405, 305, scores[2]);

	}

	//about
	else if (gameState == 2){

		fage = 0;
		//iSetColor(0, 0, 255);
		iShowBMP(0, 0, about);
		//iShowImage(0, 0, 800, 600, image12);
		//iText(160, 535, "Press HOME to go Menu Page", GLUT_BITMAP_HELVETICA_18);
		//iText(160, 535, name, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	//play
	else if (gameState == 0){
		fage = 1;
		if (fage == 1){
			if (Level == 2){
				iShowImage(pic_x, pic_y, screenWidth, screenHeight, image1);//left 
				iShowImage(pic2_x, pic2_y, screenWidth, screenHeight, image2);//right to left
			}
			else
			{
				iShowImage(pic_x, pic_y, screenWidth, screenHeight, image11);
				iShowImage(pic2_x, pic2_y, screenWidth, screenHeight, image11);
			}
			iSetColor(255, 0, 0);	//Red

			if (Level == 1)
			{
				iText(14, 521, "LEVEL  - 1", GLUT_BITMAP_HELVETICA_18);
			}
			else
			{
				iText(14, 521, "LEVEL  - 2", GLUT_BITMAP_HELVETICA_18);
			}

			iSetColor(0, 255, 0);
			iFilledRectangle(550, 550, 100, 20);
			iFilledRectangle(570, 550, 20, 20);
			iFilledRectangle(590, 550, 20, 20);
			iFilledRectangle(610, 550, 20, 20);
			iFilledRectangle(630, 550, 20, 20);
			iFilledRectangle(650, 550, 20, 20);



			iSetColor(255, 0, 0);
			iText(10, 553, "SCORE:", GLUT_BITMAP_HELVETICA_18);


			iSetColor(255, 0, 0);
			iFilledRectangle(550, 550, flag, 20);


			itoa(score, a, 10);
			iText(100, 550, a, GLUT_BITMAP_TIMES_ROMAN_24);
			//iShowImage(mon_x, mon_y, 120, 180, image3);


			if (jump)
			{

				if (jumpUp)
				{

					if (Level == 1)
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg[0]);
					}
					else
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[0]);
					}
				}

				else
				{
					if (Level == 1){
						if (hero_x % 2 == 0)
						{
							iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg[1]);
						}

						else
						{
							iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg[2]);
						}
					}
					else
					{
						if (hero_x % 2 == 0)
						{
							iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[1]);
						}

						else
						{
							iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[2]);
						}
					}
				}
			}

			else
			{
				if (Level == 1){
					if (hero_x % 2 == 0)
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg[1]);
					}

					else
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg[2]);
					}
				}
				else
				{
					if (hero_x % 2 == 0)
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[1]);
					}

					else
					{
						iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[2]);
					}
				}

			}




			for (i = 0; i < 5; i++)
			{
				bool Collison = checkCollision(movingCoin[i], Coiny[i]);
				bool screenExceed = movingCoin[i] < 0;

				if (Collison == true || screenExceed == true)
				{
					movingCoin[i] = Coinx[i];
				}



				monster.display();
				checkCollisonM();


				//Scoring part

				if (Collison == true && gameState == 0)
				{
					score = score + 5;
				}
				//cout << "hero" << endl;
				//iShowImage(hero_x, hero_y + herooJump, 180, 240, heroImg1[2]);
				iShowImage(movingCoin[i], Coiny[i], 30, 30, image4);

			}
			fage = 0;

		}

	}


	//instructions
	else if (gameState == 3)
	{
		//iShowImage(0, 0, 800, 600, image1);
		iShowBMP(0, 0, instruct);
		iText(144, 340, name, GLUT_BITMAP_TIMES_ROMAN_24);
		//iShowImage(0, 0, 800, 600, image1);
	}

	//exit
	else if (gameState == 4)
	{
		fage = 0;
		iSetColor(0, 0, 255);
		iText(14, 521, "Press 'b' to go Menu Page", GLUT_BITMAP_HELVETICA_18);
		exit(0);

	}

	//fire
	if (fire == 1 && gameOver == 0)
	{

		//iShowImage(0, 0, screenWidth, screenHeight, image10);
		iShowBMPAlternativeSkipWhite(bullet_x, bullet_y, "bullet.bmp");


	}

}




/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	if (gameState == 2 && validPoint(mx, my))
	{
		check = 1;
	}
}


/*
function iPassiveMouse() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iPassiveMouseMove(int mx, int my)
{
	cout << "movey" << my << endl;
	cout << "movex" << mx << endl;
}


/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 5; i++){

			//cout << "mx" << mx << endl;
			//cout << "my" << my << endl;
			if (mx >= bCordinate[i].x && mx <= bCordinate[i].x + 130 && my >= bCordinate[i].y && my <= bCordinate[i].y + 65)
			{
				//printf("i=%d\n\n", i);
				gameState = i;
			}
		}

	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}

	//printf("x=%d\n y= %d\n", mx, my);
}



/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/



void iKeyboard(unsigned char key)
{
	//fire
	if (key == 's' && gameState == 0)
	{
		if (!fire){
			fire = 1;

			bullet_x = hero_x + 193;
			bullet_y = herooJump + 138;

		}
		else{
			if (bullet_x >= screenWidth){
				bullet_x = hero_x + 193;
				bullet_y = herooJump + 138;
			}
		}


	}
	else
	{

		hero_x = 10;
		hero_y = 15;
	}

	//back
	if (key == 'b')
	{
		fage = 0;
		gameState = -1;
		gameOver = 0;

	}


	if (key == 'm')
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			musicOn = true;
			PlaySound("wavedfile.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	//input name
	//if (gameState == 0){

}


/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/


void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_UP)
	{
		if (!jump)
		{
			jump = true;
			jumpUp = true;
		}

	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (hero_x + 465 < 1000)
		{
			hero_x = hero_x + dx1;
			hero_x = hero_x + dxx;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{

		if (hero_x > 0)
		{
			hero_x = hero_x - dx1;
			hero_x = hero_x - dxx;
		}

	}


}



//hero
void herooJumpp(){
	if (jump)
	{
		//cout << "Jumpup" << jumpUp << endl;
		if (jumpUp)
		{

			herooJump += 6;	//jump Up
			if (herooJump >= 260)	//jump length
			{
				//cout << "IF jumpUp" << jumpUp << endl;
				jumpUp = false;
			}
		}


		else
		{
			herooJump -= 6; //jump down
			if (herooJump < 0)
			{
				//cout << "Else IF jumpUp" << jumpUp << endl;
				jump = false;
			}
		}

	}


}


//background
void change()
{
	for (int i = 0; i <= 5; i++)
	{
		pic_x -= dx;//left
		pic2_x -= dx;//right
		if (pic2_x <= 0)
		{
			//cout << "pic_x" << pic_x << endl;
			//cout << "pic2_x" << pic2_x << endl;
			pic2_x = 800;
			pic_x = 0;
			for (int i = 0; i <= 5; i++)
			{


				pic_x -= dx;
				pic2_x -= dx;


			}

		}

	}

}


bool sortScores(int a, int b){
	return b < a;
}


void updateHighScores()
{
	highScoreAlreadyUpdated = true;

	FILE *fp;

	fp = fopen("highscore.txt", "r");

	for (int i = 0; i < 3; i++)
	{
		fscanf(fp, "%d\n", &tempScore);

		topScores.push_back(tempScore);
	}

	fclose(fp);

	topScores.push_back(score);

	sort(topScores.begin(), topScores.end(), &sortScores);
	topScores.pop_back();

	fp = fopen("highscore.txt", "w");
	for (auto it = topScores.begin(); it != topScores.end(); it++)
	{
		fprintf(fp, "%d\n", *it);
	}

	fclose(fp);
}


void monChange()
{
	if (gameState == 0)
	{
		monster.run();
		if (score >= 100 && score < 200)
			monster.speed = 10;
		else if (score >= 200 && score < 300)
			monster.speed = 20 + 1;
		else if (score >= 300 && score < 400)
			monster.speed = 30 + 2;
		else if (score >= 400 && score < 500)
			monster.speed = 40 + 3;
		else if (score >= 500 && score < 600)
			monster.speed = 50 + 4;
		else if (score >= 600 && score < 700)
			monster.speed = 60 + 5;
		else if (score >= 700 && score < 800)
			monster.speed = 70 + 6;
		else if (score >= 800 && score < 900)
			monster.speed = 80 + 7;
		else if (score >= 900 && score < 1000)
			monster.speed = 90 + 8;
		else if (score >= 1000)
			monster.speed = 100;

		if (score >= 200)
		{
			Level = 2;
		}
		else
		{
			Level = 1;
		}
	}
}


void LoadImage()
{

	// loading images.
	/* iLoadImage() will return an interger type id
	for each image you load.
	*/


	image1 = iLoadImage("pic3 (1).jpg");
	image2 = iLoadImage("pic3 (1).jpg");
	image3 = iLoadImage("monster1.png");
	image4 = iLoadImage("Coin.png");
	image5 = iLoadImage("GameOver.jpg");


	heroImg[0] = iLoadImage("hero-2.png");
	heroImg[1] = iLoadImage("hero-0.png");
	heroImg[2] = iLoadImage("hero-1.png");

	heroImg1[0] = iLoadImage("hero2.png");
	heroImg1[1] = iLoadImage("hero0.png");
	heroImg1[2] = iLoadImage("hero1.png");

	image9 = iLoadImage("Score.jpg");
	image10 = iLoadImage("instruct.jpg");
	image11 = iLoadImage("BackGround1.jpg");
	image12 = iLoadImage("username.png");
}



int main()
{

	///srand((unsigned)time(NULL));
	for (int i = 4; i >= 0; i--){


		bCordinate[i].x = 50;
		bCordinate[i].y = sum;
		sum += 100;
	}


	PlaySound("wavedfile.wav", NULL, SND_LOOP | SND_ASYNC);


	iInitialize(screenWidth, screenHeight, "Animation with image");

	Initialize();
	//updateHighScores();
	iSetTimer(1, herooJumpp);
	iSetTimer(5, change);
	iSetTimer(20, monChange);
	iSetTimer(20, bulletMove);
	iSetTimer(10, update);



	LoadImage();

	iStart();
	return 0;
}