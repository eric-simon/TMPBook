#pragma once

#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/iterator_range.hpp>

template <class BidirectionalIterator>
struct reverse_iterator
{
	typedef boost::mpl::bidirectional_iterator_tag category;
};

namespace boost {
	namespace mpl {

		//forward iterator requirement
		template <class BidirectionalIterator>
		struct next<reverse_iterator<BidirectionalIterator>	>
		{
			typedef reverse_iterator<
				typename prior<BidirectionalIterator>::type
			> type;
		};
		
		//bidirectional iterator requirement
		template <class BidirectionalIterator>
		struct prior<reverse_iterator<BidirectionalIterator>	>
		{
			typedef reverse_iterator<
				typename next<BidirectionalIterator>::type
			> type;
		};
		
		template <class BidirectionalIterator>
		struct deref<
			reverse_iterator<BidirectionalIterator>
		>
		{
			typedef typename boost::mpl::prior<
												BidirectionalIterator
											   >::type BaseIterator;

			typedef typename boost::mpl::deref<BaseIterator>::type type;
		};
	}
}

template <class Sequence>
struct reverse_view : boost::mpl::iterator_range<
		reverse_iterator<
						typename boost::mpl::end<Sequence>::type
						>,
		reverse_iterator<
						typename boost::mpl::begin<Sequence>::type
						>
>
{};
