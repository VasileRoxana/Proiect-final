# Proiect-final
Proiectul meu final consta intr-un robot masinuta controlat prin telecomanda ce foloseste doua motoare dc.
BOM: 
https://docs.google.com/spreadsheets/d/1_GYeWjBXVv_4aekasxN6_g4DxXadq2Kq5P1_7F1olAA/edit#gid=1564006692&range=D2

#include "IRremote.h"
#define M1A 2
#define M1B 3
#define M2A 4
#define M2B 5
int rec = 6;

IRrecv irrecv(rec);           // create instance of 'irrecv'
decode_results results;       // create instance of 'decode_results'

void fw();
void bw();
void left();
void right();
void stop();

void setup() 
{
  pinMode(rec, INPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
void loop() 
{
  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume();
  }
}
void translateIR()
{
  switch(results.value)
  {
    case 0xFF38C7:
      fw(); 
      break;
    case 0xFF42BD: 
      left();
      break;
    case 0xFF4AB5:  
      bw();
      break;
    case 0xFF52AD:  
      right();
      break;
    default:
      stop();
  }
  delay(500);
}
void fw()
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);

  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);
}
void bw()
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);

  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
}
void left()
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);

  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
}
void right()
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);

  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);
}
void stop()
{
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);

  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}
