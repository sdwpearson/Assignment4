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
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE initialization_bt
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(initialize_uniform_test)
{
    int length = 5;        // length of the table
	int total = 100;		// total number of ants on the table
	rarray<int,2> number_of_ants(length,length);

	initialize_uniform(number_of_ants, total);

	std::cout << number_of_ants << std::endl;
}









