#include <Manager.h>

Manager::Manager() {
  contextStack = new Context[MAX_CONTEXTS];
  contextStack[contextOffset].setupContext();
}

void Manager::addListener(Listener *lstn) {
  contextStack[contextOffset].addListener(lstn);
}

void Manager::removeListener(Listener *lstn) {
    contextStack[contextOffset].removeListener(lstn);
}

Context *Manager::currentContext () {
  return &contextStack[contextOffset];
}

Context *Manager::pushContext() {
  contextOffset++;
  contextStack[contextOffset].setupContext();
  return &contextStack[contextOffset];
}

Context *Manager::resetContext() {
  contextStack[contextOffset].setupContext();
  return &contextStack[contextOffset];
}

Context *Manager::popContext() {
  contextOffset--;
  return &contextStack[contextOffset];
}

void Manager::loopIteration() {
  contextStack[contextOffset].loopIteration();
}

Context::Context() {
}

void Context::loopIteration() {
  for(int i = 0; i < listenerCount; i++) {
    if(listeners[i]) { 
      if(listeners[i]->isEventTriggered()) {
        if(listeners[i]->performTriggerAction(this)) {
          return;
        }
      }
    }
  }
}

void Context::setupContext() {
  if(data){
    delete data;
  }
  if(listeners) {
    for(int i = 0; i < listenerCount; i++) {
      if(listeners[i]) {
        delete listeners[i];
      }
    }
    delete listeners;
  }

  listeners = new Listener *[MAX_LISTENERS];
  listenerCount = 0;
}
  
void Context::addListener(Listener *lstn) {
  for(int i = 0; i < listenerCount; i++) {
    if(listeners[listenerCount] == 0) { 
      listeners[listenerCount] = lstn;
      return;
    }
  }

  listeners[listenerCount] = lstn;
  lstn->setupListener();
  listenerCount++;
}

void Context::removeListener(Listener *lstn) {
  for(int i = 0; i < listenerCount; i++) {
    if(listeners[i] == lstn) {
      delete lstn;
      listeners[i] = 0;      
    }
  }
}

void Listener::setupListener() {
  
}

bool Listener::isEventTriggered() {
  return false;
}

bool Listener::performTriggerAction(Context *ctx) {
  return (*triggerAction)(this, ctx);
}

HardwareListener::HardwareListener() {
  
}

HardwareListener::HardwareListener(int pin, int debounce, bool targetValue, Action action) {
  this->pin = pin;
  this->debounce = debounce;
  this->targetValue = targetValue;
  this->triggerAction = action;
}

HardwareListener::HardwareListener(int pin, int debounce, Action action) {
  this->pin = pin;
  this->debounce = debounce;
  this->triggerAction = action;
}

HardwareListener::HardwareListener(int pin, Action action) {
  this->pin = pin;
  this->triggerAction = action;
}

void HardwareListener::setupListener() {
  startState = digitalRead(pin);
}

bool HardwareListener::isEventTriggered() {
  bool val = digitalRead(pin); 

  if(firstNoticed) {
    unsigned long curMillis = millis();
    if(curMillis > firstNoticed + debounce) {
      firstNoticed = 0;

      if(val == targetValue) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }
  
  if(mustStartOpposite && (startState == targetValue)) {
    if(val == startState) {
    } else {
      startState = val;
    }

    return false;
  } else {
    if(val == targetValue) {
      if(debounce == 0) {
        return true;
      } else {
        firstNoticed = millis();
        return false;
      }
    } else {
      return false;
    }
  }
}