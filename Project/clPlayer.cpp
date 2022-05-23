#include "clPlayer.h"

//Constructor
clPlayer::clPlayer()
{

    //Initialize position
    mPosX = PLAYER_STARTING_X_POS;
    mPosY = PLAYER_STARTING_Y_POS;
    //Initialize velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize hitbox and status
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = PLAYER_WIDTH;
    mBox.h = PLAYER_HEIGHT;
    mCurrentState = ePlayerAnimationState::RIGHT_FALL;

    //Load player spritesheet texture
    if (!mPlayerSpritesheet.createFromFile(gRenderer, "data/player_spritesheet_new.png"))
    {
        cout << "Player Spritesheet image loading failed!" << endl;
    }
    else
    {
        //Transparency for life lost animation
        mLastSpriteRendered = 0;
        mLastSpriteTimer = SDL_GetTicks();
        mAlphaValue = 255;
        mPlayerSpritesheet.setBlendMode(SDL_BLENDMODE_BLEND);

        //Set sprite clips
        //movement sprites
        mPlayerSpriteClips[RIGHT_1].x = 0;
        mPlayerSpriteClips[RIGHT_1].y = 0;
        mPlayerSpriteClips[RIGHT_1].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_2].x = 40;
        mPlayerSpriteClips[RIGHT_2].y = 0;
        mPlayerSpriteClips[RIGHT_2].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_3].x = 80;
        mPlayerSpriteClips[RIGHT_3].y = 0;
        mPlayerSpriteClips[RIGHT_3].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_4].x = 120;
        mPlayerSpriteClips[RIGHT_4].y = 0;
        mPlayerSpriteClips[RIGHT_4].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_5].x = 160;
        mPlayerSpriteClips[RIGHT_5].y = 0;
        mPlayerSpriteClips[RIGHT_5].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_6].x = 200;
        mPlayerSpriteClips[RIGHT_6].y = 0;
        mPlayerSpriteClips[RIGHT_6].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_7].x = 240;
        mPlayerSpriteClips[RIGHT_7].y = 0;
        mPlayerSpriteClips[RIGHT_7].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_8].x = 280;
        mPlayerSpriteClips[RIGHT_8].y = 0;
        mPlayerSpriteClips[RIGHT_8].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_JUMP].x = 320;
        mPlayerSpriteClips[RIGHT_JUMP].y = 0;
        mPlayerSpriteClips[RIGHT_JUMP].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_JUMP].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_FALL].x = 360;
        mPlayerSpriteClips[RIGHT_FALL].y = 0;
        mPlayerSpriteClips[RIGHT_FALL].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_FALL].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_1].x = 0;
        mPlayerSpriteClips[LEFT_1].y = 65;
        mPlayerSpriteClips[LEFT_1].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_2].x = 40;
        mPlayerSpriteClips[LEFT_2].y = 65;
        mPlayerSpriteClips[LEFT_2].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_3].x = 80;
        mPlayerSpriteClips[LEFT_3].y = 65;
        mPlayerSpriteClips[LEFT_3].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_4].x = 120;
        mPlayerSpriteClips[LEFT_4].y = 65;
        mPlayerSpriteClips[LEFT_4].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_5].x = 160;
        mPlayerSpriteClips[LEFT_5].y = 65;
        mPlayerSpriteClips[LEFT_5].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_6].x = 200;
        mPlayerSpriteClips[LEFT_6].y = 65;
        mPlayerSpriteClips[LEFT_6].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_7].x = 240;
        mPlayerSpriteClips[LEFT_7].y = 65;
        mPlayerSpriteClips[LEFT_7].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_8].x = 280;
        mPlayerSpriteClips[LEFT_8].y = 65;
        mPlayerSpriteClips[LEFT_8].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_JUMP].x = 320;
        mPlayerSpriteClips[LEFT_JUMP].y = 65;
        mPlayerSpriteClips[LEFT_JUMP].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_JUMP].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_FALL].x = 360;
        mPlayerSpriteClips[LEFT_FALL].y = 65;
        mPlayerSpriteClips[LEFT_FALL].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_FALL].h = PLAYER_HEIGHT;

        // idle sprites
        mPlayerSpriteClips[RIGHT_IDLE_1].x = 0;
        mPlayerSpriteClips[RIGHT_IDLE_1].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_1].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_2].x = 40;
        mPlayerSpriteClips[RIGHT_IDLE_2].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_2].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_3].x = 80;
        mPlayerSpriteClips[RIGHT_IDLE_3].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_3].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_4].x = 120;
        mPlayerSpriteClips[RIGHT_IDLE_4].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_4].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_5].x = 160;
        mPlayerSpriteClips[RIGHT_IDLE_5].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_5].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_6].x = 200;
        mPlayerSpriteClips[RIGHT_IDLE_6].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_6].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_7].x = 240;
        mPlayerSpriteClips[RIGHT_IDLE_7].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_7].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_8].x = 280;
        mPlayerSpriteClips[RIGHT_IDLE_8].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_8].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_9].x = 320;
        mPlayerSpriteClips[RIGHT_IDLE_9].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_9].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_9].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_IDLE_10].x = 360;
        mPlayerSpriteClips[RIGHT_IDLE_10].y = 130;
        mPlayerSpriteClips[RIGHT_IDLE_10].w = PLAYER_WIDTH;
        mPlayerSpriteClips[RIGHT_IDLE_10].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_1].x = 0;
        mPlayerSpriteClips[LEFT_IDLE_1].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_1].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_2].x = 40;
        mPlayerSpriteClips[LEFT_IDLE_2].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_2].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_3].x = 80;
        mPlayerSpriteClips[LEFT_IDLE_3].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_3].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_4].x = 120;
        mPlayerSpriteClips[LEFT_IDLE_4].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_4].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_5].x = 160;
        mPlayerSpriteClips[LEFT_IDLE_5].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_5].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_6].x = 200;
        mPlayerSpriteClips[LEFT_IDLE_6].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_6].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_7].x = 240;
        mPlayerSpriteClips[LEFT_IDLE_7].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_7].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_8].x = 280;
        mPlayerSpriteClips[LEFT_IDLE_8].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_8].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_9].x = 320;
        mPlayerSpriteClips[LEFT_IDLE_9].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_9].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_9].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_IDLE_10].x = 360;
        mPlayerSpriteClips[LEFT_IDLE_10].y = 195;
        mPlayerSpriteClips[LEFT_IDLE_10].w = PLAYER_WIDTH;
        mPlayerSpriteClips[LEFT_IDLE_10].h = PLAYER_HEIGHT;

        // dead sprites
        mPlayerSpriteClips[RIGHT_DEAD_1].x = 0;
        mPlayerSpriteClips[RIGHT_DEAD_1].y = 260;
        mPlayerSpriteClips[RIGHT_DEAD_1].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_2].x = 80;
        mPlayerSpriteClips[RIGHT_DEAD_2].y = 260;
        mPlayerSpriteClips[RIGHT_DEAD_2].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_3].x = 160;
        mPlayerSpriteClips[RIGHT_DEAD_3].y = 260;
        mPlayerSpriteClips[RIGHT_DEAD_3].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_4].x = 240;
        mPlayerSpriteClips[RIGHT_DEAD_4].y = 260;
        mPlayerSpriteClips[RIGHT_DEAD_4].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_5].x = 320;
        mPlayerSpriteClips[RIGHT_DEAD_5].y = 260;
        mPlayerSpriteClips[RIGHT_DEAD_5].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_6].x = 0;
        mPlayerSpriteClips[RIGHT_DEAD_6].y = 325;
        mPlayerSpriteClips[RIGHT_DEAD_6].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_7].x = 80;
        mPlayerSpriteClips[RIGHT_DEAD_7].y = 325;
        mPlayerSpriteClips[RIGHT_DEAD_7].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_8].x = 160;
        mPlayerSpriteClips[RIGHT_DEAD_8].y = 325;
        mPlayerSpriteClips[RIGHT_DEAD_8].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_9].x = 240;
        mPlayerSpriteClips[RIGHT_DEAD_9].y = 325;
        mPlayerSpriteClips[RIGHT_DEAD_9].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_9].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[RIGHT_DEAD_10].x = 320;
        mPlayerSpriteClips[RIGHT_DEAD_10].y = 325;
        mPlayerSpriteClips[RIGHT_DEAD_10].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[RIGHT_DEAD_10].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_1].x = 0;
        mPlayerSpriteClips[LEFT_DEAD_1].y = 390;
        mPlayerSpriteClips[LEFT_DEAD_1].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_1].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_2].x = 80;
        mPlayerSpriteClips[LEFT_DEAD_2].y = 390;
        mPlayerSpriteClips[LEFT_DEAD_2].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_2].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_3].x = 160;
        mPlayerSpriteClips[LEFT_DEAD_3].y = 390;
        mPlayerSpriteClips[LEFT_DEAD_3].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_3].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_4].x = 240;
        mPlayerSpriteClips[LEFT_DEAD_4].y = 390;
        mPlayerSpriteClips[LEFT_DEAD_4].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_4].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_5].x = 320;
        mPlayerSpriteClips[LEFT_DEAD_5].y = 390;
        mPlayerSpriteClips[LEFT_DEAD_5].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_5].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_6].x = 0;
        mPlayerSpriteClips[LEFT_DEAD_6].y = 455;
        mPlayerSpriteClips[LEFT_DEAD_6].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_6].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_7].x = 80;
        mPlayerSpriteClips[LEFT_DEAD_7].y = 455;
        mPlayerSpriteClips[LEFT_DEAD_7].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_7].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_8].x = 160;
        mPlayerSpriteClips[LEFT_DEAD_8].y = 455;
        mPlayerSpriteClips[LEFT_DEAD_8].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_8].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_9].x = 240;
        mPlayerSpriteClips[LEFT_DEAD_9].y = 455;
        mPlayerSpriteClips[LEFT_DEAD_9].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_9].h = PLAYER_HEIGHT;

        mPlayerSpriteClips[LEFT_DEAD_10].x = 320;
        mPlayerSpriteClips[LEFT_DEAD_10].y = 455;
        mPlayerSpriteClips[LEFT_DEAD_10].w = PLAYER_WIDTH * 2;
        mPlayerSpriteClips[LEFT_DEAD_10].h = PLAYER_HEIGHT;
    }

    //Sound Effects
    mJump_sfx = Mix_LoadWAV("data/jump_sfx.wav");
    if (mJump_sfx == NULL)
        cout << "Failed to load jump SFX! SDL_mixer Error: " << Mix_GetError() << endl;
    else
        Mix_VolumeChunk(mJump_sfx, SFX_VOLUME);

    mLife_lost_sfx = Mix_LoadWAV("data/life_lost_sfx.wav");
    if (mLife_lost_sfx == NULL)
        cout << "Failed to load life_lost SFX! SDL_mixer Error: " << Mix_GetError() << endl;
    else
        Mix_VolumeChunk(mLife_lost_sfx, SFX_VOLUME);

}

