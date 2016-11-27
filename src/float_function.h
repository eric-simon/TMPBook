#pragma once

float_function
{
private:
	struct impl
	{
		virtual ~impl() {}
		virtual impl* clone() const = 0;
		virtual float operator() (float) const = 0;
	};

	template <class F>
	struct wrapper : impl
	{
		explicit wrapper(F const& f) : f(f) {}

		impl* clone() const
		{
			return new wrapper<F>(this->f); //delegate
		}

		float operator()(float x) const
		{
			return this->f(x);
		}
	private:
		F f;
	};

public:
	//implicit conversion from F
	template <class F>
	float_function(F const& f) : pimpl(new wrapper<F>(f)) {}

	float_function(float_function const& rhs) : pimpl(rhs.pimpl->clone()) {}

	float_function& operator=(float_function const& rhs)
	{
		this->pimpl.reset(rhs.pimpl->clone());
		return *this;
	}

	float operator()(float x) const
	{
		return (*this->pimpl)(x);
	}
private:
	std::auto_ptr<impl> pimpl;
}
