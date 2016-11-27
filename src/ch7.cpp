#include "stdafx.h"
#include "zip_view.h"
#include "permutation_iterator.h"
#include "reverse_iterator.h"
#include "crossproduct_view.h"
#include <boost\mpl\vector_c.hpp>
#include <boost\mpl\list_c.hpp>
#include <boost\mpl\vector.hpp>
#include <boost\mpl\equal.hpp>
#include <boost\static_assert.hpp>
#include <boost\mpl\range_c.hpp>
#include <boost\mpl\char.hpp>
#include <boost\mpl\list.hpp>

typedef boost::mpl::vector_c<int, 1, 2, 3> v1;
typedef boost::mpl::vector_c<int, 4, 5, 6> v2;
typedef boost::mpl::vector_c<int, 7, 8, 9> v3;

typedef zip_view<boost::mpl::vector<v1,v2,v3> > result;

BOOST_MPL_ASSERT((boost::is_same<
								boost::mpl::iterator_category<result::begin>::type,
								boost::mpl::random_access_iterator_tag
								>
								));

BOOST_MPL_ASSERT((boost::is_same<
								boost::mpl::iterator_category<result::end>::type,
								boost::mpl::random_access_iterator_tag
								>
								));


typedef boost::mpl::begin<result>::type IteratorsOne;

typedef boost::mpl::deref<IteratorsOne>::type SequenceOne;

typedef boost::mpl::next<IteratorsOne>::type IteratorsTwo;

typedef boost::mpl::prior<IteratorsTwo>::type IteratorsOneAlso;

typedef boost::mpl::deref<IteratorsOneAlso>::type SequenceOneAlso;

typedef boost::mpl::deref<IteratorsTwo>::type SequenceTwo;

typedef boost::mpl::next<IteratorsTwo>::type IteratorsThree;

typedef boost::mpl::advance<IteratorsOne,boost::mpl::int_<2>>::type IteratorsThreeAlso;

typedef boost::mpl::prior<IteratorsThree>::type IteratorsTwoAlso;

typedef boost::mpl::deref<IteratorsTwoAlso>::type SequenceTwoAlso;

typedef boost::mpl::deref<IteratorsThree>::type SequenceThree;

typedef boost::mpl::deref<IteratorsThreeAlso>::type SequenceThreeAlso;


BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceOne,
								SequenceOneAlso
									>::value));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceTwo,
								SequenceTwoAlso
									>::value));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceOne,
								boost::mpl::vector_c<int,1,4,7>
									>::value));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceTwo,
								boost::mpl::vector_c<int,2,5,8>
									>::value));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceThree,
								boost::mpl::vector_c<int,3,6,9>
									>::value));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								SequenceThree,
								SequenceThreeAlso
									>::value));

BOOST_STATIC_ASSERT((boost::mpl::distance<IteratorsOne, IteratorsThree>::type::value == 2));

typedef boost::mpl::vector<boost::mpl::forward_iterator_tag, boost::mpl::bidirectional_iterator_tag, boost::mpl::random_access_iterator_tag> AllCategories;

typedef boost::mpl::vector<boost::mpl::bidirectional_iterator_tag, boost::mpl::random_access_iterator_tag> BiAndRandomCategories;

typedef boost::mpl::vector<boost::mpl::random_access_iterator_tag> RandomCategories;


BOOST_MPL_ASSERT((boost::is_same<
								least_refined_category<AllCategories>::type,
								boost::mpl::forward_iterator_tag
								>
								));

BOOST_MPL_ASSERT((boost::is_same<
								least_refined_category<BiAndRandomCategories>::type,
								boost::mpl::bidirectional_iterator_tag
								>
								));

BOOST_MPL_ASSERT((boost::is_same<
								least_refined_category<RandomCategories>::type,
								boost::mpl::random_access_iterator_tag
								>
								));

typedef boost::mpl::vector_c<int, 2, 5, 8> RandomAccess1;
typedef boost::mpl::vector_c<int, 3, 5, 8> RandomAccess2;
typedef boost::mpl::vector_c<int, 6, 5, 8> RandomAccess3;

BOOST_MPL_ASSERT((boost::is_same<
								boost::mpl::iterator_category<RandomAccess1::begin>::type,
								boost::mpl::random_access_iterator_tag
								>
								));

