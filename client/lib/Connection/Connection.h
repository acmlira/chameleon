#include "WiFi.h"

class Connection {
private:
 
public:
  Connection();

  void begin(const char* ssid,const char* password);
  
  void catchIP();

  String IP;
};