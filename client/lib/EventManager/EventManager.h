#include "Eventually.h"

typedef bool (*Action)(EvtListener *, EvtContext *);

class EventManager: public EvtManager
{
};

class HardwareListener: public EvtPinListener
{
    using EvtPinListener::EvtPinListener;
};

#define loop(manager) void loop() { manager.loopIteration(); }