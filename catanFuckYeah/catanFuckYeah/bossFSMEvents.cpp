#include "bossFSMEvents.h"

networkingEv::networkingEv(networkingEventTypes header_)
{
	error = true;
	if (validHeader(header_))
	{
		header = static_cast<networkingEventTypes>(header_);
		error = false;
	}
}

bool networkingEv::validHeader(char header_)
{
	return ((header_ == ACK) || ((header_ >= NAME) && (header_ <= I_START)) || ((header_ >= DICES_ARE) && (header_ <= PASS)) || (header_ >= DEV_CARD) && (header_ <= KNIGHT) || (header_ == YES) || (header_ == NO) || ((header_ >= I_WON) && (header_ <= GAME_OVER)) || (header_ == ERROR_PCKG) || (header_ == QUIT));
}