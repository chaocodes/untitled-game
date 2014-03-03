// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _METEORSPAWNER_H
#define _METEORSPAWNER_H

#include "Globals.h"
#include "Meteor.h"

class MeteorSpawner
{
	private:
		// game bound information
		int B_WIDTH;
		int B_HEIGHT;

		// meteors
		Meteor meteors[MAX_METEORS];

		int index;
		int ticks;
		int delay;
		int spawnSpeed;
		int difficulty_interval;

	public:
		// initialization
		MeteorSpawner(void);
		MeteorSpawner(int, int); 
		~MeteorSpawner(void);

		// redraw
		void draw(void);
		void update(void);
		void check_collision(Player&);

		// create meteor
		void spawn(Player&);
		bool canSpawn(void);

		void bomb(void);

		void restart(void);
};

#endif