typedef boost::mpl::list_c<int, 3, 4, 7> Forward1;
typedef boost::mpl::list_c<int, 5, 4, 7> Forward2;
typedef boost::mpl::list_c<int, 7, 4, 7> Forward3;


typedef boost::mpl::vector<RandomAccess1,Forward1,Forward1> ForwardExpected1;
typedef boost::mpl::vector<RandomAccess1,RandomAccess2,RandomAccess3> RandomExpected1;



typedef zip_view<ForwardExpected1> ForwardExpectedResult;

typedef zip_view<RandomExpected1> RandomExpectedResult;

BOOST_MPL_ASSERT((boost::is_same<
								boost::mpl::iterator_category<ForwardExpectedResult::begin>::type,
								boost::mpl::forward_iterator_tag
								>
								));

BOOST_MPL_ASSERT((boost::is_same<
								boost::mpl::iterator_category<RandomExpectedResult::begin>::type,
								boost::mpl::random_access_iterator_tag
								>
								));

typedef boost::mpl::vector_c<int, 5,6,7,8,9,0,1,2,3,4> v;

typedef rotate_view<
					v,
					boost::mpl::advance_c<boost::mpl::begin<v>::type,5>::type
				   > view;


typedef boost::mpl::iterator_range<
							typename boost::mpl::advance_c<boost::mpl::begin<v>::type,5>::type,
							typename boost::mpl::end<v>::type
							>::type SecondHalf;

typedef boost::mpl::iterator_range<
									typename boost::mpl::begin<v>::type,
									typename boost::mpl::advance_c<
																	boost::mpl::begin<v>::type,5
																   >::type
								  >::type FirstHalf;

BOOST_STATIC_ASSERT((boost::mpl::begin<SecondHalf>::type::type::value == 0));
BOOST_STATIC_ASSERT((boost::mpl::prior<boost::mpl::end<SecondHalf>::type>::type::type::value == 4));

BOOST_STATIC_ASSERT((boost::mpl::begin<FirstHalf>::type::type::value == 5));
BOOST_STATIC_ASSERT((boost::mpl::prior<boost::mpl::end<FirstHalf>::type>::type::type::value == 9));


BOOST_STATIC_ASSERT((boost::mpl::equal<
								view,
								boost::mpl::range_c<int,0,10>
								>::value));

typedef boost::mpl::list_c<int,2,1,3,0,2> indices;

typedef boost::mpl::vector_c<int,11,22,33,44> sourceSeq;

typedef boost::mpl::begin<sourceSeq>::type elementIter;

typedef boost::mpl::begin<indices>::type indicesIter1;
typedef boost::mpl::next<indicesIter1>::type indicesIter2;
typedef boost::mpl::next<indicesIter2>::type indicesIter3;
typedef boost::mpl::next<indicesIter3>::type indicesIter4;
typedef boost::mpl::next<indicesIter4>::type indicesIter5;
typedef boost::mpl::end<indices>::type indicesIterEnd;

typedef permutation_iterator<elementIter, indicesIter1> permIter1;
typedef boost::mpl::next<permIter1>::type permIter2;
typedef boost::mpl::next<permIter2>::type permIter3;
typedef boost::mpl::next<permIter3>::type permIter4;
typedef boost::mpl::next<permIter4>::type permIter5;

typedef permutation_iterator<elementIter, indicesIterEnd> permIterEnd;

typedef boost::mpl::iterator_range<permIter1,permIterEnd> transformedSequence;

typedef boost::mpl::list_c<int,33,22,44,11,33> expectedView;

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								transformedSequence,
								expectedView
									>::value));


//typedef boost::mpl::prior<permIterEnd>::type permIterNextToEnd;

//BOOST_STATIC_ASSERT((boost::mpl::deref<permIterNextToEnd>::type::value == 44));

BOOST_STATIC_ASSERT((boost::mpl::deref<elementIter>::type::value == 11));

BOOST_STATIC_ASSERT((boost::mpl::deref<indicesIter1>::type::value == 2));

BOOST_STATIC_ASSERT((boost::mpl::deref<permutation_iterator<elementIter, indicesIter1>>::type::value == 33));
BOOST_STATIC_ASSERT((boost::mpl::deref<permutation_iterator<elementIter, indicesIter2>>::type::value == 22));
BOOST_STATIC_ASSERT((boost::mpl::deref<permutation_iterator<elementIter, indicesIter3>>::type::value == 44));
BOOST_STATIC_ASSERT((boost::mpl::deref<permutation_iterator<elementIter, indicesIter4>>::type::value == 11));
BOOST_STATIC_ASSERT((boost::mpl::deref<permutation_iterator<elementIter, indicesIter5>>::type::value == 33));

