// ---------------------------------------------------------------------------
// ~LICENSE IN EXTERNAL FILE~
// DESCRIPTION: None
// AUTHOR: Chao Lai
// ---------------------------------------------------------------------------

#include "Globals.h"
#include "Player.h"
#include "MeteorSpawner.h"
#include "PowerupSpawner.h"
#include "UserInterface.h"

const float W_FPS = 60;
const int W_WIDTH = 1000;
const int W_HEIGHT = 480;

int mouse_x = 0;
int mouse_y = 0;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *background = NULL;
bool running;
int state;

Player p(W_WIDTH, W_HEIGHT); // create player with bounds of window
MeteorSpawner ms(W_WIDTH, W_HEIGHT);
PowerupSpawner ps(W_WIDTH, W_HEIGHT);
UserInterface ui(W_WIDTH, W_HEIGHT);

POINT spawn;

void game_abort(const char* message)
{
	al_show_native_message_box(al_get_current_display(), "Error!", "Error", message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	exit(1);
}

void game_init(void)
{
	if (!al_init())
		game_abort("Failed to initialize allegro");

	if (!al_init_native_dialog_addon())
		game_abort("Failed to initialize native dialog");

	if (!al_init_image_addon())
		game_abort("Failed to initialize image addon");

	if (!al_init_primitives_addon())
		game_abort("Failed to initialize graphics primatives");

	al_init_font_addon();
	al_init_ttf_addon();

	if (!al_install_keyboard())
		game_abort("Failed to install keyboard");

	if (!al_install_mouse())
		game_abort("Failed to install mouse");

	timer = al_create_timer(1.0 / W_FPS);
	if (!timer)
		game_abort("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(W_WIDTH, W_HEIGHT);
	if (!display)
		game_abort("Failed to create display");

	event_queue = al_create_event_queue();
	if (!event_queue)
		game_abort("Failed to create event queue");

	background = al_load_bitmap("background.png");
	if (background == NULL)
		game_abort("Failed to load bitmap");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	spawn = { W_WIDTH / 2, W_HEIGHT - 50 };
	p.init(spawn, LEFT);

	ui.init_font();

	running = true;
	state = MENU;
}

void game_shutdown(void)
{
	if (timer)
		al_destroy_timer(timer);

	if (display)
		al_destroy_display(display);

	if (event_queue)
		al_destroy_event_queue(event_queue);

	al_destroy_bitmap(background);

	ui.close();
}

void game_update(void)
{
	if (state == GAME)
	{
		p.update();
		ms.update();
		ps.update();
		ms.check_collision(p); // make this happen with update
		ps.check_collision(p);
		ms.spawn(p);
		ps.spawn();
		ui.update(p);

		if (p.isShooting())
			p.create_bullet(mouse_x, mouse_y);
	}

	if (p.getHealth() <= 0)
	{
		state = END;
	}
}

void game_draw(void)
{
	if (state == MENU)
	{
		ui.draw_menu();
	}
	else if (state == GAME)
	{
		//al_draw_bitmap(background, 0, 0, 0);
		al_clear_to_color(WHITE);

		// redraw enviornment
		p.draw();
		ms.draw();
		ps.draw();
		ui.draw();
	}
	else if (state == END)
	{
		ui.draw_end();
	}

	al_flip_display();
}

void game_loop(void)
{
	bool redraw = true;
	al_start_timer(timer);

	while (running) 
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				redraw = true;

				if (p.getHealth() > 0)
				{
					game_update();
				}

				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (event.keyboard.keycode)
				{
					case ALLEGRO_KEY_A: case ALLEGRO_KEY_LEFT:
						p.left();
						break;
					case ALLEGRO_KEY_D: case ALLEGRO_KEY_RIGHT:
						p.right();
						break;
					case ALLEGRO_KEY_W: case ALLEGRO_KEY_UP:
						p.jump();
						break;
					case ALLEGRO_KEY_SPACE:
						if (state == MENU)
						{
							state = GAME;
						}
						else if (state == GAME)
						{
							p.jump();
						}
						else
						{
							spawn = { W_WIDTH / 2, W_HEIGHT - 50 };
							p.init(spawn, LEFT);
							ms.restart();
							ps.restart();
							state = GAME;
						}
						break;
					case ALLEGRO_KEY_Q:
						if (p.getBombs() > 0)
						{
							p.use_bomb();
							ms.bomb();
						}
						break;
					case ALLEGRO_KEY_ENTER:
						if (p.getHealth() <= 0)
					
						break;
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				switch (event.keyboard.keycode)
				{
					case ALLEGRO_KEY_A: case ALLEGRO_KEY_LEFT:
						p.left();
						break;
					case ALLEGRO_KEY_D: case ALLEGRO_KEY_RIGHT:
						p.right();
						break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				switch (event.mouse.button)
				{
					case 1:
						p.shoot();
						mouse_x = event.mouse.x;
						mouse_y = event.mouse.y;
						break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				if (p.isShooting())
				{
					mouse_x = event.mouse.x;
					mouse_y = event.mouse.y;
				}
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				running = false;
				break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) 
		{
			redraw = false;
			game_draw();
		}
	}
}

int main(int argc, char **argv)
{
	game_init();
	game_loop();
	game_shutdown();

	return 0;
}