//Destructor
clPlayer::~clPlayer()
{
    mPlayerSpritesheet.freeTexture();
    Mix_FreeChunk(mJump_sfx);
    Mix_FreeChunk(mLife_lost_sfx);
    mJump_sfx       = NULL;
    mLife_lost_sfx  = NULL;
}

//Gets Player position
int clPlayer::getPosX()
{
	return mBox.x;
}

int clPlayer::getPosY()
{
	return mBox.y;
}

//Handling functions
void clPlayer::handleEvent(SDL_Event& event)
{
    //If a key was pressed
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        //Adjust the velocity
        switch (event.key.keysym.sym)
        {
        case SDLK_UP: 
            if (mCurrentState != ePlayerAnimationState::RIGHT_JUMP &&
                mCurrentState != ePlayerAnimationState::LEFT_JUMP  &&
                mCurrentState != ePlayerAnimationState::RIGHT_FALL &&
                mCurrentState != ePlayerAnimationState::LEFT_FALL)
            {
                mVelY -= JUMP_MOMENTUM;
                Mix_PlayChannel(-1, mJump_sfx, 0);
                if (mCurrentState == ePlayerAnimationState::RIGHT || mCurrentState == ePlayerAnimationState::RIGHT_IDLE)
                    mCurrentState = ePlayerAnimationState::RIGHT_JUMP;
                if (mCurrentState == ePlayerAnimationState::LEFT ||  mCurrentState == ePlayerAnimationState::LEFT_IDLE)
                    mCurrentState = ePlayerAnimationState::LEFT_JUMP;
            }break;
        //case SDLK_DOWN: mVelY += PLAYER_SPEED; break;
        case SDLK_LEFT: mVelX -= PLAYER_SPEED; break;
        case SDLK_RIGHT: mVelX += PLAYER_SPEED; break;
        }
    }
    //If a key was released
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        //Adjust the velocity
        switch (event.key.keysym.sym)
        {
        //case SDLK_UP: mVelY += PLAYER_SPEED; break;
        //case SDLK_DOWN: mVelY -= PLAYER_SPEED; break;
        case SDLK_LEFT:  mVelX += PLAYER_SPEED; break;
        case SDLK_RIGHT: mVelX -= PLAYER_SPEED; break;
        }
    }

    // Fix the case when the user keep the LEFT or RIGHT key pressed before the stage loads
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
    {
        mVelX = 0;
    }
}

