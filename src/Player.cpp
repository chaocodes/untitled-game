// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "player.h"

Player::Player() {}

Player::Player(int w, int h)
{
	B_WIDTH = w;
	B_HEIGHT = h;
}

Player::~Player() {}

void Player::init(POINT pos, int dir)
{
	// player information
	position = pos;
	width = 30;
	height = 80;
	direction = dir;
	health = 100;
	score = 0;

	// bounding box
	update_bound();

	// vertical movement
	xspeed = 0;
	max_xspeed = 7;
	friction = 1;

	// horizontal movement
	yspeed = 0;
	max_yspeed = 25;
	gravity = 3; // change to float
	
	// update variables
	for (int i = 0; i < DTOTAL; i++)
	{
		moving[i] = false;
	}
	jumping = false;

	// weapon information
	bullet_speed = 7;
	ammo_wait = 0;
	ammo_recharge = 10;
	shooting = false;
	bombs = 3;

	for (int i = 0; i < PTOTAL; i++)
	{
		powerup[i] = false;
		ptime[i] = 0;
	}

	alive = true;
}

void Player::draw(void)
{
	if (alive)
	{
		// body
		al_draw_filled_rectangle(bound_box.left, bound_box.top, bound_box.right, bound_box.bottom, BLACK);

		if (direction == LEFT)
		{
			al_draw_filled_rectangle(bound_box.left, bound_box.top + 5, bound_box.left + 5, bound_box.top + 10, WHITE); // eye 5x5 square
		}
		else if (direction == RIGHT)
		{
			al_draw_filled_rectangle(bound_box.right, bound_box.top + 5, bound_box.right - 5, bound_box.top + 10, WHITE); // eye 5x5 square
		}

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i].isAlive())
			{
				bullets[i].draw();
			}
		}
	}
}

void Player::update(void)
{
	if (alive)
	{
		xspeed = xspeed + friction;
		if (xspeed >= max_xspeed)
		{
			xspeed = max_xspeed;
		}

		if (moving[LEFT])
		{
			direction = LEFT;
			position.x = position.x - xspeed;

			if (position.x < 0) // check bounds
			{
				position.x = 0;
			}
		}

		if (moving[RIGHT])
		{
			direction = RIGHT;
			position.x = position.x + xspeed;

			if (position.x > B_WIDTH) // check bounds
			{
				position.x = B_WIDTH;
			}
		}

		if (jumping)
		{
			position.y = position.y - yspeed; // lower y value = up
			yspeed = yspeed - gravity;

			if (onSurface())
			{
				jumping = false;
				position.y = B_HEIGHT - 50;
			}
		}

		update_bound(); // update bounding box

		// update bullets
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bullets[i].isAlive())
			{
				bullets[i].update();
			}
		}

		// update powerups
		for (int i = 0; i < PTOTAL; i++)
		{
			if (powerup[i] == true)
			{
				if (ptime[i] > 0)
				{
					ptime[i]--;
				}
				else
				{
					if (i == THREE_PRONG)
					{
						powerup_three_prong(false);
					}
					else if (i == BULLET_SPEED)
					{
						powerup_bullet_speed(false);
					}
					else if (i == MOVE_SPEED)
					{
						powerup_move_speed(false);
					}
				}
			}
		}
	}
}

void Player::left(void)
{
	xspeed = 0;
	moving[LEFT] = !moving[LEFT];
}

void Player::right(void)
{
	xspeed = 0;
	moving[RIGHT] = !moving[RIGHT];
}

void Player::jump(void)
{
	if (!jumping)
	{
		jumping = true;
		yspeed = max_yspeed;
	}
}

bool Player::onSurface(void)
{
	return position.y >= B_HEIGHT - 50; // TODO -- surface collision logic
}

void Player::update_bound(void)
{
	bound_box.left = position.x - width / 2;
	bound_box.right = position.x + width / 2;
	bound_box.top = position.y - height / 2;
	bound_box.bottom = position.y + height / 2;
}

RECT Player::getBound(void)
{
	return bound_box;
}

void Player::shoot(void)
{
	shooting = !shooting;
	ammo_wait = 10; // shoot first bullet instantly
}

