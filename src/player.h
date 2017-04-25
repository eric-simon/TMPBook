#pragma once

#include "state_machine.h"
#include <boost/mpl/vector.hpp>
#include <iostream>

struct play {};
struct open_close {}; //events
struct cd_detected {};
struct pause {};
struct stop {};

class player : public state_machine<player>
{
private:
	enum States {
		Empty, Open, Stopped, Playing, Paused, initial_state = Empty
	};

	//transition actions

	void start_playback(play const&) { std::cout << "start_playback" << std::endl; };
	void open_drawer(open_close const&) { std::cout << "open_drawer" << std::endl; };
	void close_drawer(open_close const&) { std::cout << "close_drawer" << std::endl; };
	void store_cd_info(cd_detected const&) { std::cout << "store_cd_info" << std::endl; };
	void stop_playback(stop const&) { std::cout << "stop_playback" << std::endl; };
	void pause_playback(pause const&) { std::cout << "pause_playback" << std::endl; };
	void resume_playback(play const&) { std::cout << "resume_playback" << std::endl; };
	void stop_and_open(open_close const&) { std::cout << "stop_and_open" << std::endl; };

	friend class state_machine<player>;
	typedef player p; //makes transition table cleaner

	struct transition_table : boost::mpl::vector11<

		//Start		Event	Next	Action
		//+---+-----+---+--------+
		row < Stopped, play, Playing, &p::start_playback  >,
		row < Stopped, open_close, Open, &p::open_drawer  >,

		//+---+-----+---+--------+
		row < Open, open_close, Empty, &p::close_drawer  >,

		//+---+-----+---+--------+
		row < Empty, open_close, Open, &p::open_drawer  >,
		row < Empty, cd_detected, Stopped, &p::store_cd_info  >,

		//+---+-----+---+--------+
		row < Playing, stop, Stopped, &p::stop_playback  >,
		row < Playing, pause, Paused, &p::pause_playback  >,
		row < Playing, open_close, Open, &p::stop_and_open  >,

		//+---+-----+---+--------+
		row < Paused, play, Playing, &p::resume_playback  >,
		row < Paused, stop, Stopped, &p::stop_playback  >,
		row < Paused, open_close, Open, &p::stop_and_open  >
	> {};


};