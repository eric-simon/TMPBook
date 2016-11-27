#include "stdafx.h"
#include <boost/mpl/assert.hpp>
#include "boost/mpl/or.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/not_equal_to.hpp"
#include <boost/type_traits.hpp>
#include <boost/type_traits/is_member_pointer.hpp>

#include "boost/mpl/if.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/not_equal_to.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_scalar.hpp>

#include "boost/mpl/greater.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/multiplies.hpp"
#include "boost/mpl/minus.hpp"

#include <list>
#include <iostream>
#include <algorithm>
#include "ch3.h"




//mpl::or_  mpl::and_ using short-circuit behavior
using namespace boost;

int ch4(int argc, _TCHAR* argv[])
{
	return 0;
}

//first, a basic test for or_
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<true>, mpl::bool_<true> >::value));
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<true>, mpl::bool_<false> >::value));
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<false>, mpl::bool_<true> >::value));
BOOST_STATIC_ASSERT(mpl::not_<mpl::or_<mpl::bool_<false>, mpl::bool_<false> > >::value);

//next, a basic test for and_
BOOST_STATIC_ASSERT((mpl::and_<mpl::bool_<true>, mpl::bool_<true> >::value));
BOOST_STATIC_ASSERT(mpl::not_<mpl::and_<mpl::bool_<false>, mpl::bool_<false> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<mpl::and_<mpl::bool_<true>, mpl::bool_<false> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<mpl::and_<mpl::bool_<false>, mpl::bool_<true> > >::value);

//this class will fail to compile if instantiated
template <class T>
struct uninstantiable
{
typedef typename T::crasher value;
};

//these statements instantiate uninstatiable, so they cause compilation failures
//BOOST_STATIC_ASSERT(mpl::or_<uninstantiable<void>, mpl::bool_<false> >::value);
//BOOST_STATIC_ASSERT(mpl::or_<mpl::bool_<false>,     uninstantiable<void> >::value);

//BOOST_STATIC_ASSERT(mpl::not_< mpl::and_< uninstantiable<void>, mpl::bool_<true> > >::value);
//BOOST_STATIC_ASSERT(mpl::not_< mpl::and_< mpl::bool_<true>,    uninstantiable<void> > >::value);

//the short-circuit only applies to when the left-most argument forces the result
//BOOST_STATIC_ASSERT(mpl::or_<uninstantiable<void>, mpl::bool_<true> >::value);
//BOOST_STATIC_ASSERT(mpl::not_< mpl::and_< uninstantiable<void>, mpl::bool_<false> > >::value);

//these short-circuit and pass
BOOST_STATIC_ASSERT(mpl::or_<mpl::bool_<true>,     uninstantiable<void> >::value);

BOOST_STATIC_ASSERT(mpl::not_< mpl::and_< mpl::bool_<false>,    uninstantiable<void> > >::value);

//or this simpler test I found online:
class crash{};

BOOST_STATIC_ASSERT(mpl::or_<mpl::bool_<true>,     crash >::value);

BOOST_STATIC_ASSERT(mpl::not_< mpl::and_< mpl::bool_<false>,    crash > >::value);

//metafunction binary logical_or and logical_and that model mpl::and_ and mpl::or_

template <class N1, class N2>
struct logical_or : mpl::not_<
							mpl::and_<
									mpl::equal_to<N1, mpl::int_<0> >, 
									mpl::equal_to<N2, mpl::int_<0> >
								>
							>
{
};

BOOST_STATIC_ASSERT(mpl::equal_to<mpl::int_<0>, mpl::int_<0> >::value);

//basic test
BOOST_STATIC_ASSERT((logical_or<mpl::int_<0>, mpl::int_<1> >::value));
BOOST_STATIC_ASSERT((logical_or<mpl::int_<1>, mpl::int_<0> >::value));
BOOST_STATIC_ASSERT((logical_or<mpl::int_<0>, mpl::int_<1> >::value));
BOOST_STATIC_ASSERT(mpl::not_<logical_or<mpl::int_<0>, mpl::int_<0> > >::value);

//short-circuit test
BOOST_STATIC_ASSERT(logical_or<mpl::int_<1>,     crash >::value);

