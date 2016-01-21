class Character{

protected:
	Point2D pos;
	Rect borderRect;
	Circle borderCircle;
	AnimatedSprite *characterTexture;
	int currentAnim;
	

public:
	Character(string name, int myWidth, int myHeight, float xx, float yy, int ID)
	{
		
	}
	Character(AnimatedSprite *texture, int myWidth, int myHeight, float xx, float yy, int ID)
	{

	}

	Character(){}
	~Character(){
		//free (this);
	}


	void draw();
	void update();
	
	void die();
	Rect getBorderRect();
	Circle getBorderCircle();
	void updateBorderRect();
	Point2D getPosition();
	void setPositionY(int y);

private:
	void updatePos(Point2D pos);
	void setBorderRect(int l, int b, int width, int height);
	void setBorderCircle(int centerX, int centerY, int radius);
	void updateTexture();
};


void Character::draw(){
	currentAnim = characterTexture->currentAnimState;
	characterTexture->drawSprite();
}

void Character::update(){
	//this->updatePos();
	this->updateTexture();
	this->updateBorderRect();
}



void Character::updatePos(Point2D pos){
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Character::setBorderRect(int l, int b, int width, int height){
	this->borderRect.left = l;
	this->borderRect.bottom = b;
	this->borderRect.width = width;
	this->borderRect.height = height;
}

void Character::setBorderCircle(int centerX, int centerY, int radius){
	this->borderCircle.centerX = centerX;
	this->borderCircle.centerY = centerY;
	this->borderCircle.radius = radius;
}

Rect Character::getBorderRect(){
	return this->borderRect;
}

Circle Character::getBorderCircle(){
	return this->borderCircle;
}

void Character::updateBorderRect(){
	this->setBorderRect(this->characterTexture->x, this->characterTexture->y, this->characterTexture->w, this->characterTexture->h);
}




void Character::updateTexture(){
	currentAnim = characterTexture->currentAnimState;
	characterTexture->anim[currentAnim].currentFrames++;
	characterTexture->setFrame((characterTexture->anim[currentAnim].currentFrames++) % 5);
	characterTexture->sy = 1;
}

Point2D Character::getPosition(){
	return Point2D{ characterTexture->x, characterTexture->y };
}

void Character::setPositionY(int y)
{
	characterTexture->y = y;
}