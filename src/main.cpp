#include <Arduino.h>
#include <PWMServo.h>


  //i am making mini humanoid robot and it has 19 servo motors. i vat to control servo positions pose by pose and(example: sit walk dance etc)
  //and servo moves must occur wtihin a certain time. i want to make a program that can do this. i am using teensy 4.0 and 19 servo motors.

  //servo names : leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, hip_r1, hip_l1, shl_r1, arm_r1, arm_r2, shl_l1, arm_l1, arm_l2, head, nothing
  //servo initial positions : 90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90

  //servo pins : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 22, 23, 24

  //servo min and max positions : 0, 180

  //i want to attach servo names and pins first in loop and then i want to control servo positions in loop. i want to control servo positions pose by pose and(example: sit walk dance etc)

  //bu sıranın değiştirilmesi kötü şeylere sebep olabilir.
enum servoNames {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, hip_r1, hip_l1, shl_r1, arm_r1, arm_r2, shl_l1, arm_l1, arm_l2, head, NUM_SERVOS};

const int servoPins[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,18,19,22,23};

PWMServo servos[NUM_SERVOS];

const int mainPositions[NUM_SERVOS] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90};

const char* nameServo[NUM_SERVOS] = {"leg_r1", "leg_r2", "leg_r3", "leg_r4", "leg_r5", "leg_l1", "leg_l2", "leg_l3", "leg_l4", "leg_l5", "hip_r1", "hip_l1", "shl_r1", "arm_r1", "arm_r2", "shl_l1", "arm_l1", "arm_l2", "head"};



  //I want to control the servos over time. For example, I want a movement from 120 degrees to 90 degrees to take 1 second, etc. Let me enter a speed variable, and the robot's movements should accelerate accordingly. 
  //When giving input to the PWM servo, I want to move step by step and complete the entire movement within that duration.
  //but i cant read servos position i have to make a array and save servos last position in here
  //i want to make a array and save servos last position in here
  
int previousPositions[NUM_SERVOS];
int duration_time = 1000;

void moveServoSmooth(int finalPose[], int duration, int servoPositions[]) {
  int step[NUM_SERVOS];

  for (int i = 0; i < NUM_SERVOS; i++) {
    int initialPose = servoPositions[i];
    int difference = finalPose[i] - initialPose+1;

    step[i] = difference *100 / duration;

    Serial.print("step: ");
    Serial.println(step[i]);
  }
  
  

  for (int i = 0; i < duration; i++) {
    for (int j = 0; j < NUM_SERVOS; j++) {
      servoPositions[j] += step[j];
      servos[j].write(servoPositions[j]);
      
      //.print("servo name: ");
      //.print(nameServo[j]);
      //Serial.print("     Instant position: ");
      //Serial.println(servoPositions[j]);
    }
    //Serial.println(" ");
    delay(1);
  }
    
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoPositions[i] = finalPose[i];
    servos[i].write(servoPositions[i]);
    previousPositions[i] = servoPositions[i];
    Serial.print("servo name: ");
    Serial.print(nameServo[i]);
    Serial.print("   last position: ");
    Serial.println(servoPositions[i]);
    delay(50);
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(mainPositions[i]);
    previousPositions[i] = mainPositions[i];
      delay(50);
    //i want to serial print sero name and last position
    Serial.print("servo name: ");
    Serial.print(nameServo[i]);
    Serial.print("   last position: ");
    Serial.println(mainPositions[i]);
  }
}


  void sitPose(){
    int posesit[NUM_SERVOS] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90, 30, 60, 30, 150, 120, 150, 90};
    moveServoSmooth(posesit, duration_time, previousPositions);
  }

  void mainPose(){
    int posemain[NUM_SERVOS] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90};
    moveServoSmooth(posemain, duration_time, previousPositions);
  }

  void loop(){

    if (Serial.available()>0){
      char command = Serial.read();
      if (command == '2'){
        sitPose();
      }
      else if (command == '1'){
        mainPose();
      }
      else
      {
        Serial.println("invalid command");
      }
    }

  }
