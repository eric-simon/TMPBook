#include "stdafx.h"
#include <boost/mpl/assert.hpp>
#include "boost/mpl/or.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/same_as.hpp"
#include "boost/mpl/vector_c.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/not_equal_to.hpp"
#include <boost/type_traits.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost\type_traits\is_array.hpp>


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
#include "boost/mpl/less.hpp"
#include "boost/mpl/less_equal.hpp"
#include "boost/mpl/greater_equal.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/back.hpp"
#include "boost/mpl/multiplies.hpp"
#include "boost/mpl/divides.hpp"
#include "boost/mpl/minus.hpp"

#include <list>
#include <iostream>
#include <algorithm>
#include "ch3.h"
#include "tiny.h"
#include "fibonacci_series.h"
#include "bounded_fibonacci_series.h"
#include "dimensions.h"
#include "tree.h"

//mpl::or_  mpl::and_ using short-circuit behavior
using namespace boost;

int ch5(int argc, _TCHAR* argv[])
{
	return 0;
}

//first, a basic test for or_
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<true>, mpl::bool_<true> >::value));
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<true>, mpl::bool_<false> >::value));
BOOST_STATIC_ASSERT((mpl::or_<mpl::bool_<false>, mpl::bool_<true> >::value));
BOOST_STATIC_ASSERT((mpl::not_<mpl::or_<mpl::bool_<false>, mpl::bool_<false> > >::value));

typedef tiny<long, char, short> tiny3shiftedtypes;
typedef tiny<char, short, int> tiny3types;
typedef tiny<char, short> tiny2types;
typedef tiny<char> tiny1types;
typedef tiny<> tinyEmpty;

typedef tiny<short, int> tiny2Reverse;
typedef tiny<int> tiny1Reverse;

typedef tiny<int, char, short> tiny3typesA;
typedef tiny<char, int, short> tiny3typesB;
typedef tiny<char, short, int> tiny3typesC;

typedef tiny<short, int> tiny3typesFrontPopped;
typedef tiny<short> tiny2typesFrontPopped;

typedef tiny<char, short> tiny3typesBackPopped;
typedef tiny<char, int> tiny3typesMiddlePopped;

//BOOST_MPL_ASSERT(( is_same< tiny3shiftedtypes,  mpl::push_front<tiny3types, long>::type> )); 


//push back
BOOST_MPL_ASSERT(( is_same< tiny3types,  mpl::push_back<tiny2types, int>::type> )); 

BOOST_MPL_ASSERT_NOT(( is_same<tiny3types, mpl::push_back<tiny2types, double>::type > )); 

BOOST_MPL_ASSERT(( is_same< tiny2types,  mpl::push_back<tiny1types, short>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny1types,  mpl::push_back<tinyEmpty, char>::type> )); 

//pop back

BOOST_MPL_ASSERT(( is_same< tiny2types,  mpl::pop_back<tiny3types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny1types,  mpl::pop_back<tiny2types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tinyEmpty,  mpl::pop_back<tiny1types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tinyEmpty,  mpl::pop_back<tinyEmpty>::type> )); 

//pop front

BOOST_MPL_ASSERT(( is_same< tiny3typesFrontPopped,  mpl::pop_front<tiny3types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny2typesFrontPopped,  mpl::pop_front<tiny2types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tinyEmpty,  mpl::pop_front<tiny1types>::type> )); 

BOOST_MPL_ASSERT(( is_same< tinyEmpty,  mpl::pop_front<tinyEmpty>::type> )); 

//push front
BOOST_MPL_ASSERT(( is_same< tiny3types,  mpl::push_front<tiny2Reverse, char>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny2Reverse,  mpl::push_front<tiny1Reverse, short>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny1Reverse,  mpl::push_front<tinyEmpty, int>::type> )); 

//erase
BOOST_MPL_ASSERT(( is_same< tiny3typesFrontPopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<0> > >::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesMiddlePopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<1> > >::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesBackPopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<2> > >::type> )); 



