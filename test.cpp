#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

#include "starboard/mocks/file-mock.h"
#include "starboard/mocks/event-mock.h"

/* Random module using Starboard */
void callFileUsingModule(const char *arg) {
  SbFileExists(arg);
}
void SomethingThatUsesEvents() {
  SbEventCancel(2);
}
void DoSomethingComplex() {
  SbFileExists(nullptr);
  SbEventCancel(3);
}
/* End module */

using ::testing::Return;

TEST(mockfiles, test) {
  auto & filemock = getFileMock();
  const char * arg = "test.txt";
  EXPECT_CALL(*filemock, SbFileExists(arg)).WillOnce(Return(true));
  callFileUsingModule(arg);
  destroyFileMock();
}

TEST(mockevents, test) {
  auto & eventmock = getEventMock();
  EXPECT_CALL(*eventmock, SbEventCancel(2));
  SomethingThatUsesEvents();
  destroyEventMock();
}

TEST(both, test) {
  auto & filemock = getFileMock();
  auto & eventmock = getEventMock();
  EXPECT_CALL(*filemock, SbFileExists(nullptr)).WillOnce(Return(true));
  EXPECT_CALL(*eventmock, SbEventCancel(3));
  DoSomethingComplex();
  destroyFileMock();
  destroyEventMock();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

