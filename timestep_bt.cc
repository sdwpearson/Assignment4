// timestep_bt.cc
//
// Boost test to verify the total number of ants either remains constant
// or decreases after each timestep. 
//
// PHY1610 Assignment 4
// Stewart Pearson, University of Toronto
// February 10, 2019

#include "initialization.h"
#include "timestep.h"
#include "randompartition.h"
#include <rarray>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE timestep_bt
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(perform_one_timestep_test)
{
	int num_tests = 10;				// total number of tests to run
	int nparts = 10;				// number of parts to partition the array
	int total = 236;				// total amount of ants to partition evenly
	int total_check = 0;			// total from the ant array to compare against
	int seed = 11;					// randomization seed
	int length = 20;				// length of the test array

	rarray<int,2> number_of_ants(length, length);			// number_of_ants array to test
	rarray<int,2> new_number_of_ants(length, length);		// auxiliary number_of_ants array to test


	initialize_uniform(number_of_ants, total);

	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		{
			total_check += number_of_ants[i][j];
		}
	}

	// Make sure that the array is initialized with the correct total number of ants
	BOOST_CHECK(total_check == total);

	perform_one_timestep(number_of_ants, new_number_of_ants, seed);

	// Reset total_check
	total_check = 0;
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		{
			total_check += number_of_ants[i][j];
		}
	}

	// Make sure that the array has an equal or less total amount of ants after one timestep
	BOOST_CHECK(total_check <= total);
}









