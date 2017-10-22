#include <chrono>
#include <iostream>

#include "elevator.h"
#include "util.h"

using namespace std;

namespace NElevator {


Elevator::Elevator(Config cfg)
  : cfg_(std::move(cfg))
  , cur_floor_(0)
  , floor_time_gap_(cfg_.floor_h / cfg_.move_speed)
{}

void Elevator::run() {
  render_status();

  while (true) {
    auto next_floor = next_floors_.get_closest(cur_floor_);

    if (next_floor != -1) {
      auto diff = std::abs(cur_floor_ - next_floor);
      auto dir  = cur_floor_ > next_floor;

      while (diff--) {
        this_thread::sleep_for(ToSeconds(floor_time_gap_));
        cur_floor_ += dir ? -1 : 1;

        render_status();
        if (next_floors_.has(cur_floor_)) {
          doors_open();
        }
      }

      doors_open();

    } else {
      this_thread::sleep_for(ToSeconds(1));
    }
  }
}

void Elevator::call(FloorValueType next_floor) {
  next_floors_.insert(next_floor);
}

void Elevator::render_status() {
  cout << "Current floor:" << cur_floor_ << endl;
}

void Elevator::doors_open() {
  cout << "Doors opened" << endl;
  this_thread::sleep_for(ToSeconds(cfg_.doors_gap));
  cout << "Doors closed" << endl;
}


} // NElevator