BOOST_MPL_ASSERT(( is_same< tiny3typesFrontPopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<0> >, tiny_iterator<tiny3types, boost::mpl::int_<1> > >::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesMiddlePopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<1> >, tiny_iterator<tiny3types, boost::mpl::int_<2> > >::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesBackPopped,  mpl::erase<tiny3types, tiny_iterator<tiny3types, boost::mpl::int_<2> >, tiny_iterator<tiny3types, boost::mpl::int_<3> > >::type> )); 


//insert
BOOST_MPL_ASSERT(( is_same< tiny3typesA,  mpl::insert<tiny2types, tiny_iterator<tiny2types, boost::mpl::int_<0> >, int>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesB,  mpl::insert<tiny2types, tiny_iterator<tiny2types, boost::mpl::int_<1> >, int>::type> )); 

BOOST_MPL_ASSERT(( is_same< tiny3typesC,  mpl::insert<tiny2types, tiny_iterator<tiny2types, boost::mpl::int_<2> >, int>::type> )); 

//at
BOOST_MPL_ASSERT(( is_same< char,  mpl::at<tiny3types,  mpl::int_<0> >::type> )); 
BOOST_MPL_ASSERT(( is_same< char,  mpl::at<tiny1types,  mpl::int_<0> >::type> )); 
BOOST_MPL_ASSERT(( is_same< char,  mpl::at<tiny2types,  mpl::int_<0> >::type> )); 

BOOST_MPL_ASSERT(( is_same< short,  mpl::at<tiny3types,  mpl::int_<1> >::type> )); 
BOOST_MPL_ASSERT(( is_same< short,  mpl::at<tiny2types,  mpl::int_<1> >::type> )); 

BOOST_MPL_ASSERT(( is_same< int,  mpl::at<tiny3types,  mpl::int_<2> >::type> )); 

//iterator

//size
BOOST_MPL_ASSERT(( is_same< mpl::int_<3>, mpl::size<tiny3types>::type>)); 
BOOST_MPL_ASSERT(( is_same< mpl::int_<2>, mpl::size<tiny2types>::type>)); 
BOOST_MPL_ASSERT(( is_same< mpl::int_<1>, mpl::size<tiny1types>::type>)); 
BOOST_MPL_ASSERT(( is_same< mpl::int_<0>, mpl::size<tinyEmpty>::type>)); 


//begin and end
BOOST_MPL_ASSERT(( is_same< char,  mpl::deref<mpl::begin<tiny3types>::type>::type >)); 
BOOST_MPL_ASSERT(( is_same< char,  mpl::deref<mpl::begin<tiny2types>::type>::type >)); 
BOOST_MPL_ASSERT(( is_same< char,  mpl::deref<mpl::begin<tiny1types>::type>::type >));

BOOST_MPL_ASSERT(( is_same< mpl::begin<tinyEmpty>::type, mpl::end<tinyEmpty>::type>));

BOOST_MPL_ASSERT(( mpl::equal_to< mpl::int_<1>,  
							mpl::distance<	mpl::begin<tiny1types>::type, 
											mpl::end<tiny1types>::type
										>::type
							>));

BOOST_MPL_ASSERT(( mpl::equal_to< mpl::int_<3>,  
							mpl::distance<	mpl::begin<tiny3types>::type, 
											mpl::end<tiny3types>::type
										>
							>));


BOOST_MPL_ASSERT(( is_same< int,  mpl::deref<
										mpl::prior<
												mpl::end<tiny3types>::type
										           >::type
										>::type
                           >)); 

BOOST_MPL_ASSERT(( is_same< short,  mpl::deref<
										mpl::prior<
												mpl::end<tiny2types>::type
										           >::type
										>::type
                           >)); 

BOOST_MPL_ASSERT(( is_same< char,  mpl::deref<
										mpl::prior<
												mpl::end<tiny1types>::type
										           >::type
										>::type
                           >)); 

//next and prior

