
class Attack{

private:
	Rect borderRect;
	Circle borderCircle;
	AnimatedSprite *attackTexture;
	int currentAnim;
	//RGBApixmap energyBall;

public:
	Attack(){

	}

	Attack(char *name, int myWidth, int myHeight, float xx, float yy, int ID){
		attackTexture = new AnimatedSprite(name, myWidth, myHeight, xx, yy, ID);
		attackTexture->colorKey(190, 76, 0);
	}

	Attack(AnimatedSprite *texture,float xx, float yy, int ID){
		texture->setPosition(xx, yy);
		attackTexture = new AnimatedSprite(*texture);
		attackTexture->colorKey(190, 76, 0);
	}
	Point2D getPosition();
	void draw();
	void update();
	void die();
	Rect getBorderRect();
	Circle getBorderCircle();
	void updateBorderRect();

private:
	void setBorderRect(int l, int b, int width, int height);
	void setBorderCircle(int centerX, int centerY, int radius);
	void updateTexture();
};

void Attack::draw(){
	currentAnim = attackTexture->currentAnimState;
	attackTexture->drawSprite();
}

void Attack::update(){
	//this->updatePos();
	this->updateTexture();
	this->updateBorderRect();
}

void Attack::setBorderRect(int l, int b, int width, int height){
	this->borderRect.left = l;
	this->borderRect.bottom = b;
	this->borderRect.width = width;
	this->borderRect.height = height;
}

void Attack::setBorderCircle(int centerX, int centerY, int radius){
	this->borderCircle.centerX = centerX;
	this->borderCircle.centerY = centerY;
	this->borderCircle.radius = radius;
}

Rect Attack::getBorderRect(){
	return this->borderRect;
}

Circle Attack::getBorderCircle(){
	return this->borderCircle;
}

void Attack::updateBorderRect(){
	this->setBorderRect(this->attackTexture->x, this->attackTexture->y, this->attackTexture->w, this->attackTexture->h);
}

void Attack::updateTexture(){
		/*currentAnim = attackTexture->currentAnimState;
		attackTexture->anim[currentAnim].currentFrames++;
		attackTexture->setFrame((attackTexture->anim[currentAnim].currentFrames++) % 5);
		attackTexture->sy = 1;*/
		
			attackTexture->x += 5.0;
		
}

Point2D Attack::getPosition(){
	return Point2D{ attackTexture->x, attackTexture->y };
}