BOOST_STATIC_ASSERT((boost::mpl::deref<permIter1>::type::value == 33));
BOOST_STATIC_ASSERT((boost::mpl::deref<permIter2>::type::value == 22));
BOOST_STATIC_ASSERT((boost::mpl::deref<permIter3>::type::value == 44));
BOOST_STATIC_ASSERT((boost::mpl::deref<permIter4>::type::value == 11));
BOOST_STATIC_ASSERT((boost::mpl::deref<permIter5>::type::value == 33));

//typedef boost::mpl::list_c<int,2,1,3,0,2> indices;

//typedef boost::mpl::vector_c<int,11,22,33,44> sourceSeq;

typedef permutation_view<
				indices,
				sourceSeq
				> transformedView;

//typedef boost::mpl::list_c<int,33,22,44,11,33> expectedView;

BOOST_STATIC_ASSERT(( boost::mpl::equal<
								transformedView,
								expectedView
									>::value));


//typedef boost::mpl::vector_c<int, 11, 22, 33, 44> sourceSeq;

typedef reverse_iterator<
						boost::mpl::end<sourceSeq>::type 
						> elementRevIter4;

typedef boost::mpl::next<elementRevIter4>::type elementRevIter3;
typedef boost::mpl::next<elementRevIter3>::type elementRevIter2;
typedef boost::mpl::next<elementRevIter2>::type elementRevIter1;



BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter4>::type::value == 44));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter3>::type::value == 33));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter2>::type::value == 22));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter1>::type::value == 11));

typedef reverse_iterator<
	boost::mpl::next<boost::mpl::begin<sourceSeq>::type>::type
> elementRevIter1A;

typedef boost::mpl::prior<elementRevIter1A>::type elementRevIter2A;
typedef boost::mpl::prior<elementRevIter2A>::type elementRevIter3A;
typedef boost::mpl::prior<elementRevIter3A>::type elementRevIter4A;


BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter1A>::type::value == 11));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter2A>::type::value == 22));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter3A>::type::value == 33));
BOOST_STATIC_ASSERT((boost::mpl::deref<elementRevIter4A>::type::value == 44));


typedef boost::mpl::list_c<int,44,33,22,11> expectedReverseView;

typedef reverse_view<sourceSeq> actualReverseView;

typedef boost::mpl::begin<actualReverseView>::type first;

BOOST_STATIC_ASSERT((boost::mpl::deref<first>::type::value == 44));
BOOST_STATIC_ASSERT((boost::mpl::deref<boost::mpl::next<first>::type>::type::value == 33));
BOOST_STATIC_ASSERT((boost::mpl::deref<boost::mpl::next<boost::mpl::next<first>::type>::type>::type::value == 22));
BOOST_STATIC_ASSERT((boost::mpl::deref<boost::mpl::next<boost::mpl::next<boost::mpl::next<first>::type>::type>::type>::type::value == 11));

BOOST_STATIC_ASSERT((boost::mpl::equal<
	actualReverseView,
	expectedReverseView
>::value));

BOOST_MPL_ASSERT((boost::is_same<boost::mpl::iterator_category<first>::type,
								 boost::mpl::bidirectional_iterator_tag>));


///////
typedef boost::mpl::list<boost::mpl::char_<'x'>, boost::mpl::char_<'y'>, boost::mpl::char_<'z'> > view_one;
typedef boost::mpl::vector<boost::mpl::int_<1>, boost::mpl::int_<2>, boost::mpl::int_<3>, boost::mpl::int_<4> > view_two;

typedef boost::mpl::char_<'x'> item_one;

typedef boost::mpl::vector<boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<1> >,
						 boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<2> >,
						 boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<3> >,
						 boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<4> >
						> expectedPartialCrossProduct;

typedef partial_crossproduct_view<item_one, view_two> actualPartialCrossProduct;

BOOST_STATIC_ASSERT((boost::mpl::equal<
	actualPartialCrossProduct,
	expectedPartialCrossProduct
>::value));

//////////


