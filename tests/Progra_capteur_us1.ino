#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
char DOUT_TRIGGER=7;
char DIN_ECHO    =6;
float disatance; 

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(DOUT_TRIGGER,OUTPUT);
  pinMode(DIN_ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Créer une impilsion de 10µs sur le TRIGGER
  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(DOUT_TRIGGER, LOW);

  //Mesure de la durée de l'impulsion sur l'ECHO et converti cette durée en distance en cm.
  distance = pulseIn(DIN_ECHO, HIGH)/58.0;

  
  
  
  
  
}
