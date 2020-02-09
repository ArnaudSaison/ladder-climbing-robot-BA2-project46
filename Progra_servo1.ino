#include<Servo.h>

Servo myServo; //Déclare l'utilisation d'un servo nommé "myServo"
int pos = 0;
void setup() {
  myServo.attach(2);//Servo connecté sur la broche DIGITAL 2
  myServo.write(pos);
  
}

void loop() {

    myServo.write(0);              // tell servo to go to position in variable 'pos'
    delay(10000);                       // waits 15ms for the servo to reach the position
 

}
