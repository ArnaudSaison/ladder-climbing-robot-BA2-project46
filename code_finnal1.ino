#include <Servo.h>
//le crochet de la crémaillère toure de 90 degré
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

  

// --- les variables : déclaration et initialisation
int pos1 = 0; // crochets 
int b = 90;   // ang crochets
int pos2 = 0;  // crochet crémaillère
int a = 90;   // ang croh cré
int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
int pinTrig1 = 2;
int pinEcho1 = 3;
int pinTrig2 = 4;
int pinEcho2 = 5;
long temps; 
float distance;
const int sensorMin=0;
const int sensorMax = 600;
const int sensorMin1=0;
const int sensorMax1= 600;
 


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
  char c = capteur_fin_de_course1();
  if( c == "pas allumé"){
  descente_crochets();
  descente_cremaillere();}

  else{
    stopped();
    delay(10000);
  }
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

char capteur_fin_de_course1(){
  long sensorReading = digitalRead(13);
  //map the sensor range to a range of four option:
  int range = map( sensorReading,sensorMin, sensorMax, 0, 3);

  switch (sensorReading) {
    case 0:    // your hand is on the sensor
      Serial.println("allumé");
      return "allumé";
      break;
    case 1:    // your hand is nowhere near the sensor
      Serial.println("pas allumé");
      return "pas allumé";
      break;
    case 2:
      Serial.println("pas allumé");
      return "pas allumé";
      break;
    case 3:
     Serial.println("pas allumé");
     return "pas allumé";
      break;
    
  }
  delay(1);
   }

char capteur_fin_de_course2(){
  long sensorReading1 = digitalRead(12);
  //map the sensor range to a range of four option:
  int range = map( sensorReading1,sensorMin1, sensorMax1, 0, 3);

  switch (sensorReading1) {
    case 0:    // your hand is on the sensor
      Serial.println("allumé");
      return "allumé";
      break;
    case 1:    // your hand is nowhere near the sensor
      Serial.println("pas allumé");
      return "pas allumé";
      break;
    case 2:
      Serial.println("pas allumé");
      return "pas allumé";
      break;
    case 3:
     Serial.println("pas allumé");
     return "pas allumé";
      break;
    
  }
  delay(1);
   }
void retraction_crochet_cremaillere(){
   for (pos2 = 0; pos2 <= a; pos2+= 1) { 
    myservo.write(pos2);              
    delay(15);  }
  
  }
  
void retraction_crochets(){
  for (pos1 = 0; pos1 <= b; pos1 += 1) { 
    myservo.write(pos1);              
    delay(15);  }
  
}
void retourne_crochets(){  
  for (pos1 = b; pos1 >= 0; pos1 -= 1) { 
    myservo.write(pos1);              
    delay(15);}
  }

void retourne_crochet_cremaillere(){
  for (pos2 = a; pos2 >= 0; pos2 -= 1) { 
    myservo.write(pos2);              
    delay(15);}
  }

void descente_crochets(){
  retraction_crochets();
  float distance = ultra_son1();
  if (distance < 1 ) {
    stopped();
    delay(10000); 
    retourne_crochets();
    }
  else {
     avance();
}}
void descente_cremaillere(){
  retraction_crochet_cremaillere();
  float distance = ultra_son2();
  if(distance<1){
    stopped();
    delay(10000);
    retourne_crochet_cremaillere(); 
  }
  else{
    back_off(155,155);
  }
 
}



  
