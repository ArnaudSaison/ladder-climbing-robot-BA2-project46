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
      if (DESCENDRE == true){
        stopped();
    }
    else if (MONTER == true) {
      monte_cremaillere(); //montée de la crémaillère
    } 
    else if (DESCENDRE == false && MONTER == false){
      stopped();
    }
    else{
      stopped();
    }
  }
}

void avance() {  // le moteur tourne dans un sens 
  analogWrite (E2,100);    
  digitalWrite(M2,HIGH);
}  

void stopped() {  //le moteur s'arrête
  Serial.println("STOP");
  digitalWrite(E2,0);
}

void monte_cremaillere(){ //cette fonction sert à faire monter la crémaillère d'un échelon 
    avance(); //sinon le moteur tourne dans un sens 
   }
