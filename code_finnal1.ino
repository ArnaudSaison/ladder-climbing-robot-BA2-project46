#include <Servo.h>

// --- les variables : déclaration et initialisation

Servo myservo;  
int pos1 = 0;    // position du servo sur le crochet de la crémaillère
int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
int pinTrig1 = 2;
int pinEcho1 = 3;
int pinTrig2 = 4;
int pinEcho2 = 5;
long temps; 
float distance;
const int sensorMin = 0;
const int sensorMax = 600;
 


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
 
 //le crochet de la crémaillère tourne de 90 degré
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
 
 //DECENTE 
 //le capteur ultrason dectecte le bareau (capteur du bas)
    float distance = ultra_son1();
 // si la distance est plus petite que 1cm le moteur s'arrete. Le crochet sur la crémaillère tourne 
  if (distance < 1 ) {
       stopped();
   //code pour les 2 autres crOCHET 
       for (pos = 90; pos >= 0; pos -= 1) {
       myservo.write(pos);              
       delay(15);}
       delay(10000);
       avance()
    }
 
 //sinon le moteur tourne
  else {
     avance();
      }
 
// code du capteur de fin de course 
 
   long sensorReading1 = digitalRead(13);
  //map the sensor range to a range of four option:
  int range = map( sensorReading, sensorMin, sensorMax, 0, 3);

  switch (sensorReading) {
    case 0:    // your hand is on the sensor
      Serial.println("allumé");
      break;
    case 1:    // your hand is nowhere near the sensor
      Serial.println("pas allumé");
      break;
   case 2:
      Serial.println("pas allumé");
      break;
   case 3;
      Serial.println("pas allumé");
      break;
    
  }
  delay(1);
 
 //Si le capteur de fin de course détecte la fin de l'échelle le moteur s'arrete le temps de déposer la charge. 
 //Une fois la charge déposée le moteur tourne dans le sens opposée.
 
  if( range == case 0){
    stopped();
    delay(60000);
    back_off(155,155);
  }
 //la montée 
  float distance = ultra_son2();
  if (distance < 1 ) {
    stopped();
   for (pos = 90; pos >= 0; pos -= 1) {
       myservo.write(pos);              
       delay(15);}
    delay(10000); 
   
    }
  else {
     avance();
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
float ultra_son1() {
  digitalWrite(pinTrig1, HIGH);            //fonction qui rencoit la distance captée par le capteur ultrason1
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
float ultra_son2() {                           //fonction qui rencoit la distance captée par le capteur ultrason1
 digitalWrite(pinTrig2, HIGH);
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
 
 
 // j'ai préférée pas toucher au code du haut 
 // j'ai juste créer 2 fonctions montée et décente quand elles seront complete je pense u'on peut mettre que ça dans void loop :)
 void decente(){
  float distance == ultra_son1();
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
  float distance == ultra_son2();
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
  
