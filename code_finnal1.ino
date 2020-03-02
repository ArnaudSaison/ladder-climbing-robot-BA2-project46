#include <Servo.h>
//le crochet de la crémaillère toure de 90 degré
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
// --- les variables : déclaration et initialisation

int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
int pinTrig1 = 2;
int pinEcho1 = 3;
int pinTrig2 = 4;
int pinEcho2 = 5;
long temps; 
float distance;
 


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
   pinMode(E2, OUTPUT); 
   pinMode(M2, OUTPUT);  
   pinMode(pinTrig1, OUTPUT);
   pinMode(pinEcho1, INPUT);
   pinMode(pinTrig2, OUTPUT);
   pinMode(pinEcho2, INPUT);
   
   digitalWrite(pinTrig1, LOW);
   digitalWrite(pinTrig2, LOW);
   
   Serial.begin(9600);
}

void loop() {
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    float distance = ultra_son();
  if (distance < 1 ) {
    stopped();
    delay(10000);  
    }
  else {
     avance();
      }
    // put your main code here, to run repeatedly:
//read the sensor;
   long sensorReading1 = digitalRead(13);
  //map the sensor range to a range of four option:
  int range = map( sensorReading,0);

  switch (range) {
    case 0:    // your hand is on the sensor
      Serial.println("allumé");
      break;
    case 1:    // your hand is nowhere near the sensor
      Serial.println("pas allumé");
      break;
  }
  delay(1);
  
  if( range == case 0){
    stopped();
    delay(60000);
    back_off(155,155);
  }
  float distance = ultra_son2();
  if (distance < 1 ) {
    stopped();
    delay(10000);  
    }
  else {
     avance();
      }

  
// --- Les fonctions -----
void avance()  { // AVANCE
  analogWrite (E2,100);    
  digitalWrite(M2,HIGH);
}  
void stopped() {
  Serial.println("STOP");
  digitalWrite(E2,0);
}
void back_off (char a,char b) {
  Serial.println("ARRIERE");
 

  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
float ultra_son1() {digitalWrite(pinTrig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig1, LOW);

  temps =  pulseIn(pinEcho1, HIGH);
  if (temps> 25000) {
    Serial.println("Echec de la mesure");
  }
  else{
    temps = temps/2;
    distance =(temps*340)/10000.0;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
  }
  delay(2000);
  return distance;
  
}
float ultra_son2() {digitalWrite(pinTrig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig2, LOW);

  temps =  pulseIn(pinEcho2, HIGH);
  if (temps> 25000) {
    Serial.println("Echec de la mesure");
  }
  else{
    temps = temps/2;
    distance =(temps*340)/10000.0;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
  }
  delay(2000);
  return distance;
  
}
