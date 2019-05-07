#include "Eventually.h"

typedef bool (*Action)(EvtListener *, EvtContext *);

class EventManager: public EvtManager {};

class HardwareListener: public EvtPinListener {
  using EvtPinListener::EvtPinListener;
};

class ConnectionListener: public EvtTimeListener {
  using EvtTimeListener::EvtTimeListener;
};

#define loop(manager) void loop() { manager.loopIteration();}