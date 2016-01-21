
class Enemy: public Character{
public:
	AnimatedSprite *flyTexture;
	AnimatedSprite *dieTexture;
	bool flag;
	bool toDie = false;
	//what is this?? any different from killcount
	int dieCount = 5;
	float g = 9.8;
	float PI = 3.142, U = 5, Time = 0.001, Vx, Vy;
	static int speedFactor;
	int enemyX; 
	int enemyY; 
	float finalAngle;
	enum Mode
	{
		FLY,
		DIE
	} currState;
	//deprecated constructor
	Enemy(string name, int myWidth, int myHeight, float xx, float yy, int ID) :
		Character(name, myWidth, myHeight, xx, yy, ID)
	{
		flyTexture = new AnimatedSprite(name, myWidth, myHeight, xx, yy, ID);
		flyTexture->colorKey(102, 153, 51);

		dieTexture = new AnimatedSprite("sprite/enemies/die.bmp", 85, 76, xx, yy, ID + 3);
		dieTexture->colorKey(102, 153, 51);
		

		Angle[0] = 30;
		Angle[1] = 45;
		Angle[2] = 60;
		i = rand() % 2 + 0;
		characterTexture = flyTexture;

	}
	//updated constructor
	Enemy(AnimatedSprite *enemyTexture, AnimatedSprite *enemyDieTexture, float xx, float yy, int ID) {
		enemyTexture->setPosition(xx, yy);
		//enemyTexture->y = yy;
		flyTexture = enemyTexture;
		flyTexture->colorKey(102, 153, 51);


		enemyDieTexture->setPosition(xx, yy);
		dieTexture = new AnimatedSprite(*enemyDieTexture);
		dieTexture->colorKey(102, 153, 51);
		
		characterTexture = new AnimatedSprite(*flyTexture);
		Angle[0] = 30;
		Angle[1] = 45;
		Angle[2] = 60;
		
		i = rand() % 2 + 0;
		flag = rand() % 2==1;
		enemyY = characterTexture->y;
		 finalAngle = Angle[i];
		finalAngle = finalAngle*PI / 180.0;
		
	}

	Enemy()
	{
		
	}


	// Public Method
	void fly();
	void changeMode(Mode state);
	


private:
	int Angle[3];
	int i; 
	
	

};

void Enemy::changeMode(Mode state)
{
	if (currState == state)
	{

		return;
	}
	currState = state;
	float x = characterTexture->x;
	float y = characterTexture->y;
	
	switch (state)
	{
	case Enemy::FLY:
		characterTexture = flyTexture;
		break;
	case Enemy::DIE:
		characterTexture = dieTexture;
		toDie = true;
		break;
	default:
		break;
	}

	characterTexture->x = x;
	characterTexture->y = y;
}

void Enemy::fly(){

	int x = characterTexture->x;
	int y = characterTexture->y;
	Vx = sqrtf(U* cos(finalAngle));
	Vy = sqrtf(U* sin(finalAngle) - g*Time);
	 

	if (characterTexture->y && !flag || characterTexture->y>enemyY + 150 || characterTexture->y>420)// DONT TOUCH THIS CONDITION
	{
		flag = false;
		y -= Enemy::speedFactor+Vy;//((Vy*Time) + 0.5*g*(Time*Time));
		x -= Enemy::speedFactor+ Vx;
	}
	else 
	{
		x -= Enemy::speedFactor+Vx;
		y += Enemy::speedFactor+Vy;//((Vy*Time) + 0.5*g*(Time*Time));
		
	}
	if (characterTexture->y <= enemyY - 150 || characterTexture->y<50){
		flag = true;
	}
	Time += 0.001;
        characterTexture->x =x;
		characterTexture->y = y;
		update();
}

int  Enemy::speedFactor = 1;
