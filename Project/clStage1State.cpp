#include "clStage1State.h"

using namespace std;

clStage1State::clStage1State()
{

    if (!mLayer0.createFromFile(gRenderer, "data/stage1_background.png"))
    {
        cout << "Layer 0 image loading failed!" << endl;
    }
    if (!mLayer1.createFromFile(gRenderer, "data/stage1_layer1.png"))
    {
        cout << "Layer 1 image loading failed!" << endl;
    }
    if (!mLayer2.createFromFile(gRenderer, "data/stage1_layer2.png"))
    {
        cout << "Layer 2 image loading failed!" << endl;
    }
    if (!mLayer3.createFromFile(gRenderer, "data/stage1_layer3.png"))
    {
        cout << "Layer 3 image loading failed!" << endl;
    }
    if (!mLayer4.createFromFile(gRenderer, "data/stage1_layer4.png"))
    {
        cout << "Layer 4 image loading failed!" << endl;
    }

    //Music and SFX
    mBackgroundMusic = Mix_LoadMUS("data/stage1_music.mp3");
    if (mBackgroundMusic == NULL)
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    else
        Mix_VolumeMusic(BACKGROUND_VOLUME);

    //HUD assets
    string stageLabel = "Stage 1";
    if (!mStageLabel.createFromText(gRenderer, gFontHUD, stageLabel.c_str(), textColorWhite))
    {
        cout << "Unable to render Stage label texture!" << endl;
    }
    if (!mLivesTexture.createFromFile(gRenderer, "data/life_sprite_mini.png"))
    {
        cout << "Mini Mini-player sprite image loading failed!" << endl;
    }
    if (!mCoinsTexture.createFromFile(gRenderer, "data/coin_sprite_mini.png"))
    {
        cout << "Mini Mini-coin sprite image loading failed!" << endl;
    }
    string scoreLabel = "Score:";
    if (!mScoreLabel.createFromText(gRenderer, gFontHUD, scoreLabel.c_str(), textColorWhite))
    {
        cout << "Unable to render Score label texture!" << endl;
    }

    load_tileset_map("data/stage1.map");
    Mix_PlayMusic(mBackgroundMusic, -1); // -1 means repeat

}

clStage1State::~clStage1State()
{

}