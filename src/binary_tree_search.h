#pragma once
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/eval_if.hpp>

#include "tree.h"

template <class PossibleSequence, class Element>
struct safe_equal : mpl::eval_if<
								typename is_tree<PossibleSequence>::type,
								mpl::bool_<false>,
								mpl::equal_to<
												Element, 
												PossibleSequence
											 >
								>
{};

//this is a separate metafunction because we want to ensure that "equal_to<Element, Leaf>" is lazily evaluated,
//or else it might be evaluated on a non-leaf type.  The difficulty with nested "eval_if" is that the conditional expression is
//always evaluated, even if the enclosing metafunction is not evaluated.

template <class Element, class Leaf, class EndPos>
struct compare_leaf : mpl::eval_if<
									typename mpl::equal_to<Element, Leaf>::type,
									mpl::identity<Leaf>,
									mpl::identity<EndPos>
									>
{};

//we make the assumption that this metafunction is ALWAYS called on a Tree.  Thus, we need to ensure that invariant is tree when recursing.  If we
//don't assume that the input sequence is a tree, it becomes difficult to prevent compilation failures when checking the elements of the tree.  
template <class Tree, class Element, class EndPos>
struct binary_tree_search_impl : mpl::eval_if<
												typename mpl::equal_to<
																	Element, 
																	typename Tree::root
																	>::type, 
												mpl::identity<typename Tree::root>,
												mpl::eval_if<
																typename mpl::less<
																				Element,
																				typename Tree::root
																				>::type,
																mpl::eval_if<
																				typename is_tree<typename Tree::left>::type,
																				binary_tree_search_impl<
																									typename Tree::left,
																									Element,
																									EndPos
																									>,
																				compare_leaf<Element, typename Tree::left, EndPos>
																			>,
																mpl::eval_if<
																				typename is_tree<typename Tree::right>::type,
																				binary_tree_search_impl<
																									typename Tree::right,
																									Element,
																									EndPos
																									>,
																				compare_leaf<Element, typename Tree::right, EndPos>
																			>
															>
												>
{};


template <class Sequence, class Element>
struct binary_tree_search : binary_tree_search_impl<Sequence, Element, typename mpl::end<Sequence>::type>
{};
