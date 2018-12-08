// MRG_main.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <ostream>
#include <limits>

#include "MRG.h"
#include "ofApp.h"


void print_usage(const char * app_name)
{
  printf("%s <axon file> <V_fe> <V_applied> <duration> <stim start> <stim end>\n", app_name);
}

int main(int argc, char ** argv)
{
  // std::cout.precision(11);
  // std::cout.setf(std::ios::fixed);
  std::cout << "Machine Epsilon is: " << std::numeric_limits<MRG_REAL>::epsilon() << std::endl << std::endl;

  if (argc < 7) {
    print_usage(argv[0]);
    return -1;
  }

  const char * axon_file_path = argv[1];
  MRG_REAL V_fe = strtod(argv[2], NULL);
  MRG_REAL V_applied = strtod(argv[3], NULL);
  MRG_REAL duration = strtod(argv[4], NULL);
  MRG_REAL stim_start = strtod(argv[5], NULL);
  MRG_REAL stim_end = strtod(argv[6], NULL);

  MRG neuron_model;

  neuron_model.run(duration, axon_file_path, V_fe, V_applied, stim_start, stim_end);

  neuron_model.write_results("results.csv");
  neuron_model.debug_dump("debug_dump.csv");

  ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp( new ofApp());

  return 0;
}
