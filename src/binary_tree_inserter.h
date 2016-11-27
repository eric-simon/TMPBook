#pragma once
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/eval_if.hpp>

#include "tree.h"

using namespace boost;

template <class Node>
struct treeize : mpl::eval_if<	typename is_tree<Node>::type, 
								//node is already a tree
								Node,
								//node is not a tree, so make it one
								tree<Node>
							 >
{};

//we need this function to avoid invoking binary_tree_insert too early (i.e, before eval_if determines which subtree to operate on)

template <class Root = null_tag, class Left = null_tag, class Right = null_tag>
struct make_tree
{
	typedef tree<typename Root::type, typename Left::type, typename Right::type> type;
};


template <class Sequence, class Element>
struct binary_tree_insert : mpl::eval_if< 
							   mpl::empty<Sequence>, 
							   make_tree<Element>, 
							   mpl::eval_if<
													typename mpl::less<
																		Element, 
																		typename Sequence::root
																	>, 
													//left
													make_tree<
														typename Sequence::root, 
														mpl::eval_if<
																				is_same<typename Sequence::left, null_tag>,
																				Element,
																				binary_tree_insert<
																									treeize<typename Sequence::left>,
																									Element
																									>
																			>,

														typename Sequence::right
													>,
													//right
													make_tree<
														typename Sequence::root, 
														typename Sequence::left, 
														mpl::eval_if<
																				is_same<typename Sequence::right, null_tag>,
																				Element,
																				binary_tree_insert<
																									treeize<typename Sequence::right>,
																									Element
																									>
																			>
														>
													>
											>
{};


template <class Sequence>
struct binary_tree_inserter : mpl::inserter<Sequence, binary_tree_insert<mpl::_,mpl::_> >
{};
