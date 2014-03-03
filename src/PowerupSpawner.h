// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _POWERUPSPAWNER_H
#define _POWERUPSPAWNER_H

#include "Globals.h"
#include "Powerup.h"

class PowerupSpawner
{
	private:
		// game bound information
		int B_WIDTH;
		int B_HEIGHT;

		Powerup powerup;

		int ticks;
		int spawnSpeed;

	public:
		// initialization
		PowerupSpawner(void);
		PowerupSpawner(int, int);
		~PowerupSpawner(void);

		// redraw
		void draw(void);
		void update(void);
		void check_collision(Player&);

		// Create powerup
		void spawn(void);
		bool canSpawn(void);

		void restart(void);
};

#endif