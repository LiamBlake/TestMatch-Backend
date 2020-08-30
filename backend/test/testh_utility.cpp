#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
//#include <boost/mpl/list.hpp>

#include <iostream>
#include <string>
#include <utility>
#include <exception>

#include "Utility.h"

BOOST_AUTO_TEST_SUITE(test_header_utility)


BOOST_AUTO_TEST_CASE(testfunc_split_str)
{
	std::vector<std::string> expected;

	// Boundary case - empty string
	BOOST_TEST(split_str("").empty());

	// Boundary case - just delimeter
	expected.push_back("");
	expected.push_back("");
	BOOST_TEST(split_str(",") == expected);
	expected.clear();

	// Boundary case - no delimeter
	expected.push_back("test");
	BOOST_TEST(split_str("test") == expected);
	expected.clear();

	// Standard case - default delimeter
	expected.push_back("a");
	expected.push_back("b");
	expected.push_back("c");
	BOOST_TEST(split_str("a,b,c") == expected);

	// Standard case - delimeter at end
	expected.push_back("");
	BOOST_TEST(split_str("a,b,c,") == expected);

	// Standard case - delimeter at start
	expected.pop_back();
	expected.insert(expected.begin(), "");
	BOOST_TEST(split_str(",a,b,c") == expected);
	expected.clear();

	// Standard case - other delimeter
	expected.push_back("1");
	expected.push_back("2");
	expected.push_back("3");
	BOOST_TEST(split_str("1 2 3", " ") == expected);

	// Standard case - other delimeter
	BOOST_TEST(split_str("1thisisadelimeter2thisisadelimeter3", "thisisadelimeter") == expected);
}



BOOST_AUTO_TEST_SUITE_END()