// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _BULLET_H
#define _BULLET_H

#include "Globals.h"

class Bullet
{
	private:
		// game bound information
		int B_WIDTH;
		int B_HEIGHT;

		// location and trajectory
		POINT position;
		double slope;
		double offset;

		// bullet speed
		int speed;

		// bullet information
		int damage;
		int width;
		int height;

		// bullet bounding box
		RECT bound_box;

		bool alive;

	public:
		Bullet(void);
		Bullet(int, int, int, POINT, POINT);
		~Bullet(void);

		void update(void);
		void draw(void);

		int getDamage(void);
		void explode(void); // for future

		void update_bound(void);
		RECT getBound(void);

		bool isAlive(void);
};

#endif