BOOST_MPL_ASSERT(( is_same< mpl::end<tiny1types>::type,
							mpl::next<
									mpl::begin<tiny1types>::type
										>::type
                           >));

BOOST_MPL_ASSERT(( is_same< mpl::begin<tiny1types>::type,
							mpl::prior<
									mpl::end<tiny1types>::type
										>::type
                           >));

BOOST_MPL_ASSERT(( is_same< mpl::next<
									mpl::begin<tiny2types>::type
										>::type,
							mpl::prior<
									mpl::end<tiny2types>::type
										>::type
                           >));

BOOST_MPL_ASSERT(( is_same< mpl::next<
								mpl::next<
									mpl::begin<tiny2types>::type
								>::type
							>::type,
							mpl::end<tiny2types>::type
                           >));

BOOST_MPL_ASSERT(( is_same< mpl::next<
								mpl::next<
									mpl::begin<tiny3types>::type
								>::type
							>::type,
							mpl::prior<
									mpl::end<tiny3types>::type
										>::type
                           >));

//iterator
BOOST_MPL_ASSERT(( is_same< mpl::begin<tiny3types>::type,  
							tiny_iterator<tiny3types,
										  boost::mpl::int_<0>
										 >
                           >));

//deref
BOOST_MPL_ASSERT(( is_same< char,  
							mpl::deref<
								tiny_iterator<tiny3types,
											  boost::mpl::int_<0>
											  >
									>::type
                           >));

//advance

//note: we can't compare the type two iterators because one may have "int_<x>" as the Pos type, and another may have "integral_c<int,x>" as the type.
BOOST_MPL_ASSERT(( is_same< char,  
							mpl::deref<
								mpl::advance<
										mpl::begin<tiny3types>::type,
										mpl::int_<0>
											>::type
							   >::type
                           >));

BOOST_MPL_ASSERT(( is_same< short,  
							mpl::deref<
								mpl::advance<
										mpl::begin<tiny3types>::type,
										mpl::int_<1>
											>::type
							   >::type
                           >));

BOOST_MPL_ASSERT(( is_same< int,  
							mpl::deref<
								mpl::advance<
										mpl::begin<tiny3types>::type,
										mpl::int_<2>
											>::type
							   >::type
                           >));

BOOST_MPL_ASSERT(( mpl::is_same_iterator< tiny_iterator<tiny3types, boost::mpl::int_<0> >,
								             tiny_iterator<tiny3types, boost::mpl::int_<0> >		
                           >));

BOOST_STATIC_ASSERT(( mpl::is_same_iterator< tiny_iterator<tiny3types, boost::mpl::int_<0> >,
								             tiny_iterator<tiny3types, boost::mpl::int_<0> >		
                           >::value == true));

BOOST_STATIC_ASSERT(( mpl::is_same_iterator< tiny_iterator<tiny3types, boost::mpl::int_<0> >,
								             tiny_iterator<tiny3types, boost::mpl::integral_c<int, 0> >		
                           >::value == true));

BOOST_STATIC_ASSERT(( mpl::is_same_iterator< tiny_iterator<tiny3types, boost::mpl::int_<0> >,
								             tiny_iterator<tiny2types, boost::mpl::int_<0> >		
                           >::value == false));


BOOST_STATIC_ASSERT((mpl::and_< mpl::true_, mpl::false_ >::value == false));

BOOST_MPL_ASSERT(( mpl::is_same_iterator< mpl::begin<tiny3types>::type,
							mpl::advance<
									mpl::begin<tiny3types>::type,
									mpl::int_<0>
										>::type
                           >));

BOOST_MPL_ASSERT(( mpl::is_same_iterator< mpl::advance<
									mpl::begin<tiny3types>::type,
									mpl::int_<2>
										>::type,
							mpl::prior<
									mpl::end<tiny3types>::type
										>::type
                           >));

