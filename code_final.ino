#include <Metro.h>
#include <DFMobile.h>
#include <GoBLE.h>
#include <QueueArray.h>
#include <Servo.h>


// --- les variables : déclaration et initialisation
Servo myservo; 
Servo myservo2;
int pos1 = 0; //positions des crochets 
int b = 180;  //angle des crochets
int pos2 = 0; //postion du crochet crémaillère
int a = 90;   //ang crochet cré
int E2 = 6;   //M2 : vitesse du moteur M2
int M2 = 7;   //M2 Direction : horaire/anti-horaire
int pinTrig1 = 2; //capteur ultrason1
int pinEcho1 = 3; //capteur ultrason1
int pinTrig2 = 4; //capteur ultrason2
int pinEcho2 = 5; //capteur ultrason 2
int joystickX, joystickY; //joystick ble
int buttonState[7];
long temps; 
float distance;
const int sensorMin=0;
const int sensorMax = 600;
const int sensorMin1=0;
const int sensorMax1= 600;

bool MONTER = false;
bool DESCENDRE = false;


void setup() {
  myservo.attach(9);
  myservo2.attach(8);
  
   Goble.begin();
   Serial.begin(115200);
   pinMode(E2, OUTPUT); 
   pinMode(M2, OUTPUT);  
   pinMode(pinTrig1, OUTPUT);
   pinMode(pinEcho1, INPUT);
   pinMode(pinTrig2, OUTPUT);
   pinMode(pinEcho2, INPUT);
   
   digitalWrite(pinTrig1, LOW);
   digitalWrite(pinTrig2, LOW);
   
   Serial.begin(115200);
}


void loop() {
  if( Goble.available() ) {
    joystickX = Goble.readJoystickX();
    joystickY = Goble.readJoystickY();
    buttonState[SWITCH_SELECT] = Goble.readSwitchSelect();
    buttonState[SWITCH_START]  = Goble.readSwitchStart();

    if (joystickX > 0) {
      MONTER = true;
      DESCENDRE = false;
    }
    else if (joystickX < 0) {
      DESCENDRE = true;
      MONTER = false;
    }

    
    else {
      MONTER = false;
      DESCENDRE = false;
    }
    

   if (DESCENDRE == true && capteur_fin_de_course2() == 0){
        descente_crochets();  // descente des crochets
        if (pos2==b){
        descente_cremaillere(); // décente de la crémaillère
        }
    }
    else if (MONTER == true && capteur_fin_de_course1() == 0) {
      monte_cremaillere(); //montée de la crémaillère
      if (pos1==a){
      monte_crochets(); // montée des crochets
      }
    } 
    else if (DESCENDRE == false && MONTER == false){
      stopped();
    }
    else{
      stopped();
    }
  }
}

// --- Les fonctions ---


void avance() {  // le moteur tourne dans un sens 
  analogWrite (E2,200);    
  digitalWrite(M2,HIGH);
}  

void stopped() {  //le moteur s'arrête
  Serial.println("STOP");
  digitalWrite(E2,0);
}

void back_off (char a,char b) { // le moteur tourne dans l'autre sens 
  Serial.println("ARRIERE");
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}