void clPlayer::move(float timestep, int const maxWidth, int const maxHeight, clTile* tiles[], int total_tiles)
{

    int clipToRender = -1;
    bool h_collision = false;
    bool v_collision = false;

    //Move the player left or right
    mPosX += mVelX * timestep;
    mBox.x = mPosX;

    //If the player went too far to the left or right
    while ((mPosX < 0) || (mPosX + PLAYER_WIDTH > maxWidth) || tilesetCollision(mBox, tiles, total_tiles))
    {
        //Move back
        mPosX = mPosX - (abs(mVelX) / mVelX);
        mBox.x = mPosX;
        h_collision = true;
    }

    //Gravity
    if (mVelY < MAX_GRAVITY_SPEED)
    {
        mVelY = mVelY + GRAVITY_ACCELERATION * timestep;
    }

    //Apply jump and gravity
    mPosY += mVelY * timestep;
    mBox.y = mPosY;
    
    //If the player went too far up or down
    while ((mPosY < 0) || (mPosY + PLAYER_HEIGHT > maxHeight) || tilesetCollision(mBox, tiles, total_tiles))
    {
        //Move back
        mPosY = mPosY - (abs(mVelY) / mVelY);
        mBox.y = mPosY;
        v_collision = true;
    }

    // Update player status
    if (v_collision)
    {
        if (mVelY > 0) //player landed or already on ground
        {
            if (mCurrentState == ePlayerAnimationState::RIGHT_JUMP ||
                mCurrentState == ePlayerAnimationState::RIGHT_FALL ||
                mCurrentState == ePlayerAnimationState::RIGHT)
            {
                mCurrentState = ePlayerAnimationState::RIGHT;
            }
            if (mCurrentState == ePlayerAnimationState::LEFT_JUMP ||
                mCurrentState == ePlayerAnimationState::LEFT_FALL ||
                mCurrentState == ePlayerAnimationState::LEFT)
            {
                mCurrentState = ePlayerAnimationState::LEFT;
            }
        }

        if (mVelY < 0)  // head hit
        {
            mVelY = 0;  // immediately resume falling
            if (mCurrentState == ePlayerAnimationState::RIGHT_JUMP ||
                mCurrentState == ePlayerAnimationState::RIGHT)
                mCurrentState = ePlayerAnimationState::RIGHT_FALL;
            if (mCurrentState == ePlayerAnimationState::LEFT_JUMP ||
                mCurrentState == ePlayerAnimationState::LEFT)
                mCurrentState = ePlayerAnimationState::LEFT_FALL;
        }


        if (mCurrentState != ePlayerAnimationState::RIGHT_JUMP &&
            mCurrentState != ePlayerAnimationState::RIGHT_FALL &&
            mCurrentState != ePlayerAnimationState::LEFT_JUMP  &&
            mCurrentState != ePlayerAnimationState::LEFT_FALL)
        {
            if (mVelX > 0)
                mCurrentState = ePlayerAnimationState::RIGHT;
            if (mVelX < 0)
                mCurrentState = ePlayerAnimationState::LEFT;
            if (mVelX == 0)
            {
                if (mCurrentState == ePlayerAnimationState::LEFT)
                    mCurrentState = ePlayerAnimationState::LEFT_IDLE;
                if (mCurrentState == ePlayerAnimationState::RIGHT)
                    mCurrentState = ePlayerAnimationState::RIGHT_IDLE;
            }
        }
    }
    else // jumping or free falling
    {
        // jumping
        if (mVelY < 0)
        {
            if (mVelX > 0)
                mCurrentState = ePlayerAnimationState::RIGHT_JUMP;
            if (mVelX < 0)
                mCurrentState = ePlayerAnimationState::LEFT_JUMP;
        }
        // falling
        if (mVelY > 0)
        {
            if (mVelX > 0)
                mCurrentState = ePlayerAnimationState::RIGHT_FALL;
            if (mVelX < 0)
                mCurrentState = ePlayerAnimationState::LEFT_FALL;
            if (mVelX == 0)
            {
                if (mCurrentState == ePlayerAnimationState::RIGHT_JUMP ||
                    mCurrentState == ePlayerAnimationState::RIGHT)
                    mCurrentState = ePlayerAnimationState::RIGHT_FALL;
                if (mCurrentState == ePlayerAnimationState::LEFT_JUMP ||
                    mCurrentState == ePlayerAnimationState::LEFT)
                    mCurrentState = ePlayerAnimationState::LEFT_FALL;
            }
        }
    }
}