BOOST_MPL_ASSERT((  mpl::is_same_iterator< mpl::advance<
									mpl::begin<tiny3types>::type,
									mpl::int_<3>
										>::type,
							mpl::end<tiny3types>::type
                           >));

//5.1

template<class myRandomAccessSequence, class N>
struct double_element : mpl::multiplies<
										mpl::int_<2>,
													typename mpl::at<
														myRandomAccessSequence,
														N
													>::type
										>
{
};


template<class myRandomAccessSequence, class Element>
struct replace_first_element : mpl::push_front<
											typename mpl::pop_front<
												myRandomAccessSequence
												>::type,
												Element
											>
{
};

template<class myRandomAccessSequence>
struct double_first_element : replace_first_element<
													myRandomAccessSequence,
													typename double_element<
															myRandomAccessSequence,
															mpl::int_<0>
														>::type
													>
{
};

template<class myRandomAccessSequence, bool>
struct double_all_elements_recursive
{};


template<class myRandomAccessSequence>
struct double_all_elements : double_all_elements_recursive<
															myRandomAccessSequence, 
															mpl::empty<
																	myRandomAccessSequence
																		>::type::value
															>

{
};

template<class myRandomAccessSequence>
struct double_all_elements_recursive<myRandomAccessSequence, false> : mpl::push_front<
																						typename double_all_elements<
																												typename mpl::pop_front<
																													myRandomAccessSequence
																												>::type
																											>::type,
																						typename double_element<myRandomAccessSequence,
																									   typename mpl::int_<0>
																										>::type
																					>

{
};

template<class myRandomAccessSequence>
//struct double_all_elements_recursive<myRandomAccessSequence, true> : mpl::clear<myRandomAccessSequence>
struct double_all_elements_recursive<myRandomAccessSequence, true> : myRandomAccessSequence

{
};



template<class myRandomAccessSequence, bool, class N>
struct double_first_half_recursive
{};


template<class myRandomAccessSequence, class N>
struct double_first_half_size_checker : double_first_half_recursive<
															myRandomAccessSequence, 
															mpl::less_equal<
																		typename mpl::size<
																							myRandomAccessSequence
																						   >::type,
																		typename mpl::divides<
																								N,
																								mpl::int_<2>
																							  >::type
																		>::type::value,
															N
															>

{
};

template<class myRandomAccessSequence, class N>
struct double_first_half_recursive<myRandomAccessSequence, false, N> : mpl::push_front<
																						typename double_first_half_size_checker<
																																typename mpl::pop_front<
																																	myRandomAccessSequence
																																>::type,
																																N
																															>::type,
																						typename double_element<myRandomAccessSequence,
																									   typename mpl::int_<0>
																										>::type
																					>

{
};

template<class myRandomAccessSequence>
struct double_first_half : double_first_half_size_checker<
															myRandomAccessSequence, 
															typename mpl::size<
																	myRandomAccessSequence
																		>::type
															>

{
};

template<class myRandomAccessSequence, class N>
//struct double_all_elements_recursive<myRandomAccessSequence, true> : mpl::clear<myRandomAccessSequence>
struct double_first_half_recursive<myRandomAccessSequence, true, N> : myRandomAccessSequence

{
};


BOOST_MPL_ASSERT((mpl::equal<
							double_all_elements<
											mpl::vector_c<int,1,2,3,4>
												>::type,
							mpl::vector_c<int,2,4,6,8>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_element<
											mpl::vector_c<int,1,2,3,4>,
											mpl::integral_c<int,1>
												>::type,
							mpl::integral_c<int,4>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_element<
											mpl::vector_c<int,1,2,3,4>,
											mpl::integral_c<int,1>
												>::type,
							mpl::integral_c<int,4>
>));


BOOST_MPL_ASSERT((mpl::equal<
							replace_first_element<
											mpl::vector_c<int,1,2,3,4>,
											mpl::integral_c<int,2>
												>::type,
							mpl::vector_c<int,2,2,3,4>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_first_element<
											mpl::vector_c<int,1,2,3,4> 
												>::type,
							mpl::vector_c<int,2,2,3,4>
>));


