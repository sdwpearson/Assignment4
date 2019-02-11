// randompartition_bt.cc
//
// Boost test to verify the random partition function
// partitions the array with the correct total number of ants. 
//
// PHY1610 Assignment 4
// Stewart Pearson, University of Toronto
// February 10, 2019

#include "randompartition.h"
#include <rarray>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE randompartition_bt
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(randompartition_test)
{
	int num_tests = 10;				// total number of tests to run
	int nparts = 10;				// number of parts to partition the array
	int total = 100;				// total amount of numbers to partition
	int sum = 0;					// sum of the elements in the array
	rarray<int,1> nperpart(nparts);

	for (int test = 0; test < num_tests; test++)
	{
		rand_partition(total, nparts, nperpart, test+1);

		// clear sum variable each test
		sum = 0;
		for (int part = 0; part < nparts; part++)
		{	
			// increment sum for each part of the array
			sum += nperpart[part];
		}

		// verify that all of the array entries add up to the specified total
		BOOST_CHECK(sum == total);
	}
}









