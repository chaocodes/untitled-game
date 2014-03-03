// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "PowerupSpawner.h"

PowerupSpawner::PowerupSpawner(void) {}

PowerupSpawner::PowerupSpawner(int w, int h)
{
	srand(time(0));
	B_WIDTH = w;
	B_HEIGHT = h;
	ticks = 0;
	spawnSpeed = rand() % 500 + 500;
}

PowerupSpawner::~PowerupSpawner(void) {}

void PowerupSpawner::draw(void)
{
	if (powerup.isAlive())
	{
		powerup.draw();
	}
}

void PowerupSpawner::update(void)
{
	if (powerup.isAlive())
	{
		powerup.update();
	}
}

void PowerupSpawner::check_collision(Player &p)
{
	if (powerup.isAlive())
	{
		powerup.player_collision(p);
	}
}

void PowerupSpawner::spawn(void)
{
	if (!powerup.isAlive())
	{
		if (canSpawn())
		{
			POINT end;

			end.x = rand() % (B_WIDTH - 400) + 200;
			end.y = B_HEIGHT;

			powerup = Powerup(end);

			ticks = 0; // reset
		}
	}

	ticks++;
}

bool PowerupSpawner::canSpawn(void)
{
	return ticks >= spawnSpeed;
}

void PowerupSpawner::restart(void)
{
	ticks = 0;
	spawnSpeed = rand() % 500 + 500;
	powerup.setAlive(false);
}