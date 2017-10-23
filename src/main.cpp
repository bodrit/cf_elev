#include <iostream>
#include <string>
#include <thread>

#include "elevator.h"
#include "config.h"
#include "util.h"

int main(int argc, char** argv) {
  NElevator::Config cfg;

  try {
     cfg = NElevator::Config(argc, argv);
  } catch(const std::logic_error& e) {
    std::cout << e.what() << std::endl;
    exit(1);
  }


  NElevator::Elevator elev(cfg, cout);

  auto elevator_main = [](NElevator::Elevator& elev) {
    elev.run();
  };

  auto elevator_daemon = std::thread(elevator_main, std::ref(elev));

  elevator_daemon.detach();

  for (std::string line; std::getline(std::cin, line);) {
    try {
      auto floor = NElevator::from_string<long long>(line);
      if (floor < 1 || floor > cfg.max_floor) {
        cout << "Floor should be positive int from interval [1, " << cfg.max_floor << "]" << endl;
      } else {
        elev.call(floor);
      }
    } catch (const std::exception& e) {
      cout << "Floor should be positive int from interval [1, " << cfg.max_floor << "]" << endl;
    }
  }
}