typedef mpl::vector_c<int,1,2,3,4> testSequence;

BOOST_MPL_ASSERT((mpl::equal<
								mpl::push_front<
													mpl::pop_front<
														testSequence
														>::type,
														mpl::multiplies<
															mpl::int_<2>,
															mpl::at<
																testSequence,
																mpl::int_<0>
															>::type
														>::type
												>::type
							, mpl::vector_c<int,2,2,3,4>
>));


BOOST_MPL_ASSERT((mpl::equal<
								mpl::at<
										testSequence,
										mpl::int_<0>
										>::type
							, mpl::integral_c<int,1>
>));

BOOST_MPL_ASSERT((mpl::equal<
								mpl::push_front<
													mpl::pop_front<
														mpl::vector_c<int,1,2,3,4>
														>::type,
													mpl::integral_c<int,1>
												>::type
							, mpl::vector_c<int,1,2,3,4>
>));

BOOST_MPL_ASSERT((mpl::equal<
								mpl::push_back<
													mpl::vector_c<int,1,2,3,4>, 
													mpl::integral_c<int,5>
												>::type
							, mpl::vector_c<int,1,2,3,4,5>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_first_half<
											mpl::vector_c<int,1,2,3,4>
												>::type,
							mpl::vector_c<int,2,4,3,4>
>));

//assume that if we have 5 elements, we double 3
BOOST_MPL_ASSERT((mpl::equal<
							double_first_half<
											mpl::vector_c<int,1,2,3,4,5>
												>::type,
							mpl::vector_c<int,2,4,6,4,5>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_first_half<
											mpl::vector_c<int,1>
												>::type,
							mpl::vector_c<int,2>
>));

BOOST_MPL_ASSERT((mpl::equal<
							double_first_half<
											mpl::vector_c<int,1,2>
												>::type,
							mpl::vector_c<int,2,2>
>));


typedef mpl::advance_c<
	mpl::begin<fibonacci_series>::type, 6 >::type p;
BOOST_STATIC_ASSERT(mpl::deref<p>::type::value == 8 );

typedef mpl::advance_c< p, 4 >::type q;
BOOST_STATIC_ASSERT(mpl::deref<q>::type::value == 55 );

typedef dimensions<char [10][5][2]> seq;

typedef char testarray[10][5][2];

BOOST_STATIC_ASSERT( sizeof(char[10]) == 10);

BOOST_STATIC_ASSERT( sizeof(char[10][5]) == 50);

BOOST_STATIC_ASSERT( sizeof(char[10][5][2]) == 100);

BOOST_STATIC_ASSERT( sizeof(char[10][5][2]) == 100);

BOOST_STATIC_ASSERT( sizeof(testarray) == 100);

BOOST_STATIC_ASSERT( sizeof(remove_bounds<testarray>::type) == 10);

BOOST_STATIC_ASSERT( is_array<char [10][5][2]>::value == true);

BOOST_STATIC_ASSERT( is_array<testarray>::value == true);

BOOST_STATIC_ASSERT( sizeof(testarray)/sizeof(remove_bounds<testarray>::type) == 10);

BOOST_STATIC_ASSERT( dim<char [10][5][2]>::value == 10);

BOOST_STATIC_ASSERT( dim<char [5][2]>::value == 5);

BOOST_STATIC_ASSERT( dim<char [2]>::value == 2);




BOOST_STATIC_ASSERT( mpl::size<seq>::value == 3);
BOOST_STATIC_ASSERT( mpl::at_c<seq,0>::value == 2);
BOOST_STATIC_ASSERT( mpl::at_c<seq,1>::value == 5);
BOOST_STATIC_ASSERT( mpl::at_c<seq,2>::value == 10);

BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<0> >::value == 2);
BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<1> >::value == 5);
BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<2> >::value == 10);

