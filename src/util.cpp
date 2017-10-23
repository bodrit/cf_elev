#include "util.h"

namespace NElev {

std::chrono::duration<int, std::milli> ToSeconds(float value) {
  return std::chrono::milliseconds(static_cast<int>(std::floor(value * 1000)));
}

} // NElev
