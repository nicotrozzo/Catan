#include "startMenu.h"

dibujator::dibujator()
{
}

void dibujator::menuInit()
{
	if (al_init() == true)
	{
		if ((display = al_create_display(DISPLAY_WIDHT, DISPLAY_HEIGHT)) != NULL)
		{
			if (al_install_keyboard() == true)
			{
				if (al_install_mouse() == true)
				{
					if (al_init_image_addon())
					{
						if (al_init_primitives_addon())
						{
							if (al_init_font_addon())
							{
								if (al_init_ttf_addon())
								{
									if ((queue = al_create_event_queue()) != NULL)
									{
										al_register_event_source(queue, al_get_keyboard_event_source());
										al_register_event_source(queue, al_get_mouse_event_source());
										initializationError = true;
										return;
									}
									else
									{
										cout << "No se pudo crear la cola de eventos" << endl;
									}
									al_destroy_font(font);
									cout << "No se pudo crear font" << endl;
								}
								else
								{
									cout << "No se pudo inicializar ttf addon" << endl;
								}
								al_shutdown_font_addon();
							}
							else
							{
								cout << "No se pudo inicializar font addon" << endl;
							}
							al_shutdown_primitives_addon();
						}
						else
						{
							cout << "No se pudi inicializar primitives addon" << endl;
						}
						al_shutdown_image_addon();
					}
					else
					{
						cout << "No se pudo inicializar image addon" << endl;
					}
				}
				else
				{
					cout << "No se pudo instalar el driver del mouse" << endl;
				}
			}
			else
			{
				cout << "No se pudo instalar el driver del teclado" << endl;
			}
			al_destroy_display(display);
		}
		else
		{
			cout << "No se pudo crear display" << endl;
		}
	}
	else
	{
		cout << "Fallo iniciando allegro" << endl;
	}
	initializationError = false;
	return;
}

bool dibujator::menuImageLoad()
{
	if ((menuBitmap = al_load_bitmap("graficoCatan\\menues\\mainmenu.png")) == NULL || (playBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonplay1.png")) == NULL || (exitBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonexit1.png")) == NULL)
	{
		return false;
	}
	else
	{
		al_draw_bitmap(menuBitmap, 0, 0, 0);
		al_flip_display();
		al_draw_bitmap(playBitmap, DISPLAY_WIDHT / 4, DISPLAY_HEIGHT / 2, 0);
		al_flip_display();
		al_draw_bitmap(exitBitmap, 2 * DISPLAY_WIDHT / 4, DISPLAY_HEIGHT / 2, 0);
		al_flip_display();
	}
	//else if((al))
	return true;
}

bool dibujator::getInitializationError()
{
	return initializationError;
}


dibujator::~dibujator()
{
}
