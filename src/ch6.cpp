#include "stdafx.h"
#include <boost\mpl\assert.hpp>
#include <boost\mpl\vector.hpp>
#include <boost\static_assert.hpp>
#include <boost\mpl\list.hpp>
#include <boost\mpl\pop_front.hpp>
#include <boost\mpl\equal.hpp>
#include <boost\mpl\equal_to.hpp>
#include <boost\mpl\empty.hpp>
#include <boost\mpl\vector_c.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>

#include <iostream>
#include "binary_tree_inserter.h"
#include "smallest.h"
#include "tree.h"
#include "binary_tree_search.h"

BOOST_STATIC_ASSERT((
	boost::is_same<
		smallest< mpl::vector<int[2], char, double&> >::type,
		char
	>::value
	));

BOOST_STATIC_ASSERT((
	boost::is_same<
		smallest2< mpl::vector<int[2], char, double&> >::type,
		char
	>::value
	));

BOOST_STATIC_ASSERT((
	boost::is_same<
		smallest_using_fold< mpl::vector<int[2], char, double&> >::type,
		char
	>::value
	));

BOOST_STATIC_ASSERT((
	boost::mpl::equal<
		typename mpl::pop_front<mpl::vector<int[2], char, double&> >::type,
		mpl::vector<char, double&>
	>::type::value
	));

typedef tree<> emptyTree;

typedef mpl::vector<> emptyVector;

typedef tree<> empty_tree;

typedef tree<mpl::int_<17> > root_only;

typedef tree<mpl::int_<17>, mpl::int_<10> > left_half;

typedef tree<mpl::int_<17>, null_tag, mpl::int_<25> > right_half;

BOOST_STATIC_ASSERT((mpl::less<mpl::int_<17>, mpl::int_<25> >::type::value == true));

BOOST_STATIC_ASSERT((mpl::less<mpl::int_<25>, mpl::int_<17> >::type::value == false));

BOOST_MPL_ASSERT((is_same<typename root_only::left, null_tag>::type));

BOOST_MPL_ASSERT((is_same<typename root_only::right, null_tag>::type));

BOOST_MPL_ASSERT((is_same<typename root_only::root, mpl::int_<17> >::type));

typedef binary_tree_insert<
							root_only, 
							mpl::int_<10> 
							>::type
				left_half2;

typedef binary_tree_insert<
							left_half, 
							mpl::int_<25> 
							>::type
				both_sides2;

typedef binary_tree_insert<
							right_half, 
							mpl::int_<10> 
							>::type
				both_sides3;

BOOST_STATIC_ASSERT((mpl::empty<empty_tree>::type::value == true));
BOOST_STATIC_ASSERT((mpl::empty<root_only>::type::value == false));

BOOST_STATIC_ASSERT((treeize<tree<mpl::int_<17> >>::root::type::type::value == 17));

BOOST_STATIC_ASSERT((treeize<mpl::int_<17> >::root::value == 17));


BOOST_STATIC_ASSERT(( boost::mpl::equal<
	inorder_view<both_sides2>::type,
	boost::mpl::vector_c<int, 10, 17, 25>,
	boost::mpl::equal_to<boost::mpl::_1,boost::mpl::_2>
>::value));


BOOST_STATIC_ASSERT(( boost::mpl::equal<
	inorder_view<both_sides3>::type,
	boost::mpl::vector_c<int, 10, 17, 25>,
	boost::mpl::equal_to<boost::mpl::_1,boost::mpl::_2>
>::value));


typedef tree<mpl::int_<17>, mpl::int_<10>, mpl::int_<25> > both_sides;

typedef tree<mpl::int_<17>, 
			 tree<mpl::int_<10>, mpl::int_<2>>,
			 mpl::int_<25>
			> almost_done;

//               int_<17>
//                /      \
//            int_<10>    int_<25>
//             /    
//         int_<2>  

typedef tree<mpl::int_<17>, 
			 tree<mpl::int_<10>, mpl::int_<2>, mpl::int_<11> >,
			 mpl::int_<25>
			> full_tree;

//               int_<17>
//                /      \
//            int_<10>    int_<25>
//             /     \
//         int_<2>  int_<11>

BOOST_MPL_ASSERT((mpl::empty<empty_tree>::type));

BOOST_STATIC_ASSERT(( boost::mpl::equal<
	inorder_view<both_sides>::type,
	boost::mpl::vector_c<int, 10, 17, 25>,
	boost::mpl::equal_to<boost::mpl::_1,boost::mpl::_2>
>::value));

typedef mpl::copy<
					mpl::vector_c<int, 17, 25, 10, 2, 11>,
					binary_tree_inserter< tree<> >
				>::type bst;

//               int_<17>
//                /      \
//            int_<10>    int_<25>
//             /     \
//         int_<2>  int_<11>

BOOST_STATIC_ASSERT(( mpl::equal<
								inorder_view<bst>,
								mpl::vector_c<int,2,10,11,17,25>
					>::value));

typedef binary_tree_search<bst,mpl::int_<11> >::type pos1;
typedef binary_tree_search<bst,mpl::int_<20> >::type pos2;
typedef mpl::end<bst>::type end_pos;

BOOST_STATIC_ASSERT((!boost::is_same<pos1, end_pos>::value));
BOOST_STATIC_ASSERT((boost::is_same<pos2, end_pos>::value));