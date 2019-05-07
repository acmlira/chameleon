#include "Arduino.h"

#define MIN 0
#define MAX 255

class ColorSensor {
private:
  int S0, S1, S2, S3, Out;
public:
  ColorSensor();
  ColorSensor(int S0, int S1, int S2, int S3, int Out);

  int R, R_max, R_min; 
  int G, G_max, G_min;
  int B, B_max, B_min;

  void begin();
  void read();

  String RGB();
};