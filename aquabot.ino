
 
int motorPin1 = 8;               
int motorPin2 = 9;               
int enable1=10;
int motorPin3 =  11 ;             
int motorPin4 = 12;          
int enable2= 13;
int bt_vcc=7;
char data;



int enableA =4;
int MotorA1 = 3;
int MotorA2 = 2;



void setup()  
{ 
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enable2,OUTPUT);
  
  pinMode(bt_vcc,OUTPUT);
  digitalWrite(bt_vcc,HIGH);
  

 pinMode (enableA, OUTPUT);
pinMode (MotorA1, OUTPUT);
pinMode (MotorA2, OUTPUT);

 digitalWrite(enable1,HIGH);
 digitalWrite(enable2,HIGH);
 digitalWrite(enableA,HIGH);
                        


  
}

void loop() 
{

 
 if (Serial.available())
  {
   data=Serial.read();
   Serial.println(data);
  
  
      if (data=='0')
      {
          sgt();
          Serial.println("Straight shafts");
      }
      
         

       else if(data=='1')
       
          {
            
             ang();
             Serial.println("Angled shafts");
           
          }   

                else if (data=='2')
                      {
                      digitalWrite(motorPin1, HIGH); 
                      digitalWrite(motorPin2, LOW); 
                      digitalWrite(motorPin3, HIGH); 
                      digitalWrite(motorPin4, LOW); 
                      Serial.println("Motors are rotating right,  BOT MOVING FORWARDS");
                      }
                    
                    else if (data=='3')
                    {
                      digitalWrite(motorPin1, LOW);   
                      digitalWrite(motorPin2, HIGH);  
                      digitalWrite(motorPin3, LOW);   
                      digitalWrite(motorPin4, HIGH);  
                      Serial.println("Motors are rotating left, BOT MOVING BACKWARDS");
                    }
                   else if (data=='4')
                    {
                        
                      digitalWrite(motorPin1, HIGH); 
                      digitalWrite(motorPin2, LOW); 
                      digitalWrite(motorPin3, LOW); 
                      digitalWrite(motorPin4, HIGH); 
                      Serial.println("First Motor is rotating right & Second is left,  BOT MOVING RIGHT");
                    }
                    else if (data=='5')
                    {
                       
                      digitalWrite(motorPin1, LOW); 
                      digitalWrite(motorPin2, HIGH); 
                      digitalWrite(motorPin3, HIGH); 
                      digitalWrite(motorPin4, LOW); 
                      Serial.println("First Motor is rotating Left & second is right,  BOT MOVING LEFT");
                    }
                
                    else if(data=='6')
                
                    {
                        digitalWrite(enable1,LOW);
                        digitalWrite(enable2,LOW);
                      digitalWrite(motorPin1, LOW);   
                      digitalWrite(motorPin2, LOW);   
                      digitalWrite(motorPin3, LOW);   
                      digitalWrite(motorPin4, LOW);   
                      Serial.println("Motors are Off");
                
                    }
   

                   
              
  
}

} 


            
void ang()
{
Serial.println ("Enabling Motors");
digitalWrite (enableA, HIGH);

Serial.println ("angled shafts");
digitalWrite (MotorA1, HIGH);
digitalWrite (MotorA2, LOW);
delay (50);

Serial.println ("Stoping motors");
digitalWrite (enableA, LOW);
delay(3000);

}


void sgt()
{

 Serial.println ("Enabling Motors");
digitalWrite (enableA, HIGH);

Serial.println ("straight shafts");
digitalWrite (MotorA1,LOW);
digitalWrite (MotorA2,HIGH);
delay (50);

Serial.println ("Stoping motors");
digitalWrite (enableA, LOW);
delay(3000);

}
  
