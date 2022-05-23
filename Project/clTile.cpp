#include "clTile.h"

clTile::clTile()
{

    mBox.x = 0;
    mBox.y = 0;

    mBox.w = 0;
    mBox.h = 0;

    mType = 0;
    mActive = false;
    mAnimated = false;
}

clTile::clTile(int x, int y, int tileType, bool animated)
{

    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;
    mActive = true;
    mAnimated = animated;
}

int clTile::getType()
{
    return mType;
}

void clTile::setType(int newType)
{
    mType = newType;
}

bool clTile::isAnimated()
{
    return mAnimated;
}

bool clTile::isActive()
{
    return mActive;
}

void clTile::setInactive()
{
    mActive = false;
}

SDL_Rect clTile::getBox()
{
    return mBox;
}

void clTile::render(const clCamera& camera)
{

    //If the tile is on screen and active
    if (rectCollision(camera.getCamera(), mBox) && mActive)
    {
        //Show the tile
        gTileSpriteSheet.render(gRenderer, mBox.x - camera.getPosX(), mBox.y - camera.getPosY(), &gTileSpriteClips[mType]);
    }

}