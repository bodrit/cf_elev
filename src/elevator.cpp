#include <chrono>
#include <iostream>

#include "elevator.h"
#include "util.h"

using namespace std;

namespace NElev {


Elevator::Elevator(Config cfg, ostream& out = cout)
  : cfg_(std::move(cfg))
  , cur_floor_(1)
  , floor_time_gap_(cfg_.floor_h / cfg_.move_speed)
  , out_(out)
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
        if (next_floors_.CheckAndDelete(cur_floor_)) {
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
  out_ << "Current floor:" << cur_floor_ << endl;
}

void Elevator::doors_open() {
  out_ << "Doors opened" << endl;
  this_thread::sleep_for(ToSeconds(cfg_.doors_gap));
  out_ << "Doors closed" << endl;
}


} // NElev
