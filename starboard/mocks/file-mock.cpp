#include "starboard/mocks/file-mock.h"

std::unique_ptr<MockFileAPI> api_instance;

// "singleton" boilerplate
std::unique_ptr<MockFileAPI>& getFileMock() {
    if (!api_instance) {
        api_instance = std::make_unique<MockFileAPI>();
    }
    return api_instance;
}
void destroyFileMock() {
    api_instance.reset();
}
// end singleton

extern "C" {

bool SbFileExists(const char *path) {
    return getFileMock()->SbFileExists(path);
}

}
