#include "stdafx.h"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#if 0
 template<typename T1, typename T2>
 void same()
 {
     const bool v = boost::is_same<T1, T2>::value;
     BOOST_STATIC_ASSERT(v);
 }
 template<bool cond, typename X, typename Y>
 struct select;
 template<typename X, typename Y>
 struct select<true, X, Y>
 {
     typedef X type;
 };
 template<typename X, typename Y>
 struct select<false, X, Y>
 {
     typedef Y type;
 };
 // primary template assumes fundamental type
 template<typename C, typename X, typename Y>
 struct replace_type
 {
     static const bool issame = boost::is_same<C, X>::value;
     typedef typename select<issame, Y, C>::type type;
 };
 template<typename C, typename X, typename Y>
 struct replace_type<C *, X *, Y>
 {
     typedef typename replace_type<C, X *, Y>::type *up;
     static const bool issame = boost::is_same<C, X>::value;
     typedef typename select<issame, Y, up>::type type;
 };
 template<typename C, typename X, typename Y>
 struct replace_type<C &, X &, Y>
 {
     typedef typename replace_type<C, X &, Y>::type & up;
     static const bool issame = boost::is_same<C, X>::value;
     typedef typename select<issame, Y, up>::type type;
 };
 template<typename C, typename X, typename Y, std::size_t N>
 struct replace_type<C[N], X[N], Y>
 {
     typedef typename replace_type<C, X[N], Y>::type up[N];
     static const bool issame = boost::is_same<C, X>::value;
     typedef typename select<issame, Y, up>::type type;
 };
 template<typename C, typename X, typename Y>
 struct replace_type<C *, X, Y>
 {
     typedef typename replace_type<C, X, Y>::type *type;
 };
 template<typename C, typename X, typename Y>
 struct replace_type<C &, X, Y>
 {
     typedef typename replace_type<C, X, Y>::type & type;
 };
 template<typename C, typename X, typename Y, std::size_t N>
 struct replace_type<C[N], X, Y>
 {
     typedef typename replace_type<C, X, Y>::type type[N];
 };
 template<typename C, typename X, typename Y>
 struct replace_type<C (*)(), X, Y>
 {
     typedef typename replace_type<C, X, Y>::type R;
     typedef R (*type)();
 };
 template<typename C, typename X, typename Y, typename A>
 struct replace_type<C (*)(A), X, Y>
 {
     typedef typename replace_type<C, X, Y>::type R;
     typedef typename replace_type<A, X, Y>::type B;
     typedef R (*type)(B);
 };
 int main()
 {
     same<int, replace_type<void, void, int>::type>();
     same<int *, replace_type<void *, void, int>::type>();
     same<int &, replace_type<char &, char, int>::type>();
     same<int **, replace_type<void **, void, int>::type>();
     same<int *&, replace_type<void *&, void, int>::type>();
     same<int[5], replace_type<char[5], char, int>::type>();
     same<long *[10], replace_type<const int *[10], const int, long>::type>();
     same<int, replace_type<char (*)(char), char, int>::R>();
     same<int, replace_type<char (*)(char), char, int>::B>();
     same<long& (*)(long &), replace_type<char& (*)(char &), char, long>::type>();
     same<long& (*)(long &), replace_type<char& (*)(char &), char&, long&>::type>();
     same<long& (*)(int &), replace_type<char & (*)(int &), char&, long&>::type>();
     same<long *, replace_type<int **, int *, long>::type>();
     same<long &, replace_type<int **&, int **, long>::type>();
     return 0;
 }
#endif