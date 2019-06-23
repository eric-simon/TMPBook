// MPL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>
#include "assert.h"
#include <iostream>
#include <string>
#include <vector>
#include "ch3.h"
#include "binary.h"
#include "boost/mpl/equal_to.hpp"
#include <boost/core/enable_if.hpp>

using namespace boost::mpl;

namespace mpl = boost::mpl;

template <class F, class T>
struct twice : apply1<F, typename apply1<F,T>::type>
{};


template <class X>
struct two_pointers : twice<boost::add_pointer<_1>, X>
{};

template <class X>
struct four_pointers1 : twice<  twice<typename lambda<boost::add_pointer<_1> >::type, _1>, X>
{};

template <class X>
struct four_pointers2 : twice<two_pointers<_1>, X>
{};

template <class X>
struct four_pointers3: twice<boost::add_pointer<_1>, typename twice<boost::add_pointer<_1>, X>::type>
{};

template <class X>
struct four_pointers4
{
	typedef typename twice<boost::add_pointer<_1>, X>::type two_ptr;

	typedef typename twice<boost::add_pointer<_1>, two_ptr>::type type;
};

typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> null;
typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;

typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;
typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;

template <class T, class Dimensions>
struct quantity
{

	explicit quantity(T x)
		: m_value(x)
	{}

	T value() const { return m_value; }

	template <class OtherDimensions>
	quantity(quantity<T, OtherDimensions> const& rhs) : m_value(rhs.value())
	{
		BOOST_STATIC_ASSERT((mpl::equal<Dimensions, OtherDimensions>::type::value));
	}

private:
		T m_value;
};

#if 0
template <class T, class D>
quantity<T, D> operator+(quantity<T,D> x, quantity<T,D> y)
{
	return quantity<T, D>(x.value() + y.value());
}
#endif

#if 0
template <class T, class D1, class D2>
quantity<T, D1> operator+(quantity<T,D1> x, quantity<T,D2> y)
{
	BOOST_STATIC_ASSERT((mpl::equal<D1, D2>::type::value));

	return quantity<T, D1>(x.value() + y.value());
}
#endif

template <class T, class D1, class D2>
typename boost::enable_if<
							typename mpl::equal<D1, D2>::type
						  , quantity<T, D1>
						>::type

operator+(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, D1>(x.value() + y.value());
}

template <class T, class D1, class D2>
bool operator==(quantity<T, D1> x, quantity<T, D2> y)
{
	BOOST_STATIC_ASSERT((mpl::equal<D1, D2>::type::value));

	return (x.value() == y.value());
}

template <class D1, class D2>
struct multiply_dimensions : mpl::transform<D1, D2, mpl::plus<_1, _2> >
{};

template <class T, class D1, class D2>
quantity<T, typename multiply_dimensions<D1, D2>::type> operator*(quantity<T,D1> x, quantity<T,D2> y)
{
	return quantity<T, typename multiply_dimensions<D1, D2>::type>(x.value() * y.value());
}


template <class T, class D1, class D2>
quantity<T, D1> operator-(quantity<T,D1> x, quantity<T,D2> y)
{
	BOOST_STATIC_ASSERT((mpl::equal<D1, D2>::type::value));

	return quantity<T, D1>(x.value() - y.value());
}

//
//build a lambda expression that has functionality equivalent to twice.  Hint: mpl::apply is a metafunction
//
struct twice_f
{
	template <class F, class X>
	struct apply
	{
		typedef typename apply1<F, typename apply1<F,X>::type>::type type;
	};

};

struct plus_f
{
	template <class T1, class T2>
	struct apply
	{
		typedef typename mpl::plus<T1, T2>::type type;
	};

};


