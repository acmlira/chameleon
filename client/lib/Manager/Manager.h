#include <limits.h>
#include <Arduino.h>

#define MAX_CONTEXTS 10
#define MAX_LISTENERS 20

class Manager;
class Context;
class Listener;

typedef bool (*Action)(Listener *, Context *);

class Manager {
  public:
  Manager();
  void loopIteration();
  Context *pushContext();
  Context *resetContext();
  Context *popContext();
  Context *currentContext();
  void addListener(Listener *lstn);
  void removeListener(Listener *lstn);

  private:
  Context *contextStack = 0;
  int contextOffset = 0;
  int contextDepth = 0;
};

class Context {
  public:
  void *data = 0;

  Context();
  void setupContext();
  void loopIteration();
  void addListener(Listener *lstn);
  void removeListener(Listener *lstn);

  private:
  Listener **listeners = 0;
  int listenerCount;
};

class Listener {
  public:
  void *extraData = 0;
  Action triggerAction;

  virtual void setupListener();
  virtual bool isEventTriggered();
  virtual bool performTriggerAction(Context *); 

  protected:
};

class HardwareListener : public Listener {
  public:
  HardwareListener();
  HardwareListener(int pin, Action trigger);
  HardwareListener(int pin, int debounce, Action action);
  HardwareListener(int pin, int debounce, bool targetValue, Action action);
  int pin = 0;
  int debounce = 40;  
  bool targetValue = HIGH;
  bool mustStartOpposite = true;
  bool startState;
  unsigned long firstNoticed = 0;

  void setupListener();
  bool isEventTriggered();
};


#define loop(manager) void loop() { manager.loopIteration(); }