#pragma once


#include <iterator>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include "stdafx.h"
#include <boost/iterator/iterator_facade.hpp>


//given an Iterator that points to a container, get the 
//value_type of that container's iterators
#if 0
template <class Iterator>
struct inner_value
	: boost::iterator_value<
	typename boost::iterator_value<Iterator>::type::iterator
	>
{};
#endif

template <class Iterator>
struct get_nested_iterator : boost::iterator_value<Iterator>::type::iterator
{
	//typedef typename boost::iterator_value<Iterator>::type::iterator type;
};

template <class Iterator>
struct inner_value : boost::mpl::eval_if<
											boost::is_arithmetic<
												typename boost::iterator_value<Iterator>::type
											>,
											typename boost::iterator_value<Iterator>,
											inner_value<
														get_nested_iterator<Iterator>
											>
										>
{};


//if Iterator refers to an arithmetic type, then that type becomes the return type of "sum"
//otherwise, there is no return type and "sum" not defined for that template argument
//it will be defined later
template <class Iterator>
typename boost::enable_if<
							boost::is_arithmetic<     //enabling condition
												typename boost::iterator_value<Iterator>::type
												>
						  , typename boost::iterator_value<Iterator>::type
						>::type

sum(Iterator start, Iterator end)
{
	typename boost::iterator_value<Iterator>::type x(0);

	for (; start != end; ++start)
		x += *start;

	return x;
}





//if Iterator refers to an arithmetic type, then the return type of sum is NOT defined.
//otherwise, we define sum as the "inner_value" of Iterator.  "inner_value" should recurse
//till it finds an arithmetic type.
template <class Iterator>
typename boost::lazy_disable_if<
	boost::is_arithmetic<     //disabling condition
		typename boost::iterator_value<Iterator>::type
		>
	, inner_value<Iterator>  //result metafunction
>::type
sum(Iterator start, Iterator end)
{
	typename inner_value<Iterator>::type x(0);

	for (; start != end; ++start)
		x += sum(start->begin(), start->end());

	return x;
}


