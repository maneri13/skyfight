

class Background{

private:
	AnimatedSprite *bg;
	int currentAnim;

public:
	Background(char *name, int myWidth, int myHeight, float xx, float yy, int ID){
		bg = new AnimatedSprite(name, myWidth, myHeight, xx, yy, ID);
		bg ->colorKey(255, 255, 255);
	}
	void draw();
	void setBg(float change);
};

void Background::draw()
{
	currentAnim = bg-> currentAnimState;
	bg -> drawSprite();
}

void Background::setBg(float change)
{
	bg->anim[0].u += change;
}