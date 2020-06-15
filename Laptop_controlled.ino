
int motorL[]={3,2};  
int motorR[]={5,4};
int movement;
int flag=0;

void setup() 
{
Serial.begin(9600);

        pinMode(motorL[0],OUTPUT);
        pinMode(motorL[1],OUTPUT);
        pinMode(motorR[0],OUTPUT);
        pinMode(motorR[1],OUTPUT);
  
Serial.println("\tHow to use:-\n\t W-Forward \tS-Backwards\tA-Left\tD-Right "  );




}   



void loop() 
{   
    
     if (Serial.available())

      {      movement= Serial.read();
      
            if(movement== int('w')||movement==int('W'))
               flag=1;
             
            else if(movement== int('a')||movement==int('A'))
               flag=2;
            
            else if(movement== int('D')||movement==int('d'))
               flag=3;
            
            else if(movement== int('S')||movement==int('s'))
               flag=4;
          
      }
    
        if(flag==1)
        { 
          Serial.println("Moving Forward");
          fwd();
        }
        else if (flag == 2)
        { 
          Serial.println("Moving Left");
          left();
        }
        else if (flag==3)
        {
          Serial.println("Moving Right");
          right();
        }
        else if(flag==4)
        {
          Serial.println("Moving Backward");
          bck();
        }
        else
          nomove();

        
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
void right()
{
  digitalWrite(motorR[0],HIGH);
  digitalWrite(motorR[1],LOW);
  digitalWrite(motorL[0],LOW);
  digitalWrite(motorL[1],HIGH);

}

void left()
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
