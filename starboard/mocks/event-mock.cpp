#include "starboard/mocks/event-mock.h"

std::unique_ptr<MockEventAPI> api_instance;

// "singleton" boilerplate. This can be part of a mock class template
std::unique_ptr<MockEventAPI>& getEventMock() {
    if (!api_instance) {
        api_instance = std::make_unique<MockEventAPI>();
    }
    return api_instance;
}
void destroyEventMock() {
    api_instance.reset();
}
// end singleton

extern "C" {

void SbEventCancel(SbEventId event_id) {
    return getEventMock()->SbEventCancel(event_id);
}

}