int ch3(int argc, _TCHAR* argv[])
{
	typedef boost::mpl::vector_c<int,1,2,3> input1;
	typedef boost::mpl::vector_c<int,4,7,10> input2;

	BOOST_STATIC_ASSERT( (apply2<mpl::plus<_1, _2>, mpl::int_<23>, mpl::int_<42> >::type::value == 65) );

	BOOST_STATIC_ASSERT( (apply2<plus_f, mpl::int_<23>, mpl::int_<42> >::type::value == 65) );

	BOOST_STATIC_ASSERT( (twice_f::apply<mpl::plus<_1, _1>, mpl::int_<42> >::type::value == 168) );

	BOOST_STATIC_ASSERT( (mpl::apply<twice_f, mpl::plus<_1, _1>, mpl::int_<42> >::type::value == 168) );

	BOOST_STATIC_ASSERT((binary<0>::type::value == 0));
	BOOST_STATIC_ASSERT((binary<1>::type::value == 1));
	BOOST_STATIC_ASSERT((binary<10>::type::value == 2));
	BOOST_STATIC_ASSERT((binary<11>::type::value == 3));
	BOOST_STATIC_ASSERT((binary<100>::type::value == 4));
	BOOST_STATIC_ASSERT((binary<101>::type::value == 5));
	BOOST_STATIC_ASSERT((binary<110>::type::value == 6));
	BOOST_STATIC_ASSERT((binary<111>::type::value == 7));

	typedef boost::mpl::vector_c<int,1,2,3> test;

	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 0 >::type::value == 1 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 1 >::type::value == 2 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 2 >::type::value == 3 ) );

	typedef boost::mpl::transform<test, boost::mpl::plus<_1, int_<1> > >::type result1;

	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result1, 0 >::type::value == 2 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result1, 1 >::type::value == 3 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result1, 2 >::type::value == 4 ) );

	typedef boost::mpl::transform<test, boost::mpl::times<_1, _1> >::type result2;

	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result2, 0 >::type::value == 1 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result2, 1 >::type::value == 4 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< result2, 2 >::type::value == 9 ) );

	BOOST_STATIC_ASSERT(( boost::is_same<two_pointers<int>::type, int**>::value));

	BOOST_STATIC_ASSERT(( boost::is_same<four_pointers1<int>::type, int****>::value));

	BOOST_STATIC_ASSERT(( boost::is_same<four_pointers2<int>::type, int****>::value));

	BOOST_STATIC_ASSERT(( boost::is_same<four_pointers3<int>::type, int****>::value));

	BOOST_STATIC_ASSERT(( boost::is_same<four_pointers4<int>::type, int****>::value));

	//std::cout << binary<121>::value << std::endl;
	//std::cout << binary<2>::value << std::endl;
	//std::cout << binary<2101>::value << std::endl;



	quantity<float, length> len1( 1.0f);
	quantity<float, length> len2( 2.0f);

	quantity<float, length> len3( 0.0f);

	len3 = len1 + len2;

	quantity<float, velocity> v1( 4.0f);
	quantity<float, time> t1( 2.0f);

	quantity<float, length> d1( 0.0f);

	quantity<float, force> f1( 1.2f);

	quantity<float, force> f2( 0.0f);

	quantity<float, force> f3( 0.0f);

	quantity<float, mass> m1( 2.0f);

	quantity<float, acceleration> a1( 1.3f);

	quantity<float, force> expectedF2(2.6f);

	quantity<float, force> expectedF3(3.8f);

	//f3 + m1;
	
	d1 = v1 * t1;

	f2 = (m1 * a1);

	assert(f2 == expectedF2);

	f3 = f1 + f2;

	assert(f3 == expectedF3);
	
	f3 = f1 + (m1 * a1);

	f3 = f1 - (m1 * a1);

	f2 = f1 + m1 * a1;

	return 0;
}

//metafunction is a template class with an attribute called "type" which is the "return type" of the metafunction
//metafunction class is a class with an embedded metafunction called apply.  In other words, "apply" is a template class with type attribute

//metafunctions:
//mpl::apply<> : invokes the first argument (which must be a lambda expression) on the remaining arguments
//mpl::lambda<> : transforms the argument (a lambda expression) into a metafunction class.  In other words, the output class
//                     has an apply metafunction which takes template arguments, feeds them into the lambda expression, and generates the return type.

//example: mpl::lambda<boost::add_pointer<_> > takes the lambda expression boost::add_pointer<_1> and creates a class, which is available in type.  This class
//is a metafunction class, and apply<T> passes the argument T to add_pointer and returns the type T*
BOOST_STATIC_ASSERT((boost::is_same<mpl::lambda<boost::add_pointer<_>>::type::apply<int>::type, int *>::type::value));


