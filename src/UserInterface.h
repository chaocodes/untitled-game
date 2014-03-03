// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include "Globals.h"
#include "Player.h"

class UserInterface
{
	private:
		// game bound information
		int B_WIDTH;
		int B_HEIGHT;

		ALLEGRO_FONT *score_font;
		ALLEGRO_FONT *powerup_font;

		int p_health;
		int p_score;
		int p_bombs;
		string p_powerups;

	public:
		// initialization
		UserInterface(void);
		UserInterface(int, int);
		~UserInterface(void);
		void init_font(void);

		// redraw
		void draw(void);
		void update(Player&);

		void draw_menu(void);
		void draw_end(void);
	
		void close(void);
};

#endif