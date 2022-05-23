#include "clTitleState.h"

using namespace std;

clTitleState::clTitleState()
{
    mFadeOut = false;
    mTextAlpha = 255;

    //Load title background
    if (!mTitleBackground.createFromFile(gRenderer, "data/title_background.png"))
    {
        cout << "Background image loading failed!" << endl;
    }
    mTitleBackground.setBlendMode(SDL_BLENDMODE_BLEND); //ready to fade out

    string messageAuthor = "by Emanuele Carrino";
    if (!mTextAuthor.createFromText(gRenderer, gFontHUD, messageAuthor.c_str(), textColorWhite))
    {
        cout << "Unable to render Author message texture!" << endl;
    }
    mTextAuthor.setBlendMode(SDL_BLENDMODE_BLEND);

    //options: NEW GAME
    string arrow = "-";
    if (!mNewGameArrow.createFromText(gRenderer, gFontHUD, arrow.c_str(), textColorWhite))
    {
        cout << "Unable to render - texture!" << endl;
    }
    mNewGameArrow.setBlendMode(SDL_BLENDMODE_BLEND);

    string new_game = "New Game";
    if (!mNewGameLabel.createFromText(gRenderer, gFontHUD, new_game.c_str(), textColorWhite))
    {
        cout << "Unable to render NewGame texture!" << endl;
    }
    mNewGameLabel.setBlendMode(SDL_BLENDMODE_BLEND);

    //options: CONTINUE
    if (!mContinueArrow.createFromText(gRenderer, gFontHUD, arrow.c_str(), textColorWhite))
    {
        cout << "Unable to render Continue arrow texture!" << endl;
    }
    mContinueArrow.setBlendMode(SDL_BLENDMODE_BLEND);

    SDL_Color continueColor;
    if (gSaveFileFound)
        continueColor = textColorWhite;
    else
        continueColor = textColorGray;

    string str_continue = "Continue";
    if (!mContinueLabel.createFromText(gRenderer, gFontHUD, str_continue.c_str(), continueColor))
    {
        cout << "Unable to render Continue texture!" << endl;
    }
    mContinueLabel.setBlendMode(SDL_BLENDMODE_BLEND);
        
    /*
    string messageEnter = "Press Enter";
    if (!mTextEnter.createFromText(gRenderer, gFontHUD, messageEnter.c_str(), textColorWhite))
    {
        cout << "Unable to render Enter message texture!" << endl;
    }
    mTextEnter.setBlendMode(SDL_BLENDMODE_BLEND); //ready to fade out
    */

    //Sound Effects
    mMenuBeep_sfx = Mix_LoadWAV("data/menu_beep_sfx.wav");
    if (mMenuBeep_sfx == NULL)
        cout << "Failed to load menu beep SFX! SDL_mixer Error: " << Mix_GetError() << endl;
    else
        Mix_VolumeChunk(mMenuBeep_sfx, 2);

    mMenuError_sfx = Mix_LoadWAV("data/menu_error_sfx.wav");
    if (mMenuError_sfx == NULL)
        cout << "Failed to load menu beep SFX! SDL_mixer Error: " << Mix_GetError() << endl;
    else
        Mix_VolumeChunk(mMenuError_sfx, 2);
}

clTitleState::~clTitleState()
{
    //Free the resources
    mTitleBackground.freeTexture();
    mTextAuthor.freeTexture();
    mTextEnter.freeTexture();

    mNewGameArrow.freeTexture();
    mNewGameLabel.freeTexture();
    mContinueArrow.freeTexture();
    mContinueLabel.freeTexture();

    Mix_FreeChunk(mMenuBeep_sfx);
    Mix_FreeChunk(mMenuError_sfx);
    mMenuBeep_sfx = NULL;
    mMenuError_sfx = NULL;
}

