#include <boost\mpl\begin.hpp>
#include "fibonacci_series.h"

#ifndef _BOUNDED_FIBONACCI_SERIES_
#define _BOUNDED_FIBONACCI_SERIES_

using namespace boost;

struct bounded_fibonacci_series_tag {};

template <int N>
struct bounded_fibonacci_series
{
	typedef bounded_fibonacci_series_tag tag;
	typedef bounded_fibonacci_series type;
	typedef mpl::int_<N> size;
};

template <int Pos>
struct bounded_fibonacci_series_iterator
{
	typedef mpl::random_access_iterator_tag category;
	int pos;
};

namespace boost { namespace mpl {
	template<>
	struct begin_impl<bounded_fibonacci_series_tag>
	{
		template <class bounded_fibonacci_series>
		struct apply
		{
			typedef bounded_fibonacci_series_iterator<0> type;
		};
	};

	template<>
	struct end_impl<bounded_fibonacci_series_tag>
	{
		template <class bounded_fibonacci_series>
		struct apply
		{
			typedef bounded_fibonacci_series_iterator<bounded_fibonacci_series::size::value> type;
		};
	};

	template <int Pos>
	struct deref< bounded_fibonacci_series_iterator<Pos> >
	{
		typedef fibonacci_sequence<Pos> type;
	};

	//random access iterator requirements
	template <int Pos, class N>
	struct advance<bounded_fibonacci_series_iterator<Pos>,N>
	{
		typedef bounded_fibonacci_series_iterator<Pos + N::value> type;
	};

	//forward iterator requirement
	template <int Pos>
	struct next<bounded_fibonacci_series_iterator<Pos> >
	{
		typedef bounded_fibonacci_series_iterator<Pos+1> type;
	};

	//bidirectional iterator requirement
	template <int Pos>
	struct prior<bounded_fibonacci_series_iterator<Pos> >
	{
		typedef bounded_fibonacci_series_iterator<Pos-1> type;
	};

	template <>
	struct size_impl<bounded_fibonacci_series_tag>
	{
		template <class bounded_fibonacci_series>
		struct apply
		{
			typedef typename bounded_fibonacci_series::size type;
		};
	};
}}


BOOST_MPL_ASSERT(( is_same< mpl::begin<bounded_fibonacci_series<8> >::type,
							bounded_fibonacci_series_iterator<0>
                           >));

BOOST_STATIC_ASSERT(mpl::deref<bounded_fibonacci_series_iterator<0>>::type::value == 0 );
BOOST_STATIC_ASSERT(mpl::deref<bounded_fibonacci_series_iterator<1>>::type::value == 1 );
BOOST_STATIC_ASSERT(mpl::deref<bounded_fibonacci_series_iterator<6>>::type::value == 8 );

#endif