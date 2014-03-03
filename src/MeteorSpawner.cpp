// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "MeteorSpawner.h"

MeteorSpawner::MeteorSpawner(void) {}

MeteorSpawner::MeteorSpawner(int w, int h)
{
	srand(time(0));

	B_WIDTH = w;
	B_HEIGHT = h;

	index = 0;
	ticks = 0;
	delay = 0;
	spawnSpeed = 15;

	difficulty_interval = 200;
}

MeteorSpawner::~MeteorSpawner(void) {}

void MeteorSpawner::draw(void)
{
	for (int i = 0; i < MAX_METEORS; i++)
	{
		if (meteors[i].isAlive())
		{
			meteors[i].draw();
		}
	}
}

void MeteorSpawner::update(void)
{
	difficulty_interval--;

	if (difficulty_interval <= 0) // update difficulty
	{
		difficulty_interval = rand() % 100 + 100;
		spawnSpeed--;

		if (spawnSpeed < 3)
		{
			spawnSpeed = 3;
		}
	}

	for (int i = 0; i < MAX_METEORS; i++)
	{
		if (meteors[i].isAlive())
		{
			meteors[i].update();
		}
	}
}

void MeteorSpawner::check_collision(Player &p)
{
	for (int i = 0; i < MAX_METEORS; i++)
	{
		if (meteors[i].isAlive())
		{
			meteors[i].player_collision(p);
			meteors[i].bullet_collision(p);
		}
	}
}

void MeteorSpawner::spawn(Player &p)
{
	int n = 1;

	if (canSpawn())
	{
		POINT start;
		POINT end;
		int velocity;

		for (int i = index; i < (n + index); i++)
		{
			i = i % MAX_METEORS;

			if (meteors[i].isAlive()) // don't overwrite existing meteors
				continue;

			start.x = rand() % (B_WIDTH + 80) - 40;
			start.y = -50;
			end.x = p.getPosition().x + ((rand() % 200) - 100);
			end.y = B_HEIGHT;
			velocity = rand() % 50 + 30;

			if (start.x == end.x) // TODO: handle undefined slopes
			{
				end.x++;
			}

			meteors[i] = Meteor(start, end, velocity);
		}

		index = (index + n) % MAX_METEORS;
		ticks = 0; // reset
	}
	else
	{
		ticks++;
		if (delay != 0)
			delay--;
	}
}

bool MeteorSpawner::canSpawn(void)
{
	return ticks >= spawnSpeed && delay == 0;
}

void MeteorSpawner::bomb(void)
{
	for (int i = 0; i < MAX_METEORS; i++)
	{
		meteors[i].explode();
	}

	delay = 100;
	spawnSpeed = spawnSpeed + 5;
}

void MeteorSpawner::restart(void)
{
	for (int i = 0; i < MAX_METEORS; i++)
	{
		meteors[i].setAlive(false);
	}

	index = 0;
	ticks = 0;
	delay = 0;
	spawnSpeed = 15;

	difficulty_interval = 300;
}