template <class N1, class N2>
struct logical_and : mpl::and_<
							mpl::not_equal_to<N1, mpl::int_<0> >, 
							mpl::not_equal_to<N2, mpl::int_<0> >
								>
{
};


BOOST_STATIC_ASSERT(mpl::not_<logical_and<mpl::bool_<false>, mpl::bool_<false> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_and<mpl::bool_<true>, mpl::bool_<false> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_and<mpl::bool_<false>, mpl::bool_<true> > >::value);


BOOST_STATIC_ASSERT(mpl::not_< logical_and< mpl::bool_<false>,    crash > >::value);

template <class N1, class N2, class N3 = mpl::int_<1>, class N4 = mpl::int_<1>, class N5 = mpl::int_<1> >
struct logical_andm : mpl::eval_if<mpl::equal_to<N1, mpl::int_<0> >,
								   mpl::false_,
								   logical_andm<N2, N3, N4, N5, mpl::int_<1> > >
{
};

template <>
struct logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> > :mpl::true_
{
};

template <class N1, class N2, class N3 = mpl::int_<0>, class N4 = mpl::int_<0>, class N5 = mpl::int_<0> >
struct logical_orm : mpl::eval_if<mpl::equal_to<N1, mpl::int_<1> >,
								   mpl::true_,
								   logical_orm<N2, N3, N4, N5, mpl::int_<0> > >
{
};

template <>
struct logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > :mpl::false_
{
};

//2 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(logical_andm<mpl::int_<1>, mpl::int_<1> >::value);

