#pragma once
#include "clGameState.h"
#include "clPlayer.h"
#include "clCamera.h"

class clGenericStageState : public clGameState
{

    public:

        //Load State assets
        clGenericStageState();
        //Free State assets
        virtual ~clGenericStageState();

        //Main loop functions
        virtual void handle_events();
        virtual void logic();
        virtual void render();

    protected:

        //Stage screen resources and variables
        clTexture mLayer0;
        clTexture mLayer1;
        clTexture mLayer2;
        clTexture mLayer3;
        clTexture mLayer4;

        int mLayer1Offset;
        int mLayer1Remainder;
        int mLayer2Offset;
        int mLayer2Remainder;
        int mLayer3Offset;
        int mLayer3Remainder;
        int mLayer4Offset;
        int mLayer4Remainder;
        float mLayer1AnimOffset;

        clPlayer  mPlayer;
        clCamera  mCamera;

        float mTimeStep;
        Uint32 mLastAnimationTime;

        clTile* mTileset[TOTAL_STAGES_TILE];

        //HUD assets
        clTexture mStageLabel;
        clTexture mLivesTexture;
        clTexture mLivesValue;
        clTexture mCoinsTexture;
        clTexture mCoinsValue;
        clTexture mScoreLabel;
        clTexture mScoreValue;

        // Music and Sounds
        Mix_Music* mBackgroundMusic;
        Mix_Chunk* mLevelCleared_sfx;

        //utility functions
        bool load_tileset_map(string map_file);
        eGameStates find_next_state();
        void update_savefile();

};