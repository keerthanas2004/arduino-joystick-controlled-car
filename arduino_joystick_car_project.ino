#include<NewPing.h>          
#include<AFMotor.h>           

#define TRIG A1           // Trigger pin - pin A1 
#define ECHO A0           // Echo pin - pin A0 
#define MAX_DISTANCE 200      // Maximum ping distance
#define X_AXIS A2         //ANALOG INPUT OF X AXIS VALUE FROM JOYSTICK
#define Y_AXIS A3         //ANALOG INPUT OF Y AXIS VALUE FROM JOYSTICK

unsigned int distance = 0;      //Distance measured by ultrasonic sensor   

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);  //NewPing setup of pins and maximum distance

//Create motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

void setup() 
{ 
   pinMode(X_AXIS,INPUT);    //SET X-AXIS PIN OF JOYSTICK AS ANALOG INPUT
   pinMode(Y_AXIS,INPUT);    //SET Y-AXIS PIN OF JOYSTICK AS ANALOG INPUT
}

void loop() 
{                        
  delay(50);                                        
  distance = sonar.ping_cm();        //Send ping, get distance in cm and store 
  int xread=analogRead(X_AXIS);     //READ VALUE OF X-AXIS FROM JOYSTICK
  int yread=analogRead(Y_AXIS);     //READ VALUE OF Y-AXIS FROM JOYSTICK

  //According to the position of the joystick, move the car/robot
  if(yread >= 800)           // If the joystick is pointing towards front
  {
    if(distance > 9)         //If not object is detected right in front of the car/robot, move the car forward
    { 
    Motor1.setSpeed(150);  
    Motor1.run(FORWARD);   
    Motor2.setSpeed(150);  
    Motor2.run(FORWARD);   
    Motor3.setSpeed(150);  
    Motor3.run(FORWARD);  
    Motor4.setSpeed(150);  
    Motor4.run(FORWARD);  
    }
    else if((distance > 1) && (distance <= 9))    //If an object is detected right in front of the car/robot, do not move the car forward
    {
      Motor1.setSpeed(0);    
      Motor1.run(RELEASE);   
      Motor2.setSpeed(0);    
      Motor2.run(RELEASE);   
      Motor3.setSpeed(0);    
      Motor3.run(RELEASE);   
      Motor4.setSpeed(0);    
      Motor4.run(RELEASE); 
    }
  }

  if(xread >= 800)       //If the joystick is pointing towards left, move left
  {
    Motor1.setSpeed(150);  
    Motor1.run(BACKWARD);  
    Motor2.setSpeed(150);  
    Motor2.run(BACKWARD);  
    Motor3.setSpeed(150);  
    Motor3.run(FORWARD);   
    Motor4.setSpeed(150);  
    Motor4.run(FORWARD);   
    delay(150);
  }
  

  if(yread == 0)      //If the joystick is pointing backwards, move back
  {
    Motor1.setSpeed(100);   
    Motor1.run(BACKWARD);   
    Motor2.setSpeed(100);    
    Motor2.run(BACKWARD);   
    Motor3.setSpeed(100);    
    Motor3.run(BACKWARD);   
    Motor4.setSpeed(100);   
    Motor4.run(BACKWARD);   
  }

  if(xread == 0)      //If the joystick is pointing towards right, move right
  {
    Motor1.setSpeed(100);  
    Motor1.run(FORWARD);   
    Motor2.setSpeed(150);  
    Motor2.run(FORWARD);   
    Motor3.setSpeed(100);  
    Motor3.run(BACKWARD);  
    Motor4.setSpeed(150);  
    Motor4.run(BACKWARD);  
  }
  
  if((xread > 0 && xread < 800) && (yread > 0 && yread < 800))   // If the joystick is in its original position (in the middle)
  {
    Motor1.setSpeed(0);    
    Motor1.run(RELEASE);   
    Motor2.setSpeed(0);    
    Motor2.run(RELEASE);   
    Motor3.setSpeed(0);    
    Motor3.run(RELEASE);   
    Motor4.setSpeed(0);    
    Motor4.run(RELEASE); 
  }
  
}