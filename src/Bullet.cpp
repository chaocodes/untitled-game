// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "Bullet.h"

Bullet::Bullet(void) 
{
	alive = false;
}

Bullet::Bullet(int w, int h, int s, POINT start, POINT end)
{
	B_WIDTH = w;
	B_HEIGHT = h;

	position = start;
	if (end.x - start.x == 0)
	{
		end.x++; // temporary alignment
	}

	slope = (end.y - start.y) / (double)(end.x - start.x); // dy/dx
	offset = (end.y - (slope * (double)end.x)); // b = y - mx

	speed = s;

	damage = 10;
	width = 4;
	height = 4;

	alive = true;
}

Bullet::~Bullet(void) {}

void Bullet::update(void)
{
	position.y = position.y - speed;
	position.x = (position.y - offset) / slope; // x = (y - b) / m

	if (position.y > B_HEIGHT || position.y < 0 || position.x > B_WIDTH || position.x < 0)
	{
		alive = false;
	}

	update_bound();
}

void Bullet::draw(void)
{
	// maybe?? fancier bullet
	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);

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

int Bullet::getDamage(void)
{
	return damage;
}

void Bullet::explode(void)
{
	alive = false; 
	// TODO: add more logic
}

void Bullet::update_bound(void)
{
	bound_box.left = position.x - width / 2;
	bound_box.right = position.x + width / 2;
	bound_box.top = position.y - height / 2;
	bound_box.bottom = position.y + height / 2;
}

RECT Bullet::getBound(void)
{
	return bound_box;
}

bool Bullet::isAlive(void)
{
	return alive;
}