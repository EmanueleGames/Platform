#include "globals.h"
#include "clTitleState.h"
#include "clStage1State.h"
#include "clStage2State.h"
#include "clStage3State.h"
#include "clGameOverState.h"

using namespace std;

//Gaming window and window renderer
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Game status variables
eGameStates  gActualState = eGameStates::STATE_NULL;
eGameStates  gNextState = eGameStates::STATE_NULL;
clGameState* ptrCurrentState = NULL;

//The event structure
SDL_Event gEvent;

//Game setup variables
string savefile_name = "data/savefile.bin";
bool gSaveFileFound = false;
structSaveData gSaveData = { 1,STARTING_LIVES,0,0 };
eGameOption gSelectedOption = eGameOption::NEW_GAME;
eGameStates gNextStage = eGameStates::STATE_STAGE1;

//Gameplay variables
int  gLives = STARTING_LIVES;
int  gCoins = 0;
int  gScore = 0;
bool gLifeLost = false;
bool gStageCleared = false;
bool gStageCheckpoint = false;
int gPlayerSpawnX = 0;
int gPlayerSpawnY = 0;
TTF_Font*  gFontHUD;
clTexture  gTileSpriteSheet;
SDL_Rect   gTileSpriteClips[TILE_SPRITE_TOTAL];
clTimer    gAnimationTimer;
Mix_Chunk* gCoin_sfx;
Mix_Chunk* gOneUp_sfx;

//FPS timer and variables
clTimer   gCalcFPStimer;
clTexture gFPSTextTexture;
TTF_Font* gFontFPS;
float gAvgFPS;
int   gCountedFrames;
int   gDecimalDigitValue;
stringstream gTextFPS;

//Global Textures and Colors
const SDL_Color textColorBlack = { 0, 0, 0, 255 };
const SDL_Color textColorGray  = { 100, 100, 100, 255 };
const SDL_Color textColorWhite = { 240, 240, 240, 255 };

/*************** FUNCTIONS ***************/

bool SDL_initialize()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "Warning: Linear texture filtering not enabled!" << endl;
	}

	//Create Game Window
	gWindow = SDL_CreateWindow("Platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		cout << "Window creation failed! SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	//Create Renderer for the window (vsync ON)
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		cout << "Renderer creation failed! SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	//PNG loading initialization (SDL_image)
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	//Font loading initialization (SDL_ttf)
	if (TTF_Init() == -1)
	{
		cout << "SDL_ttf failed to initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		return false;
	}

	//Audio loading initialization (SDL_mixer)
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer failed to initialize! SDL_mixer Error: " << Mix_GetError() << endl;
		return false;
	}

	//Everything was fine
	return true;
}

void SDL_close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool load_game_data()
{
	//Success flag
	bool fl_success = true;

	//Open the fonts
	gFontFPS = TTF_OpenFont("data/Quicksand.ttf", 12);
	if (gFontFPS == NULL)
	{
		cout << "Failed to load Quicksand font! SDL_ttf Error: " << TTF_GetError() << endl;
		fl_success = false;
	}

	//Open HUD font
	gFontHUD = TTF_OpenFont("data/mk_font.ttf", 28);
	if (gFontHUD == NULL)
	{
		cout << "Failed to load early_gameboy font for labels! SDL_ttf Error: " << TTF_GetError() << endl;
		fl_success = false;
	}

	//Load game sprites for player and tiles
	if (!gTileSpriteSheet.createFromFile(gRenderer, "data/tile_sprite_sheet.png"))
	{
		cout << "Tile Sprite Sheet loading failed!" << endl;
		fl_success = false;
	}

	//Sound Effects
	gCoin_sfx = Mix_LoadWAV("data/coin_sfx.wav");
	if (gCoin_sfx == NULL)
		cout << "Failed to coin SFX! SDL_mixer Error: " << Mix_GetError() << endl;
	else
		Mix_VolumeChunk(gCoin_sfx, SFX_VOLUME);

	gOneUp_sfx = Mix_LoadWAV("data/oneup_sfx.wav");
	if (gOneUp_sfx == NULL)
		cout << "Failed to life up SFX! SDL_mixer Error: " << Mix_GetError() << endl;
	else
		Mix_VolumeChunk(gOneUp_sfx, SFX_VOLUME);

	return fl_success;
}

