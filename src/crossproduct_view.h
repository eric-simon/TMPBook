#pragma once

#include <boost/mpl/empty.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>


template <class Item1, class Seq2>
struct partial_crossproduct_f : boost::mpl::transform<
														Seq2,
														boost::mpl::pair<Item1, boost::mpl::_1>
													>
{
};

template <class Item1, class Seq2>
struct partial_crossproduct_view : partial_crossproduct_f<Item1, Seq2>::type
{
};
/*
template <class Seq1, class Seq2>
struct crossproduct_view : boost::mpl::transform<
													Seq1,
													partial_crossproduct_f<boost::mpl::_1, Seq2>
												>::type
{
};*/

template <class Seq>
struct safe_pop : boost::mpl::eval_if<					//if seq2remaining is empty, reset it to seq2 and advance Seq1
										boost::mpl::empty<Seq>,
										boost::mpl::identity<Seq>,
										boost::mpl::pop_front<Seq>
									>
{};

template <class Seq>
struct safe_front : boost::mpl::eval_if<					//if seq2remaining is empty, reset it to seq2 and advance Seq1
	boost::mpl::empty<Seq>,
	boost::mpl::identity<Seq>,
	boost::mpl::front<Seq>
>
{};

template <class Seq, class Item>
struct safe_push : boost::mpl::push_back<Seq, Item>
{};


template <class Seq1, class Seq1Remaining, class Seq2, class Seq2Remaining, class OutputSequence>
struct crossproduct_view_impl : boost::mpl::eval_if<										//if seq1remaining is empty, return
													boost::mpl::empty<Seq1Remaining>,
													boost::mpl::identity<OutputSequence>,
													boost::mpl::eval_if<					//if seq2remaining is empty, reset it to seq2 and advance Seq1
																		boost::mpl::empty<Seq2Remaining>,
																		crossproduct_view_impl<Seq1, 
																							   typename safe_pop<Seq1Remaining>::type,
																							   Seq2, 
																							   Seq2, 
																							   OutputSequence>,
																		crossproduct_view_impl<Seq1, 
																							   Seq1Remaining,
																							   Seq2, 
																							   typename safe_pop<Seq2Remaining>::type,
																							   typename safe_push<OutputSequence,
																													 typename boost::mpl::pair<
																																	  typename safe_front<Seq1Remaining>::type,
																																	  typename safe_front<Seq2Remaining>::type
																																	>::type
																													>::type
																							   >
																		>               
												>
{
};


template <class Seq1, class Seq2>
struct crossproduct_view : crossproduct_view_impl<Seq1, Seq1, Seq2, Seq2, boost::mpl::vector<> >::type
{
};
