// initialization_bt.cc
//
// Boost test to verify the initializiation funciton
// evenly initializes a small array 10 times. 
//
// PHY1610 Assignment 4
// Stewart Pearson, University of Toronto
// February 10, 2019

#include "initialization.h"
#include <rarray>
#include <random>
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE initialization_bt
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(initialize_uniform_test)
{
	int num_tests = 10;			// total number of tests to run
	int max_total = 100;		// maximum total number of ants for the random generator
	int max_length = 8;			// maximum length of the table dimensions for the random generator
	int total_cnt = 0;			// counts all of the ants to make sure it's the same as the specified total
	int uni_ant = 0;			// lower bound on the uniform distribution of ants to check against.
	bool uni_check = false;		// boolean variable to see if the cell has the correct number of ants
	std::random_device rd;		// creates a random seed for the array initialization

	for (int test = 0; test < num_tests; test++)
	{
	    static std::mt19937 engine(rd());										// Create two random numbers to test the array initialization
	    std::uniform_int_distribution<int> uniformint_length(2, max_length);	// Randomize the length of the array
	    std::uniform_int_distribution<int> uniformint_total(1, max_total);		// Randomize the total ants to put in the array

	    int length = uniformint_length(engine);        	// length of the table
		int total = uniformint_total(engine);			// total number of ants on the table
		rarray<int,2> number_of_ants(length,length);	// Initialize the randomized array

		total_cnt = 0;						// Reset the total count of the ants in the array
		uni_ant = total/(length*length);	// Find the lower bound of the ants in each cell.

		initialize_uniform(number_of_ants, total);	// Initialize the ants on the table

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{	
				total_cnt = total_cnt + number_of_ants[i][j]; // count the total number of ants
				
				// Check that each ant entry has a uniform number of ants. If the length of the table
				// and the total number of ants don't line up nicely you get leftovers which is why in 
				// some cases you'll have uni_ant+1 ants in a cell. Ex. length = 2 and total = 7 will
				// yield 7/4 = 1.75 so some cells have one ant others have two.
				uni_check = number_of_ants[i][j] == uni_ant || number_of_ants[i][j] == uni_ant+1;
				BOOST_CHECK(uni_check);
			}
		}

		// Make sure the total number of ants initialized in the array is correct
		BOOST_CHECK(total==total_cnt);	
	}
}