void free_game_data()
{

	//Free game sprites for player and tiles
	//gTiles[]

	//Free sfx
	Mix_FreeChunk(gCoin_sfx);
	Mix_FreeChunk(gOneUp_sfx);
	gCoin_sfx = NULL;
	gOneUp_sfx = NULL;

	TTF_CloseFont(gFontFPS);
	TTF_CloseFont(gFontHUD);
	gFontFPS = NULL;
	gFontHUD = NULL;
}

bool game_initialize()
{
	//Success flag
	bool fl_success = true;

	//FPS counter initialization
	gDecimalDigitValue = 1;
	if (FPS_DECIMAL_DIGIT > 0)
	{
		for (int i = 0; i < FPS_DECIMAL_DIGIT; i++)
		{
			gDecimalDigitValue *= 10;
		}
	}
	float gAvgFPS = 0;
	int gCountedFrames = 0;

	//Load game sprite clips
	gTileSpriteClips[TILE_NONE].x = 0;
	gTileSpriteClips[TILE_NONE].y = 0;
	gTileSpriteClips[TILE_NONE].w = TILE_WIDTH;
	gTileSpriteClips[TILE_NONE].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_EARTH].x = 40;
	gTileSpriteClips[TILE_EARTH].y = 0;
	gTileSpriteClips[TILE_EARTH].w = TILE_WIDTH;
	gTileSpriteClips[TILE_EARTH].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_GRASS].x = 80;
	gTileSpriteClips[TILE_GRASS].y = 0;
	gTileSpriteClips[TILE_GRASS].w = TILE_WIDTH;
	gTileSpriteClips[TILE_GRASS].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_BRICK].x = 120;
	gTileSpriteClips[TILE_BRICK].y = 0;
	gTileSpriteClips[TILE_BRICK].w = TILE_WIDTH;
	gTileSpriteClips[TILE_BRICK].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_BRICK_DARK].x = 160;
	gTileSpriteClips[TILE_BRICK_DARK].y = 0;
	gTileSpriteClips[TILE_BRICK_DARK].w = TILE_WIDTH;
	gTileSpriteClips[TILE_BRICK_DARK].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_SPIKE].x = 200;
	gTileSpriteClips[TILE_SPIKE].y = 0;
	gTileSpriteClips[TILE_SPIKE].w = TILE_WIDTH;
	gTileSpriteClips[TILE_SPIKE].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_COIN1].x = 0;
	gTileSpriteClips[TILE_COIN1].y = 40;
	gTileSpriteClips[TILE_COIN1].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN1].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_COIN2].x = 40;
	gTileSpriteClips[TILE_COIN2].y = 40;
	gTileSpriteClips[TILE_COIN2].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN2].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_COIN3].x = 80;
	gTileSpriteClips[TILE_COIN3].y = 40;
	gTileSpriteClips[TILE_COIN3].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN3].h = TILE_HEIGHT;
	
	gTileSpriteClips[TILE_COIN4].x = 120;
	gTileSpriteClips[TILE_COIN4].y = 40;
	gTileSpriteClips[TILE_COIN4].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN4].h = TILE_HEIGHT;
	
	gTileSpriteClips[TILE_COIN5].x = 160;
	gTileSpriteClips[TILE_COIN5].y = 40;
	gTileSpriteClips[TILE_COIN5].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN5].h = TILE_HEIGHT;
	
	gTileSpriteClips[TILE_COIN6].x = 200;
	gTileSpriteClips[TILE_COIN6].y = 40;
	gTileSpriteClips[TILE_COIN6].w = TILE_WIDTH;
	gTileSpriteClips[TILE_COIN6].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_FLAG_END].x = 0;
	gTileSpriteClips[TILE_FLAG_END].y = 80;
	gTileSpriteClips[TILE_FLAG_END].w = TILE_WIDTH;
	gTileSpriteClips[TILE_FLAG_END].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_FLAG_CP].x = 40;
	gTileSpriteClips[TILE_FLAG_CP].y = 80;
	gTileSpriteClips[TILE_FLAG_CP].w = TILE_WIDTH;
	gTileSpriteClips[TILE_FLAG_CP].h = TILE_HEIGHT;

	gTileSpriteClips[TILE_FLAGPOLE].x = 80;
	gTileSpriteClips[TILE_FLAGPOLE].y = 80;
	gTileSpriteClips[TILE_FLAGPOLE].w = TILE_WIDTH;
	gTileSpriteClips[TILE_FLAGPOLE].h = TILE_HEIGHT;

	//gTileSpriteClips[TILE_TEST].x = xxx;
	//gTileSpriteClips[TILE_TEST].y = yyy;
	//gTileSpriteClips[TILE_TEST].w = TILE_WIDTH;
	//gTileSpriteClips[TILE_TEST].h = TILE_HEIGHT;


	//Try to load a game
	gSaveFileFound = load_game();
	
	//Game starts in Intro State
	gActualState = eGameStates::STATE_TITLE;
	//Set the current game state object
	ptrCurrentState = new clTitleState();

	return fl_success;
}

