// Copyright 2018 The Cobalt Authors. All Rights Reserved.
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

#include "starboard/shared/uwp/log_writer_win32.h"

#include <string>

#include "starboard/common/file.h"
#include "starboard/common/log.h"
#include "starboard/common/semaphore.h"
#include "starboard/common/string.h"

using starboard::ScopedFile;

namespace starboard {
namespace shared {
namespace uwp {
namespace {

class LogWriterWin32 : public ILogWriter {
 public:
  explicit LogWriterWin32(const std::string& file_path) {
    file_.reset(
        new ScopedFile(file_path.c_str(), O_CREAT | O_TRUNC | O_WRONLY));
    if (!file_->IsValid()) {
      SB_LOG(ERROR) << "Could not create watchdog file " << file_path;
      file_.reset();
    }
  }

  ~LogWriterWin32() { FlushToDisk(); }

  void Write(const char* content, int size) override {
    starboard::ScopedLock lock(mutex_);
    if (IsValid_Locked()) {
      file_->Write(content, size);
    }
    return;
  }

 private:
  bool IsValid_Locked() const { return file_ && file_->IsValid(); }

  void FlushToDisk() {
    starboard::ScopedLock lock(mutex_);
    if (IsValid_Locked()) {
      file_->Flush();
    }
  }
  std::string file_path_;
  starboard::Mutex mutex_;
  std::unique_ptr<ScopedFile> file_;
};

}  // namespace.

std::unique_ptr<ILogWriter> CreateLogWriterWin32(const char* path) {
  std::unique_ptr<ILogWriter> output(new LogWriterWin32(path));
  return output;
}

}  // namespace uwp
}  // namespace shared
}  // namespace starboard
