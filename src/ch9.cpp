#include "stdafx.h"
#include "compose.h"
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "ch9.h"
#include <boost/function.hpp>
#include "sum.h"
#include <vector>
#include <list>
#include <boost\mpl\equal.hpp>
#include <boost\mpl\assert.hpp>
#include "generalized_iterator.h"
#include "calculator.h"
#include "named_parameters.h"

float input[5] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f };

float output[5];

float sin_squared(float x) { float y = std::sin(x); return y*y; }

float output2[5];

float output3[5];

float input2[5] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f };

float sin_squared2(float x) { return std::sin(std::sin(x));}

float mylog2(float x) { return std::log(x) / std::log(2.0f); }

typedef float(*floatfun)(float);

//float(*myfloatfun)(float) = &mylog2;

floatfun myfloatfun = mylog2;

float * ignored = std::transform(
	input, 
	input + 5, 
	output, 
	//compose<float>(std::negate<float>(), &sin_squared)
	compose<float>(std::negate<float>(), std::negate<float>())
);

float * also_ignored = std::transform(
	input2,
	input2 + 5,
	output2,
	compose_fg2<float, floatfun, sin_squared, floatfun, mylog2>()
	);

#if 0
float * also_also_ignored = std::transform(
	input,
	input + 5,
	output3,
	compose_fg2<float, floatfun, sin_squared, floatfun, myfloatfun>()
	);
#endif

template <class iterator_category>
void test_increment(generalized_iterator<int, iterator_category>& myIter)
{
	assert(1 == *(myIter));

	myIter.increment();
	assert(2 == *(myIter));

	myIter.increment();
	assert(3 == *(myIter));
}

template <class iterator_category>
void test_decrement(generalized_iterator<int, iterator_category>& myIter)
{
	myIter.decrement();
	assert(3 == *(myIter));

	myIter.decrement();
	assert(2 == *(myIter));

	myIter.decrement();
	assert(1 == *(myIter));
}

template <class iterator_category>
void test_random_access(generalized_iterator<int, iterator_category>& myIter)
{
	assert(1 == myIter[0]);

	assert(2 == myIter[1]);

	assert(3 == myIter[2]);
}

namespace Eparameter
{
	NAMED_PARAMETER(slew, float);
	NAMED_PARAMETER(name, char*);
	NAMED_PARAMETER(score, int);

	NAMED_FUNCTION(f, score, 0, name, "x", slew, (float)0.1)
	//NAMED_FUNCTION(f, score, 0, name, "x", slew, (float)0.1)
	//NAMED_FUNCTION(f, ((score, 0), (name, "x"), (slew, (float)0.1)))
	//NAMED_FUNCTION(f, ((score,0))((name,"x"))((slew,(float)0.1)))
	{
		std::cout << "score: " << score.value << " name: " << name.value << " slew: " << slew.value << std::endl;
	}
};

/*
void f(int score = 0, char* name = "x", float slew = 0.1)
{
	std::cout << "score: " << score << " name: " << name << " slew: " << slew << std::endl;
}*/




/*
void f(Eparameter::args args)
{
	f(args.score, args.name, args.slew);
}
*/





int ch9(int argc, _TCHAR* argv[])
{
	std::vector<int> simple1;
	simple1.push_back(1);
	simple1.push_back(25);
	simple1.push_back(134);
	simple1.push_back(34);
	simple1.push_back(59);

	std::vector<int> simple2;
	simple2.push_back(23);
	simple2.push_back(65);
	simple2.push_back(34);
	simple2.push_back(78);
	simple2.push_back(1313);

	std::vector<std::vector<int>> complex1;
	complex1.push_back(simple1);
	complex1.push_back(simple2);

	std::vector<int> simple3;
	simple3.push_back(54);
	simple3.push_back(87);
	simple3.push_back(15);
	simple3.push_back(78);
	simple3.push_back(13113);

	std::vector<int> simple4;
	simple4.push_back(83);
	simple4.push_back(27);
	simple4.push_back(1);
	simple4.push_back(2);
	simple4.push_back(2);

	std::vector<std::vector<int>> complex2;
	complex2.push_back(simple3);
	complex2.push_back(simple4);

	std::vector<std::vector<std::vector<int>>> supercomplex;
	supercomplex.push_back(complex1);
	supercomplex.push_back(complex2);
	
	std::cout << "output: " << output[0] << " " << output[1] << " " << output[2] << " " << output[3] << " " << output[4] << std::endl;

	std::cout << "output2: " << output2[0] << " " << output2[1] << " " << output2[2] << " " << output2[3] << " " << output2[4] << std::endl;

	std::cout << "output3: " << output3[0] << " " << output3[1] << " " << output3[2] << " " << output3[3] << " " << output3[4] << std::endl;

	std::cout << myfloatfun(1) << std::endl;

	std::cout << "simple list sum 1 : " << sum(simple1.begin(), simple1.end()) << std::endl;//253

	std::cout << "simple list sum 2 : " << sum(simple2.begin(), simple2.end()) << std::endl;//1513

	std::cout << "complex 1 list sum: " << sum(complex1.begin(), complex1.end()) << std::endl;//1766
	
	std::cout << "simple list sum 3 : " << sum(simple3.begin(), simple3.end()) << std::endl; //13347

	std::cout << "simple list sum 4 : " << sum(simple4.begin(), simple4.end()) << std::endl; //115

	std::cout << "complex 2 list sum: " << sum(complex2.begin(), complex2.end()) << std::endl; //13462

	std::cout << "supercomplex list sum: " << sum(supercomplex.begin(), supercomplex.end()) << std::endl; //15228

	std::vector<int> myVec;
	myVec.push_back(1);
	myVec.push_back(2);
	myVec.push_back(3);

	test_increment(make_iterator_wrapper(myVec.begin()));

	test_decrement(make_iterator_wrapper(myVec.end()));

	test_random_access(make_iterator_wrapper(myVec.begin()));

	std::list<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);

	test_increment(make_iterator_wrapper(myList.begin()));

	test_decrement(make_iterator_wrapper(myList.end()));

	calculator calc; ///our grammar

	std::string str;



	using namespace Eparameter;

	//f(score = 3);
	//f(score = 3, name = "e");
	//f(slew = (float)0.799, name = "z", score = 4);
	f(score = 2, name = "x", slew = (float)0.599);
	f(score = 3, name = "e");
	//f(name = "t", slew = (float)0.389, score = 8);
	//f();
	//f(3, "y", 0.2);

	while (std::getline(std::cin, str))
	{
		int n = 0;
		boost::spirit::classic::parse(str.c_str(), calc[phoenix::var(n) = phoenix::arg1], boost::spirit::classic::space_p);
		std::cout << "result = " << n << std::endl;
	}


	return 0;
}


