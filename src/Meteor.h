// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _METEOR_H
#define _METEOR_H

#include "Globals.h"
#include "Player.h"
#include "Bullet.h"

class Meteor
{
	private:
		// meteor
		int meteor_shape;
		COLOR meteor_color;
		POINT position;
		POINT end;
		double slope;
		double offset;
		int width;
		int height;
		int health; // maybe?? size dependent on health // damage calculation based on health

		// bounding box
		RECT bound_box;

		// meteor speed
		int velocity;
		int acceleration;
		int max_speed;

		bool alive;

	public:
		// initialization
		Meteor(void);
		Meteor(POINT, POINT);
		~Meteor(void);

		// redraw
		void draw(void);
		void update(void);

		// on collision
		void explode(void);

		// bounding box
		void update_bound(void);
		RECT getBound(void);

		// collision detection
		void player_collision(Player&);
		void bullet_collision(Player&);

		void setAlive(bool);
		bool isAlive(void);
};

#endif