// MRG_main.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <ostream>
#include <limits>
#include <functional>
#include <thread>

#include "MRG.h"
#include "ofApp.h"


static constexpr int BUFFER_SIZE = 1000;


void print_usage(const char * app_name)
{
  printf("%s <axon file> <V_fe> <V_applied> <period> <stim start> <stim end>\n", app_name);
  puts("    <axon file>   tab separated values file describing the axon (see reference)");
  puts("    <V_fe>        background voltage (mV)");
  puts("    <V_applied>   voltage being applied by stimulus (mV)");
  puts("    <period>      periodic duration of applied stimulus (ms)");
  puts("    <stim start>  start time within period of applied stimulus (ms)");
  puts("    <stim end>    end time within period of applied stimulus (ms)\n");
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
  MRG_REAL period = strtod(argv[4], NULL);
  MRG_REAL stim_start = strtod(argv[5], NULL);
  MRG_REAL stim_end = strtod(argv[6], NULL);

  if (period <= 0.0) {
    printf("error: <period> needs to be greater than zero (got %f)\n", period);
    return -1;
  }
  if (stim_start < 0.0 || stim_start >= period) {
    printf("error: <stim start> needs to be a positive value between 0.0 and <period> (got %f)\n", stim_start);
    return -1;
  }
  if (stim_end <= 0.0 || stim_start > period) {
    printf("error: <stim start> needs to be a positive value between 0.0 and <period> (got %f)\n", stim_end);
    return -1;
  }
  if (stim_start >= stim_end) {
    printf("error: <stim end> needs to be greater than <stim start> (got [%f, %f])\n", stim_start, stim_end);
    return -1;
  }

  MRG neuron_model;
  RingBuffer<MRG_MATRIX_REAL> output_buffer(BUFFER_SIZE);
  std::thread t(&MRG::run, &neuron_model, axon_file_path, V_fe, V_applied,
                period, stim_start, stim_end, std::ref(output_buffer));

  // this kicks off the running of my app can be OF_WINDOW or OF_FULLSCREEN pass in width and height too:
  ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context
  ofRunApp(new ofApp());

  return 0;
}