BOOST_STATIC_ASSERT( dimensions_at<char [10][5][2],mpl::long_<2> >::value == 10);
BOOST_STATIC_ASSERT( dimensions_at<char [10][5][2],mpl::int_<1> >::value == 5);
BOOST_STATIC_ASSERT( dimensions_at<char [10][5][2],mpl::int_<0> >::value == 2);

BOOST_STATIC_ASSERT( mpl::size<dimensions<char> >::value == 0);
BOOST_STATIC_ASSERT( mpl::size<dimensions<char[10]> >::value == 1);
BOOST_STATIC_ASSERT( mpl::size<dimensions<char[10][5]> >::value == 2);

BOOST_STATIC_ASSERT( is_array<dimensions<char[10][2]>::my_type>::value == true);

BOOST_STATIC_ASSERT( dimensions_size<char>::value == 0);
BOOST_STATIC_ASSERT( dimensions_size<char[10]>::value == 1);
BOOST_STATIC_ASSERT( dimensions_size<char[10][5]>::value == 2);
BOOST_STATIC_ASSERT( dimensions_size<char[10][5][2]>::value == 3);

BOOST_MPL_ASSERT( (mpl::equal<
								dimensions_size<char[10][5][2]>,
								mpl::int_<3>
								>));

BOOST_MPL_ASSERT( (mpl::equal<
								dimensions_size<char[10][5][2]>,
								mpl::int_<3>
								>));


BOOST_STATIC_ASSERT( dimensions_size<char>::value == 0);
BOOST_STATIC_ASSERT( dimensions_size<char*>::value == 1);
BOOST_STATIC_ASSERT( dimensions_size<char**>::value == 2);
BOOST_STATIC_ASSERT( dimensions_size<char***>::value == 3);

BOOST_MPL_ASSERT((mpl::equal<
							remove_bounds<char[10][5][2]>,
							char[10][5]
>));

BOOST_MPL_ASSERT((mpl::equal<
							remove_bounds<char[10][5]>,
							char[10]
>));

BOOST_STATIC_ASSERT((is_array<remove_bounds<char [10][5][2]>::type >::value == true));

BOOST_STATIC_ASSERT((is_array<char [10][5][2]>::value == true));

//bidirectional iter and push_back, pop_back
//begin and end
BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<0> >::value == 2);
BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<1> >::value == 5);
BOOST_STATIC_ASSERT( mpl::at<seq,mpl::int_<2> >::value == 10);

BOOST_STATIC_ASSERT(( mpl::deref<
								mpl::begin<seq>::type
								>::value == 2 )); 

BOOST_STATIC_ASSERT(( mpl::deref<
								dimensions_iterator<seq,mpl::int_<0> >
								>::value == 2 ));

BOOST_STATIC_ASSERT(( mpl::deref<
								dimensions_iterator<seq,mpl::int_<1> >
								>::value == 5 ));

BOOST_STATIC_ASSERT(( mpl::deref<
								dimensions_iterator<seq,mpl::int_<2> >
								>::value == 10 ));

BOOST_STATIC_ASSERT(( mpl::deref<
								mpl::next<
										mpl::begin<seq>::type
										>::type
								>::value == 5 )); 



BOOST_STATIC_ASSERT(( mpl::deref<
								mpl::prior<
											mpl::end<seq>::type
											>::type
								>::value == 5 )); 


BOOST_STATIC_ASSERT(( mpl::deref<
								mpl::end<seq>::type
								>::value == 10 )); 




BOOST_STATIC_ASSERT( mpl::at_c<seq,0>::value == 2);
BOOST_STATIC_ASSERT( mpl::at_c<seq,1>::value == 5);
BOOST_STATIC_ASSERT( mpl::at_c<seq,2>::value == 10);


BOOST_MPL_ASSERT((is_same<
							dimensions_push<
											char[10][5][2],
											3
											>::type,
							char[3][10][5][2]
							>));

BOOST_MPL_ASSERT((is_same<
							dimensions_push<
											char,
											4
											>::type,
							char[4]
							>));

