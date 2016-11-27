#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/cat.hpp>

template <class Type>
struct arg_wrapper
{
	arg_wrapper(Type arg) :value(arg) {};
	arg_wrapper() {};
	arg_wrapper operator=(Type arg) { value = arg; return *this; }
	Type value;
};

#define NAMED_PARAMETER(_NAME_, _TYPE_)\
typedef arg_wrapper<_TYPE_> wrapper_##_NAME_;\
wrapper_##_NAME_ _NAME_;\

#define NAMED_ARG(r, data, elem) (BOOST_PP_CAT(wrapper_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) BOOST_PP_TUPLE_ELEM(2, 0, elem) = BOOST_PP_TUPLE_ELEM(2, 1, elem))  //expands (elem[0], elem[1]) to (wrapper_elem[0] elem[0] = elem[1])

#define NAMED_ARG_SEQ(_ARGS_) BOOST_PP_SEQ_FOR_EACH(NAMED_ARG, dummy, _ARGS_)  //expands ((arg1,def1))((arg2,def2)) to (wrapper_arg1 arg1 = def1)(wrapper_arg2 arg2 = def2) ...

#define NAMED_ARG_LIST(_ARGS_) BOOST_PP_SEQ_ENUM(NAMED_ARG_SEQ(_ARGS_))         //expands ((arg1,def1))((arg2,def2)) to wrapper_arg1 arg1, wrapper_arg2 arg2, ...

#define NAMED_FUNCTION(_FUNC_,  _ARGS_) void _FUNC_(NAMED_ARG_LIST(_ARGS_))    //ARGS = ((score, 0))((name, "x"))((slew, 0.1)) expands to wrapper_score score = def1, wrapper_name name = def2, wrapper_slew slew = def3

