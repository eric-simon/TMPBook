#include "stdafx.h"
#include <boost/mpl/plus.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector_c.hpp>

//#include "crossproduct_view.h"


template <class T, class U>
struct plus_dbg
{
	typedef typename boost::mpl::print<
										typename boost::mpl::plus<T, U>::type
									   >::type type;
};

typedef boost::mpl::fold<
	boost::mpl::range_c<int, 1, 6>,
	boost::mpl::int_<0>,
	plus_dbg<boost::mpl::_1, boost::mpl::_2>
>::type sum;
/*
typedef boost::mpl::fold<
	boost::mpl::range_c<int, 2, 6>,
	boost::mpl::int_<0>,
	plus_dbg<boost::mpl::_1, boost::mpl::_2>
>::type sum2;*/

/*
//typedef boost::mpl::range_c<int, 0, 10> range10;

typedef boost::mpl::vector_c<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10> range10;

typedef boost::mpl::transform<
	range10,
	boost::mpl::print<boost::mpl::_1>
>::type printrange;

/*
template <int N>
struct non_primes
{
	typedef boost::mpl::range_c<int, 0, N> seed;
	typedef crossproduct_view<seed, seed> pairs;
	typedef boost::mpl::transform < pairs, boost::mpl::plus<_1::first, _2::second>::type sum;
};


template <int N>
struct primes
{
	typedef boost::mpl::range_c<int, 0, N> all;
};*/



