#include "clGenericStageState.h"

using namespace std;

clGenericStageState::clGenericStageState()
{
    mLayer1Offset = 0;
    mLayer1Remainder = 0;
    mLayer2Offset = 0;
    mLayer2Remainder = 0;
    mLayer3Offset = 0;
    mLayer3Remainder = 0;
    mLayer4Offset = 0;
    mLayer4Remainder = 0;
    mLayer1AnimOffset = 0;

    gStageCheckpoint = false;
    mTimeStep = gAnimationTimer.getTicks() / 1000.f;
    mLastAnimationTime = 0;

    gPlayerSpawnX = PLAYER_STARTING_X_POS;
    gPlayerSpawnY = PLAYER_STARTING_Y_POS;

    //Sound Effects
    mLevelCleared_sfx = Mix_LoadWAV("data/level_cleared_sfx.wav");
    if (mLevelCleared_sfx == NULL)
        cout << "Failed to load level cleared SFX! SDL_mixer Error: " << Mix_GetError() << endl;
    else
        Mix_VolumeChunk(mLevelCleared_sfx, 5);

    gAnimationTimer.start();
}

clGenericStageState::~clGenericStageState()
{
    mLayer0.freeTexture();
    mLayer1.freeTexture();
    mLayer2.freeTexture();
    mLayer3.freeTexture();
    mLayer4.freeTexture();

    //HUD assets
    mStageLabel.freeTexture();
    mLivesTexture.freeTexture();
    mLivesValue.freeTexture();
    mCoinsTexture.freeTexture();
    mCoinsValue.freeTexture();
    mScoreLabel.freeTexture();
    mScoreValue.freeTexture();

    //Music and SFX
    Mix_FreeMusic(mBackgroundMusic);
    mBackgroundMusic = NULL;
    Mix_FreeChunk(mLevelCleared_sfx);
    mLevelCleared_sfx = NULL;
}

void clGenericStageState::handle_events()
{
    //Polling for a new event
    while (SDL_PollEvent(&gEvent))
    {
        //User requests to exit
        if (gEvent.type == SDL_QUIT)
        {
            set_next_state(eGameStates::STATE_EXIT);
        }

        if (!gLifeLost)
            mPlayer.handleEvent(gEvent);
    }
}

