#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/iterator_range.hpp>

template <class RandomIterator, class ForwardIterator>
struct permutation_iterator
{
	typedef boost::mpl::forward_iterator_tag category;
	typedef RandomIterator myRandomIterator;
	typedef ForwardIterator myForwardIterator;
};

namespace boost { namespace mpl {

	//forward iterator requirement
	template <class RandomIterator, class ForwardIterator>
	struct next<
				permutation_iterator<RandomIterator, 
									 ForwardIterator> 
				> 
	{
		typedef permutation_iterator<
	    							RandomIterator,
									typename mpl::next<ForwardIterator>::type
									> type;
	};
/*
	template <class RandomIterator, class ForwardIterator>
	struct prior<
				permutation_iterator<RandomIterator, 
									 ForwardIterator> 
				> 
	{
		typedef permutation_iterator<
	    							RandomIterator,
									typename mpl::prior<ForwardIterator>::type
									> type;
	};*/

	template <class RandomIterator, class ForwardIterator>
	struct deref<
				permutation_iterator<RandomIterator, 
									 ForwardIterator> 
				> 
	{
		typedef typename boost::mpl::advance<
											RandomIterator, 
											typename boost::mpl::deref<ForwardIterator>::type
											>::type BaseIterator;

		typedef typename boost::mpl::deref<BaseIterator>::type type;
	};
}}

template <class Indices, class Sequence>
struct permutation_view : boost::mpl::iterator_range<
														permutation_iterator<
																			 typename boost::mpl::begin<Sequence>::type,
																			 typename boost::mpl::begin<Indices>::type
																			>,
														permutation_iterator<
																			 typename boost::mpl::begin<Sequence>::type,
																			 typename boost::mpl::end<Indices>::type
																			>
													>
{};


	