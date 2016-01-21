#include "Includes.h"

using namespace std;

void display(void);
void myTimer(int id);
void myMouse(int Btn, int state, int x, int y);
void myKB_Handler(unsigned char key, int mx, int my);
void pressKeySpecial(int key, int x, int y);
void registerCallbacks();
void loadSprites();
void checkCollisions();
void generateEnemies();
void resetGame();
void changeLevel();
void scoreRead();
void scoreWrite();
void NumericScreenWriter(int num, int x, int y);
void PassiveMotion(int x, int y);
void resizeScreen(int x, int y);


/* Setup Data */
// initialize a setup object
_Setup *mySetup = new _Setup();
// acess all your constants with 'CONSTANTS' from anywhere in your project
// all your structs are available to you anywhere in your project
Shanu *myLib = new Shanu();

static int timerCount = 0;
static int levelKillCount = 0;
static int score = 0;
static int highScore = 0;
int displayScreen = 0;



/* Global Data */
Background *background1;
Background *background2;
Background *background3;
Background *background4;
Background *background5;
Birds *hero;

vector<Enemy> enemies;
int enemiesIndex=0;
int enemyGenIndex;
int enemyRandomizer=1;
int randomEnemyY = 0;
int attackCount = 0;
int currentCharacter = 1;
Point2D GlobalMouse;

//load all sprites here
AnimatedSprite *enemyTexture[5];
AnimatedSprite *enemyDieTexture;

AnimatedSprite *heroTexture;
AnimatedSprite *heroShootTexture;
AnimatedSprite *heroFaintTexture;

AnimatedSprite *heroShootTexture1;
AnimatedSprite *heroFaintTexture1;
AnimatedSprite *heroTexture1;

AnimatedSprite *heroShootTexture2;
AnimatedSprite *heroFaintTexture2;
AnimatedSprite *heroTexture2;

AnimatedSprite *heroShootTexture3;
AnimatedSprite *heroFaintTexture3;
AnimatedSprite *heroTexture3;

AnimatedSprite *heroHealthTexture;
AnimatedSprite *heroAttackTexture;

AnimatedSprite *n1;
AnimatedSprite *n2;
AnimatedSprite *n3;
AnimatedSprite *n4;
AnimatedSprite *n5;
AnimatedSprite *n6;
AnimatedSprite *n7;
AnimatedSprite *n8;
AnimatedSprite *n9;
AnimatedSprite *n0;

AnimatedSprite *pausebtn;
//load all screens
RGBApixmap mainScreen;
RGBApixmap pauseScreen;
RGBApixmap creditsScreen;
RGBApixmap QuitScreen;
RGBApixmap GameOverScreen;
RGBApixmap storeScreen;
RGBApixmap ch1Screen;
RGBApixmap ch2Screen;
RGBApixmap ch3Screen;





