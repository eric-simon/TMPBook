#pragma once

#include <boost\mpl\eval_if.hpp>
#include <boost\mpl\empty.hpp>
#include <boost\mpl\at.hpp>
#include <boost\mpl\begin.hpp>
#include <boost\mpl\iterator_tags.hpp>
#include <boost\mpl\distance.hpp>
#include <boost\mpl\size.hpp>
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_front.hpp>
#include <boost\mpl\push_back.hpp>
#include <boost\mpl\pop_back.hpp>
#include <boost\mpl\insert.hpp>
#include <boost\mpl\erase.hpp>
#include <boost\mpl\aux_\na_fwd.hpp>
#include <boost\mpl\reverse_fold.hpp>

#if 0

template <unsigned long N>
struct binary
{
	BOOST_STATIC_ASSERT(N%10 < 2);

	static unsigned const value
		= binary<N/10>::value * 2
		  + N%10;
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
};

#endif

struct none {}; //tag type to denote no element

struct binary_tag {};

template <unsigned int N>
struct binary_sequence
{
	typedef binary_tag tag;
	typedef binary_sequence type;
	const static unsigned int n = N;
};

template <unsigned int N>
struct binary_iterator
{
	BOOST_STATIC_ASSERT(N%10 < 2);

	static unsigned int const digit = N%10;

	typedef binary_iterator type;

	static unsigned int const remainder = N/10;

};


namespace boost { namespace mpl {

	//forward iterator requirement
	template <unsigned int N>
	struct next<binary_iterator<N> >
	{
		typedef binary_iterator<
								binary_iterator<N>::remainder
								> type;
	};

	template <unsigned int N>
	struct deref< binary_iterator<N> >
	{
		typedef int_<binary_iterator<N>::digit> type;
	};

	template<>
	struct begin_impl<binary_tag>
	{
		template <class binary_sequence>
		struct apply
		{
			typedef binary_iterator<binary_sequence::n> type;
		};
	};

	template <>
	struct end_impl<binary_tag>
	{
		template <class binary_sequence>
		struct apply
		{
			typedef binary_iterator<0> type;
		};
	};
	
	template <unsigned int N>
	struct binary : mpl::reverse_fold<
								binary_sequence<N>, 
								int_<0>,
								mpl::plus<mpl::times<_1,int_<2> >, _2>
									>
	{};
	
}}