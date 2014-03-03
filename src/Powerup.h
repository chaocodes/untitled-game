// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _POWERUP_H
#define _POWERUP_H

#include "Globals.h"
#include "Player.h"

class Powerup
{
	private:
		// powerup
		POINT position;
		POINT end;
		ALLEGRO_FONT *font;
		int speed;

		// which powerup?
		int powerup;
		std::string powerup_name;

		// bounding box
		RECT bound_box;
		int bound_width;

		bool alive;

	public:
		Powerup(void);
		Powerup(POINT);
		~Powerup(void);

		void draw(void);
		void update(void);

		// powerup effect
		void give_power(Player&);

		// bounding box
		void update_bound(void);
		RECT getBound(void);

		// collision detection
		void player_collision(Player&);

		void setAlive(bool);
		bool isAlive(void);
};

#endif