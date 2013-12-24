// MRG_main.cpp : Defines the entry point for the console application.
//

#include <assert.h>
#include <stdio.h>
#include <ostream>
#include <limits>

#include "MRG.h"


int main(int argc, char **argv)
{
	std::cout << "Machine Epsilon is: " << std::numeric_limits<MRG_REAL>::epsilon() << std::endl << std::endl;

	assert(argc >= 2);

	// std::cout.precision(11);
	// std::cout.setf(std::ios::fixed);
	
	MRG neuron_model;
	// neuron_model.run(3, argv[1], 1, 1, 1, 2);
	neuron_model.run(3, argv[1], 1, 1, 0, 2);
	neuron_model.write_results("results.csv");
	neuron_model.debug_dump("debug_dump.csv");

	return 0;
}