void clGenericStageState::logic()
{
    //Calculate create texture for FPS
    calc_and_texture_FPS();

    if (gLifeLost)
    {
        //Life Lost animation
        if (SDL_GetTicks() - mLastAnimationTime > GAME_OVER_ANIM_DELAY)
        {
            if (mPlayer.animatingGameOver()) //animation in progress
            {
                mLastAnimationTime = SDL_GetTicks();
            }
            else //animation over
            {
                SDL_Delay(100);
                mLayer1AnimOffset = 0;
                mPlayer.reset(gPlayerSpawnX, gPlayerSpawnY);
                gLives--;
                gLifeLost = false;
            }
        }

        //Check Game Over
        if (gLives < 0)
        {
            set_next_state(eGameStates::STATE_GAME_OVER);
            //delete save file? HC mode
        }
    }

    else if (gStageCleared)
    {
        //if there was background music...
        if (Mix_PlayingMusic())
        {   //...stop it and play victory sfx
            Mix_HaltMusic();
            SDL_Delay(100);
            Mix_PlayChannel(-1, mLevelCleared_sfx, 0);
        }
        // wait for victory SFX
        if (SDL_GetTicks() - mLastAnimationTime > LEVEL_CLEARED_DELAY)
        {
            gStageCleared = false;
            gStageCheckpoint = false;

            //find next State
            set_next_state(find_next_state());

            //update or delete the savefile
            update_savefile();
        }
    }

    else
    {
        mTimeStep = gAnimationTimer.getTicks() / 1000.f;

        //Moves the player
        mPlayer.move(mTimeStep, STAGES_WIDTH, STAGES_HEIGHT, mTileset, TOTAL_STAGES_TILE);

        //Center camera on player
        mCamera.center(mPlayer.getPosX(), mPlayer.getPosY(), STAGES_WIDTH, STAGES_HEIGHT);

       //Layer 1
        mLayer1Offset = (mCamera.getPosX() + mLayer1Remainder) / LAYER1_SCROLL_SPEED;// + (mTimeStep * LAYER1_MOVING_SPEED);
        mLayer1Remainder = mCamera.getPosX() % LAYER1_SCROLL_SPEED;
        //Animate Layer 1 indipendently
        mLayer1AnimOffset = mLayer1AnimOffset - (mTimeStep * LAYER1_MOVING_SPEED);
        if (mLayer1AnimOffset < -WINDOW_WIDTH)
            mLayer1AnimOffset = 0;
        while (mLayer1Offset - mLayer1AnimOffset  >= WINDOW_WIDTH)
            mLayer1Offset = mLayer1Offset - WINDOW_WIDTH;

        //Layer 2
        mLayer2Offset = (mCamera.getPosX() + mLayer2Remainder) / LAYER2_SCROLL_SPEED;
        mLayer2Remainder = mCamera.getPosX() % LAYER2_SCROLL_SPEED;
        while (mLayer2Offset >= WINDOW_WIDTH)
            mLayer2Offset = mLayer2Offset - WINDOW_WIDTH;

        //Layer 3
        mLayer3Offset = (mCamera.getPosX() + mLayer3Remainder) / LAYER3_SCROLL_SPEED;
        mLayer3Remainder = mCamera.getPosX() % LAYER3_SCROLL_SPEED;
        while (mLayer3Offset >= WINDOW_WIDTH)
            mLayer3Offset = mLayer3Offset - WINDOW_WIDTH;

        //Layer 4
        mLayer4Offset = (mCamera.getPosX() + mLayer4Remainder) / LAYER4_SCROLL_SPEED;
        mLayer4Remainder = mCamera.getPosX() % LAYER4_SCROLL_SPEED;
        while (mLayer4Offset >= WINDOW_WIDTH)
            mLayer4Offset = mLayer4Offset - WINDOW_WIDTH;

        //Update the animated tiles
        if (SDL_GetTicks() - mLastAnimationTime > TILES_ANIM_DELAY)
        {
            for (int i = 0; i < TOTAL_STAGES_TILE; ++i)
            {
                if (mTileset[i]->isAnimated() && mTileset[i]->isActive())
                {
                    if (mTileset[i]->getType() >= TILE_COIN1 && mTileset[i]->getType() <= TILE_COIN6)
                    {
                        if (mTileset[i]->getType() == TILE_COIN6)
                            mTileset[i]->setType(TILE_COIN1);
                        else
                            mTileset[i]->setType(mTileset[i]->getType() + 1);
                    }
                }
            }
            mLastAnimationTime = SDL_GetTicks();
        }
    }

    //Update HUD Values
    string livesNumber;
    string coinsNumber;
    string scoreNumber;
    livesNumber = std::to_string(gLives);
    coinsNumber = std::to_string(gCoins);
    scoreNumber = std::to_string(gScore);

    if (!mLivesValue.createFromText(gRenderer, gFontHUD, livesNumber.c_str(), textColorWhite))
    {
        cout << "Unable to render Level Number texture!" << endl;
    }
    if (!mCoinsValue.createFromText(gRenderer, gFontHUD, coinsNumber.c_str(), textColorWhite))
    {
        cout << "Unable to render Lines Number texture!" << endl;
    }
    if (!mScoreValue.createFromText(gRenderer, gFontHUD, scoreNumber.c_str(), textColorWhite))
    {
        cout << "Unable to render Points Number texture!" << endl;
    }

    //Restart step timer
    gAnimationTimer.start();
}

