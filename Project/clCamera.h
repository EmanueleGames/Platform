#pragma once

#include "constants.h"
#include "globals.h"

class clCamera
{
public:

	//Initialization
	clCamera();
	~clCamera();

	//Handling functions
	int getPosX() const;
	int getPosY() const;
	SDL_Rect getCamera() const;
	void center(int const posX, int const posY, int const maxWidth, int const maxHeight);

private:

	SDL_Rect mCamera;

};

