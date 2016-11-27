#include <boost\mpl\begin.hpp>

#ifndef _FIBONACCI_SERIES_
#define _FIBONACCI_SERIES_



template <int N>
struct fibonacci_sequence
{
	static const int value = fibonacci_sequence<N-1>::value + fibonacci_sequence<N-2>::value;
};


template <>
struct fibonacci_sequence<1>
{
	static const int value = 1;
};

template <>
struct fibonacci_sequence<0>
{
	static const int value = 0;
};

BOOST_STATIC_ASSERT((fibonacci_sequence<0>::value == 0));
BOOST_STATIC_ASSERT((fibonacci_sequence<1>::value == 1));
BOOST_STATIC_ASSERT((fibonacci_sequence<2>::value == 1));
BOOST_STATIC_ASSERT((fibonacci_sequence<3>::value == 2));
BOOST_STATIC_ASSERT((fibonacci_sequence<4>::value == 3));
BOOST_STATIC_ASSERT((fibonacci_sequence<5>::value == 5));
BOOST_STATIC_ASSERT((fibonacci_sequence<6>::value == 8));

using namespace boost;

struct fibonacci_series_tag {};

struct fibonacci_series
{
	typedef fibonacci_series_tag tag;
	typedef fibonacci_series type;
};

template <int Pos>
struct fibonacci_series_iterator
{
	typedef mpl::random_access_iterator_tag category;
	int pos;
};

namespace boost { namespace mpl {
	template<>
	struct begin_impl<fibonacci_series_tag>
	{
		template <class fibonacci_series>
		struct apply
		{
			typedef fibonacci_series_iterator<0> type;
		};
	};

	template <int Pos>
	struct deref< fibonacci_series_iterator<Pos> >
	{
		typedef fibonacci_sequence<Pos> type;
	};

	//random access iterator requirements
	template <int Pos, class N>
	struct advance<fibonacci_series_iterator<Pos>,N>
	{
		typedef fibonacci_series_iterator<Pos + N::value> type;
	};

		//forward iterator requirement
	template <int Pos>
	struct next<fibonacci_series_iterator<Pos> >
	{
		typedef fibonacci_series_iterator<Pos+1> type;
	};

}}


BOOST_MPL_ASSERT(( is_same< mpl::begin<fibonacci_series>::type,
							fibonacci_series_iterator<0>
                           >));

BOOST_STATIC_ASSERT(mpl::deref<fibonacci_series_iterator<0>>::type::value == 0 );
BOOST_STATIC_ASSERT(mpl::deref<fibonacci_series_iterator<1>>::type::value == 1 );
BOOST_STATIC_ASSERT(mpl::deref<fibonacci_series_iterator<6>>::type::value == 8 );

#endif
