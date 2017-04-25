#pragma once

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <iostream>
#include <string>

namespace qi = boost::spirit::qi;


/*
line       = *(expression >> separator) >> *expression >> *'\n'
separator  = *(*' ' | *'\t')
//expression = doubleExpr
*/

template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v)
{
	using boost::spirit::qi::double_;
	using boost::spirit::qi::phrase_parse;
	using boost::spirit::qi::_1;
	using boost::spirit::ascii::space;
	//using boost::phoenix::ref;

	bool r = phrase_parse(first, last,

		//  Begin grammar
		(
			double_[boost::phoenix::push_back(boost::phoenix::ref(v), _1)]
			>> *(',' >> double_[boost::phoenix::push_back(boost::phoenix::ref(v), _1)])
			)
		,
		//  End grammar

		space);

	if (first != last) // fail if we did not get a full match
		return false;
	return r;
}