typedef boost::mpl::vector<boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<1> >,
					     boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<2> >,
						 boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<3> >,
						 boost::mpl::pair<boost::mpl::char_<'x'>, boost::mpl::int_<4> >,

						 boost::mpl::pair<boost::mpl::char_<'y'>, boost::mpl::int_<1> >,
						 boost::mpl::pair<boost::mpl::char_<'y'>, boost::mpl::int_<2> >,
						 boost::mpl::pair<boost::mpl::char_<'y'>, boost::mpl::int_<3> >,
						 boost::mpl::pair<boost::mpl::char_<'y'>, boost::mpl::int_<4> >,

						 boost::mpl::pair<boost::mpl::char_<'z'>, boost::mpl::int_<1> >,
						 boost::mpl::pair<boost::mpl::char_<'z'>, boost::mpl::int_<2> >,
						 boost::mpl::pair<boost::mpl::char_<'z'>, boost::mpl::int_<3> >,
						 boost::mpl::pair<boost::mpl::char_<'z'>, boost::mpl::int_<4> >

							> expectedCrossProduct;

typedef crossproduct_view<view_one, view_two> actualCrossProduct;


BOOST_STATIC_ASSERT((boost::mpl::equal<
	actualCrossProduct,
	expectedCrossProduct
>::value));


typedef boost::mpl::push_front< 
								boost::mpl::vector<
													boost::mpl::char_<'a'>
													>::type
								>::type seq2;

typedef boost::mpl::begin<actualCrossProduct>::type firstIter;

typedef boost::mpl::next<firstIter>::type secondIter;

typedef boost::mpl::next<secondIter>::type thirdIter;

typedef boost::mpl::next<thirdIter>::type fourthIter;

typedef boost::mpl::next<fourthIter>::type fifthIter;

//i think we created a sequence of sequences


BOOST_STATIC_ASSERT((boost::mpl::deref<firstIter>::type::first::value == 'x'));
BOOST_STATIC_ASSERT((boost::mpl::deref<firstIter>::type::second::value == 1));

BOOST_STATIC_ASSERT((boost::mpl::deref<secondIter>::type::first::value == 'x'));
BOOST_STATIC_ASSERT((boost::mpl::deref<secondIter>::type::second::value == 2));

BOOST_STATIC_ASSERT((boost::mpl::deref<thirdIter>::type::first::value == 'x'));
BOOST_STATIC_ASSERT((boost::mpl::deref<thirdIter>::type::second::value == 3));

BOOST_STATIC_ASSERT((boost::mpl::deref<fourthIter>::type::first::value == 'x'));
BOOST_STATIC_ASSERT((boost::mpl::deref<fourthIter>::type::second::value == 4));

BOOST_STATIC_ASSERT((boost::mpl::deref<fifthIter>::type::first::value == 'y'));
BOOST_STATIC_ASSERT((boost::mpl::deref<fifthIter>::type::second::value == 1));


/*
typedef boost::mpl::begin<actualCrossProduct>::type beginActual;

typedef boost::mpl::deref<beginActual>::type firstActual;

typedef boost::mpl::deref<boost::mpl::next<firstActual>::type>::type secondActual;

typedef boost::mpl::deref<boost::mpl::next<secondActual>::type>::type thirdActual;

typedef boost::mpl::deref<boost::mpl::next<thirdActual>::type>::type fourthActual;

typedef boost::mpl::deref<boost::mpl::next<fourthActual>::type>::type fifthActual;

//i think we created a sequence of sequences


BOOST_STATIC_ASSERT((firstActual::item::first::value == 'x'));

BOOST_STATIC_ASSERT((firstActual::item::second::value == 1));

BOOST_STATIC_ASSERT((secondActual::item::first::value == 'x'));

BOOST_STATIC_ASSERT((secondActual::item::second::value == 2));

BOOST_STATIC_ASSERT((thirdActual::item::first::value == 'x'));

BOOST_STATIC_ASSERT((thirdActual::item::second::value == 3));

BOOST_STATIC_ASSERT((fourthActual::item::first::value == 'x'));

BOOST_STATIC_ASSERT((fourthActual::item::second::value == 4));

BOOST_STATIC_ASSERT((boost::mpl::deref<boost::mpl::next<beginActual>::type>::type::item::first::value == 'y'));

BOOST_STATIC_ASSERT((boost::mpl::deref<boost::mpl::next<beginActual>::type>::type::item::second::value == 1));
*/