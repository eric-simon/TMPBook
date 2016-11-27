#pragma once

#include <boost\mpl\iterator_tags.hpp>
//#include <boost\iterator\iterator_facade.hpp>

using namespace boost;

template <class value_type, class iterator_category>
struct generalized_iterator
{
};

template <class value_type, class iterator_category>
struct deref_iterator
{
	virtual value_type operator*(void) = 0;
//	virtual value_type* operator->(void) = 0;

};

template <class value_type, class iterator_category>
struct forward_iterator
{
	virtual void increment(void) = 0;
//	virtual generalized_iterator<value_type, iterator_category> operator++(void) = 0;
//	virtual generalized_iterator<value_type, iterator_category> operator+=(int) = 0;
};


template <class value_type, class iterator_category>
struct bidirectional_iterator
{
	virtual void decrement(void) = 0;
	//virtual generalized_iterator<value_type, iterator_category> operator--(int) = 0;
	//virtual generalized_iterator<value_type, iterator_category> operator--(void) = 0;
	//virtual generalized_iterator<value_type, iterator_category> operator-=(int) = 0;
};


template <class value_type, class iterator_category>
struct random_access_iterator
{
	virtual value_type operator[](int) = 0;
};


template <class value_type>
struct generalized_iterator<value_type, std::forward_iterator_tag> :
	public deref_iterator<value_type, std::forward_iterator_tag>,
	public forward_iterator<value_type, std::forward_iterator_tag>
{
};

template <class value_type>
struct generalized_iterator<value_type, std::bidirectional_iterator_tag> :
	public deref_iterator<value_type, std::bidirectional_iterator_tag>,
	public forward_iterator<value_type, std::bidirectional_iterator_tag>,
	public bidirectional_iterator<value_type, std::bidirectional_iterator_tag>
{
};

template <class value_type>
struct generalized_iterator<value_type, std::random_access_iterator_tag> :
	public deref_iterator<value_type, std::random_access_iterator_tag>,
	public forward_iterator<value_type, std::random_access_iterator_tag>,
	public bidirectional_iterator<value_type, std::random_access_iterator_tag>,
	public random_access_iterator<value_type, std::random_access_iterator_tag>
{
};


template <class Iterator>
struct iterator_wrapper : public generalized_iterator<typename Iterator::value_type, typename Iterator::iterator_category>
{
	iterator_wrapper(Iterator iter) :baseIter(iter) {}

	typename Iterator::value_type operator[](int index)
	{
		return baseIter[index];
	}

	void increment(void)
	{
		++baseIter;
	}

	void decrement(void)
	{
		--baseIter;
	}

	typename Iterator::value_type operator*(void)
	{
		return (*baseIter);
	}

private:
	Iterator baseIter;
};

template <class Iterator>
iterator_wrapper<Iterator> make_iterator_wrapper(Iterator iter)
{
	return iterator_wrapper<Iterator>(iter);
};
