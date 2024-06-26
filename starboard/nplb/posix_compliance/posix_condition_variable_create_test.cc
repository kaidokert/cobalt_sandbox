// Copyright 2024 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <pthread.h>

#include "testing/gtest/include/gtest/gtest.h"

namespace starboard {
namespace nplb {
namespace {

const int kALot = 128 * 1024;
const int kABunch = 2 * 1024;

TEST(PosixConditionVariableCreateTest, SunnyDay) {
  pthread_cond_t condition;
  EXPECT_EQ(pthread_cond_init(&condition, NULL), 0);
  EXPECT_EQ(pthread_cond_destroy(&condition), 0);
}

TEST(PosixConditionVariableCreateTest, SunnyDayAutoInit) {
  pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
  EXPECT_EQ(pthread_cond_init(&condition, NULL), 0);
  EXPECT_EQ(pthread_cond_destroy(&condition), 0);
}

TEST(PosixConditionVariableCreateTest, SunnyDayALot) {
  for (int i = 0; i < kALot; ++i) {
    pthread_cond_t condition;
    EXPECT_EQ(pthread_cond_init(&condition, NULL), 0);
    EXPECT_EQ(pthread_cond_destroy(&condition), 0);
  }
}

TEST(PosixConditionVariableCreateTest, SunnyDayABunchAtOnce) {
  pthread_cond_t conditions[kABunch];
  for (int i = 0; i < kABunch; ++i) {
    EXPECT_EQ(pthread_cond_init(&conditions[i], NULL), 0);
  }

  for (int i = 0; i < kABunch; ++i) {
    EXPECT_EQ(pthread_cond_destroy(&conditions[i]), 0);
  }
}

}  // namespace
}  // namespace nplb
}  // namespace starboard
