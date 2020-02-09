char PWM_ENABLE = 3;
char DO_MOTOR_1 = 2;
char DO_MOTOR_2 = 4;
char AN_POTENTIOMETRE = 0;
int valeurPotentiometre = 0;
int vitesseDuMoteur = 0;
//ce code permet de controler la sens de rotation du moteur en fonction de la position du potentiomètre
void setup() {
  // put your setup code here, to run once:
  pinMode(DO_MOTOR_1, OUTPUT);
  pinMode(DO_MOTOR_2, OUTPUT);
  pinMode(PWM_ENABLE, OUTPUT);

  digitalWrite(DO_MOTOR_1, LOW);
  digitalWrite(DO_MOTOR_2, LOW);
  analogWrite(PWM_ENABLE, 0);

  Serial.begin(9000);
  }

void loop() {
  // put your main code here, to run repeatedly:
  valeurPotentiometre = analogRead(AN_POTENTIOMETRE);
  if(valeurPotentiometre > 512)
  {
    //roation horaire
    digitalWrite(DO_MOTOR_1, LOW);
    digitalWrite(DO_MOTOR_2, HIGH);
    //Conversion proportionnelle 
    vitesseDuMoteur = map(valeurPotentiometre, 512, 1023, 0, 255);
    Serial.print("+");
  }
  else
  {
    //rotation anti-horaire
    digitalWrite(DO_MOTOR_2, LOW);
    digitalWrite(DO_MOTOR_1, HIGH);
    //Conversion inversement proportionnelle 
    vitesseDuMoteur = map(valeurPotentiometre, 0, 512, 255, 0);
    Serial.print("-");
  }
  analogWrite(PWM_ENABLE, vitesseDuMoteur);
  Serial.println(vitesseDuMoteur);
  delay(20);
}