void reset_game()
{
	gLives = STARTING_LIVES;
	gCoins = 0;
	gScore = 0;
	gLifeLost = false;
	gStageCleared = false;
}

bool load_game()
{
	//Check if there is a save file
	SDL_RWops* savefile = SDL_RWFromFile(savefile_name.c_str(), "r+b");

	//File does not exist
	if (savefile == NULL)
	{
		cout << "Could not find/open the savefile! SDL Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		//Load data
		cout << "Reading savefile..." << endl;
		SDL_RWread(savefile, &(gSaveData.stage), sizeof(int), 1);
		SDL_RWread(savefile, &(gSaveData.lives), sizeof(int), 1);
		SDL_RWread(savefile, &(gSaveData.coins), sizeof(int), 1);
		SDL_RWread(savefile, &(gSaveData.score), sizeof(int), 1);

		//Close file handler
		SDL_RWclose(savefile);

		return true;
	}
}

bool save_game()
{
	//Create savefile for writing (w)
	SDL_RWops* savefile = SDL_RWFromFile(savefile_name.c_str(), "w+b");
	if (savefile != NULL)
	{
		cout << "Savefile created!" << endl;
		gSaveFileFound = true;

		switch (gNextState)
		{
		case eGameStates::STATE_STAGE1:
			gSaveData.stage = 1;
			break;
		case eGameStates::STATE_STAGE2:
			gSaveData.stage = 2;
			break;
		case eGameStates::STATE_STAGE3:
			gSaveData.stage = 3;
			break;
		default:
			break;
		}
		gSaveData.lives = gLives;
		gSaveData.coins = gCoins;
		gSaveData.score = gScore;

		//Initialize data
		SDL_RWwrite(savefile, &(gSaveData.stage), sizeof(int), 1);
		SDL_RWwrite(savefile, &(gSaveData.lives), sizeof(int), 1);
		SDL_RWwrite(savefile, &(gSaveData.coins), sizeof(int), 1);
		SDL_RWwrite(savefile, &(gSaveData.score), sizeof(int), 1);

		//Close file handler
		SDL_RWclose(savefile);
		return true;
	}
	else
	{
		cout << "Could not create/write the savefile! SDL Error: " << SDL_GetError() << endl;
		return false;
	}
}

void set_next_state(eGameStates newState)
{
	//Only set next state if the user hasn't requested to exit
	if (gNextState != eGameStates::STATE_EXIT)
	{
		gNextState = newState;
	}
}

void change_state()
{
	//If next state is a valid one
	if (gNextState != eGameStates::STATE_NULL)
	{
		//If we need to exit, we don't delete the current state
		if (gNextState != eGameStates::STATE_EXIT)
		{
			delete ptrCurrentState;
		}

		//Change the state
		switch (gNextState)
		{
		case eGameStates::STATE_TITLE:
			ptrCurrentState = new clTitleState();
			break;
		case eGameStates::STATE_STAGE1:
			ptrCurrentState = new clStage1State();
			break;
		case eGameStates::STATE_STAGE2:
			ptrCurrentState = new clStage2State();
			break;
		case eGameStates::STATE_STAGE3:
			ptrCurrentState = new clStage3State();
			break;
		case eGameStates::STATE_GAME_OVER:
			ptrCurrentState = new clGameOverState();
			break;
		}

		//update the actual anx next state
		gActualState = gNextState;
		gNextState = eGameStates::STATE_NULL;
	}
}

float roundDown(float number, const int value)
{
	// EXAMPLE with 2 digits (value = 100):
	// 12.3456 * 100 = 1234.56		to shift the point
	// 1234.56 + .5 = 1235.06		for rounding off value 
	// then type cast to int so value is 1235
	// then divided by 100 so the value converted into 12.35 

	number = (int)(number * value + .5);
	return (number / value);
}