enum ScreenModes
{
	SCREEN_MAIN,
	SCREEN_GAME,
	SCREEN_PAUSE,
	SCREEN_CREDITS,
	SCREEN_QUIT,
	SCREEN_GAME_OVER,
	SCREEN_STORE,
	SCREEN_CHARACTER
}CurrentScreen;

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	
	srand(time(NULL));
	Enemy::speedFactor =1;
	/* Project Environment Setup */
	mySetup->setupEnvironment(
		"Simple Project Structure",
		Screen{ CONSTANTS.SCREEN_WIDTH, CONSTANTS.SCREEN_HEIGHT },
		Screen{ 50, 50 },
		CartesianSystem{ 0, CONSTANTS.SCREEN_WIDTH, 0, CONSTANTS.SCREEN_HEIGHT }
	);

	
	glClear(GL_STENCIL_BUFFER_BIT);
	loadSprites();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, CONSTANTS.SCREEN_WIDTH, 0, CONSTANTS.SCREEN_HEIGHT);
	PlayBackgroundSound("sounds/game_main.wav");
	scoreRead();
	registerCallbacks();	// event handlers
	glutMainLoop();			// wait state
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, GL_ONE);
	

	/*
	displayScreen = 0 = Main Menu Screen
	displayScreen = 1 = In Game Screen
	displayScreen = 2 = pause Screen
	
	
	*/

	switch (CurrentScreen)
	{


	case SCREEN_MAIN:

		
		
		mainScreen.mDraw();
		NumericScreenWriter(highScore, 480, 30);
		
		break;

	case SCREEN_CHARACTER:

		switch (currentCharacter)
		{
		case 1:
			ch1Screen.mDraw();
			break;

		case 2:
			ch2Screen.mDraw();
			break;

		case 3:
			ch3Screen.mDraw();
			break;
		default:
			break;
		}

		

		break;


	case SCREEN_GAME:

		// Drawing Area
		background1->draw();
		background2->draw();
		background3->draw();
		background4->draw();
		background5->draw();
		hero->drawBird();

		
		if (enemies.size() != 0){
			for (long index = 0; index < (long)enemiesIndex; ++index) {
				enemies.at(index).draw();
			}
		}
		pausebtn->drawSprite();
		NumericScreenWriter(score, 130, 455);
		NumericScreenWriter(hero->fireCount, 512, 455);
		break;


	case SCREEN_PAUSE:
		// Drawing Area
		background1->draw();
		background2->draw();
		background3->draw();
		background4->draw();
		background5->draw();
		hero->drawBird();

		
		if (enemies.size() != 0){
			for (long index = 0; index < (long)enemiesIndex; ++index) {
				enemies.at(index).draw();
			}
		}

		pauseScreen.mDraw();
		break;



	case SCREEN_CREDITS:
		creditsScreen.mDraw();
		break;
	

	case SCREEN_QUIT:
		QuitScreen.mDraw();
		break;


	case SCREEN_GAME_OVER:
		// Drawing Area
		background1->draw();
		background2->draw();
		background3->draw();
		background4->draw();
		background5->draw();
		hero->drawBird();

		
		if (enemies.size() != 0){
			for (long index = 0; index < (long)enemiesIndex; ++index) {
				enemies.at(index).draw();
			}
		}

		GameOverScreen.mDraw();
		NumericScreenWriter(score, 516, 194);
		NumericScreenWriter(highScore, 516, 162);
		break;

	case SCREEN_STORE:

		storeScreen.mDraw();

		break;

	default:
		break;
	}	
	glutSwapBuffers();
}

void myTimer(int id){
	// Change Postion, Change Size, Change Orientation, use your object update() method
	// updation

	Point2D flyupHero = hero->getPosition();

	switch (CurrentScreen)
	{
	case SCREEN_MAIN:
		
		break;


	case SCREEN_GAME:
		background1->setBg(0.001);
		background2->setBg(0.003);
		background3->setBg(0.005);
		background4->setBg(0.008);
		background5->setBg(0.010);
		if (timerCount % 2 == 0){
			hero->updateBird();
			
		}
		changeLevel();
		

		if (attackCount == 8)
		{
			hero->changeMode(Birds::FLY);
			hero->attackMode = false;
			attackCount = 0;
		}

		if (timerCount % 50 == 0 && enemiesIndex<12)
		{
			generateEnemies();
		}
		checkCollisions();

		if (hero->attackMode)
		{
			attackCount++;
		}

		timerCount++;
		break;


	case SCREEN_PAUSE:
		
		break;
	

	case SCREEN_GAME_OVER:
		

		if (timerCount % 3 == 0){
			hero->setPositionY(flyupHero.y + 1);
			hero->updateBird();
		}


		timerCount++;
		break;
		
	default:

		break;
	}
	
	glutPostRedisplay();
	glutTimerFunc(CONSTANTS.FRAME_DELAY_SPRITE, myTimer, 1);
}

void registerCallbacks(){
	glutDisplayFunc(display);
	glutTimerFunc(CONSTANTS.FRAME_DELAY_SPRITE, myTimer, 1);
	glutKeyboardFunc(myKB_Handler);
	glutSpecialFunc(pressKeySpecial);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(PassiveMotion);
	glutReshapeFunc(resizeScreen);
}

