/*
Constant class contain constant values that won't change through out the project
define all your constants in this class
*/
class _Constants{
public:
	static float gravity;
	static const int  FRAMES_PER_SECOND_SPRITE = 50;
	static const int FRAME_DELAY_SPRITE = 1000 / FRAMES_PER_SECOND_SPRITE;
	static const int BIRD_TEXTURE_ID = 1000;
	static const int ENEMY_TEXTURE_ID = 4000;
	static const int BACKGROUND_TEXTURE_ID = 2000;
	static const int NUMBER_TEXTURE_ID = 5000;
	static const int FIRE_TEXTURE_ID = 3000;
	static const int SCREEN_WIDTH = 1000;
	static const int SCREEN_HEIGHT = 500;
};

_Constants CONSTANTS;