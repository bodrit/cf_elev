#include <exception>

#include "gtest/gtest.h"
#include "config.h"

using namespace std;
using namespace NElev;

namespace {

TEST(ConfigTest, IncorrectInput) {
  auto hlp_msg = Config::generate_help_msg();

  try {
    const char* input[4] = {"2", "2", "3", "4"};
    Config cfg(3, const_cast<char**>(input)); // const_cast is absolute evil,
                                              // used here under control and only in testing purpose
  } catch (const exception& e) {
    ASSERT_EQ(e.what(), hlp_msg);
  }

  try {
    const char* input[5] = {"asdf", "0", "2", "3", "4"};
    Config cfg(5, const_cast<char**>(input)); // const_cast is absolute evil,
                                              // used here under control and only in testing purpose
  } catch (const exception& e) {
    ASSERT_EQ(e.what(), hlp_msg);
  }
}

TEST(ConfigTest, CorrectInput) {
  auto hlp_msg = Config::generate_help_msg();
  bool got_exc = false;
  try {
    const char* input[5] = {"asdf", "2", "2", "3", "4"};
    Config cfg(5, const_cast<char**>(input)); // const_cast is absolute evil,
                                              // used here under control and only in testing purpose
  } catch (const exception& e) {
    got_exc = true;
  }

  ASSERT_EQ(got_exc, false);
}

}
