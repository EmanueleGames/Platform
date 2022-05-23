#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "constants.h"
#include "clTexture.h"
#include "clTimer.h"
#include "clCamera.h"
#include "clTile.h"
#include "clGameState.h"

using namespace std;

class clGameState;
class clTexture;
class clTimer;
class clCamera;
class clTile;

//Gaming window and window renderer
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Game status variables
extern eGameStates gActualState;
extern eGameStates gNextState;
extern clGameState* ptrCurrentState;

//The event structure
extern SDL_Event gEvent;

//Game setup variables
extern string savefile_name;
extern bool gSaveFileFound;
struct structSaveData {
	int stage;
	int lives;
	int coins;
	int score;
};
extern structSaveData gSaveData;
extern eGameOption gSelectedOption;
extern eGameStates gNextStage;

//Game play variables
extern int gLives;
extern int gCoins;
extern int gScore;
extern bool gLifeLost;
extern bool gStageCleared;
extern bool gStageCheckpoint;
extern int gPlayerSpawnX;
extern int gPlayerSpawnY;
extern TTF_Font* gFontHUD;
extern clTexture gTileSpriteSheet;
extern SDL_Rect  gTileSpriteClips[];
extern clTimer     gAnimationTimer;
extern Mix_Chunk*  gCoin_sfx;
extern Mix_Chunk*  gOneUp_sfx;

//FPS timer and variables
extern clTimer   gCalcFPStimer;
extern clTexture gFPSTextTexture;
extern TTF_Font* gFontFPS;
extern float gAvgFPS;
extern int   gCountedFrames;
extern int   gDecimalDigitValue;
extern stringstream gTextFPS;

//Global Textures and Colors
extern const SDL_Color textColorBlack;
extern const SDL_Color textColorGray;
extern const SDL_Color textColorWhite;

/*************** FUNCTIONS ***************/

bool SDL_initialize();		//Starts up SDL and creates window
void SDL_close();			//Frees media and shuts down SDL
bool load_game_data();		//Loads media
void free_game_data();		//Frees media
bool game_initialize();		//Set the game starting variables
void reset_game();			//restore game initial values

//Save and Load functions
bool load_game();
bool save_game();

//State functions
void set_next_state(eGameStates newState);
void change_state();

//utility functions
float roundDown(float number, const int value);
void calc_and_texture_FPS();

//collisions functions
//Two Rectangles collision detector (separated axis test)
bool rectCollision(SDL_Rect a, SDL_Rect b);
//Checks collision against the tileset hitboxes
bool tilesetCollision(SDL_Rect box, clTile* tileset[], int tileset_number);