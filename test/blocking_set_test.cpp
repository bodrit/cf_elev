#include "gtest/gtest.h"
#include "blocking_set.h"

using namespace std;
using namespace NElev;

namespace {

TEST(BlockingSetTest, Closest) {
  BlockingSet<int> bset;
  bset.insert(2);
  bset.insert(5);
  bset.insert(7);
  bset.insert(10);
  bset.insert(20);
  ASSERT_EQ(bset.get_closest(8), 7);
  ASSERT_EQ(bset.get_closest(22), 20);
  ASSERT_EQ(bset.get_closest(1), 2);
}

}
