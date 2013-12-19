/*
 * Drawer.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: pj
 */

#include "Drawer.h"

Drawer::Drawer() {
	init();

}

Drawer::~Drawer() {
	// TODO Auto-generated destructor stub
}

void Drawer::init() {
	putenv("SDL_VIDEO_CENTERED=1");
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		cerr << "Impossible d'initialiser la SDL !" << endl;
		exit(EXIT_FAILURE);
	}
	//
	atexit(SDL_Quit);
	//
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_HWSURFACE | SDL_NOFRAME);
	if (screen == NULL) {
		cerr << "Impossible d'initialiser la vidéo !" << endl;
		exit(EXIT_FAILURE);
	}
	SDL_Delay(3000);
}

