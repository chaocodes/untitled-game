// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Globals.h"
#include "Bullet.h"

class Player
{
	private:
		// game bound information
		int B_WIDTH;
		int B_HEIGHT;

		// player information
		POINT position;
		int width;
		int height;
		int direction;
		int health;
		int score;

		// bounding box for intersection
		RECT bound_box;

		// vertical movement
		int xspeed;
		int max_xspeed;
		int friction; // not good name

		// horizontal movement
		int yspeed;
		int max_yspeed;
		int gravity;

		// update variables
		bool moving[DTOTAL];
		bool jumping;

		// Weapons
		Bullet bullets[MAX_BULLETS];
		int bullet_speed;
		int ammo_wait;
		int ammo_recharge; // TODO
		bool shooting;
		int bombs;

		// powerups
		bool powerup[PTOTAL];
		int ptime[PTOTAL];

		bool alive;

	public:
		// initialization
		Player(void);
		Player(int, int);
		~Player(void);
		void init(POINT, int);

		// redraw
		void draw(void);
		void update(void);

		// movement
		void left(void);
		void right(void);
		void jump(void);
		bool onSurface(void);

		// bounding box
		void update_bound(void);
		RECT getBound(void);

		// weapon
		void shoot(void);
		void create_bullet(int, int);
		Bullet* getBullets(void);
		bool isShooting(void);

		int getBombs(void);
		void use_bomb(void);

		// powerup effects
		void powerup_three_prong(bool);
		void powerup_bullet_speed(bool);
		void powerup_move_speed(bool);

		// setters -- maybe use for powerups?
		void setBulletSpeed(int);
		void setAmmoRecharge(int);
		void setMoveSpeed(int);

		// health
		int getHealth(void);
		void setHealth(int);

		// score
		int getScore(void);
		void setScore(int);

		// other getters
		POINT getPosition(void);
		string getActivePowerups(void);
};

#endif