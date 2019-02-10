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
#include <rarrayio>
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

	for (int test = 0; test < num_tests; test++)
	{
	    static std::mt19937 engine(test+1);				// Create two random numbers to test the array initialization
	    std::uniform_int_distribution<int> uniformint_length(2, max_length);
	    std::uniform_int_distribution<int> uniformint_total(1, max_total);

	    int length = uniformint_length(engine);        	// length of the table
		int total = uniformint_total(engine);			// total number of ants on the table
		rarray<int,2> number_of_ants(length,length);

		total_cnt = 0;

		initialize_uniform(number_of_ants, total);

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{	
				total_cnt = total_cnt + number_of_ants[i][j]; // count the total number of ants
			}
		}

		std::cout << "Test number: " << test << std::endl;
		std::cout << "Length: " << length << " Total: " << total << std::endl;
		std::cout << number_of_ants << std::endl;	

		// Make sure the total number of ants initialized in the array is correct
		BOOST_CHECK(total==total_cnt);	
	}
}









