#pragma once

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_attribute.hpp>
#include <iostream>
#include <string>

using namespace boost::spirit::classic;
using namespace phoenix;


/*
group      = '(' >> expression >> ')';
factor     = integer | group;
term       = factor >> *(('*' >> factor) | ('/' >> factor));
expression = term >> *(('+' >> term) | ('-' >> term));
*/

struct vars : boost::spirit::classic::closure<vars, int>  //CRTP
{
	member1 value; //..called value in lazy expressions
};

//calculator is a grammar with attached int called value

struct calculator : public boost::spirit::classic::grammar<calculator, vars::context_t>   //CRTP
{
#if 0
	template <class Tokenizer>
	struct definition
	{
		//all our rules have an attached in called "value" too...
		boost::spirit::classic::rule<Tokenizer, vars::context_t> expression, term, factor, group, integer;

		//...except the top rule
		boost::spirit::classic::rule<Tokenizer> top;

		//build the grammar
		definition(calculator const& self)
		{
			top = expression[self.value = arg1];

			group = '(' >> expression[group.value = arg1] >> ')';

			factor = integer[factor.value = arg1] | group[factor.value = arg1];

			term = factor[term.value = arg1]
				>> *(  ('*' >> factor[term.value *= arg1])
					 | ('/' >> factor[term.value /= arg1])
					);

			expression = term[expression.value = arg1]
				>> *(  ('+' >> term[expression.value += arg1])
					 | ('-' >> term[expression.value -= arg1])
					);

			integer = int_p[integer.value = arg1];
		}
		
		//tell spirit to start parsing with "top"
		boost::spirit::classic::rule<Tokenizer> const& start() const { return top; }

	};
#endif
	template <class Tokenizer>
	struct definition
	{
		subrule<0, vars::context_t> expression;
		subrule<1, vars::context_t> group;
		subrule<2, vars::context_t> term;
		subrule<3, vars::context_t> factor;
		subrule<4, vars::context_t> integer;

		rule<Tokenizer> top;

		//build the grammar
		definition(calculator const& self)
		{
			top = (
				expression = term[expression.value = arg1]
				>> *(('+' >> term[expression.value += arg1])
					| ('-' >> term[expression.value -= arg1])
					),

				group = '(' >> expression[group.value = arg1] >> ')',

				factor = integer[factor.value = arg1] | group[factor.value = arg1],

				term = factor[term.value = arg1]
				>> *(('*' >> factor[term.value *= arg1])
					| ('/' >> factor[term.value /= arg1])),

				integer = int_p[integer.value = arg1]
				)[self.value = arg1];
		}

		//tell spirit to start parsing with "top"
		boost::spirit::classic::rule<Tokenizer> const& start() const { return top; }

	};
};



