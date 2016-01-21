/*
* File:   Hero.h
* Author: humera
*
* Created on August 20, 2011, 6:00 AM
*/

#ifndef HERO_H
#define	HERO_H

typedef struct Frame
{
	// a single (s,t) texture coordinate
	float u, v;
	int currentFrames; // frameID
}FrameST;

class AnimatedSprite
{
public:

	static const int  FRAMES_PER_SECOND_SPRITE = 10;
	static const int FRAME_DELAY_SPRITE = 1000 / FRAMES_PER_SECOND_SPRITE;
	/* no animation can have more than 100 frames */
	static const int MAX_ANIM = 100;

	/* anim types */
	enum { ANIM_ACTION = 0, ANIM_JUMP, ANIM_WALK_LEFT, ANIM_WALK_RIGHT, ANIM_IDLE };
	FrameST anim[5]; //because I only have 5 anim in this sheet

	//RGBpixmap sheet;
	RGBApixmap sheet;
	int sheetWidth, sheetHeight;


	// normalized width/height of sprite for texture
	float texWidth, texHeight;


	/* position info */
	float x, y;
	/* height of sprite in pixels on screen*/
	float w, h;

	int currentAnimState;
	// the sprite comes from a sprite sheet
	unsigned long quadID;
	unsigned int texID;
	float sx, sy;



	AnimatedSprite(string name, int myWidth, int myHeight, float xx, float yy, int ID)
	{
		cout << "\n" + name << "\n";
		int ret;
		ret = this->sheet.readBMPFile(name, 1);
		cout << endl << endl << " Orig Image width is:" << sheet.nCols;
		cout << endl << " Orig Image ht is:" << sheet.nRows;

		this->sheetWidth = sheet.nCols;
		this->sheetHeight = sheet.nRows;

		this->x = xx;
		this->y = yy;

		this->w = myWidth;
		this->h = myHeight;

		this->texHeight = h / (float)sheetHeight;
		this->texWidth = w / (float)sheetWidth;

		if (texWidth >1.0){ sx = texWidth; }
		else sx = 1.0;
		if (texHeight >1.0){ sy = texHeight; }
		else sy = 1.0;

		this->currentAnimState = ANIM_IDLE; //initializes the character's initial state

		this->texID = ID;
		//glGenTextures(1,&this->texID);

		this->anim->u = 0;
		this->anim->v = 0;

		this->anim[this->currentAnimState].currentFrames = 0;
	}

	void colorKey(int r, int g, int b)
	{
		this->sheet.setChromaKey(r, g, b);
		this->sheet.setTexture(this->texID);
	}

	void setFrame(int frame)
	{
		this->anim[this->currentAnimState].currentFrames = frame;
	}

	void drawSprite()
	{
		//cout << endl << "@@@@@@@@@@@@@@New Sprite@@@@@@@@@@@@@@" << endl;

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

		glPushMatrix();
		glTranslatef(this->x, this->y, 0);
		glScalef(this->sx, this->sy, 1.0f);

		int currentAnim = this->currentAnimState;
		int currentFrame = this->anim[currentAnim].currentFrames;

		FrameST* UV = this->anim;

		float u = UV->u + this->texWidth*currentFrame;
		float v = UV->v + this->texHeight*currentAnim;

		/* bind the appropriate texture frame */
		glBindTexture(GL_TEXTURE_2D, this->texID);

		glBegin(GL_QUADS);
		//glTexCoord2f(0,0);
		glTexCoord2f(u, v);
		glVertex2f(0, 0);

		//glTexCoord2f(0,1);
		glTexCoord2f(u, v + this->texHeight);
		glVertex2f(0, this->h);

		//glTexCoord2f(1,1);
		glTexCoord2f(u + this->texWidth, v + this->texHeight);
		glVertex2f(this->w, this->h);

		//glTexCoord2f(1,0);
		glTexCoord2f(u + this->texWidth, v);
		glVertex2f(this->w, 0);
		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);

	}// end drawSprite

	// new methods

	void setPosition(float x, float y);

};

void AnimatedSprite::setPosition(float x, float y){
	this->x = x;
	this->y = y;

}



#endif