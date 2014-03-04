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

Meteor::Meteor(POINT start, POINT finish)
{
	// random meteor properties
	meteor_shape = rand() % 3;
	meteor_color.r = rand() % 255;
	meteor_color.g = rand() % 255;
	meteor_color.b = rand() % 255;
	if (meteor_color.r == 255 && meteor_color.g == 255 && meteor_color.b == 255)
	{
		meteor_color.r = 200;
		meteor_color.g = 200;
		meteor_color.b = 200;
	}

	position = start;
	end = finish;

	slope = (end.y - start.y) / (double)(end.x - start.x); // dy/dx
	offset = (end.y - (slope * (double)end.x)); // b = y - mx 

	width = rand() % 50 + 20;
	height = width;
	health = width / 5;

	update_bound();

	velocity = 2500 / width; // smaller = faster
	acceleration = 1;
	max_speed = rand() % 3 + 3;

	alive = true;
}

Meteor::~Meteor(void) {}

void Meteor::draw(void)
{
	if (alive)
	{
		glLoadIdentity();
		glColor3f(meteor_color.r / 255.0f, meteor_color.g / 255.0f, meteor_color.b / 255.0f);

		if (meteor_shape == TRIANGLE)
		{
			int x1 = position.x;
			int y1 = position.y;
			int x2 = position.x - width / 2;
			int y2 = position.y + height / 2;
			int x3 = position.x + width / 2;
			int y3 = position.y + height / 2;

			glBegin(GL_TRIANGLES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
			glVertex2i(x3, y3);
			glEnd();
		}
		else if (meteor_shape == RECTANGLE)
		{
			glRectf(bound_box.left, bound_box.top, bound_box.right, bound_box.bottom);
		}
		else if (meteor_shape == CIRCLE)
		{
			int x1 = position.x;
			int y1 = position.y;
			int x2;
			int y2;

			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x1, y1);
			for (float angle = 1.0f; angle < 361.0f; angle += 0.2f)
			{
				x2 = x1 + sin(angle) * (width / 2);
				y2 = y1 + cos(angle) * (width / 2);
				glVertex2f(x2, y2);
			}
			glEnd();
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