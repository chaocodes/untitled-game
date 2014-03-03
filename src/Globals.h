// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <string>
using std::string;

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define BLUE al_map_rgb(0, 0, 255)
#define GREEN al_map_rgb(0, 255, 0)
#define RED al_map_rgb(255, 0, 0)
#define GRAY al_map_rgb (180, 180, 180)

#define MAX_METEORS 60
#define MAX_BULLETS 40

enum DIRECTIONS
{
	LEFT,
	RIGHT,
	UP,
	DTOTAL
};

enum METEOR_SHAPE
{
	RECTANGLE,
	TRIANGLE,
	CIRCLE
};

enum POWERUPS
{
	HEALTH,
	THREE_PRONG,
	BULLET_SPEED,
	MOVE_SPEED,
	PTOTAL
};

enum STATE
{
	MENU,
	GAME,
	END
};

#endif