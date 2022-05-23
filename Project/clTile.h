#pragma once

#include "constants.h"
#include "globals.h"

class clCamera;

class clTile
{
public:
    //Initialization
    clTile();
    clTile(int x, int y, int tileType, bool animated);

    //Handling functions
    SDL_Rect getBox();  //Get the collision box
    int getType();
    void setType(int newType);

    bool isAnimated();
    bool isActive();
    void setInactive();

    void render(const clCamera& camera);

private:

    //Tile attributes
    SDL_Rect mBox;
    int mType;
    bool mActive;
    bool mAnimated;
};