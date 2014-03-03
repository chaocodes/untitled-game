// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "Meteor.h"

Meteor::Meteor(void) 
{
	alive = false;
}

Meteor::Meteor(POINT start, POINT finish, int vel)
{
	// random meteor properties
	meteor_shape = rand() % 3;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	if (r == 255 && g == 255 && b == 255)
	{
		r = 50;
		g = 20;
		b = 200;
	}

	meteor_color = al_map_rgb(r, g, b);

	position = start;
	end = finish;

	slope = (end.y - start.y) / (double)(end.x - start.x); // dy/dx
	offset = (end.y - (slope * (double)end.x)); // b = y - mx 

	width = rand() % 50 + 20;
	height = width;
	health = 10; // change based on size ALSO change speed based on size

	update_bound();

	velocity = vel;
	acceleration = 1;
	max_speed = rand() % 3 + 3;

	alive = true;
}

Meteor::~Meteor(void) {}

void Meteor::draw(void)
{
	if (alive)
	{
		if (meteor_shape == TRIANGLE)
		{
			int x1 = position.x;
			int y1 = position.y;
			int x2 = position.x - width / 2;
			int y2 = position.y + height / 2;
			int x3 = position.x + width / 2;
			int y3 = position.y + height / 2;

			al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, meteor_color);
		}
		else if (meteor_shape == RECTANGLE)
		{
			al_draw_filled_rectangle(bound_box.left, bound_box.top, bound_box.right, bound_box.bottom, meteor_color);
		}
		else if (meteor_shape == CIRCLE)
		{
			al_draw_filled_circle(position.x, position.y, width / 2, meteor_color);
		}
	}
}

void Meteor::update(void)
{
	position.y = position.y + velocity;
	position.x = (position.y - offset) / slope; // x = (y - b) / m
	velocity = velocity + acceleration;

	if (velocity >= max_speed)
	{
		velocity = max_speed;
	}

	if (position.y >= end.y)
	{
		alive = false;
	}

	update_bound();
}

void Meteor::explode(void)
{
	alive = false;
}

void Meteor::update_bound(void)
{
	bound_box.left = position.x - width / 2;
	bound_box.right = position.x + width / 2;
	bound_box.top = position.y - height / 2;
	bound_box.bottom = position.y + height / 2;
}

RECT Meteor::getBound(void)
{
	return bound_box;
}

void Meteor::player_collision(Player &p)
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

	explode();
	p.setHealth(p.getHealth() - health); // damage based on meteor health
}

void Meteor::bullet_collision(Player &p) 
{
	Bullet *bullets = p.getBullets();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].isAlive())
		{
			RECT b_bound_box = bullets[i].getBound();
			if (b_bound_box.right < bound_box.left ||
				b_bound_box.top > bound_box.bottom ||
				bound_box.right < b_bound_box.left ||
				bound_box.top > b_bound_box.bottom)
			{
				continue;
			}

			bullets[i].explode();
			health = health - bullets[i].getDamage();

			if (health <= 0)
			{
				explode();
				p.setScore(p.getScore() + (width / 10));
			}
		}
	}
}

void Meteor::setAlive(bool a)
{
	alive = a;
}

bool Meteor::isAlive(void)
{
	return alive;
}