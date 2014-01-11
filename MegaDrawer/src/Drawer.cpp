/*
 * Drawer.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: pj
 */

#include "Drawer.h"

Drawer::Drawer() {
	init();
	while(flag) {
		testEvent();
		pauseVBL();
		displayBrush();
	}
}

Drawer::~Drawer() {
	SDL_FreeSurface(brush);
	SDL_FreeSurface(screen);
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
	//
	brush= IMG_Load("/home/pj/workspace_cpp/DrawMaker/brush.png");
	if(brush==NULL) {
		cerr << "Impossible de charger le brush." <<  endl;
		SDL_FreeSurface(screen);
		exit(EXIT_FAILURE);
	}
	view=SDL_CreateRGBSurface(0, BRUSHW, BRUSHH, 32,0,0,0,0);
	//
	//SDL_ShowCursor(SDL_DISABLE);
	prevX=xPos=WIDTH/2-1;
	prevY=yPos=HEIGHT/2-1;
	SDL_WarpMouse(xPos, yPos);
	flag=true;
	//
	counter=SDL_GetTicks();
	prevCounter=counter;
}

void Drawer::pauseVBL() {
	while((counter*prevCounter)<(1000/FPS)) {
		counter=SDL_GetTicks();
	}
	prevCounter=counter;
}

void Drawer::displayBrush() {
	viewPos.x=prevX-BRUSHW/2;
	viewPos.y=prevY-BRUSHH/2;
	viewPos.w=BRUSHW;
	viewPos.h=BRUSHH;
	SDL_BlitSurface(view, NULL, screen, &viewPos);
	//
	viewPos.x=xPos-BRUSHW/2;
	viewPos.y=yPos-BRUSHH/2;
	viewPos.w=BRUSHW;
	viewPos.h=BRUSHH;
	SDL_BlitSurface(screen, NULL, view, &viewPos);
	//
	brushPos.x=xPos-BRUSHW/2;
	brushPos.y=yPos-BRUSHH/2;
	brushPos.w=BRUSHW;
	brushPos.h=BRUSHH;
	SDL_BlitSurface(brush, NULL, screen, &brushPos);
	SDL_Flip(screen);
	//
	prevX=xPos;
	prevY=yPos;
}

void Drawer::testEvent() {
	SDL_PollEvent(&event);
	switch(event.type) {
	case SDL_KEYDOWN:
		switch(event.key.keysym.sym) {
			case SDLK_ESCAPE:
				flag=false;
				break;
			default:
				break;
		}
		break;
	case SDL_MOUSEMOTION:
		xPos=event.motion.x;
		yPos=event.motion.y;
		break;
	}
}

