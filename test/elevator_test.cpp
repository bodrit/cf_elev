#include <sstream>
#include <iostream>
#include <thread>

#include "gtest/gtest.h"
#include "elevator.h"
#include "util.h"

using namespace NElev;

namespace {

TEST(ElevatorTest, RegularMode) {
  const char* input[5] = {"asdf", "10", "4", "12", "3"};
  Config cfg(5, const_cast<char**>(input)); // const_cast is absolute evil,

  stringstream log;

  NElev::Elevator elev(cfg, log);
  auto elevator_daemon = std::thread([](NElev::Elevator& elev){ elev.run(); }, std::ref(elev));
  elevator_daemon.detach();

  elev.call(6);
  elev.call(4);
  std::this_thread::sleep_for(ToSeconds(2));

  EXPECT_EQ(log.str(), "Current floor:1\n"
                      "Current floor:2\n"
                      "Current floor:3\n"
                      "Current floor:4\n"
                      "Doors opened\n"
  );
}

}
