#include "TCS230.h"

TCS230::TCS230() {
  
}

TCS230::TCS230(int S0, int S1, int S2, int S3, int Out) {
  this->S0 = S0;
  this->S1 = S1;
  this->S2 = S2;
  this->S3 = S3;
  this->Out = Out;
  this->R_max = MIN;
  this->R_min = MAX;
  this->G_max = MIN;
  this->G_min = MAX;
  this->B_max = MIN;
  this->B_min = MAX;
}

void TCS230::begin() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Out, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void TCS230::read() {
    // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  R = pulseIn(Out, LOW);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  G = pulseIn(Out, LOW);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  B = pulseIn(Out, LOW);
}

String TCS230::rgb() {
  return (String(map(R, R_min, R_max, MIN,MAX)) + "," + String(map(G, G_min, G_max,MIN,MAX)) + "," + String(map(B, B_min, B_max,MIN,MAX)));
}