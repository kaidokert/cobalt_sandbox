#include "starboard/event.h"

#include "gmock/gmock.h"

// Simply forwards to C functions through a virtual, so gmock can cope
struct EventAPIHelper {
  virtual void SbEventCancel(SbEventId event_id) { return SbEventCancel(event_id); }
};

// Actual mock
struct MockEventAPI : public EventAPIHelper {
  //MOCK_METHOD(void, SbEventCancel, (SbEventId event_id), (override));
  MOCK_METHOD1(SbEventCancel, void(SbEventId event_id));
};

// Get/release mock instance
std::unique_ptr<MockEventAPI>& getEventMock();
void destroyEventMock();
