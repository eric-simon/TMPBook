#ifndef _SMALLEST_H
#define _SMALLEST_H

#include <boost\mpl\copy.hpp>
#include <boost\mpl\fold.hpp>
#include <boost\mpl\front.hpp>
#include <boost\mpl\push_back.hpp>
#include <boost\mpl\placeholders.hpp>
#include <boost\mpl\inserter.hpp>
#include <boost\mpl\min.hpp>

using namespace boost;

template <class T1, class T2>
struct is_smaller
{
	static const bool T1smaller = sizeof(T1) < sizeof(T2); 
};

template <class T1, class T2, bool T1smaller>
struct smaller_type_impl
{};

template <class T1, class T2>
struct smaller_type_impl<T1, T2, true>
{
	typedef T1 type;
};

template <class T1, class T2>
struct smaller_type_impl<T1, T2, false>
{
	typedef T2 type;
};

template <class T1, class T2>
struct smaller_type : smaller_type_impl<T1,T2,is_smaller<T1,T2>::T1smaller>
{};

BOOST_MPL_ASSERT((is_same<
						smaller_type<char,int>::type,
						char
						>));


BOOST_MPL_ASSERT((is_same<
							mpl::min<
									mpl::int_<1>,
									mpl::int_<2>
									>::type,
						mpl::int_<1>
						>));

template <class SmallestType>
struct smallest_ins : mpl::inserter<
					SmallestType,
					smaller_type<mpl::_1,mpl::_2> 
					>
{};

template <class Seq>
struct smallest : mpl::copy<Seq, 
						    smallest_ins<typename mpl::front<Seq>::type> 
                           >
{};

template <class Seq>
struct smallest_using_fold : mpl::fold<
							typename mpl::pop_front<Seq>::type, 
						    typename mpl::front<Seq>::type,
							smaller_type<mpl::_1,mpl::_2> 
                           >
{};

template <class Seq>
struct smallest2 : mpl::copy<typename mpl::pop_front<Seq>::type, 
						    smallest_ins<typename mpl::front<Seq>::type> 
                           >
{};

#endif