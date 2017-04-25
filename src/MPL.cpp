// MPL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/transform.hpp>
#include "assert.h"
#include <iostream>
#include <string>
#include <boost/mpl/placeholders.hpp>
#include "ch3.h"
#include "ch4.h"
#include "ch9.h"
#include "ch11.h"

template <bool B, class U, class V> struct select_type;

template <class U, class V> struct select_type<true, U, V>
{
	typedef V type;
};

template <class U, class V> struct select_type<false, U, V>
{
	typedef U type;
};

template <class T> struct add_const_ref
{
	typedef T & type;
};

template <class T> struct add_const_ref<T&>
{
	typedef T const& type;			
};

template <class C, class X, class Y> struct replace_type
{
	typedef typename boost::is_same<C, X>::type true_or_false;

	typedef typename select_type<true_or_false::value, C, Y>::type type;
};


template <class C, class X, class Y> struct replace_type<C*, X, Y>
{
	typedef typename replace_type<C, X, Y>::type* type;			
};

template <class C, class X, class Y> struct replace_type<C*, X*, Y>
{
	typedef typename boost::is_same<C, X>::type true_or_false;

	typedef typename replace_type<C, X*, Y>::type* recurse; 

	typedef typename select_type<true_or_false::value, recurse, Y>::type type;	
//	typedef typename select_type<true_or_false::value, C*, Y>::type type;	
};

template <class C, class X, class Y> struct replace_type<C&, X&, Y>
{
	typedef typename boost::is_same<C, X>::type true_or_false;

	typedef typename select_type<true_or_false::value, C&, Y>::type type;		
};

template <class C, class X, class Y> struct replace_type<C&, X, Y>
{
	typedef typename replace_type<C, X, Y>::type& type;			
};

template <class R, class A, class X, class Y> struct replace_type<R (*)(A), X, Y>
{
	typedef typename replace_type<R, X, Y>::type result_type;			

	typedef typename replace_type<A, X, Y>::type arg_type;

	typedef typename result_type (*type)(typename arg_type);
};

template <class R, class X, class Y> struct replace_type<R (*)(), X, Y>
{
	typedef typename replace_type<R, X, Y>::type result_type;			

	typedef typename result_type (*type)();
};

template <std::size_t N, class C, class X, class Y> struct replace_type<C[N], X, Y>
{
	typedef typename replace_type<C, X, Y>::type type[N];
};

