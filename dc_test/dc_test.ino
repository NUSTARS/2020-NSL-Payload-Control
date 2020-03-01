int m0_speed = 5;
int m0_dir= 6; 
int m0_sleep = 7;

int m1_speed = 2; 
int m1_dir = 3; 
int m1_sleep = 4; 
void setup() {
  pinMode(m0_speed,OUTPUT); 
  pinMode(m0_dir, OUTPUT); 
  pinMode(m0_sleep, OUTPUT); 
  
  pinMode(m1_speed, OUTPUT); 
  pinMode(m1_dir, OUTPUT); 
  pinMode(m1_sleep, OUTPUT);

}

void loop() {
  // Go forward


  digitalWrite(m0_sleep, HIGH);
  digitalWrite(m0_dir, HIGH);
  analogWrite(m0_speed, 255);
  
  //forwards(); 
  //delay(10000); 

  //Coast
  //coast(); 
  //delay(1000); 
  //backwards
  //backwards(); 

}





void forwards(){ 
  digitalWrite(m0_sleep, LOW); 
  digitalWrite(m0_sleep, LOW);
  
  digitalWrite(m0_dir, HIGH); 
  digitalWrite(m1_dir, HIGH);

  analogWrite(m0_speed, 255); 
  analogWrite(m0_speed, 255);
}
void backwards() { 
  digitalWrite(m0_sleep, LOW); 
  digitalWrite(m0_sleep, LOW);
  
  digitalWrite(m0_dir, HIGH); 
  digitalWrite(m1_dir, HIGH);

  analogWrite(m0_speed, 255); 
  analogWrite(m0_speed, 255);

}

void coast() { 
   digitalWrite(m0_sleep, HIGH); 
  digitalWrite(m0_sleep, HIGH);
} 
