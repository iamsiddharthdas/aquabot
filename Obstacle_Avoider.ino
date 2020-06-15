int motorL[]={3,2};  
int motorR[]={5,4}; 
int vcc = A0; 
int trig = A1;
int echo = A2; 
int gnd = A3; 
int duration;
void setup() 
{  
    Serial.begin(9600);
 
    for(int i=0;i<2;i++)
    {   pinMode(motorL[i],OUTPUT);
        pinMode(motorR[i],OUTPUT);
    }
    pinMode (vcc,OUTPUT);
    pinMode (gnd,OUTPUT);
    digitalWrite(vcc,HIGH);          
    digitalWrite(gnd,LOW);
    pinMode(echo,INPUT);
    pinMode(trig, OUTPUT);
     
}            
void loop() 
{                
        
        
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);
        
        duration = pulseIn(echo, HIGH);
       
          if (duration< 1300)  
           { Serial.println("Moving right");
              right();
              delay(500);
           } 
           else 
           { Serial.println("Moving Forward"); 
              fwd();
           }       

}      
void fwd()

{ 
  digitalWrite(motorR[0],HIGH);
  digitalWrite(motorR[1],LOW);
  digitalWrite(motorL[0],HIGH);
  digitalWrite(motorL[1],LOW);

}
void bck()
{ 
  digitalWrite(motorR[0],LOW);
  digitalWrite(motorR[1],HIGH);
  digitalWrite(motorL[0],LOW);
  digitalWrite(motorL[1],HIGH);

}
void left()
{
  digitalWrite(motorR[0],HIGH);
  digitalWrite(motorR[1],LOW);
  digitalWrite(motorL[0],LOW);
  digitalWrite(motorL[1],HIGH);

}

void right()
{
  digitalWrite(motorR[0],LOW);
  digitalWrite(motorR[1],HIGH);
  digitalWrite(motorL[0],HIGH);
  digitalWrite(motorL[1],LOW);

}

void nomove()
{
  digitalWrite(motorR[0],LOW);
  digitalWrite(motorR[1],LOW);
  digitalWrite(motorL[0],LOW);
  digitalWrite(motorL[1],LOW);
}
