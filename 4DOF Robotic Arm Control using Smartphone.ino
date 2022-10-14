#include <Servo.h> 
#include <math.h>  
#define pie 3.141

Servo Servomotorbase;  
Servo Servomotorshoulder;  
Servo Servomotorelbow; 
Servo Servomotorgripper;

int command;

struct joint_Angle{
  int servo_base;
  int servo_shoulder;
  int servo_elbow;
};

int desiredservo_Grip;
int gripperservo_Pos;

int desiredservo_Delay;

int servo_Speed = 15;
int ready = 0;

struct joint_Angle desired_Angle;


int servo_Parallel_Control (int the_Pos, Servo the_Servo );


void setup()
{ 
  Serial.begin(9600);
  Servomotorbase.attach(9);        
  Servomotorshoulder.attach(10);
  Servomotorelbow.attach(11);
  Servomotorgripper.attach(6);
  
  Serial.setTimeout(50);      
  Serial.println("Begin");
  Servomotorbase.write(90);        
  Servomotorshoulder.write(150);
  Servomotorelbow.write(110);
  ready = 0;
} 


void loop() 
{ 
  if (Serial.available()){
    ready = 1;
    desired_Angle.base = Serial.parseInt();
    desired_Angle.shoulder = Serial.parseInt();
    desired_Angle.elbow = Serial.parseInt();
    desired_Grip = Serial.parseInt();
    desired_Delay = Serial.parseInt();

    if(Serial.read() == '\n'){              

        Serial.flush();                    
         
        Serial.print('dlt');      
    }
  }
  
  int status_1 = 0;
  int status_2 = 0;
  int status_3 = 0;
  int status_4 = 0;
  int done = 0 ; 
  
  while(done == 0 && ready == 1){  
    //move the servo to the desired position
    status_1 = servo_Parallel_Control(desired_Angle.base, Servomotorbase, desired_Delay);
    status_2 = servo_Parallel_Control(desired_Angle.shoulder,  Servomotorshoulder, desired_Delay);
    status_3 = servo_Parallel_Control(desired_Angle.elbow, Servomotorelbow, desired_Delay);      
    status_4 = servo_Parallel_Control(desired_Grip, Servomotorgripper, desired_Delay);  
    
    if (status_1 == 1 & status_2 == 1 & status_3 == 1 & status_4 == 1){
      done = 1;
      
    }
        
  }// end of while
  

  
  
}


int servo_Parallel_Control (int the_Pos, Servo the_Servo, int the_Speed ){
  
    int start_Pos = the_Servo.read();       
    int new_Pos = start_Pos;
    
    if (start_Pos < (the_Pos-5)){
          
       new_Pos = new_Pos + 1;
       the_Servo.write(new_Pos);
       delay(the_Speed);
       return 0;
           
    }
  
   else if (new_Pos > (the_Pos + 5)){
  
      new_Pos = new_Pos - 1;
      the_Servo.write(new_Pos);
      delay(the_Speed);
      return 0;
          
    }  
    
    else {
        return 1;
    }  
    
  
}