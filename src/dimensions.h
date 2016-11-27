#include <boost\mpl\iterator_category.hpp>
#include <boost\mpl\iterator_tags.hpp>
#include <boost\mpl\size.hpp>

using namespace boost::mpl;

struct dimensions_tag{};

template<class T>
struct dimensions
{
	typedef dimensions_tag tag;
	typedef dimensions type;
	typedef T my_type;
};

template <class T>
struct dimensions_size : mpl::eval_if<
										is_array<T>,
										mpl::plus<
												  mpl::int_<1>,
												  dimensions_size<
													  			  typename remove_bounds<T>::type
																 >
												 >,
										mpl::int_<0>
									 >
{};

template <class T>
struct dimensions_size<T*> : mpl::plus<mpl::int_<1>, dimensions_size<T> >
{};

template <class T>
struct dim
{
	const static int value = sizeof(T)/sizeof(remove_bounds<T>::type);
};
	
template <class T, class Pos>
struct dimensions_at : mpl::eval_if<
									typename equal_to<
											typename mpl::next<Pos>::type, 
											typename dimensions_size<T>::type
											>::type,
									dim<T>,
									dimensions_at<
													typename remove_bounds<T>::type, 
													Pos
											>
									>
{};

template<class T>
struct dimensions_pop
{
	typedef typename remove_bounds<T>::type type;
};

template<class T, int N>
struct dimensions_push
{
	typedef T type[N];
};

template <class Dimensions, class Pos>
struct dimensions_iterator
{
	typedef mpl::bidirectional_iterator_tag category;
	typedef Dimensions dimensions;
	typedef Pos pos;
};


namespace boost { namespace mpl {

	template<class Dimensions, class Pos>
	struct deref<dimensions_iterator<Dimensions, Pos> > : at<Dimensions, Pos>
	{
	};

	template<>
	struct begin_impl<dimensions_tag>
	{
		template <class Dimensions>
		struct apply
		{
			typedef dimensions_iterator<Dimensions, mpl::int_<0> > type;
		};
	};

	template<>
	struct end_impl<dimensions_tag>
	{
		template <class Dimensions>
		struct apply
		{
			typedef dimensions_iterator<
										Dimensions, 
										typename mpl::prior<
													dimensions_size<typename Dimensions::my_type>
													>::type
										> type;
		};
	};

	template<class Dimensions, class Pos>
	struct prior<
				dimensions_iterator<Dimensions, Pos> 
				>
	{
		typedef dimensions_iterator<
									Dimensions,
									typename mpl::prior<Pos>::type
									> type;
										
	};
	
	template<class Dimensions, class Pos>
	struct next<
				dimensions_iterator<Dimensions, Pos>
				>
	{
		typedef dimensions_iterator<
										Dimensions,
										typename mpl::next<Pos>::type
										> type;
										
	};
	
	template <>
	struct size_impl<dimensions_tag>
	{
		template <class Dimensions>
		struct apply : dimensions_size<typename Dimensions::my_type>
		{};
	};

	template <>
	struct at_impl<dimensions_tag>
	{
		template <class Dimensions, class Pos>
		struct apply : dimensions_at<typename Dimensions::my_type, Pos>
		{};
	};

	template<>
	struct push_back_impl<dimensions_tag>
	{
		template <class Dimensions, class T>
		struct apply : dimensions_push<typename Dimensions::my_type, T::value>
		{};
	};

	template<>
	struct pop_back_impl<dimensions_tag>
	{
		template <class Dimensions>
		struct apply : dimensions_pop<typename Dimensions::my_type>
		{};
	};


}};