void clPlayer::render(int const cameraX, int const cameraY)
{
    // Find the next clip to use for the player 
    int next_sprite = findNextSprite();
    int h_offset = 0, v_offset = 0;
    if (mCurrentState == ePlayerAnimationState::RIGHT_DEAD)
    {
        h_offset = dead_sprite_h_offset;
        v_offset = dead_sprite_v_offset;
    }
    if (mCurrentState == ePlayerAnimationState::LEFT_DEAD)
    {
        //h_offset = 0;
        v_offset = dead_sprite_v_offset;
    }
    mPlayerSpritesheet.render(gRenderer, mBox.x - cameraX - h_offset, mBox.y - cameraY - v_offset, &mPlayerSpriteClips[next_sprite]);
    mLastSpriteRendered = next_sprite;
}

int clPlayer::findNextSprite()
{
    int spriteToRender = mLastSpriteRendered;

    
    switch (mCurrentState)
    {
    case ePlayerAnimationState::RIGHT_IDLE:
        // If the player was NOT in IDLE_RIGHT state
        if (mLastSpriteRendered < RIGHT_IDLE_1 ||
            mLastSpriteRendered > RIGHT_IDLE_10)
            // we use the first sprite for right idle
            spriteToRender = RIGHT_IDLE_1;

        // If the player was already in IDLE_RIGHT state and sufficient time has passed since last sprite
        if (mLastSpriteRendered >= RIGHT_IDLE_1 &&
            mLastSpriteRendered <= RIGHT_IDLE_10 &&
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_IDLE_ANIM_DELAY))
        {
            // then use the next right sprite
            mLastSpriteTimer = SDL_GetTicks();
            if (mLastSpriteRendered == RIGHT_IDLE_10)
                spriteToRender = RIGHT_IDLE_1;
            else
                spriteToRender = mLastSpriteRendered + 1;
        }
        break;

    case ePlayerAnimationState::RIGHT:
        // If the player was NOT going right
        if (mLastSpriteRendered < RIGHT_1 ||
            mLastSpriteRendered > RIGHT_8 )
            // we use the first sprite for right direction
            spriteToRender = RIGHT_1;

        // If the player was already going right and sufficient time has passed since last sprite
        if (mLastSpriteRendered >= RIGHT_1 &&
            mLastSpriteRendered <= RIGHT_8 &&
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_RUN_ANIM_DELAY))
        {
            // then use the next right sprite
            mLastSpriteTimer = SDL_GetTicks();
            if (mLastSpriteRendered == RIGHT_8)
                spriteToRender = RIGHT_1;
            else
                spriteToRender = mLastSpriteRendered + 1;
        }
        break;

    case ePlayerAnimationState::RIGHT_JUMP:
        spriteToRender = RIGHT_JUMP;
        break;

    case ePlayerAnimationState::RIGHT_FALL:
        spriteToRender = RIGHT_FALL;
        break;

    case ePlayerAnimationState::RIGHT_DEAD:
        // If the player JUST died
        if (mLastSpriteRendered < RIGHT_DEAD_1 ||
            mLastSpriteRendered > RIGHT_DEAD_10)
            // we use the first sprite for right direction
            spriteToRender = RIGHT_DEAD_1;

        // Death animation already started
        if (mLastSpriteRendered >= RIGHT_DEAD_1 &&
            mLastSpriteRendered <= RIGHT_DEAD_9 && // 10 not included, we stop animating at 10
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_GAMEOVER_DELAY))
        {
            // then use the next KO sprite
            mLastSpriteTimer = SDL_GetTicks();
            spriteToRender = mLastSpriteRendered + 1;
        }
        break;

    case ePlayerAnimationState::LEFT_IDLE:
        // If the player was NOT in IDLE_LEFT state
        if (mLastSpriteRendered < LEFT_IDLE_1 ||
            mLastSpriteRendered > LEFT_IDLE_10)
            // we use the first sprite for left idle
            spriteToRender = LEFT_IDLE_1;

        // If the player was already in IDLE_LEFT state and sufficient time has passed since last sprite
        if (mLastSpriteRendered >= LEFT_IDLE_1 &&
            mLastSpriteRendered <= LEFT_IDLE_10 &&
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_IDLE_ANIM_DELAY))
        {
            // then use the next left sprite
            mLastSpriteTimer = SDL_GetTicks();
            if (mLastSpriteRendered == LEFT_IDLE_10)
                spriteToRender = LEFT_IDLE_1;
            else
                spriteToRender = mLastSpriteRendered + 1;
        }
        break;

    case ePlayerAnimationState::LEFT:
        // If the player was NOT going left
        if (mLastSpriteRendered < LEFT_1 ||
            mLastSpriteRendered > LEFT_8)
            // we use the first sprite for right direction
            spriteToRender = LEFT_1;

        // If the player was already going right and sufficient time has passed since last sprite
        if (mLastSpriteRendered >= LEFT_1 &&
            mLastSpriteRendered <= LEFT_8 &&
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_RUN_ANIM_DELAY))
        {
            // then use the next left sprite
            mLastSpriteTimer = SDL_GetTicks();
            if (mLastSpriteRendered == LEFT_8)
                spriteToRender = LEFT_1;
            else
                spriteToRender = mLastSpriteRendered + 1;
        }
        break;
    case ePlayerAnimationState::LEFT_JUMP:
        spriteToRender = LEFT_JUMP;
        break;
    case ePlayerAnimationState::LEFT_FALL:
        spriteToRender = LEFT_FALL;
        break;
    case ePlayerAnimationState::LEFT_DEAD:
        // If the player JUST died
        if (mLastSpriteRendered < LEFT_DEAD_1 ||
            mLastSpriteRendered > LEFT_DEAD_10)
            // we use the first sprite for right direction
            spriteToRender = LEFT_DEAD_1;

        // Death animation already started
        if (mLastSpriteRendered >= LEFT_DEAD_1 &&
            mLastSpriteRendered <= LEFT_DEAD_9 && // 10 not included, we stop animating at 10
            (SDL_GetTicks() - mLastSpriteTimer > PLAYER_GAMEOVER_DELAY))
        {
            // then use the next KO sprite
            mLastSpriteTimer = SDL_GetTicks();
            spriteToRender = mLastSpriteRendered + 1;
        }
        break;

    default:
        break;

    }

    //stop animation if stage is cleared and we are waiting for the new one
    if (gStageCleared)
        spriteToRender = mLastSpriteRendered;

    //update last sprite used
    mLastSpriteRendered = spriteToRender;

    return spriteToRender;
}

