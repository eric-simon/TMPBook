#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/cat.hpp>

template <class Type>
struct arg_wrapper
{
	arg_wrapper(Type arg) :value(arg) {};
	Type value;
};

template <class Type>
struct arg_factory
{
	arg_factory() {};
	arg_wrapper<Type> operator=(Type arg) { return arg_wrapper<Type>(arg); }
	typedef Type type;
};

#define NAMED_PARAMETER(_NAME_, _TYPE_)\
typedef arg_wrapper<_TYPE_> wrapper_##_NAME_;\
typedef arg_factory<_TYPE_> factory_##_NAME_;\
factory_##_NAME_ _NAME_;\

#define NAMED_ARG(r, data, elem) (BOOST_PP_CAT(wrapper_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) BOOST_PP_CAT(arg_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) = BOOST_PP_TUPLE_ELEM(2, 1, elem))  //expands (elem[0], elem[1]) to (wrapper_elem[0] arg_elem[0] = elem[1])

#define NAMED_ARG_SEQ(_ARGS_) BOOST_PP_SEQ_FOR_EACH(NAMED_ARG, dummy, _ARGS_)  //expands ((arg1,def1))((arg2,def2)) to (wrapper_arg1 arg_arg1 = def1)(wrapper_arg2 arg_arg2 = def2) ...

#define NAMED_ARG_LIST(_ARGS_) BOOST_PP_SEQ_ENUM(NAMED_ARG_SEQ(_ARGS_))         //expands ((arg1,def1))((arg2,def2)) to wrapper_arg1 arg_arg1, wrapper_arg2 arg_arg2, ...

//#define NAMED_FUNCTION(_FUNC_,  _ARGS_) void _FUNC_(NAMED_ARG_LIST(_ARGS_))    //ARGS = ((score, 0))((name, "x"))((slew, 0.1)) expands to wrapper_score arg_score = def1, wrapper_name arg_name = def2, wrapper_slew arg_slew = def3

#define NAMED_FUNCTION(_FUNC_,  _ARGS_)\
class parameters\
{\
public:\
	factory_slew::type operator[](const factory_slew&) { return arg_slew.value; }\
	factory_score::type operator[](const factory_score&) { return arg_score.value; }\
	factory_name::type operator[](const factory_name&) { return arg_name.value; }\
\
	parameters(wrapper_score arg_score_, wrapper_slew arg_slew_, wrapper_name arg_name_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
	parameters(wrapper_score arg_score_, wrapper_name arg_name_, wrapper_slew arg_slew_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
	parameters(wrapper_slew arg_slew_, wrapper_score arg_score_, wrapper_name arg_name_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
	parameters(wrapper_slew arg_slew_, wrapper_name arg_name_, wrapper_score arg_score_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
	parameters(wrapper_name arg_name_, wrapper_score arg_score_, wrapper_slew arg_slew_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
	parameters(wrapper_name arg_name_, wrapper_slew arg_slew_, wrapper_score arg_score_) :arg_score(arg_score_), arg_slew(arg_slew_), arg_name(arg_name_) {}\
\
private:\
	wrapper_score arg_score;\
	wrapper_slew arg_slew;\
	wrapper_name arg_name;\
\
};\
\
void BOOST_PP_CAT(_FUNC_, _impl(parameters param);)\
\
void f(wrapper_score arg_score_, wrapper_slew arg_slew_, wrapper_name arg_name_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
void f(wrapper_score arg_score_, wrapper_name arg_name_, wrapper_slew arg_slew_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
void f(wrapper_slew arg_slew_, wrapper_score arg_score_, wrapper_name arg_name_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
void f(wrapper_slew arg_slew_, wrapper_name arg_name_, wrapper_score arg_score_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
void f(wrapper_name arg_name_, wrapper_score arg_score_, wrapper_slew arg_slew_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
void f(wrapper_name arg_name_, wrapper_slew arg_slew_, wrapper_score arg_score_)\
{\
	f_impl(parameters(arg_score_, arg_slew_, arg_name_));\
}\
\
void BOOST_PP_CAT(_FUNC_, _impl(parameters param))