float ultra_son1() {digitalWrite(pinTrig1, HIGH);  // cette fonction nous revoit la distance que capte le capteur ultrason 1
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


float ultra_son2() {digitalWrite(pinTrig2, HIGH); // cette fonction nous revoit la distance que capte le capteur ultrason  2
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


int capteur_fin_de_course1(){ //cette fonction nous renvoit si le capteur de fin de course 1 est allumé ou non 
  long sensorReading = digitalRead(13);
  //map the sensor range to a range of four option:
  int range = map( sensorReading,sensorMin, sensorMax, 0, 3);

  switch (sensorReading) {
    case 0:
      Serial.println("allumé");
      return 1;
      break;
    case 1:
      Serial.println("pas allumé");
      return 0;
      break;
    case 2:
      Serial.println("pas allumé");
      return 0;
      break;
    case 3:
     Serial.println("pas allumé");
     return 0;
      break;
    
  }
  delay(1);
}


char capteur_fin_de_course2(){  //cette fonction nous renvoit si le capteur de fin de course  2 est allumé ou non 
  long sensorReading1 = digitalRead(12);
  //map the sensor range to a range of four option:
  int range = map( sensorReading1,sensorMin1, sensorMax1, 0, 3);

  switch (sensorReading1) {
    case 0:
      Serial.println("allumé");
      return 1;
      break;
    case 1:
      Serial.println("pas allumé");
      return 0;
      break;
    case 2:
      Serial.println("pas allumé");
      return 0;
      break;
    case 3:
     Serial.println("pas allumé");
     return 0;
      break;
  }
  delay(1);
}


void retraction_crochet_cremaillere(){  //cette fonction sert à rétracter le crochet de la crémaillère ( grace au servo moteur  2)
  for (pos2 = 0; pos2 <= a; pos2+= 1) { 
    myservo2.write(pos2);              
    delay(15);  
  }
}
  

void retraction_crochets(){ //cette fonction sert à rétracter les crochets  ( grace au servo moteur 1)
  for (pos1 = 0; pos1 <= b; pos1 += 1) { 
    myservo.write(pos1);              
    delay(15);  
  }
}

void retourne_crochets(){ // cette fontion sert à retourner les crochets 
  for (pos1 = b; pos1 >= 0; pos1 -= 1) { 
    myservo.write(pos1);              
    delay(15);
  }
}


void retourne_crochet_cremaillere(){ //cette fontion sert à retourner le crochet de la crémaillère
  for (pos2 = a; pos2 >= 0; pos2 -= 1) { 
    myservo2.write(pos2);              
    delay(15);
  }
}


void descente_crochets(){ // cette fonction sert à décendre les crochets d'un échelon 
  retourne_crochets(); // étape 1 on retourne les crochets
  float distance = ultra_son1();
  if (distance < 1 ) {  // si la distance capté par le capteur ultrason n1 est plus petite que 1 alors le moteur s'arrête et on rétracte les crochets
    stopped();
    delay(2000);
    retraction_crochets(); 
    }
  else {
     avance();  // sinon le moteur tourne dans un sens 
  }
}


void descente_cremaillere(){ // cette fonction sert à décendre le crochet de la crémaillère
 retourne_crochet_cremaillere();  // étape 1 on retourne le crochet de la crémaillère
  float distance = ultra_son2(); // si la distance capté par le capteur ultrason n2 est plus petite que 1 alors le moteur s'arrête et on rétracte le crochet de la crémaillère
  if(distance<1){
    stopped();
    delay(2000);
  retraction_crochet_cremaillere(); 
  }
  else {
    back_off(155,155); // sinon le moteur tourne dans l' autre sens (dans le but d'apporter la crémaillère au même échelon que les crochets)
  }
 
}


void monte_cremaillere(){ //cette fonction sert à faire monter la crémaillère d'un échelon 
  retourne_crochet_cremaillere();// étape 1 on retourne le crochet de la crémaillère
  float distance = ultra_son2(); // si la distance capté par le capteur ultrason n2 est plus petite que 1 alors le moteur s'arrête et on rétracte le crochet de la crémaillère
  if(distance<1){
    stopped();
    delay(2000);
    retraction_crochet_cremaillere(); 
  }
  else {
    avance(); //sinon le moteur tourne dans un sens 
  }  
}


void monte_crochets(){  //cette fonction sert à faire monter  les crochets  d'un échelon
   retourne_crochets();// étape 1 on retourne les crochets
  float distance = ultra_son1(); // si la distance capté par le capteur ultrason n1 est plus petite que 1 alors le moteur s'arrête et on rétracte les crochets
  if (distance < 1 ) {
    stopped();
    delay(2000);
   retraction_crochets(); ;
  }
  else {
    back_off(155,155); // sinon le moteur tourne dans l' autre sens (dans le but d'apporter les crochets au même échelon que la crémaillère)
  }
}