template <class Target, class Source>
inline Target polymorphic_downcast(Source* x)
{
	assert( dynamic_cast<Target>(x) == x);
	return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast(Source& x)
{
	assert( dynamic_cast<boost::remove_reference<Target>::type*>(&x) == &x);
	return *static_cast<boost::remove_reference<Target>::type*>(&x);
}

struct A 
{ 
	virtual ~A() {} 
};

struct B : A {};

template <class T> struct type_descriptor
{
	std::ostream & print(std::ostream & out) const
	{
		if (boost::is_same<T, int>::value)
		{
			return out << "int";
		}
		else if (boost::is_same<T, short int>::value)
		{
			return out << "short int";
		}
		else if (boost::is_same<T, char>::value)
		{
			return out << "char";
		}
		else if (boost::is_same<T, long int>::value)
		{
			return out << "long int";
		}
		else if (boost::is_const<T>::value)
		{
			return out << type_descriptor<boost::remove_const<T>::type>() << " const";
		}
		else if (boost::is_reference<T>::value)
		{
			return out << type_descriptor<boost::remove_reference<T>::type>() << "&";
		}
		else if (boost::is_pointer<T>::value)
		{
			//return out << type_descriptor<boost::remove_pointer<T>::type>() << "*";
			return out << "pointer to " << type_descriptor<boost::remove_pointer<T>::type>();
		}
		else if (boost::is_array<T>::value)
		{
			//return out << type_descriptor<boost::remove_pointer<T>::type>() << "*";
			return out << "array of " << type_descriptor<boost::remove_extent<T>::type>();
		}
		else
		{
			return out << "ERROR";
		}

	}
};


template <class R> struct type_descriptor<R (*)()>
{
	std::ostream & print(std::ostream & out) const
	{
		return out << "pointer to function returning " << type_descriptor<R>();
	}
};

#if 0
template <class T> struct type_descriptor
{
	std::ostream & print(std::ostream & out) const {}
};

template<>
struct type_descriptor<int>
{
	std::ostream & print(std::ostream & out) const { return out << "int";}
};

template<>
struct type_descriptor<short int>
{
	std::ostream & print(std::ostream & out) const { return out << "short int";}
};


template<>
struct type_descriptor<char>
{
	std::ostream & print(std::ostream & out) const { return out << "char";}
};

template<>
struct type_descriptor<long int>
{
	std::ostream & print(std::ostream & out) const { return out << "long int";}
};


template<class T>
struct type_descriptor<T*>
{
	std::ostream& print(std::ostream& out) const { return out << type_descriptor<T>() << "*";}
};

template<class T>
struct type_descriptor<T&>
{
	std::ostream& print(std::ostream& out) const { return out << type_descriptor<T>() << "&";}
};

template<class T>
struct type_descriptor<T const>
{
	virtual std::ostream& print(std::ostream& out) const { return out << type_descriptor<T>() << " const";}
};
#endif

template<typename T>
std::ostream & operator<< (std::ostream & out, const type_descriptor<T> & desc)
{
     return desc.print(out);
}



void poly()
{
	B b;
	A* a_ptr = &b;
	B* b_ptr = polymorphic_downcast<B*>(a_ptr);

	A& a_ref = b;
	B& b_ref = polymorphic_downcast<B&>(a_ref);
}

template <unsigned long N>
struct binary
{
	BOOST_STATIC_ASSERT(N%10 < 2);

	static unsigned const value
		= binary<N/10>::value * 2
		  + N%10;
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
};


int _tmain(int argc, _TCHAR* argv[])
{
	ch11(argc, argv);

	ch9(argc, argv);

	ch3(argc, argv);

	ch4();

	std::cout << binary<0>::value << std::endl;
	std::cout << binary<1>::value << std::endl;
	std::cout << binary<10>::value << std::endl;
	std::cout << binary<11>::value << std::endl;
	std::cout << binary<100>::value << std::endl;
	std::cout << binary<101>::value << std::endl;
	std::cout << binary<110>::value << std::endl;
	std::cout << binary<111>::value << std::endl;

	typedef boost::mpl::vector_c<int,1,2,3> test;

	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 0 >::type::value == 1 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 1 >::type::value == 2 ) );
	BOOST_STATIC_ASSERT( (boost::mpl::at_c< test, 2 >::type::value == 3 ) );

	BOOST_MPL_ASSERT(( boost::is_same<int&, add_const_ref<int>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<const int&, add_const_ref<int&>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<int*, replace_type<void*, void, int>::type > ));

	BOOST_MPL_ASSERT(( boost::is_same<int*, replace_type<void*, void*, int*>::type > ));

	BOOST_MPL_ASSERT(( boost::is_same<int&, replace_type<char&, char, int>::type > ));

	BOOST_MPL_ASSERT(( boost::is_same<int&, replace_type<char&, char&, int&>::type > ));

	BOOST_MPL_ASSERT(( boost::is_same<char, replace_type<char, int, long>::type > ));

	BOOST_MPL_ASSERT(( boost::is_same<long[10], replace_type<int[10], int, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long* [10], replace_type<int const*[10], int const, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long (*)(), replace_type<char (*)(), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long& (*)(), replace_type<char& (*)(), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long& (*)(), replace_type<char& (*)(), char&, long&>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long* (*)(), replace_type<char* (*)(), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long*, replace_type<char*, char*, long*>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long* (*)(), replace_type<char* (*)(), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long (*)(int), replace_type<char (*)(int), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long (*)(long), replace_type<char (*)(long), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long& (*)(long&), replace_type<char& (*)(char&), char&, long&>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long* (*)(long*), replace_type<char* (*)(char*), char, long>::type > )); 

	BOOST_MPL_ASSERT(( boost::is_same<long& (*)(long*), replace_type<char& (*)(char*), char, long>::type > )); 

	//prints "int"
	std::cout << type_descriptor<int>() << std::endl;

	//prints "char"
	std::cout << type_descriptor<char>() << std::endl;

	//prints "char*"
	std::cout << type_descriptor<char*>() << std::endl;

	//prints "char&"
	std::cout << type_descriptor<char&>() << std::endl;

	//prints "long const"
	std::cout << type_descriptor<long const>() << std::endl;

	//prints "long const*"
	std::cout << type_descriptor<long const*>() << std::endl;

	//prints "long const&"
	std::cout << type_descriptor<long const&>() << std::endl;

	//prints "long const*&"
	std::cout << type_descriptor<long const*&>() << std::endl;

	std::cout << type_descriptor<char* (*)()>() << std::endl;

	std::cout << type_descriptor<char*[]>() << std::endl;

	//prints "char* (*[])()"
	std::cout << type_descriptor<char *(*[])()>() << std::endl;

	return 0;
}


 