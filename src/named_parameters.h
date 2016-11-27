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

#define NAMED_FUNCTION(_FUNC_, _ARG1_, _DEFAULT1_, _ARG2_, _DEFAULT2_, _ARG3_, _DEFAULT3_)\
void _FUNC_(wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_, wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_);\
void _FUNC_(wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_, wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_)\
{\
_FUNC_(_ARG1_, _ARG2_, _ARG3_);\
}\
void _FUNC_(wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_, wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_)\
{\
_FUNC_(_ARG1_, _ARG2_, _ARG3_);\
}\
void _FUNC_(wrapper_##_ARG1_ arg1, wrapper_##_ARG2_ _ARG2_, wrapper_##_ARG3_ _ARG3_)\

/*
#define NAMED_ARG(r, data, elem) (BOOST_PP_CAT(wrapper_, elem) elem)  //expands to (wrapper_elem elem)

#define NAMED_ARG_DEF(r, data, elem) (BOOST_PP_CAT(wrapper_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) BOOST_PP_TUPLE_ELEM(2, 0, elem) = BOOST_PP_TUPLE_ELEM(2, 1, elem))  //expands to (wrapper_elem[0] elem[0] = elem[1])

#define NAMED_ARG_SEQ(_ARGS_) BOOST_PP_SEQ_FOR_EACH(NAMED_ARG_DEF, dummy, _ARGS_)  //expands to (wrapper_arg1 arg1 = def1)(wrapper_arg2 arg2 = def2) ...

#define NAMED_ARG_LIST(_ARGS_) BOOST_PP_SEQ_ENUM(NAMED_ARG_SEQ(_ARGS_))         //expands to wrapper_arg1 arg1 = def1, wrapper_arg2 arg2 = def2, ...

#define NAMED_FUNCTION(_FUNC_,  _ARGS_) void _FUNC_(NAMED_ARG_LIST(_ARGS_))    //ARGS = ((score,0))((name,"x"))((slew,0.1)))

#define NAMED_ARG_DEF(r, data, elem) (BOOST_PP_CAT(wrapper_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) BOOST_PP_TUPLE_ELEM(2, 0, elem) = BOOST_PP_TUPLE_ELEM(2, 1, elem))  //expands to (wrapper_elem[0] elem[0] = elem[1])

#define NAMED_ARG(r, data, elem) (BOOST_PP_CAT(wrapper_, BOOST_PP_TUPLE_ELEM(2, 0, elem)) BOOST_PP_TUPLE_ELEM(2, 0, elem))  //expands to (wrapper_elem[0] elem[0])

#define NAMED_ARG_SEQ(_ARGS_) BOOST_PP_SEQ_FOR_EACH(NAMED_ARG_DEF, dummy, _ARGS_)  //expands to (wrapper_arg1 arg1 = def1)(wrapper_arg2 arg2 = def2) ...

#define NAMED_ARG_LIST(_ARGS_) BOOST_PP_SEQ_ENUM(NAMED_ARG_SEQ(_ARGS_))         //expands to wrapper_arg1 arg1 = def1, wrapper_arg2 arg2 = def2, ...

#define NAMED_ARG_SEQ_NO_DEFAULTS(_ARGS_) BOOST_PP_SEQ_FOR_EACH(NAMED_ARG, dummy, _ARGS_)  //expands to (wrapper_arg1 arg1)(wrapper_arg2 arg2) ...

#define NAMED_ARG_LIST_NO_DEFAULTS(_ARGS_) BOOST_PP_SEQ_ENUM(NAMED_ARG_SEQ_NO_DEFAULTS(_ARGS_))         //expands to wrapper_arg1 arg1, wrapper_arg2 arg2, ...

#define NAMED_FUNCTION_INVOKER(_FUNC_, _ARGS1_, _TARGET_ARGS_)\
void _FUNC_( NAMED_ARG_LIST(_ARGS1_))\
{\
_FUNC_( NAMED_ARG_LIST(_TARGET_ARGS_) );\
}\

//ARGS = ((score,0))((name,"x"))((slew,0.1)))
//#define NAMED_FUNCTION(_FUNC_, _ARGS_) void _FUNC_( NAMED_ARG_LIST(_ARGS_) )

#define NAMED_FUNCTION(_FUNC_, _ARGS_) \
void _FUNC_( NAMED_ARG_LIST(_ARGS_) );\
\
NAMED_FUNCTION_INVOKER(_FUNC_, _TARGET_ARGS_, _TARGET_ARGS_)\
\
void _FUNC_( NAMED_ARG_LIST_NO_DEFAULTS(_ARGS_) )\


BOOST_PP_SEQ_FOR_EACH_PRODUCT((_ARGS_)(

	*/
//\
//void _FUNC_( NAMED_ARG_LIST(_ARGS_) )\

/*
void _FUNC_(wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_, wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_); \
void _FUNC_(wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_, wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_)\
{\
_FUNC_(_ARG1_, _ARG2_, _ARG3_);\
}\
void _FUNC_(wrapper_##_ARG2_ _ARG2_ = _DEFAULT2_, wrapper_##_ARG3_ _ARG3_ = _DEFAULT3_, wrapper_##_ARG1_ _ARG1_ = _DEFAULT1_)\
{\
_FUNC_(_ARG1_, _ARG2_, _ARG3_);\
}\
void _FUNC_(wrapper_##_ARG1_ arg1, wrapper_##_ARG2_ _ARG2_, wrapper_##_ARG3_ _ARG3_)\
*/

#define NAMED_PARAMETER(_NAME_, _TYPE_)\
typedef arg_wrapper<_TYPE_> wrapper_##_NAME_;\
wrapper_##_NAME_ _NAME_;\

//TODO: allow any argument order!!!!