//3 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//4 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//5 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> > >::value);
BOOST_STATIC_ASSERT(mpl::not_<logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_andm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//2 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_orm<mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1> >::value);

//3 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//4 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//5 arg test
BOOST_STATIC_ASSERT(mpl::not_<logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> > >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0>, mpl::int_<1> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<0> >::value);
BOOST_STATIC_ASSERT(logical_orm<mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1>, mpl::int_<1> >::value);

//4.3 1
#if 0
template< typename N, typename Predicate >
struct next_if : mpl::if_<
			typename mpl::apply<Predicate, N>::type,
			typename mpl::next<N>::type,
			N>
{};
#endif

template< typename N, typename Predicate >
struct next_if : mpl::eval_if<
			typename mpl::apply<Predicate, N>::type,
			typename mpl::next<N>,
			N>
{};

BOOST_STATIC_ASSERT(mpl::equal_to<next_if<mpl::int_<0>, mpl::lambda<mpl::equal_to<mpl::_, mpl::int_<0> > >::type >::type, mpl::int_<1> >::value);

BOOST_STATIC_ASSERT(mpl::equal_to<next_if<mpl::int_<0>, mpl::lambda<mpl::equal_to<mpl::_, mpl::int_<1> > >::type >::type, mpl::int_<0> >::value);

//let's use a type for which "next" does not apply

BOOST_STATIC_ASSERT(mpl::equal_to<next_if<mpl::bool_<false>, mpl::lambda<mpl::equal_to<mpl::_, mpl::bool_<true> > >::type >::type, mpl::bool_<false> >::value);

//4.3 2
#if 0
template<typename N1, typename N2 >
struct formula : mpl::if_<
					mpl::not_equal_to<N1, N2>,
					typename mpl::if_<
						mpl::greater<N1, N2>,
						typename mpl::minus<N1,N2>::type,
						N1>::type,
					typename mpl::plus<N1,
										typename mpl::multiplies<N1,
																mpl::int_<2> >::type
						>::type
				>::type
{};
#endif

template<typename N1, typename N2 >
struct formula : mpl::eval_if<
					mpl::not_equal_to<N1, N2>,
					typename mpl::eval_if<
						mpl::greater<N1, N2>,
						typename mpl::minus<N1,N2>,
						N1>,
					typename mpl::plus<N1,
										typename mpl::multiplies<N1,
																mpl::int_<2> >
						>
				>
{};


//N1 != N2, and N1 > N2  (result = N1 - N2)
BOOST_STATIC_ASSERT(mpl::equal_to<formula<mpl::int_<5>, mpl::int_<2> >, mpl::int_<3> >::value);

//N1 != N2, and N1 <= N2  (result = N1)
BOOST_STATIC_ASSERT(mpl::equal_to<formula<mpl::int_<2>, mpl::int_<5> >, mpl::int_<2> >::value);

//N1 == N2 (result = N1 + N1*2)
BOOST_STATIC_ASSERT(mpl::equal_to<formula<mpl::int_<3>, mpl::int_<3> >, mpl::int_<9> >::value);

//4.4

//is_data_member_pointer
class myClass
{
};

BOOST_MPL_ASSERT((boost::is_member_pointer<int (myClass::*)>));
BOOST_MPL_ASSERT((boost::is_member_pointer<int (myClass::*)(char)>));

BOOST_MPL_ASSERT_NOT((boost::is_member_function_pointer<int (myClass::*)>));
BOOST_MPL_ASSERT((boost::is_member_function_pointer<int (myClass::*)(char)>));

template<typename T >
struct is_data_member_pointer : mpl::and_<boost::is_member_pointer<T>, mpl::not_< boost::is_member_function_pointer<T> > >
{};

BOOST_MPL_ASSERT((is_data_member_pointer<int (myClass::*)>));
BOOST_MPL_ASSERT_NOT((is_data_member_pointer<int (myClass::*)(char)>));

//is_pointer_to_function  (does mpl::and_ have short-circuit evaluation?  Does it prevent unecesary instantiation?
template<typename T >
struct is_pointer_to_function : mpl::and_<boost::is_pointer<T>, is_function<typename remove_pointer<T>::type> >
{};

BOOST_MPL_ASSERT((is_pointer_to_function<long (*)(double, int)>));

BOOST_MPL_ASSERT_NOT((is_pointer_to_function<long (double, int)>));

//is_reference_to_function_pointer
template<typename T >
struct is_reference_to_function_pointer : mpl::and_<boost::is_reference<T>, is_pointer_to_function<typename remove_reference<T>::type> >
{};

BOOST_MPL_ASSERT((is_reference_to_function_pointer<long (*&)(double, int)>));

BOOST_MPL_ASSERT_NOT((is_reference_to_function_pointer<long (*)(double, int)>));

//is_reference_to_non_const
template<typename T >
struct is_reference_to_non_const : mpl::and_<boost::is_reference<T>, mpl::not_<is_const<typename remove_reference<T>::type> > >
{};

BOOST_MPL_ASSERT((is_reference_to_non_const<int&>));

BOOST_MPL_ASSERT_NOT((is_reference_to_non_const<const int>));

BOOST_MPL_ASSERT_NOT((is_reference_to_non_const<const int&>));

//4.5
/*
template <class Container, class Value>
typename Container::iterator
container_find(Container& c, Value const& v)
{
	return std::find(c.begin(), c.end(), v);
}
*/

template <class Container, class Value>
typename mpl::if_<is_const<Container>, typename Container::const_iterator, typename Container::iterator>::type
container_find(Container& c, Value const& v)
{
	return std::find(c.begin(), c.end(), v);
}


void dumpList(std::list<int>& list)
{
	std::list<int>::iterator pos1 = container_find(list, 12);

	std::cout << *pos1 << std::endl;

	std::list<int>::iterator pos2 = container_find(list, 23);

	std::cout << *pos2 << std::endl;
	
	std::list<int>::iterator pos3 = container_find(list, 34);

	std::cout << *pos3 << std::endl;
	
	std::list<int>::iterator pos4 = container_find(list, 45);

	std::cout << *pos4 << std::endl;
}

void dumpConstList(const std::list<int>& list)
{
	std::list<int>::const_iterator pos1 = container_find(list, 12);

	std::cout << *pos1 << std::endl;

	std::list<int>::const_iterator pos2 = container_find(list, 23);

	std::cout << *pos2 << std::endl;
	
	std::list<int>::const_iterator pos3 = container_find(list, 34);

	std::cout << *pos3 << std::endl;
	
	std::list<int>::const_iterator pos4 = container_find(list, 45);
	
	std::cout << *pos4 << std::endl;
}

void ch4()
{
	std::list<int> myList;
	myList.push_back(12);
	myList.push_back(23);
	myList.push_back(34);
	myList.push_back(45);

	dumpList(myList);

	dumpConstList(myList);
}