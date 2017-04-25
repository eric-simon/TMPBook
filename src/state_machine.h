#pragma once

#include <boost/mpl/fold.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/assert.hpp>

using namespace boost::mpl::placeholders;

template<class Derived>
class state_machine 
{
protected:
	template<
		int CurrentState
		,class Event
		,int NextState
		,void (Derived::*action)(Event const&)
	>
	struct row
	{
		//for later use by our metaprogram
		static int const current_state = CurrentState;
		static int const next_state = NextState;
		typedef Event event;
		typedef Derived fsm_t;

		//do the transition action
		static void execute(Derived& fsm, Event const& e)
		{
			(fsm.*action)(e);
		}

	};

	template <class Event>
	int call_no_transition(int state, Event const& e)
	{
		return static_cast<Derived*>(this)->no_transition(state, e);
	}

	state_machine() :state(Derived::initial_state)
	{}

	template <class Event>
	int no_transition(int state, Event const& e)
	{
		assert(false);
		return state;
	}
	
	template<class Transition, class Next>
	struct event_dispatcher
	{
		typedef typename Transition::fsm_t fsm_t;
		typedef typename Transition::event event;

		static int dispatch(fsm_t& fsm, int state, event const& e)
		{
			if (state == Transition::current_state)
			{
				Transition::execute(fsm, e);
				return Transition::next_state;
			}
			else
			{
				return Next::dispatch(fsm, state, e);
			}
		}
	};

	struct default_event_dispatcher
	{
		template <class FSM, class Event>
		static int dispatch(state_machine<FSM>& m, int state, Event const& e)
		{
			return m.call_no_transition(state, e);
		}
	};

	template <class Transition>
	struct transition_event
	{
		typedef typename Transition::event type;
	};

	template<class Table, class Event>
	struct generate_dispatcher : boost::mpl::fold<
													boost::mpl::filter_view<
																			Table
																			, boost::is_same<Event, transition_event<_1> >
																			>
																			, default_event_dispatcher
																			, event_dispatcher<_2, _1>
												>
	{};

private:
	int state;


public:
	template<class Event>
	int process_event(Event const& evt)
	{
		//generate the dispatcher type
		typedef typename generate_dispatcher<
			typename Derived::transition_table, Event>::type dispatcher;

		//dispatch the event
		this->state = dispatcher::dispatch(
			*static_cast<Derived*>(this)
			, this->state
			, evt
			);

		//return the new state
		return this->state;
	}
};





