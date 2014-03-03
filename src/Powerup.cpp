// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "Powerup.h"

Powerup::Powerup(void)
{
	alive = false;
}

Powerup::Powerup(POINT finish)
{
	position = finish;
	position.y = 0;
	end = finish;

	font = al_load_ttf_font("arial.ttf", 12, 0);
	speed = 2;

	powerup = rand() % (PTOTAL); // always takes floor so 0 - 3

	if (powerup == HEALTH)
	{
		powerup_name = "HEALTH";
		bound_width = 50;
	}
	else if (powerup == THREE_PRONG)
	{
		powerup_name = "THREEPRONG";
		bound_width = 90;
	}
	else if (powerup == BULLET_SPEED)
	{
		powerup_name = "BULLETSPEED";
		bound_width = 90;
	}
	else if (powerup == MOVE_SPEED)
	{
		powerup_name = "MOVESPEED";
		bound_width = 80;
	}

	update_bound();

	alive = true;
}

Powerup::~Powerup(void) {}

void Powerup::draw(void)
{
	al_draw_text(font, BLACK, position.x, position.y, ALLEGRO_ALIGN_CENTER, powerup_name.c_str());
	
	// testing -- draw bound
	al_draw_rectangle(bound_box.left, bound_box.top, bound_box.right, bound_box.bottom, GRAY, 1);
}

void Powerup::update(void)
{
	position.y = position.y + speed;

	if (position.y >= end.y)
	{
		alive = false;
	}

	update_bound();
}

void Powerup::give_power(Player &p)
{
	if (powerup == HEALTH)
	{
		p.setHealth(p.getHealth() + 30); // add to health

		if (p.getHealth() > 100)
		{
			p.setHealth(100);
		}
	}
	else if (powerup == THREE_PRONG)
	{
		p.powerup_three_prong(true);
	}
	else if (powerup == BULLET_SPEED)
	{
		p.powerup_bullet_speed(true);
	}
	else if (powerup == MOVE_SPEED)
	{
		p.powerup_move_speed(true);
	}

	alive = false;
}

void Powerup::update_bound(void)
{
	bound_box.left = position.x - bound_width / 2;
	bound_box.right = position.x + bound_width / 2;
	bound_box.top = position.y - 5;
	bound_box.bottom = position.y + 15;
}

RECT Powerup::getBound(void)
{
	return bound_box;
}

void Powerup::player_collision(Player &p)
{
	// check player collsion
	RECT p_bound_box = p.getBound();

	if (p_bound_box.right < bound_box.left ||
		p_bound_box.top > bound_box.bottom ||
		bound_box.right < p_bound_box.left ||
		bound_box.top > p_bound_box.bottom)
	{
		return;
	}

	give_power(p);
}

void Powerup::setAlive(bool a)
{
	alive = a;
}

bool Powerup::isAlive(void)
{
	return alive;
}

