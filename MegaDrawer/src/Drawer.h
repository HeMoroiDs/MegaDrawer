/*
 * Drawer.h
 *
 *  Created on: 19 déc. 2013
 *      Author: pj
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define BRUSHW 32
#define BRUSHH 32
#define FPS 60
#define NBINTERP 5

class Drawer {
private:
	SDL_Surface *screen, *brush0, *brush, *view;
	SDL_Rect srcRect, destRect;
	SDL_Event event;
	void init();
	void testEvent();
	void displayBrush();
	void pauseVBL();
	int xPos, yPos, prevX, prevY, counter, prevCounter;
	bool flag, lmb, rmb, flag2;
public:
	Drawer();
	virtual ~Drawer();
};

#endif /* DRAWER_H_ */
