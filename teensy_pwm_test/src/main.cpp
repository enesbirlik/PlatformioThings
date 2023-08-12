#include <Arduino.h>
#include <PWMServo.h>

const int numLegServos = 12;
PWMServo deneme;
// Servo isimlerini burada tanımlayın
// enum LegServoName {
//   leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1,
//   leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1
// };
// PWMServo legServos[numLegServos];

// void pose_main();
// void pose_sit();
// void walk_forward();
// void move_servos_to(LegServoName servoNames[], int positions[], int duration);
// int duration = 1000;

void setup() {
  Serial.begin(9600);
  deneme.attach(19);
  // // Servo pin numaralarını burada düzenleyin
  // int legServoPins[] = {5, 4, 3, 2, 1, 23, 11, 10, 9, 8, 7, 22};

  // for (int i = 0; i < numLegServos; i++) {
  //   legServos[i].attach(legServoPins[i]);
  // }
  // pose_main();
}

void loop() {
  // if (Serial.available() > 0) {
  //   char command = Serial.read();
  //   switch (command) {
  //     case '1':
  //       pose_main();
  //       break;
  //     case '2':
  //       pose_sit();
  //       break;
  //     case '3':
  //       walk_forward();

  //       break;
  //     default:
  //       Serial.println("\nInvalid command");
  //       break;
  //   }
  // }
  deneme.write(0);
  delay(1000);
  deneme.write(90);
  delay(1000);
  deneme.write(180);
  delay(1000);

}

// void pose_main() {
//   LegServoName servoNames[] = {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1};
//   int positions[] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90};
//   move_servos_to(servoNames, positions, duration);
//   Serial.println("\nMain Pose");
// }

// void pose_sit() {
//   LegServoName servoNames[] = {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1};
//   int positions[] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90};
//   move_servos_to(servoNames, positions, duration);
//   Serial.println("\nSit Pose");
// }

// void walk_forward() {

//   //90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90
//   //110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90
//   //110, 150, 120, 65, 110, 90, 105, 30, 30, 150, 90, 90
//   //90, 150, 120, 65, 90, 90, 90, 30, 30, 150, 90, 90
//   LegServoName servoNames[] = {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1};
//   int position_1 [] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90};
//   int position_2 [] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90};
//   int position_3 [] = {110, 150, 120, 65, 110, 90, 105, 30, 30, 150, 90, 90};
//   int position_4 [] = {90, 150, 120, 65, 90, 90, 90, 30, 30, 150, 90, 90};
//   move_servos_to(servoNames, position_1, duration/2);
//   move_servos_to(servoNames, position_2, duration/2);
//   move_servos_to(servoNames, position_3, duration/2);
//   move_servos_to(servoNames, position_4, duration/2);
//   Serial.println("\nWalking Mode");

//   int step_pose1 [] = {75, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90};
//   int step_pose2 [] = {75, 150, 150, 30, 90, 90, 70, 30, 60, 120, 70, 90};
//   int step_pose3 [] = {90, 150, 150, 30, 90, 90, 90, 30, 60, 120, 90, 90};
//   int step_pose4 [] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90};
//   int step_pose5 [] = {110, 150, 120, 65, 110, 90, 105, 30, 30, 150, 90};
//   int step_pose6 [] = {90, 150, 120, 65, 90, 90, 90, 30, 30, 150, 90, 90};

//   int yanyan_array1 [] = {110, 150, 150, 30, 112, 90, 90, 30, 30, 150, 90, 90};
//   int yanyan_array2 [] = {70, 150, 150, 30, 70, 90, 70, 30, 30, 150, 70, 90};
//   int yanyan_array3 [] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90};
  
//   int steps = 10;
//   for (int i = 1; i <= steps; i++) {
//     move_servos_to(servoNames, step_pose1, duration/2);
//     move_servos_to(servoNames, step_pose2, duration/2);
//     move_servos_to(servoNames, step_pose3, duration/2);
//     move_servos_to(servoNames, step_pose4, duration/2);
//     move_servos_to(servoNames, step_pose5, duration/2);
//     move_servos_to(servoNames, step_pose6, duration/2);

//     // move_servos_to(servoNames, yanyan_array1, duration/2);
//     // move_servos_to(servoNames, yanyan_array2, duration/2);
//     // move_servos_to(servoNames, yanyan_array3, duration/2);
//   }
//   pose_main();
// }

// void move_servos_to(LegServoName servoNames[], int positions[], int duration) {
//   int startPositions[numLegServos];
//   for (int i = 0; i < numLegServos; i++) {
//     startPositions[i] = legServos[servoNames[i]].read();
//   }

//   unsigned long startTime = millis();
//   unsigned long endTime = startTime + duration;

//   while (millis() < endTime) {
//     float progress = (millis() - startTime) / (float)duration;
//     for (int i = 0; i < numLegServos; i++) {
//       int pos = startPositions[i] + (positions[i] - startPositions[i]) * progress;
//       legServos[servoNames[i]].write(pos);
//     }
//     delay(15); 
//   }

//   for (int i = 0; i < numLegServos; i++) {
//     legServos[servoNames[i]].write(positions[i]);
//   }
// }