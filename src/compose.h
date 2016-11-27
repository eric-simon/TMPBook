#pragma once
#include <boost/type_traits/is_empty.hpp>

template <class F, bool F_empty, class G, bool G_empty>
class storage;

template <class R, class F, class G>
class compose_fg : storage<F, boost::is_empty<F>::value,
	G, boost::is_empty<G>::value>
{
	typedef
		storage<
			F, boost::is_empty<F>::value,
			G, boost::is_empty<G>::value
		> base;

public:
	compose_fg(F const& f, G const& g) : base(f, g) {}

	template <class T>
	R operator()(T const& x) const
	{
		F const& f = this->get_f();
		G const& g = this->get_g();
		return (f(g(x)));
	}
};

template <class R, class F, class G>
compose_fg<R, F, G> compose(F const&f, G const& g)
{
	return compose_fg<R, F, G>(f, g);
};

template <class F, class G>
class storage<F, false, G, false>  //neither F nor G is empty
{
protected:
	storage(F const&f, G const& g) : f(f), g(g)
	{}
	F const& get_f() const { return f; }
	G const& get_g() const { return g; }
private:
	F f;
	G g;
};


template <class F, class G>
class storage<F, false, G, true>   // G is empty
	: private G
{
protected:
	storage(F const& f, G const& g) : G(g), f(f)
	{}
	F const & get_f() const { return f; }
	G const & get_g() const { return *this; }
private:
	F f;
};

template <class F, class G>
class storage<F, true, G, false>   //F is empty
	: private F
{
protected:
	storage(F const& f, G const& g) : F(f), g(g)
	{}
	F const & get_f() const { return *this; }
	G const & get_g() const { return g; }
private:
	G g;
};


#if 0
template <class F, class G>
class storage<F, true, G, true>   //F and G are both empty
	: private F, private G
{
protected:
	storage(F const& f, G const& g) : F(f), G(g)
	{}
	F const & get_f() const { return *this; }
	G const & get_g() const { return *this; }
};
#endif

template <class F, class G>
class storage<F, true, G, true>   //F and G are both empty
	//: private F, private G
{
protected:
	storage(F const& f, G const& g)
	{}
	F const & get_f() const { return F(); }
	G const & get_g() const { return G(); }
};

template <class R, class F, F f, class G, G g>
struct compose_fg2
{
	typedef R result_type;

	template <class T>
	R operator()(T const& x) const
	{
		return f(g(x));
	}
};