void clGenericStageState::render()
{

    //Clear the window
    SDL_SetRenderDrawColor(gRenderer, 240, 240, 240, 255);  //almost white
    SDL_RenderClear(gRenderer);

    //Layer 0 - Background
    mLayer0.render(gRenderer, 0, 0);
    //Layer 1 - Clouds / Stars
    mLayer1.render(gRenderer, -mLayer1Offset + (int)mLayer1AnimOffset, 0);
    mLayer1.render(gRenderer, -mLayer1Offset + WINDOW_WIDTH + (int)mLayer1AnimOffset, 0);
    //Layer 2 - Mountains / Wall
    mLayer2.render(gRenderer, -mLayer2Offset, 0);
    mLayer2.render(gRenderer, -mLayer2Offset + WINDOW_WIDTH, 0);
    //Layer 3 - Mountains / Columns
    mLayer3.render(gRenderer, -mLayer3Offset, 0);
    mLayer3.render(gRenderer, -mLayer3Offset + WINDOW_WIDTH, 0);
    //Layer 4 - Trees (stage 3 has no layer 4)
    if (gActualState != eGameStates::STATE_STAGE3)
    {
        mLayer4.render(gRenderer, -mLayer4Offset, 0);
        mLayer4.render(gRenderer, -mLayer4Offset + WINDOW_WIDTH, 0);
    }

    //Render on screen tiles
    for (int i = 0; i < TOTAL_STAGES_TILE; ++i)
    {
        mTileset[i]->render(mCamera);
    }

    //Show the player
    mPlayer.render(mCamera.getPosX(), mCamera.getPosY());

    // HUD
    //Stage
    mStageLabel.render(gRenderer, 40, 20);
    //Lives
    mLivesTexture.render(gRenderer, 405, 20);
    mLivesValue.render(gRenderer, 435, 20);
    //Coins
    mCoinsTexture.render(gRenderer, 775, 20);
    mCoinsValue.render(gRenderer, 805, 20);
    //Score
    mScoreLabel.render(gRenderer, 1060, 20);
    mScoreValue.render(gRenderer, 1180, 20);

    //Average FPS
    gFPSTextTexture.render(gRenderer, 2, 0);
}

bool clGenericStageState::load_tileset_map(string map_file)
{
    //Success flag
    bool fl_success = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the file with the tileset map
    std::ifstream map(map_file);

    //If the file can't be opened
    if (map.fail())
    {
        cout << "Unable to load tileset file!\n" << endl;
        fl_success = false;
    }
    else
    {
        //Initialize the tiles
        for (int i = 0; i < TOTAL_STAGES_TILE; i++)
        {
            //Determines what kind of tile will be made
            int tileType = -1;

            //Read tile from map file
            map >> tileType;

            //If the was a problem in reading the map
            if (map.fail())
            {
                //Stop loading map
                cout << "Error loading map: Unexpected end of file!\n" << endl;
                fl_success = false;
                break;
            }

            //If the number is a valid tile number
            if ((tileType >= 0) && (tileType < TILE_SPRITE_TOTAL))
            {
                if (tileType == TILE_COIN1)    //animated tiles
                    mTileset[i] = new clTile(x, y, tileType, true);
                else                           //static tiles
                    mTileset[i] = new clTile(x, y, tileType, false);
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                cout << "Error loading map: Invalid tile type at: " << i << endl;
                fl_success = false;
                break;
            }

            //Move to next tile spot
            x += TILE_WIDTH;

            //If we've gone too far
            if (x >= STAGES_WIDTH)
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_HEIGHT;
            }
        }
    }

    //Close the file
    map.close();

    //Success?
    return fl_success;
}

eGameStates clGenericStageState::find_next_state()
{
    switch (gActualState)
    {
    case eGameStates::STATE_TITLE:
        break;
    case eGameStates::STATE_STAGE1:
        return eGameStates::STATE_STAGE2;
        break;
    case eGameStates::STATE_STAGE2:
        return eGameStates::STATE_STAGE3;
        break;
    case eGameStates::STATE_STAGE3:
      return eGameStates::STATE_GAME_OVER;
        break;
    case eGameStates::STATE_GAME_OVER:
        break;
    default:
        break;
    }
}

void clGenericStageState::update_savefile()
{
    if (gActualState == eGameStates::STATE_STAGE3)
    {   //delete savefile
        int deleted;
        deleted = remove(savefile_name.c_str());
        if (deleted == 0)
            cout << "savefile deleted!\n";
        else
            cout << "savefile could not be deleted!\n";

        gSaveFileFound = false;
        gSelectedOption = eGameOption::NEW_GAME;
        gNextStage = eGameStates::STATE_STAGE1;

    } 
    else
        save_game(); //checkpoint
}