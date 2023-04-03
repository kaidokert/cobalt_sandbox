#include "starboard/file.h"

#include "gmock/gmock.h"

// Simply forwards to C functions through a virtual, so gmock can cope
struct FileAPIHelper {
  virtual bool SbFileExists(const char *path) { return SbFileExists(path); }
};

// Actual mock
struct MockFileAPI : public FileAPIHelper {
  //MOCK_METHOD(bool, SbFileExists, (const char *path), (override));
  MOCK_METHOD1(SbFileExists, bool(const char *path));
};

// Get/release mock instance
std::unique_ptr<MockFileAPI>& getFileMock();
void destroyFileMock();
