#include <iostream>
#include <sstream>
#include <exception>

#include "util.h"
#include "config.h"

using namespace std; //it's ok for .cpp file

namespace NElevator {

Config::Config(int argc, char** argv)
{
  if (argc < 5) {
    throw std::logic_error(generate_help_msg());
  }

  CheckAndAssign<long long>(argv[1], max_floor, 1);
  CheckAndAssign<float>(argv[2], floor_h, 0);
  CheckAndAssign<float>(argv[3], move_speed, 0);
  CheckAndAssign<float>(argv[4], doors_gap, 0);
}

std::string Config::generate_help_msg() {
  stringstream msg;
  msg << "Usage: ./elevator MAX_FLOOR FLOOR_HEIGHT ELEVATOR_MOVE_SPEED DOORS_TIME_GAP" << endl;
  msg << "---------------------------------------------------------------------------" << endl;
  msg << "MAX_FLOOR: integer, > 1"                                                     << endl;
  msg << "FLOOR_HEIGHT: positive float, meters"                                        << endl;
  msg << "ELEVATOR_MOVE_SPEED: positive float, meters/sec"                             << endl;
  msg << "DOORS_TIME_GAP: positive float, time between doors opening and closing, sec" << endl;

  return msg.str();
}

} // NElevator