void calc_and_texture_FPS()
{
	gAvgFPS = gCountedFrames / (gCalcFPStimer.getTicks() / 1000.f);
	if (gAvgFPS > 2000000)
	{
		gAvgFPS = 0;
	}
	else
	{
		gAvgFPS = roundDown(gAvgFPS, gDecimalDigitValue);
	}

	//FPS text
	gTextFPS.str("");
	gTextFPS << "Average FPS (vsync ON):  " << gAvgFPS;
	if (!gFPSTextTexture.createFromText(gRenderer, gFontFPS, gTextFPS.str().c_str(), textColorWhite))
	{
		cout << "Unable to render FPS texture!" << endl;
	}
}

bool rectCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool tilesetCollision(SDL_Rect box, clTile* tileset[], int tileset_number)
{
	bool obstacle  = false;
	bool spike_collision = false;
	bool coin_collision = false;
	bool flag_cp_collision = false;
	bool flag_end_collision = false;
	int coin_index = -1;

	//Go through the tiles
	for (int i = 0; i < tileset_number; ++i)
	{
		//If the tile is a wall type tile
		if ((tileset[i]->getType() == TILE_EARTH) ||
			(tileset[i]->getType() == TILE_GRASS) ||
			(tileset[i]->getType() == TILE_BRICK) ||
			(tileset[i]->getType() == TILE_BRICK_DARK))
		{
			//If the collision box touches the wall tile
			if (rectCollision(box, tileset[i]->getBox()))
			{
				return true;
			}
		}

		//If the tile is a spike
		if (tileset[i]->getType() == TILE_SPIKE)
		{
			//If the collision box touches the spike
			if (rectCollision(box, tileset[i]->getBox()))
			{
				spike_collision = true;
			}
		}

		//If the tile is a coin tile
		if ((tileset[i]->getType() >= TILE_COIN1) &&
			(tileset[i]->getType() <= TILE_COIN6))
		{
			//If the collision box touches coin
			if (rectCollision(box, tileset[i]->getBox()) && tileset[i]->isActive())
			{
				coin_collision = true;
				coin_index = i;
			}
		}

		//If the tile is a flag tile
		if (tileset[i]->getType() == TILE_FLAG_END)
		{
			//If the collision box touches the flag
			if (rectCollision(box, tileset[i]->getBox()) && tileset[i]->isActive())
			{
				flag_end_collision = true;
			}
		}

		//If the tile is a flag tile
		if (tileset[i]->getType() == TILE_FLAG_CP)
		{
			//If the collision box touches the flag
			if (rectCollision(box, tileset[i]->getBox()) && tileset[i]->isActive())
			{
				flag_cp_collision = true;
			}
		}
	}

	if (spike_collision)
	{
		gLifeLost = true;
		gScore = gScore - LIFE_LOSS_VALUE;
		if (gScore < 0)
			gScore = 0;
	}
	if (flag_end_collision)
	{
		gStageCleared = true;
	}
	if (flag_cp_collision)
	{
		gStageCheckpoint = true;
		switch (gActualState)
		{
		case eGameStates::STATE_TITLE:
			break;
		case eGameStates::STATE_STAGE1:
			gPlayerSpawnX = 194 * TILE_WIDTH;
			gPlayerSpawnY = 13 * TILE_HEIGHT;
			break;
		case eGameStates::STATE_STAGE2:
			gPlayerSpawnX = 219 * TILE_WIDTH;
			gPlayerSpawnY = 6 * TILE_HEIGHT;
			break;
		case eGameStates::STATE_STAGE3:
			gPlayerSpawnX = 179 * TILE_WIDTH;
			gPlayerSpawnY = 1 * TILE_HEIGHT;
			break;
		case eGameStates::STATE_GAME_OVER:
			break;
		default:
			break;
		}

	}
	if (coin_collision)
	{
		tileset[coin_index]->setInactive();
		gCoins++;
		gScore = gScore + COIN_SCORE_VALUE;
		Mix_PlayChannel(-1, gCoin_sfx, 0);

		//every N coins, the player gains a life
		if (gCoins == COIN_PER_LIFE)
		{
			gLives++;
			gCoins = 0;
			Mix_PlayChannel(-1, gOneUp_sfx, 0);
		}
	}

	//If no wall tiles were touched
	return false;
}