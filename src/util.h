#pragma once

#include <string>
#include <sstream>
#include <chrono>
#include <cmath>

namespace NElev {

template<typename Type>
Type from_string(const std::string& s) {
  std::stringstream ss(s);
  Type result;
  ss >> result;
  return result;
}

std::chrono::duration<int, std::milli> ToSeconds(float value);

} // NElev
