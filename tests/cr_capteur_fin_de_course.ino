// ce code sert a stoppé le moteur quand le capteur de fin de course est activé

int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
void setup() {
  // put your setup code here, to run once:
  pinMode(E2, OUTPUT); 
  pinMode(M2, OUTPUT);
// initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//read the sensor;
  int sensorReading = analogRead(A0);
  //map the sensor range to a range of four option:
  int range = map(sensorReading,0,1);

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
  }
  else{
    avance();
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
