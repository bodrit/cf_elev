#pragma once

#include <string>

#include "util.h"

namespace NElev {

struct Config {
public:
  Config() = default;

  Config(int argc, char** argv);

  template<typename Type>
  void CheckAndAssign(char* s, Type& var, Type min) {
    try {
      Type tmp = from_string<Type>(s);

      if (tmp <= min)
        throw std::logic_error(generate_help_msg());

      var = tmp;
    } catch (const std::exception& ) {
      throw std::logic_error(generate_help_msg());
    }
  }

  static std::string generate_help_msg();

public:
  long long max_floor = 2;
  float floor_h = 3;
  float move_speed = 1;
  float doors_gap = 1;
};

} // NElev
