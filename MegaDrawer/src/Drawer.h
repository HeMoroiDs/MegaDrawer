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

using namespace std;

#define WIDTH 800
#define HEIGHT 600

class Drawer {
private:
	SDL_Surface *screen;
	void init();
public:
	Drawer();
	virtual ~Drawer();
};

#endif /* DRAWER_H_ */
