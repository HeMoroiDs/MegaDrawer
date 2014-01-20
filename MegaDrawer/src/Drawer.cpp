/*
 * Drawer.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: pj
 */

#include "Drawer.h"

Drawer::Drawer() {
	init();
	while (flag) {
		testEvent();
		displayBrush();
		pauseVBL();
	}
}

Drawer::~Drawer() {
	SDL_FreeSurface(brush0);
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
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16,
			SDL_HWSURFACE | SDL_NOFRAME | SDL_DOUBLEBUF);
	if (screen == NULL) {
		cerr << "Impossible d'initialiser la vidéo !" << endl;
		exit(EXIT_FAILURE);
	}
	//
	brush0 = IMG_Load("/home/pj/workspace_cpp/DrawMaker/brush0.png");
	if (brush0 == NULL) {
		cerr << "Impossible de charger le brush0." << endl;
		SDL_FreeSurface(screen);
		exit(EXIT_FAILURE);
	}
	//
	brush = IMG_Load("/home/pj/workspace_cpp/DrawMaker/brush.png");
	if (brush == NULL) {
		cerr << "Impossible de charger le brush." << endl;
		SDL_FreeSurface(screen);
		exit(EXIT_FAILURE);
	}
	view = SDL_CreateRGBSurface(0, BRUSHW, BRUSHH, 32, 0, 0, 0, 0);
	//
	SDL_ShowCursor(SDL_DISABLE);
	prevX = xPos = WIDTH / 2 - 1;
	prevY = yPos = HEIGHT / 2 - 1;
	SDL_WarpMouse(xPos, yPos);
	flag = true;
	//
	counter = SDL_GetTicks();
	prevCounter = counter;
	//
	flag2 = rmb = lmb = false;
	//
	srcRect.w = BRUSHW;
	srcRect.h = BRUSHH;
	destRect.w = BRUSHW;
	destRect.h = BRUSHH;
}

void Drawer::pauseVBL() {
	while ((counter - prevCounter) < (1000 / FPS)) {
		counter = SDL_GetTicks();
	}
	prevCounter = counter;
}

void Drawer::displayBrush() {
	if (!(xPos == prevX && yPos == prevY)) {
		//
		srcRect.x = 0;
		srcRect.y = 0;
		destRect.x = prevX - BRUSHW / 2;
		destRect.y = prevY - BRUSHH / 2;
		SDL_BlitSurface(view, &srcRect, screen, &destRect);
		//
		//
		if (lmb) {
			//
			float x = (float) prevX;
			float y = (float) prevY;
			float stepX = (float) (xPos - prevX) / (float) NBINTERP;
			float stepY = (float) (yPos - prevY) / (float) NBINTERP;
			srcRect.x = 0;
			srcRect.y = 0;
			for (int i = 0; i < NBINTERP; i++) {
				destRect.x = (int) x - BRUSHW / 2;
				destRect.y = (int) y - BRUSHH / 2;
				SDL_BlitSurface(brush, &srcRect, screen, &destRect);
				x += stepX;
				y += stepY;
			}
		}
		srcRect.x = xPos - BRUSHW / 2;
		srcRect.y = yPos - BRUSHH / 2;
		destRect.x = 0;
		destRect.y = 0;
		SDL_BlitSurface(screen, &srcRect, view, &destRect);
		//
		srcRect.x = 0;
		srcRect.y = 0;
		destRect.x = xPos - BRUSHW / 2;
		destRect.y = yPos - BRUSHH / 2;
		//SDL_SetColorKey(brush, SDL_SRCCOLORKEY, SDL_MapRGB(brush->format, 0x00, 0x00, 0x00));
		SDL_BlitSurface(brush0, &srcRect, screen, &destRect);
		//
		SDL_Flip(screen);
		//
		prevX = xPos;
		prevY = yPos;
	}
}

void Drawer::testEvent() {
	while (SDL_PollEvent(&event)) {
		//lmb = false;
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				flag = false;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			xPos = event.motion.x;
			yPos = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			lmb = (event.button.button == SDL_BUTTON_LEFT);
			rmb = (event.button.button == SDL_BUTTON_RIGHT);
			break;
		case SDL_MOUSEBUTTONUP:
			lmb = !(event.button.button == SDL_BUTTON_LEFT);
			rmb = !(event.button.button == SDL_BUTTON_RIGHT);
			break;
		default:
			break;
		}
	}
}

