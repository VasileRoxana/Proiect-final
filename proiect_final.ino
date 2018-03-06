#include "IRremote.h"
#define M1A 5
#define M1B 9
#define M2A 3
#define M2B 10
#define trigPin 11
#define echoPin 13

int rec = 6;
int speedM1, speedM2;
IRrecv irrecv(rec); // create instance of 'irrecv'
decode_results results; // create instance of 'decode_results'

void fw();
void bw();
void left();
void right();
void stop();
bool goesFW = true;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rec, INPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  if (distance <= 5 && goesFW == true)
    stop();
  if (irrecv.decode( & results)) {
    translateIR();
    irrecv.resume();
  }
}

void translateIR() {
  switch (results.value) {
  case 0xFF38C7: //FW//
    {
      goesFW = true;
      speedM1 = 255;
      speedM2 = 255;
      fw(speedM1, speedM2);
      break;
    }
  case 0x488F3CBB: //FW//
    {
      goesFW = true;
      speedM1 = 255;
      speedM2 = 255;
      fw(speedM1, speedM2);
      break;
    }
  case 0xFF4AB5: //BW//  
    {
      goesFW = false;
      speedM1 = 150;
      speedM2 = 255;
      bw(speedM1, speedM2);
      break;
    }
  case 0x1BC0157B: //BW//  
    {
      goesFW = false;
      speedM1 = 150;
      speedM2 = 255;
      bw(speedM1, speedM2);
      break;
    }

  case 0xFF42BD: //LEFT//
    {
      speedM1 = 150;
      speedM2 = 10;

      if (goesFW == true) {
        fw(speedM1, speedM2);
        break;
      } else {
        bw(speedM1, speedM2);
        break;
      }
    }
  case 0x32C6FDF7: //LEFT// 
    {
      speedM1 = 150;
      speedM2 = 10;

      if (goesFW == true) {
        fw(speedM1, speedM2);
        break;
      } else {
        bw(speedM1, speedM2);
        break;
      }
    }
  case 0xFF52AD: //RIGHT//
    {
      speedM1 = 10;
      speedM2 = 150;

      if (goesFW == true) {
        fw(speedM1, speedM2);
        break;
      } else {
        bw(speedM1, speedM2);
        break;
      }
    }
  case 0x3EC3FC1B: //RIGHT//
    {
      speedM1 = 10;
      speedM2 = 160;

      if (goesFW == true) {
        fw(speedM1, speedM2);
        break;
      } else {
        bw(speedM1, speedM2);
        break;
      }
    }
  case 0xFF22DD: //SPIN LEFT
    {
      spinLeft();
      break;
    }
  case 0x52A3D41F: //SPIN LEFT
    {
      spinLeft();
      break;
    }
  case 0xF02FD: //SPIN RIGHT
    {
      spinRight();
      break;
    }
  case 0xD7E84B1B: //SPIN RIGHT
    {
      spinRight();
      break;
    }
  default:
    stop();
  }
  delay(50);
}

void fw(int val1, int val2) {
  analogWrite(M1A, val1);
  digitalWrite(M1B, 0);

  analogWrite(M2A, val2);
  digitalWrite(M2B, 0);

}

void bw(int val1, int val2) {
  analogWrite(M1B, val1);
  digitalWrite(M1A, 0);

  analogWrite(M2B, val2);
  digitalWrite(M2A, 0);
}

void spinLeft() {
  digitalWrite(M1A, 1);
  digitalWrite(M1B, 0);

  digitalWrite(M2A, 0);
  digitalWrite(M2B, 1);
}

void spinRight() {
  digitalWrite(M1A, 0);
  digitalWrite(M1B, 1);

  digitalWrite(M2A, 1);
  digitalWrite(M2B, 0);
}

void stop() {
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);

  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}