BOOST_MPL_ASSERT((is_same<
							dimensions_pop<
											char[10][5][2]
											>::type,
							char[5][2]
							>));

BOOST_MPL_ASSERT((is_same<
							dimensions_pop<
											char[10]
											>::type,
							char
							>));

BOOST_MPL_ASSERT((is_same<
							dimensions_pop<
											char
											>::type,
							char
							>));

BOOST_MPL_ASSERT((is_same<seq::my_type, char[10][5][2]>));

BOOST_MPL_ASSERT((is_same<
							mpl::push_back<seq, mpl::int_<3> >::type, 
							char[3][10][5][2]
						>));

BOOST_MPL_ASSERT((is_same<
							mpl::pop_back<seq>::type, 
							char[5][2]
						>));

typedef bounded_fibonacci_series<8> fibseq;

BOOST_STATIC_ASSERT( mpl::size<fibseq>::value == 8);

BOOST_STATIC_ASSERT( mpl::back<fibseq>::type::value == 13);

typedef tree<double, 
			 int,
			 char
			> tree_seq1;

//       double
//      /      \
//    int   char
//

BOOST_STATIC_ASSERT(( mpl::equal<
	preorder_view<tree_seq1>,
	mpl::vector<double, int, char>,
	boost::is_same<_1,_2>
>::value));

BOOST_MPL_ASSERT(( is_same<is_tree<tree_seq1>::type, true_>));

BOOST_MPL_ASSERT(( is_same<is_tree<char>::type, false_>));

BOOST_STATIC_ASSERT(( is_tree<tree_seq1>::value == true));

BOOST_STATIC_ASSERT(( is_tree<tree_seq1>::type::value == true));

BOOST_STATIC_ASSERT(( is_tree<char>::value == false));

BOOST_STATIC_ASSERT(( is_tree<char>::type::value == false));

struct test_tree : tree<int, char, long>
{};

BOOST_MPL_ASSERT((is_same<
							first_switch<
										 preorder_tag, test_tree
							            >::type, 
						    int
                          >));

BOOST_MPL_ASSERT((is_same<
							second_switch<
										 preorder_tag, test_tree
							            >::type, 
						    char
                          >));

BOOST_MPL_ASSERT((is_same<
							third_switch<
										 preorder_tag, test_tree
							            >::type, 
						    long
                          >));


BOOST_MPL_ASSERT((is_same<
							first_switch<
										 inorder_tag, test_tree
							            >::type, 
						    char
                          >));

BOOST_MPL_ASSERT((is_same<
							second_switch<
										 inorder_tag, test_tree
							            >::type, 
						    int
                          >));

BOOST_MPL_ASSERT((is_same<
							third_switch<
										 inorder_tag, test_tree
							            >::type, 
						    long
                          >));

BOOST_MPL_ASSERT((is_same<
							first_switch<
										 postorder_tag, test_tree
							            >::type, 
						    char
                          >));

BOOST_MPL_ASSERT((is_same<
							second_switch<
										 postorder_tag, test_tree
							            >::type, 
						    long
                          >));

BOOST_MPL_ASSERT((is_same<
							third_switch<
										 postorder_tag, test_tree
							            >::type, 
						    int
                          >));

typedef tree<double, 
			 tree<void*, int, long>,
			 char
			> tree_seq;

//       double
//      /      \
//    void*   char
//    /   \
//   int  long
//

BOOST_STATIC_ASSERT(( mpl::equal<
	preorder_view<tree_seq>,
	mpl::vector<double, void*, int, long, char>,
	boost::is_same<_1,_2>
>::value));

BOOST_STATIC_ASSERT(( mpl::equal<
	inorder_view<tree_seq>,
	mpl::vector<int, void*, long, double, char>,
	boost::is_same<_1,_2>
>::value));

BOOST_STATIC_ASSERT(( mpl::equal<
	postorder_view<tree_seq>,
	mpl::vector<int, long, void*, char, double>,
	boost::is_same<_1,_2>
>::value));
