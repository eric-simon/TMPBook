#include "stdafx.h"
#include "ch11.h"
#include "player.h"
#include <vector>
#include <ctime>


int ch11(int argc, _TCHAR* argv[])
{
	player p;

	p.process_event(open_close());
	p.process_event(open_close());
	//p.process_event(cd_detected("Louie, Louie", std::vector<std::clock_t>()));
	p.process_event(cd_detected());
	p.process_event(play());
	p.process_event(pause());
	p.process_event(play());
	p.process_event(stop());

	return 0;

}