bool clPlayer::animatingGameOver()
{
    if (mCurrentState == ePlayerAnimationState::RIGHT_IDLE  ||
        mCurrentState == ePlayerAnimationState::RIGHT       ||
        mCurrentState == ePlayerAnimationState::RIGHT_JUMP  ||
        mCurrentState == ePlayerAnimationState::RIGHT_FALL )
    {
        mCurrentState = ePlayerAnimationState::RIGHT_DEAD;
        Mix_PlayChannel(-1, mLife_lost_sfx, 0);
    }
    if (mCurrentState == ePlayerAnimationState::LEFT_IDLE ||
        mCurrentState == ePlayerAnimationState::LEFT      ||
        mCurrentState == ePlayerAnimationState::LEFT_JUMP ||
        mCurrentState == ePlayerAnimationState::LEFT_FALL )
    {
        mCurrentState = ePlayerAnimationState::LEFT_DEAD;
        Mix_PlayChannel(-1, mLife_lost_sfx, 0);
    }

    mAlphaValue = mAlphaValue - 15;
    mPlayerSpritesheet.setAlphaModulation(mAlphaValue);

    if (mAlphaValue == 0)
        return false;

    return true;
}

void clPlayer::reset(const int posX, const int posY)
{
    //reset position and velocity
    mPosX = posX;
    mPosY = posY;
    mVelX = 0;
    mVelY = 0;

    //reset hitbox
    mBox.x = posX;
    mBox.y = posY;
    mBox.w = PLAYER_WIDTH;
    mBox.h = PLAYER_HEIGHT;

    mCurrentState = ePlayerAnimationState::RIGHT_FALL;

    //reset alpha
    mAlphaValue = 255;
    mPlayerSpritesheet.setAlphaModulation(mAlphaValue);
    mLastSpriteTimer = SDL_GetTicks();
}