void myMouse(int Btn, int state, int x, int y)
{
	if (Btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		switch (CurrentScreen)
		{
		case SCREEN_MAIN:
			if ((x >= 424 && x <= 576) && (500 - y >= 268 && 500 - y <= 420)) // Play Button
			{
				resetGame();
				printf("play click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				PlayBackgroundSound("sounds/game_play.wav");
				CurrentScreen = SCREEN_GAME;
				
			}

			if ((x >= 537 && x <= 723) && (500 - y >= 130 && 500 - y <= 185)) // credits Button
			{
				printf("credits click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_CREDITS;
			}

			if ((x >= 775 && x <= 966) && (500 - y >= 130 && 500 - y <= 185)) // Exit Button
			{
				printf("exit click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_QUIT;
			}


			if ((x >= 48 && x <= 241) && (500 - y >= 130 && 500 - y <= 185)) // store Button
			{
				printf("store click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_STORE;
			}

			if ((x >= 291 && x <= 481) && (500 - y >= 130 && 500 - y <= 185)) // character Button
			{
				printf("store click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_CHARACTER;
			}

			if ((x >= 820 && x <= 983) && (500 - y >= 442 && 500 - y <= 472)) // fb like 
			{
				printf("gb like click\n", x, y);
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/pages/Sky-Fight/844185528948817", NULL, NULL, SW_SHOWDEFAULT);
				PlayForegroundSound("sounds/pop.wav");
			}

			break;


		case SCREEN_CHARACTER:
			if ((x >= 52 && x <= 190) && (500 - y >= 108 && 500 - y <= 147)) // select character 1
			{
				printf("ch1 select click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				currentCharacter = 1;
			}

			if ((x >= 287 && x <= 421) && (500 - y >= 108 && 500 - y <= 147)) // select character 2
			{
				printf("ch2 select click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				currentCharacter = 2;
			}

			if ((x >= 523 && x <= 653) && (500 - y >= 108 && 500 - y <= 147)) // select character 3
			{
				printf("ch3 select click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				currentCharacter = 3;
			}

			if ((x >= 821 && x <= 957) && (500 - y >= 108 && 500 - y <= 147)) // select humera
			{
				printf("humera select click\n", x, y);
				PlayForegroundSound("sounds/no.wav");
			}

			if ((x >= 13 && x <= 71) && (500 - y >= 427 && 500 - y <= 484)) // Go Back Button
			{
				printf("go back click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_MAIN;
			}

			break;
			

		case SCREEN_GAME:
			if ((x >= 9 && x <= 57) && (500 - y >= 440 && 500 - y <= 490)) // pause Button
			{
				printf("pause click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");

				CurrentScreen = SCREEN_PAUSE;
				
			}

			else
			{
				if (hero->fireCount > 0){
					hero->doAttack = true;
					hero->attack();
					hero->changeMode(Birds::SHOOT);
					PlayForegroundSound("sounds/fire.wav");
					hero->fireCount--;
				}
			}
			break;


		case SCREEN_PAUSE:
			if ((x >= 424 && x <= 487) && (500 - y >= 200 && 500 - y <= 258)) // Resume Button
			{
				printf("resume click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_GAME;
			}

			if ((x >= 532 && x <= 584) && (500 - y >= 200 && 500 - y <= 258)) // Main Menu Button
			{
				resetGame();
				printf("main menu click click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				PlayBackgroundSound("sounds/game_main.wav");
				CurrentScreen = SCREEN_MAIN;
			}

			if ((x >= 417 && x <= 583) && (500 - y >= 71 && 500 - y <= 99)) // fb like 
			{
				printf("gb like click\n", x, y);
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/pages/Sky-Fight/844185528948817", NULL, NULL, SW_SHOWDEFAULT);
				PlayForegroundSound("sounds/pop.wav");
			}

			break;


		case SCREEN_CREDITS:
			if ((x >= 13 && x <= 71) && (500 - y >= 427 && 500 - y <= 484)) // Go Back Button
			{
				printf("go back click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_MAIN;
			}

			if ((x >= 85 && x <= 250) && (500 - y >= 76 && 500 - y <= 104)) // amin fb like 
			{
				printf("gb like click\n", x, y);
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/619napster", NULL, NULL, SW_SHOWDEFAULT);
				PlayForegroundSound("sounds/pop.wav");
			}

			if ((x >= 420 && x <= 583) && (500 - y >= 76 && 500 - y <= 104)) // alveena fb like 
			{
				printf("gb like click\n", x, y);
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/elvi.sohail", NULL, NULL, SW_SHOWDEFAULT);
				PlayForegroundSound("sounds/pop.wav");
			}

			if ((x >= 754 && x <= 919) && (500 - y >= 76 && 500 - y <= 104)) // hashsham fb like 
			{
				printf("gb like click\n", x, y);
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/hashsham.maneri", NULL, NULL, SW_SHOWDEFAULT);
				PlayForegroundSound("sounds/pop.wav");
			}


			break;


			

		case SCREEN_QUIT:
			if ((x >= 419 && x <= 477) && (500 - y >= 154 && 500 - y <= 212)) // no Button
			{
				printf("no click\n", x, y);
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_MAIN;
			}

			if ((x >= 520 && x <= 583) && (500 - y >= 154 && 500 - y <= 212)) // yes Button
			{
				PlayForegroundSound("sounds/pop.wav");
				exit(0);
			}
			break;


		case SCREEN_GAME_OVER:
			if ((x >= 448 && x <= 487) && (500 - y >= 74 && 500 - y <= 111)) // main menu Button
			{
				PlayForegroundSound("sounds/pop.wav");
				PlayBackgroundSound("sounds/game_main.wav");
				CurrentScreen = SCREEN_MAIN;
			}

			if ((x >= 515 && x <= 554) && (500 - y >= 74 && 500 - y <= 111)) // restart Button
			{
				PlayForegroundSound("sounds/pop.wav");
				PlayBackgroundSound("sounds/game_play.wav");
				CurrentScreen = SCREEN_GAME;
				resetGame();
			}

			if ((x >= 418 && x <= 582) && (500 - y >= 123 && 500 - y <= 154)) // fb share Button
			{

				PlayForegroundSound("sounds/pop.wav");
				ShellExecute(HWND_DESKTOP, "open", "https://www.facebook.com/sharer/sharer.php?u=facebook.com/pages/Sky-Fight/844185528948817", NULL, NULL, SW_SHOWDEFAULT);
				
			}
			break;

		case SCREEN_STORE:
			if ((x >= 416 && x <= 447) && (500 - y >= 14 && 500 - y <= 47)) // go back Button
			{
				PlayForegroundSound("sounds/pop.wav");
				CurrentScreen = SCREEN_MAIN;
				resetGame();
			}
			break;



		default:
			break;
		}
		
		
			
	}
	//printf("\nx-> %d\n",x);
	//printf("y-> %d\n",y);
}

void myKB_Handler(unsigned char key, int mx, int my){
	switch (CurrentScreen)
	{
	case SCREEN_MAIN:
		switch (key){

		case 13:
			resetGame();
			PlayForegroundSound("sounds/pop.wav");
			CurrentScreen = SCREEN_GAME; // Go to Game Screen
			PlayBackgroundSound("sounds/game_play.wav");
			break;
		}
		break;


	case SCREEN_GAME:
		switch (key){
		case ' ':
			if (hero->fireCount > 0){
				hero->doAttack = true;
				hero->attack();
				hero->changeMode(Birds::SHOOT);
				PlayForegroundSound("sounds/fire.wav");
				hero->fireCount--;
			}
			break;
		case 'b':
			hero->changeMode(Birds::FAINT);
			break;
		case 'a':
			hero->changeMode(Birds::SHOOT);
			break;
		case 'c':

			hero->changeMode(Birds::FLY);
			break;
		case 27:
			PlayForegroundSound("sounds/pop.wav");
			CurrentScreen = SCREEN_PAUSE; // Go to pause screen 
			break;
		}
		break;


	case SCREEN_PAUSE:
		switch (key){

		case 27:
			PlayForegroundSound("sounds/pop.wav");
			CurrentScreen = SCREEN_GAME; // Go to Game Screen
			break;
		}
		break;


	case SCREEN_GAME_OVER:
	
		break;

	default:
		break;
	}
	
	
	

	
}

void pressKeySpecial(int key, int x, int y){
	
	switch (CurrentScreen)
	{
	case SCREEN_MAIN:
		break;
	case SCREEN_GAME:
		switch (key){

		case GLUT_KEY_UP:
			hero->flyUp();
			break;

		case GLUT_KEY_DOWN:
			hero->flyDown();
			break;

		}
		break;
	case SCREEN_PAUSE:
		break;
	default:
		break;
	}

	
	

}

void loadSprites(){


	//Load All Screens
	mainScreen.readBMPFile("sprite/screens/mainScreen.bmp", 1);

	pauseScreen.readBMPFile("sprite/screens/pause.bmp", 2);
	pauseScreen.setChromaKey(0, 0, 0);

	creditsScreen.readBMPFile("sprite/screens/credits.bmp", 4);

	QuitScreen.readBMPFile("sprite/screens/quit.bmp", 4);

	GameOverScreen.readBMPFile("sprite/screens/gameOverScreen.bmp", 4);
	GameOverScreen.setChromaKey(0, 0, 0);

	pausebtn = new AnimatedSprite("sprite/screens/pausebtn.bmp", 614, 60, 0, 440, 3);
	pausebtn->colorKey(255, 0, 0);

	storeScreen.readBMPFile("sprite/screens/store.bmp", 4);

	ch1Screen.readBMPFile("sprite/screens/ch1Screen.bmp", 4);
	ch2Screen.readBMPFile("sprite/screens/ch2Screen.bmp", 4);
	ch3Screen.readBMPFile("sprite/screens/ch3Screen.bmp", 4);


	background1 = new Background("sprite/bg/bg1.bmp", 1000, 500, 0, 0, CONSTANTS.BACKGROUND_TEXTURE_ID);
	background2 = new Background("sprite/bg/bg2.bmp", 1000, 500, 0, 0, CONSTANTS.BACKGROUND_TEXTURE_ID + 3);
	background3 = new Background("sprite/bg/bg3.bmp", 1000, 500, 0, 0, CONSTANTS.BACKGROUND_TEXTURE_ID + 4);
	background4 = new Background("sprite/bg/bg4.bmp", 1000, 500, 0, 0, CONSTANTS.BACKGROUND_TEXTURE_ID + 5);
	background5 = new Background("sprite/bg/bg5.bmp", 1000, 500, 0, 0, CONSTANTS.BACKGROUND_TEXTURE_ID + 6);

	enemyTexture[0] = new AnimatedSprite("sprite/enemies/bluemonster.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID+2);
	enemyTexture[1] = new AnimatedSprite("sprite/enemies/clock.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID+3);
	enemyTexture[2] = new AnimatedSprite("sprite/enemies/pencil.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID+4);
	enemyTexture[3] = new AnimatedSprite("sprite/enemies/spikes.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID+5);
	enemyTexture[4] = new AnimatedSprite("sprite/enemies/tv.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID+6);
	enemyDieTexture = new AnimatedSprite("sprite/enemies/die.bmp", 85, 76, 0, 0, CONSTANTS.ENEMY_TEXTURE_ID + 7);

	heroTexture = new AnimatedSprite("sprite/hero/4_fly.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID);
	heroFaintTexture = new AnimatedSprite("sprite/hero/4_die.bmp", 112, 102, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 2);
	heroShootTexture = new AnimatedSprite("sprite/hero/4_shoot.bmp", 124, 90, 00, 0, CONSTANTS.BIRD_TEXTURE_ID + 3);

	heroTexture1 = new AnimatedSprite("sprite/hero/3_fly.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 4);
	heroFaintTexture1 = new AnimatedSprite("sprite/hero/3_die.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 5);
	heroShootTexture1 = new AnimatedSprite("sprite/hero/3_shoot.bmp", 125, 90, 00, 0, CONSTANTS.BIRD_TEXTURE_ID + 6);

	heroTexture2 = new AnimatedSprite("sprite/hero/2_fly.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 7);
	heroFaintTexture2 = new AnimatedSprite("sprite/hero/2_die.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 8);
	heroShootTexture2 = new AnimatedSprite("sprite/hero/2_shoot.bmp", 111, 90, 00, 0, CONSTANTS.BIRD_TEXTURE_ID + 9);

	heroTexture3 = new AnimatedSprite("sprite/hero/1_fly.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 10);
	heroFaintTexture3 = new AnimatedSprite("sprite/hero/1_die.bmp", 105, 90, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 11);
	heroShootTexture3 = new AnimatedSprite("sprite/hero/1_shoot.bmp", 104, 90, 00, 0, CONSTANTS.BIRD_TEXTURE_ID + 12);

	heroHealthTexture = new AnimatedSprite("sprite/extra/life.bmp", 55, 55, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 13);
	heroAttackTexture = new AnimatedSprite("sprite/extra/bullet.bmp", 40, 20, 0, 0, CONSTANTS.BIRD_TEXTURE_ID + 14);

	n1 = new AnimatedSprite("sprite/numbers/1.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 1);
	n1->colorKey(0, 0, 0);
	n2 = new AnimatedSprite("sprite/numbers/2.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 2);
	n2->colorKey(0, 0, 0);
	n3 = new AnimatedSprite("sprite/numbers/3.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 3);
	n3->colorKey(0, 0, 0);
	n4 = new AnimatedSprite("sprite/numbers/4.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 4);
	n4->colorKey(0, 0, 0);
	n5 = new AnimatedSprite("sprite/numbers/5.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 5);
	n5->colorKey(0, 0, 0);
	n6 = new AnimatedSprite("sprite/numbers/6.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 6);
	n6->colorKey(0, 0, 0);
	n7 = new AnimatedSprite("sprite/numbers/7.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 7);
	n7->colorKey(0, 0, 0);
	n8 = new AnimatedSprite("sprite/numbers/8.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 8);
	n8->colorKey(0, 0, 0);
	n9 = new AnimatedSprite("sprite/numbers/9.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 9);
	n9->colorKey(0, 0, 0);
	n0 = new AnimatedSprite("sprite/numbers/0.bmp", 25, 30, 0, 0, CONSTANTS.NUMBER_TEXTURE_ID + 0);
	n0->colorKey(0, 0, 0);
	hero = new Birds(heroTexture, heroShootTexture, heroAttackTexture,
		heroFaintTexture, heroHealthTexture,
		1, 200, CONSTANTS.BIRD_TEXTURE_ID);



}

void checkCollisions(){
	/*
	the following if condition should do 3 things if true:
	1. make enemies fly
	2.check for enemy player collision
	3. check for fire enemy collision
	*/
	if (enemiesIndex > 0){
		vector<Attack> fires = hero->getAttacks();
		// 1. & 2.

		for (int index = 0; index < enemiesIndex; index++) {
			Point2D position = enemies.at(index).getPosition();
			//check boundary wall collision
			if (position.x <= 0.0){
				enemies.erase(enemies.begin() + index);
				enemiesIndex--;
				break;
			}
			if (timerCount % 2 == 0)
			{
				enemies.at(index).fly();
			}

			// 2.
			if (myLib->checkCollision(hero->getBorderRect(), enemies.at(index).getBorderRect())){
				//kill enemy here
				PlayForegroundSound("sounds/crash.wav");
 				enemies.erase(enemies.begin() + index);
				enemiesIndex--;
				hero->decHealth(1);
				if (hero->getHealth() == 0){
					hero->changeMode(Birds::FAINT);
					PlayBackgroundSound("sounds/game_over.wav");
					scoreWrite();
					scoreRead();
					CurrentScreen = SCREEN_GAME_OVER;
					
					//kill hero if health=0
				}
				break;
			}
			if (hero->fireBallIndex>0){
				
				for (int i = 0; i < fires.size(); i++)
				{
					if (fires[i].getPosition().x>=CONSTANTS.SCREEN_WIDTH){
					hero->removeFireball(i);
					hero->fireCount++;
					}
					if (myLib->checkCollision(fires[i].getBorderRect(), enemies.at(index).getBorderRect()) && !enemies.at(index).toDie){
						//kill enemy here && remove fireball
						hero->removeFireball(i);
						enemies.at(index).changeMode(Enemy::DIE);
						enemies.at(index).toDie = true;
						PlayForegroundSound("sounds/hit.wav");
						score++;
						levelKillCount++;
						printf("Kill Count: %d \n, score: %d \n",levelKillCount, score);
						
						hero->fireCount++;
						break;
					}
				}
			}
			else { hero->doAttack = false; }

			if (enemies.at(index).toDie)
			{
				enemies.at(index).dieCount--;
			}

			if (enemies.at(index).dieCount == 0)
			{
				enemies.erase(enemies.begin() + index);
				enemiesIndex--;
			}
		}
	}

}

void generateEnemies(){
	enemyGenIndex = rand() % enemyRandomizer + 0;
	randomEnemyY = rand() % 400 + 10;
	//randomEnemyY = randomEnemyY + rand() % 175;
	enemies.resize(enemies.size() + 1);
	enemies[enemiesIndex] = Enemy(enemyTexture[enemyGenIndex], enemyDieTexture, 1100, randomEnemyY, CONSTANTS.ENEMY_TEXTURE_ID+1);
	enemiesIndex++;
	timerCount = 0;
}

void resetGame(){
	scoreWrite();
	scoreRead();
	score = 0;
	vector<Attack> fires = hero->getAttacks();
	if (enemies.size() > 0){
		for (int index = enemiesIndex-1; index >=0; index--) {
			enemies.erase(enemies.begin() + index);
			enemiesIndex--;
			Enemy::speedFactor = 1;
			
		}
	}
	if (fires.size()>0){
		for (int i = fires.size()-1; i >=0; i--)
		{
			hero->removeFireball(i);
		}
	}
	hero->~Birds();

	switch (currentCharacter)
	{

	case 1:
		hero = new Birds(heroTexture, heroShootTexture, heroAttackTexture,
			heroFaintTexture, heroHealthTexture,
			1, 200, CONSTANTS.BIRD_TEXTURE_ID);
		break;


	case 2:
		hero = new Birds(heroTexture3, heroShootTexture3, heroAttackTexture,
			heroFaintTexture3, heroHealthTexture,
			1, 200, CONSTANTS.BIRD_TEXTURE_ID);
		break;


	case 3:
		hero = new Birds(heroTexture2, heroShootTexture2, heroAttackTexture,
			heroFaintTexture2, heroHealthTexture,
			1, 200, CONSTANTS.BIRD_TEXTURE_ID);
		break;
	default:
		break;
	}

	

	timerCount = 0;
	enemyRandomizer = 1;

}

void resizeScreen(int x, int y)
{
	glutReshapeWindow(1000, 500);
}

void scoreRead() {
	fstream stream;

	stream.open("highscore.txt", ios::in);

	if (stream.fail()) {
		cout << "\nError loading Var File\n";
		return;
	}

	stream >> highScore;

	stream.close();

	cout << "\nScore: " << highScore << endl;
	return;
}

void scoreWrite() {
	int checkScore;

	if (score > highScore)
	{
		printf("New Score on file");
		ofstream stream;
		stream.open("highscore.txt");
		stream << score;
		stream.close();
		return;
	}

	else
	{
		printf("New Score is Same or less");
	}

}

void NumericScreenWriter(int num, int x, int y)
{
	string stringNum = to_string(num);
	int padding = 0;
	for (int i = 0; i < stringNum.length(); i++)
	{
		switch (stringNum[i])
		{
		case '1':
			n1->setPosition(x + padding, y);
			n1->drawSprite();
			break;


		case '2':
			n2->setPosition(x + padding, y);
			n2->drawSprite();
			break;


		case '3':
			n3->setPosition(x + padding, y);
			n3->drawSprite();
			break;


		case '4':
			n4->setPosition(x + padding, y);
			n4->drawSprite();
			break;


		case '5':
			n5->setPosition(x + padding, y);
			n5->drawSprite();
			break;


		case '6':
			n6->setPosition(x + padding, y);
			n6->drawSprite();
			break;


		case '7':
			n7->setPosition(x + padding, y);
			n7->drawSprite();
			break;


		case '8':
			n8->setPosition(x + padding, y);
			n8->drawSprite();
			break;


		case '9':
			n9->setPosition(x + padding, y);
			n9->drawSprite();
			break;


		case '0':
			n0->setPosition(x + padding, y);
			n0->drawSprite();
			break;


		default:
			break;
		}
		padding += 22;
	}

}

void PassiveMotion(int x, int y)
{
	switch (CurrentScreen)
	{
	case SCREEN_MAIN:
		break;
	case SCREEN_GAME:
		
		if (y >90 && y < 450)
		{
			hero->setPositionY(500 - y - 50);

		}
			
		
		
		break;
	case SCREEN_PAUSE:
		break;
	case SCREEN_CREDITS:
		break;
	case SCREEN_QUIT:
		break;
	case SCREEN_GAME_OVER:
		break;
	default:
		break;
	}
	GlobalMouse.x = x;
	GlobalMouse.y = y;
}

void changeLevel(){
	if (levelKillCount % 10 == 0 && levelKillCount != 0){
		hero->flySpeed += 0.5;
		Enemy::speedFactor += 1;
		levelKillCount = 0;
		if (enemyRandomizer < 4){
			enemyRandomizer++;
		}
	}
}

