#pragma once
#include <boost\mpl\transform.hpp>
#include <boost\mpl\placeholders.hpp>
#include <boost\mpl\iterator_range.hpp>
#include <boost\mpl\eval_if.hpp>
#include <boost\mpl\contains.hpp>
#include <boost\mpl\transform.hpp>
#include <boost\mpl\transform_view.hpp>
#include <boost\mpl\joint_view.hpp>

template <class CategorySeq>
struct least_refined_category : boost::mpl::eval_if<
											   boost::mpl::contains<CategorySeq, boost::mpl::forward_iterator_tag>,
											   boost::mpl::identity<boost::mpl::forward_iterator_tag>,
											   boost::mpl::eval_if<
															  boost::mpl::contains<CategorySeq, boost::mpl::bidirectional_iterator_tag>,
															  boost::mpl::identity<boost::mpl::bidirectional_iterator_tag>,
															  boost::mpl::identity<boost::mpl::random_access_iterator_tag>
																>
													>
{};


template <class IteratorSeq>
struct iterator_category_view : boost::mpl::transform_view<
															IteratorSeq,
															boost::mpl::iterator_category<boost::mpl::_1>
														  >::type
{};

template <class IteratorSeq>
struct zip_iterator
{
	//typedef boost::mpl::forward_iterator_tag category;
	typedef typename least_refined_category<
									typename iterator_category_view<
															IteratorSeq
														 >::type
								   >::type category;

	typedef typename  boost::mpl::transform<
											IteratorSeq,
											boost::mpl::deref< boost::mpl::_1>
										>::type type;

	typedef IteratorSeq base;
};

namespace boost {namespace mpl
{
	//specialize next<...> for zip_iterator
	template <class IteratorSeq>
	struct next< ::zip_iterator<IteratorSeq> >
	{
		typedef ::zip_iterator<
								typename transform<
									IteratorSeq,
									next< boost::mpl::_1>
								>::type
							  > type;
	};

	//specialize prior<...> for zip_iterator
	template <class IteratorSeq>
	struct prior< ::zip_iterator<IteratorSeq> >
	{
		typedef ::zip_iterator<
								typename transform<
									IteratorSeq,
									prior< boost::mpl::_1>
								>::type
							  > type;
	};

	//specialize advance<...> for zip_iterator
	template <class IteratorSeq, class N>
	struct advance< ::zip_iterator<IteratorSeq>, N>
	{
		typedef ::zip_iterator<
								typename transform<
									IteratorSeq,
									advance< boost::mpl::_1, N>
								>::type
							  > type;
	};
}}

template <class Sequences>
struct zip_view : boost::mpl::iterator_range<
											typename zip_iterator<
												typename boost::mpl::transform<
																				Sequences,
																				boost::mpl::begin<boost::mpl::_1>
																			  >::type
												>,
											typename zip_iterator<
												typename boost::mpl::transform<
																				Sequences,
																				boost::mpl::end<boost::mpl::_1>
																			  >::type
												>
										>
{};



template <class Sequence, class Iterator>
struct rotate_view : boost::mpl::joint_view<
											typename boost::mpl::iterator_range<
																			   Iterator,
																			   typename boost::mpl::end<Sequence>::type
																			  >::type, 
											typename boost::mpl::iterator_range<
																				typename boost::mpl::begin<Sequence>::type,
																				Iterator
																			  >::type>
{};