//example: addptr_f2 is a metafunction class whose apply method takes a type, and feeds that type into the lambda expression (add_pointer<_>) and produces the output type.
typedef mpl::lambda<boost::add_pointer<_> >::type addptr_f2;

BOOST_STATIC_ASSERT((boost::is_same<addptr_f2::apply<int>::type, int *>::type::value));

typedef mpl::lambda<mpl::lambda<_1> >::type t1;
//working inside out...

//mpl::lambda<_1> takes a lambda expression _1, and produces a metafunction class that evaluates it
//in this example, mpl::lambda<boost::add_pointer<_> > generates a metafunction class that takes a single template argument T and produces the type T*
//
//T1 is a metafunction class whose apply metafunction takes the argument T and produces the above metafunction class and invokes it.

typedef t1::template apply<boost::add_pointer<_> >::type addptr_f;

BOOST_STATIC_ASSERT((boost::is_same<addptr_f::apply<int>::type, int *>::type::value));

BOOST_STATIC_ASSERT((boost::is_same<mpl::apply<addptr_f, int>::type, int *>::type::value));
//
//t1 is a metafunction class that takes a lambda expression and creates a class as follows:
//
//t1::apply<lambda<_1,_2...> >::type is the class
//
//struct t1_generated
//{
//	template <class T1, T2, T3...>
//	struct apply
//	{
//		typedef typename lambda<T1, T2, T3>::type type;
//	};
//};
//


struct t1_generated
{
	template <class T>
	struct apply
	{
		typedef typename boost::add_pointer<T>::type type;
	};
};

BOOST_STATIC_ASSERT((boost::is_same<t1_generated::apply<int>::type, int *>::type::value));



typedef mpl::plus<mpl::int_<23>, mpl::int_<42> >::type result;

BOOST_STATIC_ASSERT(result::value == 65);

typedef mpl::plus<_, mpl::int_<42> > result2;

BOOST_STATIC_ASSERT(mpl::apply<result2, mpl::int_<23> >::type::value == 65);




typedef mpl::apply<_1, mpl::plus<_1, _2> >::type t2;

//t2 is a lambda expression that adds the two arguments, _1 and _2
BOOST_STATIC_ASSERT((mpl::apply<t2, mpl::int_<23>, mpl::int_<42> >::type::value == 65));




typedef mpl::apply<_1, std::vector<int> >::type t3;
//t3 is just a std::vector<int>

BOOST_STATIC_ASSERT((boost::is_same<t3, std::vector<int> >::type::value));


typedef mpl::apply<_1, std::vector<_1> >::type t4;

//t4 is a lambda expression that creates a std::vector with its argument

BOOST_STATIC_ASSERT((boost::is_same<mpl::apply<t4, int>::type, std::vector<int> >::type::value));

typedef mpl::apply<mpl::lambda<_1>, std::vector<int> >::type t5;

//t5 is a std::vector<int>

BOOST_STATIC_ASSERT((boost::is_same<t5, std::vector<int> >::type::value));

typedef mpl::apply<mpl::lambda<_1>, std::vector<_1> >::type t6;

//t6 is a lambda expression that creates a std::vector of the argument type

BOOST_STATIC_ASSERT((boost::is_same<mpl::apply<t6, int>::type, std::vector<int> >::type::value));


typedef mpl::apply<mpl::lambda<_1>, mpl::plus<_1, _2> >::type t7;

//t7 is a lambda expression that adds _1 and _2

BOOST_STATIC_ASSERT((mpl::apply<t7, mpl::int_<23>, mpl::int_<42> >::type::value == 65));




typedef mpl::apply<_1,mpl::lambda< mpl::plus<_1, _2> > >::type t8;

BOOST_STATIC_ASSERT((mpl::apply<t8, mpl::int_<23>, mpl::int_<42> >::type::value == 65));

template <int n> struct factorial
{
	static unsigned const value = n * factorial<n-1>::value;
};

template <>
struct factorial<1>
{
	static unsigned const value = 1;
};

BOOST_STATIC_ASSERT((factorial<1>::value == 1));

BOOST_STATIC_ASSERT((factorial<2>::value == 2));

BOOST_STATIC_ASSERT((factorial<3>::value == 6));

BOOST_STATIC_ASSERT((factorial<4>::value == 24));