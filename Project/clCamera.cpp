#include "clCamera.h"

clCamera::clCamera()
{
	mCamera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}

clCamera::~clCamera()
{
}

//Gets Camera position
int clCamera::getPosX() const
{
    return mCamera.x;
}

int clCamera::getPosY() const
{
    return mCamera.y;
}

SDL_Rect clCamera::getCamera() const
{
    SDL_Rect camera;
    camera.x = mCamera.x;
    camera.y = mCamera.y;
    camera.w = mCamera.w;
    camera.h = mCamera.h;
    return camera;
}

void clCamera::center(int const posX, int const posY, int const maxWidth, int const maxHeight)
{
    mCamera.x = (posX + PLAYER_WIDTH / 2) - WINDOW_WIDTH / 2;
    mCamera.y = (posY + PLAYER_HEIGHT / 2) - WINDOW_HEIGHT / 2;

    //Keep the camera in bounds
    if (mCamera.x < 0)
    {
        mCamera.x = 0;
    }
    if (mCamera.y < 0)
    {
        mCamera.y = 0;
    }
    if (mCamera.x > maxWidth - mCamera.w)
    {
        mCamera.x = maxWidth - mCamera.w;
    }
    if (mCamera.y > maxHeight - mCamera.h)
    {
        mCamera.y = maxHeight - mCamera.h;
    }
}