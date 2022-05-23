#pragma once

#include "constants.h"
#include "globals.h"

using namespace std;

//Player sprites
const int RIGHT_1 = 0;
const int RIGHT_2 = 1;
const int RIGHT_3 = 2;
const int RIGHT_4 = 3;
const int RIGHT_5 = 4;
const int RIGHT_6 = 5;
const int RIGHT_7 = 6;
const int RIGHT_8 = 7;
const int RIGHT_JUMP = 8;
const int RIGHT_FALL = 9;
const int LEFT_1 = 10;
const int LEFT_2 = 11;
const int LEFT_3 = 12;
const int LEFT_4 = 13;
const int LEFT_5 = 14;
const int LEFT_6 = 15;
const int LEFT_7 = 16;
const int LEFT_8 = 17;
const int LEFT_JUMP = 18;
const int LEFT_FALL = 19;
const int RIGHT_IDLE_1 = 20;
const int RIGHT_IDLE_2 = 21;
const int RIGHT_IDLE_3 = 22;
const int RIGHT_IDLE_4 = 23;
const int RIGHT_IDLE_5 = 24;
const int RIGHT_IDLE_6 = 25;
const int RIGHT_IDLE_7 = 26;
const int RIGHT_IDLE_8 = 27;
const int RIGHT_IDLE_9 = 28;
const int RIGHT_IDLE_10 = 29;
const int LEFT_IDLE_1 = 30;
const int LEFT_IDLE_2 = 31;
const int LEFT_IDLE_3 = 32;
const int LEFT_IDLE_4 = 33;
const int LEFT_IDLE_5 = 34;
const int LEFT_IDLE_6 = 35;
const int LEFT_IDLE_7 = 36;
const int LEFT_IDLE_8 = 37;
const int LEFT_IDLE_9 = 38;
const int LEFT_IDLE_10 = 39;
const int RIGHT_DEAD_1 = 40;
const int RIGHT_DEAD_2 = 41;
const int RIGHT_DEAD_3 = 42;
const int RIGHT_DEAD_4 = 43;
const int RIGHT_DEAD_5 = 44;
const int RIGHT_DEAD_6 = 45;
const int RIGHT_DEAD_7 = 46;
const int RIGHT_DEAD_8 = 47;
const int RIGHT_DEAD_9 = 48;
const int RIGHT_DEAD_10 = 49;
const int LEFT_DEAD_1 = 50;
const int LEFT_DEAD_2 = 51;
const int LEFT_DEAD_3 = 52;
const int LEFT_DEAD_4 = 53;
const int LEFT_DEAD_5 = 54;
const int LEFT_DEAD_6 = 55;
const int LEFT_DEAD_7 = 56;
const int LEFT_DEAD_8 = 57;
const int LEFT_DEAD_9 = 58;
const int LEFT_DEAD_10 = 59;
const int PLAYER_SPRITE_TOTAL = 60;

const int dead_sprite_h_offset = 40;
const int dead_sprite_v_offset = -2;

enum class ePlayerAnimationState
{
	RIGHT_IDLE,
	RIGHT,
	RIGHT_JUMP,
	RIGHT_FALL,
	RIGHT_DEAD,
	LEFT_IDLE,
	LEFT,
	LEFT_JUMP,
	LEFT_FALL,
	LEFT_DEAD
};

class clPlayer
{
public:
	//Constructor
	clPlayer();
	//Destructor
	~clPlayer();

	//Gets Player position
	int getPosX();
	int getPosY();

	bool animatingGameOver();

	//Handling functions
	void handleEvent(SDL_Event& event);
	void move(float timestep, const int maxWidth, const int maxHeight, clTile* tiles[], int total_tiles);
	void reset(const int posX, const int posY);
	void render(const int cameraX, const int cameraY);

private:

	float mPosX;	// X position
	float mPosY;	// X position
	float mVelX;	// X velocity
	float mVelY;	// Y velocity

	SDL_Rect mBox;	// collision box

	ePlayerAnimationState mCurrentState; //player status

	// texture and animation variables
	clTexture mPlayerSpritesheet;
	SDL_Rect  mPlayerSpriteClips[PLAYER_SPRITE_TOTAL];
	int mLastSpriteRendered;
	Uint32 mLastSpriteTimer;
	Uint8 mAlphaValue;

	// Music and Sounds
	Mix_Chunk* mJump_sfx;
	Mix_Chunk* mLife_lost_sfx;

	//utility
	int findNextSprite();
};

