#pragma once

#include <boost\mpl\vector.hpp>
#include <boost\mpl\copy.hpp>
#include <boost\mpl\back_inserter.hpp>
#include <boost\mpl\eval_if.hpp>
#include <boost\mpl\sequence_tag.hpp>
#include <boost\mpl\identity.hpp>

class tree_tag{};

struct null_tag
{
	typedef null_tag type;
	typedef null_tag tag;
};

using namespace boost;

template <class Root = null_tag, class Left = null_tag, class Right = null_tag>
struct tree
{
	typedef Left left;
	typedef Root root;
	typedef Right right;
	typedef tree_tag tag;
};

template <class tag>
struct is_tree_impl : mpl::bool_<false>
{};

template <>
struct is_tree_impl<tree_tag> : mpl::bool_<true>
{
};

template <class Sequence>
struct is_tree : is_tree_impl<typename mpl::sequence_tag<Sequence>::type>
{};

class postorder_tag{};
class preorder_tag{};
class inorder_tag{};

template <class target, class case1, class case2, class case3, class value1, class value2, class value3, class defaultValue>
struct myswitch : mpl::eval_if< is_same<target, case1>, 
							  mpl::identity<value1>, 
							  mpl::eval_if< is_same<target, case2>, 
			  										mpl::identity<value2>, 
  													mpl::eval_if< is_same<target, case3>, 
			  								 								mpl::identity<value3>, 
																			mpl::identity<defaultValue>
																		>
												  >
							   >
{};

//post-order: left, right, root
//pre-order: root, left, right
//in-order: left, root, right


template <class tag, class T>
struct first_switch : myswitch<tag, postorder_tag, preorder_tag, inorder_tag, typename T::left, typename T::root, typename T::left, typename T::left>
{};

template <class tag, class T>
struct second_switch : myswitch<tag, postorder_tag, preorder_tag, inorder_tag, typename T::right, typename T::left, typename T::root, typename T::root>
{};

template <class tag, class T>
struct third_switch : myswitch<tag, postorder_tag, preorder_tag, inorder_tag, typename T::root, typename T::right, typename T::right, typename T::right>
{};

template<>
struct mpl::empty_impl<tree_tag>
{
	template <class Sequence>
	struct apply
		: is_same<typename Sequence::root, null_tag>
	{};
};

template <class seq, class T, class Tag>
struct view
{
	typedef typename first_switch<Tag, T>::type first;
	typedef typename second_switch<Tag, T>::type second;
	typedef typename third_switch<Tag, T>::type third;

	typedef typename mpl::eval_if< is_tree<first>, view<seq, first, Tag>, mpl::push_back<seq, first> >::type type1;
	typedef typename mpl::eval_if< is_tree<second>, view<type1, second, Tag>, mpl::push_back<type1, second> >::type type2;
	typedef typename mpl::eval_if< is_tree<third>, view<type2, third, Tag>, mpl::push_back<type2, third> >::type type;
};

template<class T>
struct postorder_view_impl
{
	typedef mpl::vector<> seq;
	typedef typename view<seq, T, postorder_tag>::type type;
};

template<class T>
struct postorder_view : postorder_view_impl<T>::type
{};

template<class T>
struct preorder_view_impl
{
	typedef mpl::vector<> seq;
	typedef typename view<seq, T, preorder_tag>::type type;
};

template<class T>
struct preorder_view : preorder_view_impl<T>::type
{};

template<class T>
struct inorder_view_impl
{
	typedef mpl::vector<> seq;
	typedef typename view<seq, T, inorder_tag>::type type;
};

template<class T>
struct inorder_view : inorder_view_impl<T>::type
{};