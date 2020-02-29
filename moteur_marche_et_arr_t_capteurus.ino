// --- les variables : déclaration et initialisation

int E2 = 6;    //M2 : vitesse du moteur M2
int M2 = 7;    //M2 Direction : horaire/anti-horaire
int pinTrig = 2;
int pinEcho = 3;
long temps 
float distance 

// --- le Programme : setup() et loop()
void setup() { 
   pinMode(E2, OUTPUT); 
   pinMode(M2, OUTPUT);  
   pinMode(pinTrig, OUTPUT);
   pinMode(pinEcho, INPUT);
   
   digitalWrite(pinTrig, LOW);
   
   Serial.begin(9600);

} 
  
void loop() {
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  temps =  pulseIn(pinEcho, HIGH);
  if (temps> 25000) {
    Serial.println("Echec de la mesure");
  }
  else{
    temps = temps/2;
    distance =(temps*340)/10000.0;
    Serial.print("Distance: ")
    Serial.print(distance);
    Serial.println(" cm");
    
  }
  delay(2000);
  
  if (distance < 1) {
    stopped();
    delay(10000);  
    }
  else {
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
void back_off (char a,char b) {
  Serial.println("ARRIERE");

  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
