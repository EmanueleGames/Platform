#pragma once

#include "clGameState.h"

class clTitleState : public clGameState
{
    public:

        //Load State assets
        clTitleState();
        //Free State assets
        ~clTitleState();

        //Game loop functions
        void handle_events();
        void logic();
        void render();

    private:

        //Title screen resources and variables
        clTexture mTitleBackground;
        clTexture mTextAuthor;
        clTexture mTextEnter;

        //HUD assets
        clTexture mNewGameArrow;
        clTexture mNewGameLabel;
        clTexture mContinueArrow;
        clTexture mContinueLabel;

        // Music and Sounds
        Mix_Chunk* mMenuBeep_sfx;
        Mix_Chunk* mMenuError_sfx;


        bool mFadeOut;
        Uint8 mTextAlpha;
};