void Player::create_bullet(int x, int y)
{
	if (shooting)
	{
		if (ammo_wait >= ammo_recharge)
		{
			ammo_wait = 0;

			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (!bullets[i].isAlive())
				{
					POINT end = { x, y };
					bullets[i] = Bullet(B_WIDTH, B_HEIGHT, bullet_speed, position, end);

					if (powerup[THREE_PRONG]) // three prong powerup logic -- extract later
					{
						POINT left = { x - 50, y };
						POINT right = { x + 50, y };
						bullets[i + 1 % MAX_BULLETS] = Bullet(B_WIDTH, B_HEIGHT, bullet_speed, position, left);
						bullets[i + 2 % MAX_BULLETS] = Bullet(B_WIDTH, B_HEIGHT, bullet_speed, position, right);
					}

					break;
				}
			}
		}

		ammo_wait++;
	}
}

Bullet* Player::getBullets(void)
{
	return bullets;
}

bool Player::isShooting(void)
{
	return shooting;
}

int Player::getBombs(void)
{
	return bombs;
}

void Player::use_bomb(void)
{
	bombs--;
}

void Player::powerup_three_prong(bool active)
{
	if (active && powerup[THREE_PRONG]) // refresh powerup
	{
		ptime[THREE_PRONG] = 1000;
		return;
	}

	if (active)
	{
		powerup[THREE_PRONG] = true;
		ptime[THREE_PRONG] = 1000;
	}
	else
	{
		powerup[THREE_PRONG] = false;
	}
}

void Player::powerup_bullet_speed(bool active) // maybe?? parameter powerup length
{
	if (active && powerup[BULLET_SPEED]) // refresh powerup
	{
		ptime[BULLET_SPEED] = 1000;
		return;
	}

	int speed_increase = 10;
	int recharge_increase = -7;

	if (active)
	{
		powerup[BULLET_SPEED] = true;
		ptime[BULLET_SPEED] = 1000;

		bullet_speed = bullet_speed + speed_increase;
		ammo_recharge = ammo_recharge + recharge_increase;
	}
	else
	{
		powerup[BULLET_SPEED] = false;
		bullet_speed = bullet_speed - speed_increase;
		ammo_recharge = ammo_recharge - recharge_increase;
	}
}

void Player::powerup_move_speed(bool active)
{
	if (active && powerup[MOVE_SPEED]) // refresh powerup
	{
		ptime[MOVE_SPEED] = 1000;
		return;
	}

	int speed_increase = 10;
	int friction_increase = 2;

	if (active)
	{
		if (!powerup[MOVE_SPEED])
		{
			powerup[MOVE_SPEED] = true;
			ptime[MOVE_SPEED] = 1000;

			max_xspeed = max_xspeed + speed_increase;
			friction = friction + friction_increase;
		}
	}
	else
	{
		powerup[MOVE_SPEED] = false;
		max_xspeed = max_xspeed - speed_increase;
		friction = friction - friction_increase;
	}
}

void Player::setBulletSpeed(int speed)
{
	bullet_speed = speed;
}

void Player::setAmmoRecharge(int recharge)
{
	ammo_recharge = recharge;
}

void Player::setMoveSpeed(int speed)
{
	max_xspeed = speed;
}

int Player::getHealth(void)
{
	return health;
}

void Player::setHealth(int h)
{
	health = h;

	if (health <= 0)
	{
		alive = false;
	}
}

int Player::getScore(void)
{
	return score;
}

void Player::setScore(int s)
{
	score = s;
}

POINT Player::getPosition(void)
{
	return position;
}

string Player::getActivePowerups(void)
{
	std::string active_powerups = "";

	if (powerup[THREE_PRONG])
	{
		active_powerups = active_powerups + "[[THREEPRONG]]";
	}
	
	if (powerup[BULLET_SPEED])
	{
		active_powerups = active_powerups + "[[BULLETSPEED]]";
	}

	if (powerup[MOVE_SPEED])
	{
		active_powerups = active_powerups + "[[MOVESPEED]]";
	}

	return active_powerups;
}