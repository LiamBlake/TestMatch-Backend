#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
//#include <boost/mpl/list.hpp>

#include <iostream>
#include <string>
#include <utility>
#include <exception>

#include "Player.h"
#include "Cards.h"

using namespace boost::unit_test;

// Player examples for testing
Player tp_bat("Marnus", "Labuschagne", "M", { 23, 63.43, 56.52, 756, 38.66,  63.0, 3.68, false, 5 }, "Australia");
Player tp_bowl("Trent", "Boult", "TA", { 82, 15.2, 56.86, 14874, 27.65, 55.7, 2.97, false, 8 }, "New Zealand");
Player tp_field("BJ", "Watling", "BJ", { 110, 38.5, 42.35, -1, -1, -1, -1, false, -1 }, "New Zealand");

BOOST_AUTO_TEST_SUITE(test_header_cards)

// Test cases for Dismissal class
BOOST_AUTO_TEST_CASE(testclass_dismissal) {

	// Expected dismissal strings
	std::string disms[5] = { "b Boult",
							"lbw Boult",
							"c Watling b Boult",
							"run out (Watling)",
							"st Watling b Boult" };
	// Expected bowler pointers
	Player* expect_bowl[5] = { &tp_bowl,
							 &tp_bowl,
							 &tp_bowl,
							 nullptr,
							 &tp_bowl };
	// Expected fielder pointers
	Player* expect_field[5] = { nullptr,
							   nullptr,
							   &tp_field,
							   &tp_field,
							   &tp_field };


	// Automated - making use of the fact that 
	// bowler and fielder pointers can be passed
	// even if dismissal doesn't involve them
	for (int i = 0; i < 5; i++) {
		Dismissal x(i, &tp_bowl, &tp_field);

		// Test getters
		BOOST_TEST(x.get_mode() == i);
		BOOST_TEST(x.get_bowler() == expect_bowl[i]);
		BOOST_TEST(x.get_fielder() == expect_field[i]);

		// Test print_dism() functionality
		BOOST_TEST(x.print_dism() == disms[i]);
	}

	// Invalid dismissial mode - should throw invalid_argument
	BOOST_CHECK_THROW(Dismissal(-1), std::invalid_argument);
	BOOST_CHECK_THROW(Dismissal(1583), std::invalid_argument);

}



void testcases_battercard(std::pair<std::string, std::string> x) {


}

BOOST_AUTO_TEST_CASE(testclass_battercard) {
	// Test object
	BatterCard bc(&tp_bat);

	// Ensure correct initialisation
	BOOST_TEST(bc.print_card() == "M Labuschagne not out 0 (0b 0x4 0x6) SR: -");

	// Use array of pairs to test outcomes
	std::pair<std::string, std::string> outcomes[18] = {
			{ "0", "M Labuschagne not out 0 (1b 0x4 0x6) SR: 0.00" },
			{ "1", "M Labuschagne not out 1 (2b 0x4 0x6) SR: 50.00" },
			{ "2", "M Labuschagne not out 3 (3b 0x4 0x6) SR: 100.00" },
			{ "3", "M Labuschagne not out 6 (4b 0x4 0x6) SR: 150.00" },
			{ "4", "M Labuschagne not out 10 (5b 1x4 0x6) SR: 200.00" },
			{ "5", "M Labuschagne not out 15 (6b 2x4 0x6) SR: 250.00" },
			{ "6", "M Labuschagne not out 21 (7b 2x4 1x6) SR: 300.00" },
			{ "1nb", "M Labuschagne not out 21 (8b 2x4 1x6) SR: 262.50" },
			{ "2nb", "M Labuschagne not out 22 (9b 2x4 1x6) SR: 244.44" },
			{ "5nb", "M Labuschagne not out 26 (10b 3x4 1x6) SR: 260.00" },
			{ "7nb", "M Labuschagne not out 32 (11b 3x4 2x6) SR: 290.91" },
			{ "1lb", "M Labuschagne not out 32 (12b 3x4 2x6) SR: 266.67" },
			{ "1lb", "M Labuschagne not out 32 (13b 3x4 2x6) SR: 246.15" },
			{ "4lb", "M Labuschagne not out 32 (14b 3x4 2x6) SR: 228.57" },
			{ "1b", "M Labuschagne not out 32 (15b 3x4 2x6) SR: 213.33" },
			{ "1b", "M Labuschagne not out 32 (16b 3x4 2x6) SR: 200.00" },
			{ "4b", "M Labuschagne not out 32 (17b 3x4 2x6) SR: 188.24" },
			{ "1w", "M Labuschagne not out 32 (17b 3x4 2x6) SR: 188.24" } };

	for (int i = 0; i < 18; i++) {
		bc.update_score(outcomes[i].first);
		BOOST_TEST(bc.print_card() == outcomes[i].second);
	}

	// Dismissial
	bc.update_score("W");
	bc.dismiss(0, &tp_bowl);
	BOOST_TEST(bc.print_card() == "M Labuschagne b Boult 32 (18b 3x4 2x6) SR: 177.78");


}


BOOST_AUTO_TEST_CASE(testclass_bowlercard) {
	// Test object
	BowlerCard bc(&tp_bowl);

	// Check initialisation
	BOOST_TEST(bc.print_card() == "TA Boult 0.0-0-0-0");

	// Use array of pairs to test outcomes
	std::pair<std::string, std::string> outcomes[21] = {
		{"0", "TA Boult 0.1-0-0-0"},
		{"0", "TA Boult 0.2-0-0-0"},
		{"0", "TA Boult 0.3-0-0-0"},
		{"0", "TA Boult 0.4-0-0-0"},
		{"0", "TA Boult 0.5-0-0-0"},
		{"0", "TA Boult 1.0-1-0-0"},
		{"1", "TA Boult 1.1-1-1-0"},
		{"2", "TA Boult 1.2-1-3-0"},
		{"3", "TA Boult 1.3-1-6-0"},
		{"4", "TA Boult 1.4-1-10-0"},
		{"5", "TA Boult 1.5-1-15-0"},
		{"6", "TA Boult 2.0-1-21-0"},
		{"1nb", "TA Boult 2.0-1-22-0"},
		{"5nb", "TA Boult 2.0-1-27-0"},
		{"1b", "TA Boult 2.1-1-27-0"},
		{"4b", "TA Boult 2.2-1-27-0"},
		{"1lb", "TA Boult 2.3-1-27-0"},
		{"4lb", "TA Boult 2.4-1-27-0"},
		{"1w", "TA Boult 2.4-1-28-0"},
		{"5w", "TA Boult 2.4-1-33-0"},
		{"W", "TA Boult 2.5-1-33-1"} };


	for (int i = 0; i < 21; i++) {
		bc.update_score(outcomes[i].first);
		BOOST_TEST(bc.print_card() == outcomes[i].second);
	}


}


BOOST_AUTO_TEST_CASE(testclass_over) {
	// Test object
	Over o(1);

}


BOOST_AUTO_TEST_CASE(teststruct_fow) {
	// Test obect 
	FOW f = { &tp_bat, 1, 20, 8, 2 };
	BOOST_TEST(f.print() == "1-20 (Marnus Labuschagne, 8.2 ov)");

	// TEST INVALID VALUE
}


BOOST_AUTO_TEST_CASE(teststruct_extras) {
	// Test obect 
	Extras e = { 0, 0, 0, 0 };

	// Should print nothing
	BOOST_TEST(e.print() == "");


	// TEST INVALID VALUE
}



BOOST_AUTO_TEST_SUITE_END()