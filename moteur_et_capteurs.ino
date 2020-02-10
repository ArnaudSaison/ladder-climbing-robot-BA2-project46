//ce code permet au moteur de s'arrêter et de démarer en fonction de la distance captée par les capteurs  
char PWM_ENABLE = 3; //signal périodique
char DO_MOTOR_1 = 2;
char DO_MOTOR_2 = 4;
char DOUT_TRIGGER=7;
char DIN_ECHO    =6;
float distance; 

void setup() {
  // put your setup code here, to run once:
  pinMode(DOUT_TRIGGER,OUTPUT);
  pinMode(DIN_ECHO, INPUT);
  pinMode(DO_MOTOR_1, OUTPUT);
  pinMode(DO_MOTOR_2, OUTPUT);
  pinMode(PWM_ENABLE, OUTPUT);

  digitalWrite(DO_MOTOR_1, LOW);
  digitalWrite(DO_MOTOR_2, HIGH);
  analogWrite(PWM_ENABLE, 0);

  Serial.begin(9000);
  }

void loop() {
  // put your main code here, to run repeatedly:
  // Créer une impulsion de 10µs sur le TRIGGER
  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(DOUT_TRIGGER, LOW);

  //Mesure de la durée de l'impulsion sur l'ECHO et converti cette durée en distance en cm.
  distance = pulseIn(DIN_ECHO, HIGH)/58.0;
  
  //le moteur ce déclanche si la distance esr plus petite que 1
  if(distance <= 1)
  {
  analogWrite(PWM_ENABLE, 125);
  }
  else
  {
  analogWrite(PWM_ENABLE, 0);
  }
  delay(20);
}
