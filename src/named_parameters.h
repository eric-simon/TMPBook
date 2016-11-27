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

#define NAMED_PARAMETER(_NAME_, _TYPE_)\
typedef arg_wrapper<_TYPE_> wrapper_##_NAME_;\
wrapper_##_NAME_ _NAME_;\

