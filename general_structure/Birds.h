class Birds : public Character
{
private:
	int health;
	int healthCurrentAnim = 0;
	
	AnimatedSprite *healthTexture;
	AnimatedSprite *flyTexture;
	AnimatedSprite *faintTexture;
	AnimatedSprite *shootTexture;
	AnimatedSprite *attackTexture;

	vector<Attack> fireBalls;
	
	

public:
	//public fields
	float flySpeed = 1;
	 int fireCount = 8;
	bool doAttack;
	bool attackMode;
	int fireBallIndex = 0;
	enum Mode
	{
		FLY,
		FAINT,
		SHOOT
	} currState;

	//constructor
	Birds(string name, int myWidth, int myHeight, float xx, float yy, int ID) :
		Character(name,  myWidth,  myHeight,  xx,  yy,  ID)
	{
		

		flyTexture = new AnimatedSprite(name, myWidth, myHeight, xx, yy, ID);
		flyTexture->colorKey(102, 153, 51);
		
		
		faintTexture = new AnimatedSprite("sprite/birdking/sp_birdking_gameover.bmp", 112, 102, xx, yy, ID + 3);
		faintTexture->colorKey(102, 153, 51);


		
		shootTexture = new AnimatedSprite("sprite/birdking/sp_birdking_shoot.bmp", 124, 90, xx, yy, ID + 4);
		shootTexture->colorKey(102, 153, 51);

		health = 3;
		healthTexture = new AnimatedSprite("sprite/extra/life.bmp", 55, 55, 100, 430, 3000);
		healthTexture->colorKey(102, 153, 51);

		characterTexture = flyTexture;
	}

	//updated constructor
	Birds(AnimatedSprite *heroTexture,AnimatedSprite *heroShootTexture,AnimatedSprite *heroAttackTexture,
		AnimatedSprite *heroFaintTexture,AnimatedSprite *heroHealthTexture,
	 float xx, float yy, int ID) 
	{

		//enemyDieTexture->setPosition(xx, yy);
		//dieTexture = new AnimatedSprite(*enemyDieTexture);

		heroTexture->setPosition(xx, yy);
		flyTexture = new AnimatedSprite(*heroTexture);
		flyTexture->colorKey(102, 153, 51);

		heroFaintTexture->setPosition(xx, yy);
		faintTexture = new AnimatedSprite (*heroFaintTexture);
		faintTexture->colorKey(102, 153, 51);


		
		shootTexture = new AnimatedSprite(*heroShootTexture);
		shootTexture->colorKey(102, 153, 51);

		health = 3;
		healthTexture = new AnimatedSprite(*heroHealthTexture);
		healthTexture->colorKey(102, 153, 51);

		attackTexture = new AnimatedSprite(*heroAttackTexture);
		healthTexture->colorKey(102, 153, 51);


		characterTexture = flyTexture;
	}

	~Birds(){}
	//public methods
	void drawHealth();
	void drawBird();
	void updateBird();
	void attack();
	void flyUp();
	void flyDown();
	void changeMode(Mode state);
	void decHealth(int x);
	vector<Attack> getAttacks();
	void removeFireball(int index);
	int getHealth();

};

void Birds::changeMode(Mode state)
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
	case Birds::FLY:
		characterTexture = flyTexture;
		break;
	case Birds::SHOOT:
		characterTexture = shootTexture;
		break;
	case Birds::FAINT:
		characterTexture = faintTexture;
		break;
	default:
		break;
	}

	characterTexture->x = x;
	characterTexture->y = y;
}

void Birds::drawBird()
{
	this->draw();
	drawHealth();
	if (doAttack){
		for (long index = 0; index<(long)fireBallIndex; ++index) {
			fireBalls.at(index).draw();
		}

	}
}

void Birds:: drawHealth(){
	healthTexture->y = 420;
	healthTexture->x = 800;
	for (int i = 0; i < health; i++)
	{
		healthTexture->drawSprite();
		healthTexture->x += 65;
	}

}

void Birds::attack(){
	fireBalls.resize(fireBalls.size() + 1);
	fireBalls[fireBallIndex] = Attack(attackTexture, characterTexture->x + 95, characterTexture->y+25,CONSTANTS.FIRE_TEXTURE_ID);
	fireBallIndex++;


	attackMode = true;
}

void Birds::flyUp(){
	if (characterTexture->y <= 350)
	{
		
		characterTexture->y += 8.0*flySpeed;
	}
}

void Birds::flyDown(){
	if (characterTexture->y >= 10)
	{
		characterTexture->y -= 8.0*flySpeed;
	}
}

vector<Attack> Birds::getAttacks(){
	return fireBalls;
}

void Birds::updateBird(){
	
	this->update();

	if (doAttack){
		for (long index = 0; index<(long)fireBallIndex; ++index) {
			fireBalls.at(index).update();
		}
	}

}

void Birds::decHealth(int x){
	health = health-x;
}

void Birds::removeFireball(int index){
	fireBalls.erase(fireBalls.begin() + index);
	fireBallIndex--;
}

int Birds::getHealth(){

	return health;
}