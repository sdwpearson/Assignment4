// timestep_bt.cc
//
// Boost test to verify the total number of ants either remains constant
// or decreases after each timestep. 
//
// PHY1610 Assignment 4
// Stewart Pearson, University of Toronto
// February 10, 2019

#include "timestep.h"
#include "randompartition.h"
#include <rarray>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE timestep_bt
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(perform_one_timestep_test)
{
	int number_of_ants_init = 3;	// initialize each entry of number of ants array to this number
	int total = 0;					// total amount of ants to partition evenly
	int total_check = 0;			// total from the ant array to compare against
	int seed = 11;					// randomization seed
	int length = 20;				// length of the test array

	rarray<int,2> number_of_ants(length, length);			// number_of_ants array to test
	rarray<int,2> new_number_of_ants(length, length);		// auxiliary number_of_ants array to test

	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length; j++)
		{
			number_of_ants[i][j] = number_of_ants_init;
		}
	}

	total = number_of_ants_init*length*length; // Total number of ants in the table

	perform_one_timestep(number_of_ants, new_number_of_ants, seed);

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









