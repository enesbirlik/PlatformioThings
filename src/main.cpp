#include <Arduino.h>
#include <PWMServo.h>

  //i am making mini humanoid robot and it has 19 servo motors. i vat to control servo positions pose by pose and(example: sit walk dance etc)
  //and servo moves must occur wtihin a certain time. i want to make a program that can do this. i am using teensy 4.0 and 19 servo motors.

  //servo names : leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, hip_r1, hip_l1, shl_r1, arm_r1, arm_r2, shl_l1, arm_l1, arm_l2, head, nothing
  //servo initial positions : 90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90

  //servo pins : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 22, 23, 24

  //servo min and max positions : 0, 180

  
  //bu sıranın değiştirilmesi kötü şeylere sebep olabilir.

enum servoNames {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, hip_r1, hip_l1, shl_r1, arm_r1, arm_r2, shl_l1, arm_l1, arm_l2, head, dummy, NUM_SERVOS};

const int servoPins[21] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,18,19,22,23,24};

PWMServo servos[NUM_SERVOS];

const int mainPositions[NUM_SERVOS] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};

const char* nameServo[NUM_SERVOS] = {"leg_r1", "leg_r2", "leg_r3", "leg_r4", "leg_r5", "leg_l1", "leg_l2", "leg_l3", "leg_l4", "leg_l5", "hip_r1", "hip_l1", "shl_r1", "arm_r1", "arm_r2", "shl_l1", "arm_l1", "arm_l2", "head__", "dummy_"};


  
int previousPositions[NUM_SERVOS];
int duration_time = 1000;
float increment[NUM_SERVOS];
unsigned long finalTime;
unsigned long partialTime;


void moveServoSmooth(int finalPose[], int duration, int servoPositions[]) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < static_cast<unsigned long>(duration)) {
    float progress = static_cast<float>(millis() - startTime) / duration;
    
    for (int i = 0; i < NUM_SERVOS; i++) {
      int newPosition = servoPositions[i] + static_cast<int>((finalPose[i] - servoPositions[i]) * progress);
      servos[i].write(newPosition);

    //Serial.print("servo name: ");
    //Serial.print(nameServo[i]);
    //Serial.print("   last position: ");
    //Serial.println(newPosition);
      if (i == 0)
      {
        Serial.print(newPosition);
        Serial.print(",");
      }
      if (i == 1)
      {
        Serial.println(newPosition);
      }
     
      
      
    }
    
    delay(10);
  
  }
  
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(finalPose[i]);
    servoPositions[i] = finalPose[i];
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
  int posesit[NUM_SERVOS] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90, 30, 60, 30, 150, 120, 150, 90,90};
  moveServoSmooth(posesit, duration_time, previousPositions);
}

void mainPose(){
  int posemain[NUM_SERVOS] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90,90};
  moveServoSmooth(posemain, duration_time, previousPositions);
}


int my_angle1[NUM_SERVOS]={0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,90};
int my_angle2[NUM_SERVOS]={90, 50, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90,90};
int my_angle3[NUM_SERVOS]={180, 125, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180,90};
int my_angle4[NUM_SERVOS]={45, 100, 45, 45, 45, 45, 45, 45, 45, 45, 90, 90, 45, 45, 45, 45, 45, 45, 45,90};
int my_angle5[NUM_SERVOS]={135, 150, 135, 135, 135, 135, 135, 135, 135, 135, 90, 90, 135, 135, 135, 135, 135, 135, 135,90};

  void loop(){


    int randomChoice = random(1,6); 
    if (randomChoice == 1) {
      moveServoSmooth(my_angle1, duration_time, previousPositions);
    }
    else if (randomChoice == 2) {
      moveServoSmooth(my_angle2, duration_time, previousPositions);
    }
    else if (randomChoice == 3) {
      moveServoSmooth(my_angle3, duration_time, previousPositions);
    }
    else if (randomChoice == 4) {
      moveServoSmooth(my_angle4, duration_time, previousPositions);
    }
    else if (randomChoice == 5) {
      moveServoSmooth(my_angle5, duration_time, previousPositions);
    }
    else {
      Serial.println("invalid command");
    }
    delay(1000);  // Bir sonraki rastgele seçimi beklemek için bekleme süresi


    // if (Serial.available()>0){
    //   char command = Serial.read();
    //   if (command == '1'){
    //     //sitPose();
    //     moveServoSmooth(my_angle1, duration_time, previousPositions);
    //   }
    //   else if (command == '2'){
    //     //mainPose();
    //     moveServoSmooth(my_angle2, duration_time, previousPositions);
    //   }
    //   else if (command == '3'){
    //     moveServoSmooth(my_angle3, duration_time, previousPositions);
    //   }
    //   else
    //   {
    //     Serial.println("invalid command");
    //   }
    // }

  }
