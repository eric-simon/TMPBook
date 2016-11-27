#include <boost\mpl\eval_if.hpp>
#include <boost\mpl\empty.hpp>
#include <boost\mpl\at.hpp>
#include <boost\mpl\begin.hpp>
#include <boost\mpl\iterator_tags.hpp>
#include <boost\mpl\distance.hpp>
#include <boost\mpl\size.hpp>
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_front.hpp>
#include <boost\mpl\push_back.hpp>
#include <boost\mpl\pop_back.hpp>
#include <boost\mpl\insert.hpp>
#include <boost\mpl\erase.hpp>
#include <boost\mpl\aux_\na_fwd.hpp>

using namespace boost;

struct none {}; //tag type to denote no element

struct tiny_tag {};

template <class T0 = none, class T1 = none, class T2 = none>
struct tiny
{
	typedef tiny_tag tag;
	typedef tiny type;
	typedef T0 t0;
	typedef T1 t1;
	typedef T2 t2;
};

template <class Tiny>
struct manipulate_tiny
{
	//what's T0?
	typedef typename Tiny::t0 t0;
};

template <class Tiny, class Pos>
struct tiny_iterator
{
	typedef mpl::random_access_iterator_tag category;
	typedef Tiny tiny;
	typedef Pos pos;
};

template <class Tiny, int N> struct tiny_at;

//partially specialized accessors for each index
template <class Tiny>
struct tiny_at<Tiny, 0>
{
	typedef typename Tiny::t0 type;
};

template <class Tiny>

struct tiny_at<Tiny, 1>
{
	typedef typename Tiny::t1 type;
};

template <class Tiny>
struct tiny_at<Tiny, 2>
{
	typedef typename Tiny::t2 type;
};

namespace boost { namespace mpl {

	//forward iterator requirement
	template <class Tiny, class Pos>
	struct next<tiny_iterator<Tiny, Pos> >
	{
		typedef tiny_iterator<
	    	  Tiny
			, typename mpl::next<Pos>::type
		> type;
	};

	//bidirectional iterator requirement
	template <class Tiny, class Pos>
	struct prior<tiny_iterator<Tiny, Pos> >
	{
		typedef tiny_iterator<
	    	  Tiny
			, typename mpl::prior<Pos>::type
		> type;
	};

	template <>
	struct at_impl<tiny_tag>
	{
		template <class Tiny, class N>
		struct apply : tiny_at<
				Tiny, 
				N::value>
		{};
	};

	template <class Tiny, class Pos>
	struct deref< tiny_iterator<Tiny, Pos> >
		: at<Tiny, Pos>
	{
	};

	//random access iterator requirements
	template <class Tiny, class Pos, class N>
	struct advance<tiny_iterator<Tiny, Pos>,N>
	{
		typedef tiny_iterator<
					Tiny
				  , typename mpl::plus<Pos, N>::type
		> type;
	};

	template <class Tiny, class Pos1, class Pos2>
	struct distance<
		tiny_iterator<Tiny, Pos1>,
		tiny_iterator<Tiny, Pos2>
	>
		: mpl::minus<Pos2, Pos1>
	{};

	template<>
	struct begin_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply
		{
			typedef tiny_iterator<Tiny,int_<0> > type;
		};
	};

	template <class T0, class T1, class T2>
	struct tiny_size
		: mpl::int_<3> {};

	template <class T0, class T1>
	struct tiny_size<T0, T1, none>
		: mpl::int_<2> {};

	template <class T0>
	struct tiny_size<T0, none, none>
		: mpl::int_<1> {};

	template <>
	struct tiny_size<none, none, none>
		: mpl::int_<0> {};

	template <>
	struct end_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply
		{
			typedef tiny_iterator<
				Tiny,
				typename tiny_size<
					typename Tiny::t0,
					typename Tiny::t1,
					typename Tiny::t2
				>::type
			>
			type;
		};
	};

	template<>
	struct size_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply
			: tiny_size<
						typename Tiny::t0,
						typename Tiny::t1,
						typename Tiny::t2
			>
		{};
	};

	template<>
	struct clear_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply : tiny<>
		{};
	};

#if 0
	template<>
	struct push_front_impl<tiny_tag>
	{
		template <class Tiny, class T>
		struct apply 
			: tiny<T, typename Tiny::t0, typename Tiny::t1>
		{};
	};