void clTitleState::handle_events()
{
    //Polling for a new event
    while (SDL_PollEvent(&gEvent))
    {
        //User requests to exit
        if (gEvent.type == SDL_QUIT)
        {
            set_next_state(eGameStates::STATE_EXIT);
        }
        //Key press
        else if ((gEvent.type == SDL_KEYDOWN))
        {
            if (gEvent.key.keysym.sym == SDLK_RETURN) // Enter Key
            {
                //Move to the Play screen      //removed to realize fade out
                //set_next_state(gNextStage);  //removed to realize fade out

                if (gSelectedOption == eGameOption::CONTINUE)
                {
                    //import data from save file:
                    switch (gSaveData.stage)
                    {
                    case 1:
                        gNextStage = eGameStates::STATE_STAGE1;
                        break;
                    case 2:
                        gNextStage = eGameStates::STATE_STAGE2;
                        break;
                    case 3:
                        gNextStage = eGameStates::STATE_STAGE3;
                        break;
                    default:
                        gNextStage = eGameStates::STATE_STAGE1;
                        break;
                    }
                    gLives = gSaveData.lives;
                    gCoins = gSaveData.coins;
                    gScore = gSaveData.score;
                }

                if (mFadeOut == false)
                {
                    mFadeOut = true;
                }
            }
            else if ((gEvent.key.keysym.sym == SDLK_UP) || (gEvent.key.keysym.sym == SDLK_DOWN))
            {
                if (gSaveFileFound)
                {
                    if (gSelectedOption == eGameOption::NEW_GAME)
                        gSelectedOption = eGameOption::CONTINUE;
                    else
                        gSelectedOption = eGameOption::NEW_GAME;

                    //Beep Menu
                    Mix_PlayChannel(-1, mMenuBeep_sfx, 0);
                }
                else
                {
                    //play error beep
                    Mix_PlayChannel(-1, mMenuError_sfx, 0);
                }
            }
        }
    }
}

void clTitleState::logic()
{
    //Calculate create texture for FPS
    calc_and_texture_FPS();

    //Fade out
    if (mFadeOut == true)
    {
        mTextAlpha = mTextAlpha - 3;

        //fade out
        //mTitleBackground.setAlphaModulation(mTextAlpha);
        mTextAuthor.setAlphaModulation(mTextAlpha);

        mNewGameArrow.setAlphaModulation(mTextAlpha);
        mNewGameLabel.setAlphaModulation(mTextAlpha);
        mContinueArrow.setAlphaModulation(mTextAlpha);
        mContinueLabel.setAlphaModulation(mTextAlpha);

        //mTextEnter.setAlphaModulation(mTextAlpha);
    }
    if (mTextAlpha == 0)
    {
        //Move to the Play screen
        set_next_state(gNextStage);
    }
}

void clTitleState::render()
{
    //Clear the window
    SDL_SetRenderDrawColor(gRenderer, 20, 20, 20, 255);  //almost black
    SDL_RenderClear(gRenderer);

    //Show the background
    mTitleBackground.render(gRenderer, 0, 0);

    //Average FPS
    gFPSTextTexture.render(gRenderer, 2, 0);

    //Show the Text
    mTextAuthor.render(gRenderer, (WINDOW_WIDTH - mTextAuthor.getWidth()) / 2, 280);

    if (gSelectedOption == eGameOption::NEW_GAME)
        mNewGameArrow.render(gRenderer, (WINDOW_WIDTH - mNewGameLabel.getWidth()) / 2 - 30, 550);
    mNewGameLabel.render(gRenderer, (WINDOW_WIDTH - mNewGameLabel.getWidth()) / 2, 550);

    if (gSelectedOption == eGameOption::CONTINUE)
        mContinueArrow.render(gRenderer, (WINDOW_WIDTH - mNewGameLabel.getWidth()) / 2 - 30, 600);
    mContinueLabel.render(gRenderer, (WINDOW_WIDTH - mNewGameLabel.getWidth()) / 2, 600);
    
    //mTextEnter.render(gRenderer, (WINDOW_WIDTH - mTextEnter.getWidth()) / 2, 600);
}