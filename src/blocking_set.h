#pragma once

#include <thread>
#include <mutex>
#include <algorithm>
#include <set>

namespace NElevator {

template<typename ValueType>
class BlockingSet {
public:
  void insert(const ValueType& value) {
    std::lock_guard<std::mutex> lock (mtx);
    data_.insert(value);
  }

  ValueType get_closest(const ValueType& value) {
    std::lock_guard<std::mutex> lock (mtx);
    if (data_.empty())
      return -1;

    auto it = std::lower_bound(data_.begin(), data_.end(), value);
    auto closest = it;

    if (it == data_.end()) {
      closest = std::prev(it);
    } else if (it == data_.begin()) {
      closest = it;
    } else if (*it != value) {
      auto prev = it;
      --prev;

      closest = *it - value > value - *prev ? prev : it;
    }

    auto result = *closest;
    data_.erase(closest);
    return result;
  }

  bool CheckAndDelete(const ValueType& value) {
    std::lock_guard<std::mutex> lock (mtx);
    auto it = data_.find(value);
    if (it != data_.end()) {
      data_.erase(it);
      return true;
    }

    return false;
  }

private:
  std::mutex mtx;
  std::set<ValueType> data_;
};

} // NElevator
