int led6= 13;
int a;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led6,1);
  
  delay(1000);
  digitalWrite(led6,0);
  
  delay(1000);
  a = digitalRead(13);
  if(a==0)
  Serial.println("");
}