#endif

	template<class Tiny, int N, int first, int last>
	struct tiny_erase;

	template<class Tiny>
	struct tiny_erase<Tiny, 0, -1, 0>
		: tiny<none, none, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 0, 0, 1>
		: tiny<none, none, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 1, 0, 1>
		: tiny<none, none, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 2, 0, 1>
		: tiny<typename Tiny::t1, none, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 3, 0, 1>
		: tiny<typename Tiny::t1, typename Tiny::t2, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 2, 1, 2>
		: tiny<typename Tiny::t0, none, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 3, 1, 2>
		: tiny<typename Tiny::t0, typename Tiny::t2, none>
	{};

	template<class Tiny>
	struct tiny_erase<Tiny, 3, 2, 3>
		: tiny<typename Tiny::t0, typename Tiny::t1, none>
	{};
	//

	template<class Tiny, class T, int N, int pos>
	struct tiny_insert;

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 0, 0>
		: tiny<T, none, none>
	{};

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 1, 0>
		: tiny<T, typename Tiny::t0, none>
	{};

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 1, 1>
		: tiny<typename Tiny::t0, T, none>
	{};

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 2, 0>
		: tiny<T, typename Tiny::t0, typename Tiny::t1>
	{};

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 2, 1>
		: tiny<typename Tiny::t0, T, typename Tiny::t1>
	{};

	template<class Tiny, class T>
	struct tiny_insert<Tiny, T, 2, 2>
		: tiny<typename Tiny::t0, typename Tiny::t1, T>
	{};


	template<>
	struct insert_impl<tiny_tag>
	{
		template <class Tiny, class Pos, class T>
		struct apply
			: tiny_insert<
				Tiny, T, size<Tiny>::value, Pos::pos::value
			>
		{};
	};


	template<>
	struct erase_impl<tiny_tag>
	{
		template <class Tiny, class First, class Last>
		struct apply
			: tiny_erase<
				Tiny, size<Tiny>::value, First::pos::value, Last::pos::value
			>
		{};

		template <class Tiny, class First>
		struct apply<Tiny, First, mpl::na>
			: tiny_erase<
				Tiny, size<Tiny>::value, First::pos::value, mpl::next<typename First::pos>::type::value
			>
		{};
	};
#if 0
	template<class Tiny, class T, int N>
	struct tiny_push_front;

	template<class Tiny, class T>
	struct tiny_push_front<Tiny, T, 0>
		: tiny<T, none, none>
	{};

	template<class Tiny, class T>
	struct tiny_push_front<Tiny, T, 1>
		: tiny<T, typename Tiny::t0, none>
	{};

	template<class Tiny, class T>
	struct tiny_push_front<Tiny, T, 2>
		: tiny<T, typename Tiny::t0, typename Tiny::t1>
	{};
#endif
	template<>
	struct push_front_impl<tiny_tag>
	{
		template <class Tiny, class T>
		struct apply
			: tiny_insert<
				Tiny, T, size<Tiny>::value, mpl::begin<Tiny>::type::pos::value
			>
		{};
	};

#if 0
	template<class Tiny, class T, int N>
	struct tiny_push_back;

	template<class Tiny, class T>
	struct tiny_push_back<Tiny, T, 0>
		: tiny<T, none, none>
	{};

	template<class Tiny, class T>
	struct tiny_push_back<Tiny, T, 1>
		: tiny<typename Tiny::t0, T, none>
	{};

	template<class Tiny, class T>
	struct tiny_push_back<Tiny, T, 2>
		: tiny<typename Tiny::t0, typename Tiny::t1, T>
	{};
#endif
	template<>
	struct push_back_impl<tiny_tag>
	{
		template <class Tiny, class T>
		struct apply
			: tiny_insert<
				Tiny, T, size<Tiny>::value, mpl::end<Tiny>::type::pos::value
			>
		{};
	};

	template<>
	struct pop_back_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply
			: tiny_erase<
				Tiny, size<Tiny>::value, mpl::prior<
												typename mpl::end<Tiny>::type::pos
										           >::type::value,
 										 mpl::end<Tiny>::type::pos::value
			>
		{};
	};

	template<>
	struct pop_front_impl<tiny_tag>
	{
		template <class Tiny>
		struct apply
			: tiny_erase<
				Tiny, size<Tiny>::value, mpl::begin<Tiny>::type::pos::value,
										 mpl::next<
													typename mpl::begin<Tiny>::type::pos
												>::type::value
			>
		{};
	};

	template <class iterator1, class iterator2>
	struct iterator_has_same_sequence : is_same<
											typename iterator1::tiny, 
											typename iterator2::tiny
										>
	{
	};

	template <class iterator1, class iterator2>
	struct iterator_has_same_position : mpl::equal_to<
											typename iterator1::pos, 
											typename iterator2::pos
										>
	{
	};
	template <class iterator1, class iterator2>
	struct is_same_iterator : mpl::and_<
									iterator_has_same_sequence<
										iterator1, 
										iterator2
										>, 
									iterator_has_same_position<
										iterator1, 
										iterator2
										>
								>
	{
	};
}}