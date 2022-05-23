#pragma once

//Window resolution (also camera dimensions)
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

//Assets dimension
const int TILE_WIDTH   = 40;
const int TILE_HEIGHT  = 40;
const int PLAYER_WIDTH  = 40;
const int PLAYER_HEIGHT = 65;

//Stages dimensions
//const int STAGES_WIDTH = 2560;  // test stages
const int STAGES_WIDTH = 16000;   // 16000 = 400 tiles long
const int STAGES_HEIGHT = 720;
const int TOTAL_STAGES_TILE = (STAGES_WIDTH / TILE_WIDTH) * (STAGES_HEIGHT / TILE_HEIGHT);

//Player
const int PLAYER_STARTING_X_POS = 40;
const int PLAYER_STARTING_Y_POS = 40;
const int PLAYER_RUN_ANIM_DELAY  = 50;  //(ms)
const int PLAYER_IDLE_ANIM_DELAY = 150; //(ms)
const int PLAYER_GAMEOVER_DELAY  = 250; //(ms)
const int TILES_ANIM_DELAY       = 80;  //(ms)
const int GAME_OVER_ANIM_DELAY   = 100; //(ms)
const int LEVEL_CLEARED_DELAY    = 3000; //(ms)

//Game Settings
const int STARTING_LIVES = 3;
const int PLAYER_SPEED   = 300;
const int JUMP_MOMENTUM  = 1400;
const int MAX_GRAVITY_SPEED = 400;
const int GRAVITY_ACCELERATION = 3150;
const int COIN_PER_LIFE = 20;
const int COIN_SCORE_VALUE = 100;
const int LIFE_LOSS_VALUE = 1000;
const int SAVEFILE_TOTAL_DATA = 4;

const int LAYER1_SCROLL_SPEED = 4; //bigger = SLOWER
const int LAYER2_SCROLL_SPEED = 3; //bigger = SLOWER
const int LAYER3_SCROLL_SPEED = 2; //bigger = SLOWER
const int LAYER4_SCROLL_SPEED = 1; //bigger = SLOWER
const int LAYER1_MOVING_SPEED = 6; //bigger = FASTER

const int BACKGROUND_VOLUME = 5;
const int SFX_VOLUME = 5;

//FPS limit
const int FPS_DECIMAL_DIGIT = 1;

//Tile sprites
const int TILE_NONE  = 0;
const int TILE_EARTH = 1;
const int TILE_GRASS = 2;
const int TILE_BRICK = 3;
const int TILE_BRICK_DARK = 4;
const int TILE_SPIKE = 5;
const int TILE_COIN1 = 6;
const int TILE_COIN2 = 7;
const int TILE_COIN3 = 8;
const int TILE_COIN4 = 9;
const int TILE_COIN5 = 10;
const int TILE_COIN6 = 11;
const int TILE_FLAG_END   = 12;
const int TILE_FLAG_CP    = 13;
const int TILE_FLAGPOLE   = 14;
const int TILE_SPRITE_TOTAL = 15;

//Game states
enum class eGameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_STAGE1,
    STATE_STAGE2,
    STATE_STAGE3,
    STATE_GAME_OVER,
    STATE_EXIT,
};

enum class eGameOption
{
    NEW_GAME,
    CONTINUE,
};