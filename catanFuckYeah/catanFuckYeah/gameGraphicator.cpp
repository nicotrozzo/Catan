#include "gameGraphicator.h"

gameGraphicator::gameGraphicator()
{
	message = "";
}

void gameGraphicator::refresh()
{
	if (message.length() > 0)
	{
		//mostrar fondo
		//mostrar texto
		//mensaje mas largo: "Waiting opponent to move the robber"
	}
	al_flip_display();
}

void gameGraphicator::setMessage(string message_)
{
	message = message_;
}
