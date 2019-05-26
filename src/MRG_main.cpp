// MRG_main.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <ostream>
#include <limits>
#include <algorithm>
#include <functional>
#include <thread>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionProcessor.h>

#include "MRG.h"
#include "ofApp.h"


using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionProcessor;

static constexpr int WINDOW_HEIGHT = 768;
static constexpr int WINDOW_WIDTH = 1024;


void print_usage(const char * app_name)
{
  printf("%s [--help] [--cache-off] [--record-video=video_name] <axon-file> <V_fe> <V_applied> "
         "<period> <stim-start> <stim-end> [time-steps]\n", app_name);

  puts("    [--help]         print this usage help message");
  puts("    [--cache-off]    calculate the model for every period");
  puts("    [--record-video] record animation to video");
  puts("    <axon file>      tab separated values file describing the axon (see reference)");
  puts("    <V_fe>           background voltage (mV)");
  puts("    <V_applied>      voltage being applied by stimulus (mV)");
  puts("    <period>         periodic duration of applied stimulus (ms)");
  puts("    <stim start>     start time within period of applied stimulus (ms)");
  puts("    <stim end>       end time within period of applied stimulus (ms)");
  puts("    [time-steps]     number of time steps in a period (aka time resolution)\n");
}

int main(int argc, char ** argv)
{
  // std::cout.precision(11);
  // std::cout.setf(std::ios::fixed);
  std::cout << "Machine Epsilon is: " << std::numeric_limits<MRG_REAL>::epsilon() << std::endl << std::endl;

  OptionSet opt_set;
  opt_set.addOption(Option("help", "h"));
  opt_set.addOption(Option("cache-off", "c"));
  opt_set.addOption(Option("record-video", "r").argument("video_name"));

  OptionProcessor opt_processor(opt_set);
  opt_processor.setUnixStyle(true);

  int arg_pos = 0;
  std::string axon_file_path;
  std::string video_name;
  MRG_REAL V_fe = 0.0;
  MRG_REAL V_applied = 0.0;
  MRG_REAL period = 0.0;
  MRG_REAL stim_start = 0.0;
  MRG_REAL stim_end = 0.0;
  unsigned int time_steps = 0;
  bool cache_on = true;

  for (int i = 1; i < argc; ++i) {
    std::string opt_name, opt_arg;
    bool result = opt_processor.process(argv[i], opt_name, opt_arg);
    if (result) {
      if (opt_name == "help") {
        print_usage(argv[0]);
        return 0;
      } else if (opt_name == "cache-off") {
        cache_on = false;
      } else if (opt_name == "record-video") {
        video_name = std::move(opt_arg);
      }
    } else {
      char * endptr = nullptr;

      if (arg_pos == 0) {
        axon_file_path = argv[i];
      } else if (arg_pos == 1) {
        V_fe = strtod(argv[i], &endptr);
      } else if (arg_pos == 2) {
        V_applied = strtod(argv[i], &endptr);
      } else if (arg_pos == 3) {
        period = strtod(argv[i], &endptr);
      } else if (arg_pos == 4) {
        stim_start = strtod(argv[i], &endptr);
      } else if (arg_pos == 5) {
        stim_end = strtod(argv[i], &endptr);
      } else if (arg_pos == 6) {
        time_steps = strtoul(argv[i], &endptr, 10);
      }

      if (endptr != nullptr && *endptr != '\0') {
        printf("error: invalid number (got %s)\n", argv[i]);
        return -1;
      }

      ++arg_pos;
    }
  }

  // error checking
  if (arg_pos < 6) {
    puts("error: not enough arguments given\n");
    print_usage(argv[0]);
    return -1;
  }
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
  if (time_steps == 0) {
    time_steps = std::max(static_cast<unsigned int>(100 * period), 100u);
  }

  ofDisableDataPath();

  // instantiate a neuron model
  MRG neuron_model(axon_file_path.c_str());
  std::thread t(&MRG::run, &neuron_model, V_fe, V_applied, period, stim_start, stim_end, time_steps, cache_on);

  ofGLFWWindowSettings settings;
  settings.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  settings.resizable = false;
  settings.title = "Axon Node Voltages";
  settings.windowMode = OF_WINDOW;
  ofCreateWindow(settings);
  // this kicks off the running of my app can be OF_WINDOW or OF_FULLSCREEN pass in width and height too:
  // ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);  // <-------- setup the GL context
  ofRunApp(new ofApp(neuron_model, video_name));

  return 0;
}
