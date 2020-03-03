// Idée, comme on sait qu'il commence vers le haut on peut dire que quand on touche interrupteur, on change sens moteur + 
//on passe en capteur ultra_son2


#include <Servo.h>
//le crochet de la crémaillère toure de 90 degré
Servo myservo1;// create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

// --- les variables : déclaration et initialisation

int pos1 = 0;// variable to store the servo position
int pos2 = 0;
int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
int pinTrig1 = 2;
int pinEcho1 = 3;
int pinTrig2 = 4;
int pinEcho2 = 5;
const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 600;    // sensor maximum, discovered through experiment
int angle_servo1=90;
int angle_servo2=90;
long temps;
float distance;

void setup() {
   myservo1.attach(7);
   myservo2.attach(9);
   pinMode(pinTrig1, OUTPUT);
   pinMode(pinEcho1, INPUT);
   pinMode(pinTrig2, OUTPUT);
   pinMode(pinEcho2, INPUT);

   digitalWrite(pinTrig1, LOW);
   digitalWrite(pinTrig2, LOW);

   Serial.begin(9600);   
}

  // --- Les fonctions -----

void avance()  {                       // AVANCE
  analogWrite (E2,100);    
  digitalWrite(M2,HIGH);
}  
void stopped()  {                     //ARRET
  Serial.println("STOP");
  digitalWrite(E2,0);
}
void back_off (char a,char b) {              //CHANGEMENT DE SENS
  Serial.println("ARRIERE");
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
float ultra_son1() {                           //fonction qui rencoit la distance captée par le capteur ultrason1
  digitalWrite(pinTrig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig1, LOW);

  temps = pulseIn(pinEcho1, HIGH);

  if (temps > 25000){
    Serial.print("Echec de la mesure");
    distance = 10000;
  }
  else{
    temps = temps/2;
    distance = (temps*340)/10000.0;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(2000);
  return distance;
}

float ultra_son2() {                           //fonction qui rencoit la distance captée par le capteur ultrason1
  digitalWrite(pinTrig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig2, LOW);

  temps = pulseIn(pinEcho2, HIGH);

  if (temps > 25000){
    Serial.print("Echec de la mesure");
  }
  else{
    temps = temps/2;
    distance = (temps*340)/10000.0;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(2000);
  return distance;
}

char fin_couse(){
  // read the sensor:
  int sensorReading = digitalRead(13);
  // map the sensor range to a range of four options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // do something different depending on the range value:
  switch (sensorReading) {
    case 0:    // your hand is on the sensor
      Serial.println("allumé");
      break;
    case 1:    // your hand is close to the sensor
      Serial.println("pas allumé");
      break;
    case 2:    // your hand is a few inches from the sensor
      Serial.println("pas allumé");
      break;
    case 3:    // your hand is nowhere near the sensor
      Serial.println("pas allumé");
      break;
  }
  delay(1);        // delay in between reads for stability
}


 // j'ai préférée pas touvher au code du haut 
 // j'ai juste créer 2 fonctions montée et décente quand elles seront complete je pense u'on peut mettre que ça dans void loop :)

void retraction_crocher_cremaillere(){
   for (pos1 = 0; pos1 <= angle_servo1; pos1 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void retraction_crochers(){
   for (pos2 = 0; pos2 <= angle_servo2; pos2 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void retourne_crocher_cremaillere(){
   for (pos1 = 0; pos1=0; pos1 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void retourne_crochers(){
   for (pos2 = 0; pos2 = 0; pos2 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
 void decente(){
  float distance = ultra_son1();
   // si la distance est plus petite que 1cm le moteur s'arrete.
  if (distance < 1 ) {
    stopped();
    delay(10000);  
    }
 //sinon le moteur tourne
  else {
     avance();
      }
 }

 void monte(){
  float distance = ultra_son2();
   // si la distance est plus petite que 1cm le moteur s'arrete.
  if (distance < 1 ) {
    stopped();
    delay(10000);  
    }
 //sinon le moteur tourne
  else {
     avance();
      }
 }

void loop() {
  
  
  }




