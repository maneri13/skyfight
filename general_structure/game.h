class game 
{

public:
	// Game Assets
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

	game()
	{

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

};