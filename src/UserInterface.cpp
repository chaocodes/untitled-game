// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "UserInterface.h"

UserInterface::UserInterface(){}

UserInterface::UserInterface(int w, int h)
{
	B_WIDTH = w;
	B_HEIGHT = h;
}

UserInterface::~UserInterface() 
{
	//close();
}

void UserInterface::init_font()
{
	score_font = al_load_ttf_font("fonts/arial.ttf", 48, 0);
	powerup_font = al_load_ttf_font("fonts/arial.ttf", 10, 0);
}

void UserInterface::draw()
{
	glLoadIdentity();

	// health
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f); // RED outer health
	glVertex2i(10, 10);
	glVertex2i(100 * 2, 10);
	glVertex2i(100 * 2, 60);
	glVertex2i(10, 60);

	glColor3f(0.0f, 1.0f, 0.0f); // GREEN inner health
	glVertex2i(10, 10);
	glVertex2i(p_health * 2, 10);
	glVertex2i(p_health * 2, 60);
	glVertex2i(10, 60);

	glEnd();
	al_draw_textf(score_font, BLACK, 10, 10, 0, "%d", p_health);

	// score
	al_draw_textf(score_font, BLACK, B_WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, "%d", p_score);

	// powerups
	al_draw_text(powerup_font, BLACK, 10, 70, 0, p_powerups.c_str());

	// bombs
	if (p_bombs > 0)
		al_draw_textf(powerup_font, BLACK, 10, 60, 0, "[[BOMBS: %d]]", p_bombs);
	else
		al_draw_textf(powerup_font, RED, 10, 60, 0, "[[BOMBS: %d]]", p_bombs);
}

void UserInterface::update(Player &p)
{
	p_health = p.getHealth();
	p_score = p.getScore();
	p_bombs = p.getBombs();
	p_powerups = p.getActivePowerups();
}

void UserInterface::draw_menu()
{
	al_clear_to_color(BLACK);
	al_draw_text(score_font, WHITE, B_WIDTH / 2, B_HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTER, "UNTITLED GAME");
	al_draw_text(powerup_font, WHITE, B_WIDTH / 2, B_HEIGHT / 2 + 40, ALLEGRO_ALIGN_CENTER, "[[Press SPACE to start!]]");
}

void UserInterface::draw_end()
{
	al_clear_to_color(BLACK);
	al_draw_text(score_font, RED, B_WIDTH / 2, B_HEIGHT / 2 - 40, ALLEGRO_ALIGN_CENTER, "Game Over!");
	al_draw_textf(score_font, WHITE, B_WIDTH / 2, B_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "SCORE: %d", p_score);
	al_draw_text(powerup_font, WHITE, B_WIDTH / 2, B_HEIGHT / 2 + 60, ALLEGRO_ALIGN_CENTER, "[[Press SPACE to restart!]]");
}

void UserInterface::close()
{
	al_destroy_font(score_font);
	al_destroy_font(powerup_font);
}