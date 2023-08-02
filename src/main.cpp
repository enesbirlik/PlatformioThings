#include <Arduino.h>
#include <PWMServo.h>

const int numLegServos = 12;

// Servo isimlerini burada tanımlayın
enum LegServoName {
  leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1,
  leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1
};
PWMServo legServos[numLegServos];

void pose_main();
void pose_sit();
void move_servos_to(LegServoName servoNames[], int positions[], int duration);

void setup() {
  Serial.begin(9600);

  // Servo pin numaralarını burada düzenleyin
  int legServoPins[] = {5, 4, 3, 2, 1, 23, 11, 10, 9, 8, 7, 22};

  for (int i = 0; i < numLegServos; i++) {
    legServos[i].attach(legServoPins[i]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'a':
        pose_main();
        break;
      case 's':
        pose_sit();
        break;
      default:
        Serial.println("\nInvalid command");
        break;
    }
  }
}

void pose_main() {
  LegServoName servoNames[] = {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1};
  int positions[] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90};
  move_servos_to(servoNames, positions, 1000);
  Serial.println("\nmain pose");
}

void pose_sit() {
  LegServoName servoNames[] = {leg_r1, leg_r2, leg_r3, leg_r4, leg_r5, blg_r1, leg_l1, leg_l2, leg_l3, leg_l4, leg_l5, blg_l1};
  int positions[] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90};
  move_servos_to(servoNames, positions, 1000);
  Serial.println("\nsit pose");
}

void move_servos_to(LegServoName servoNames[], int positions[], int duration) {
  int startPositions[numLegServos];
  for (int i = 0; i < numLegServos; i++) {
    startPositions[i] = legServos[servoNames[i]].read();
  }

  unsigned long startTime = millis();
  unsigned long endTime = startTime + duration;

  while (millis() < endTime) {
    float progress = (millis() - startTime) / (float)duration;
    for (int i = 0; i < numLegServos; i++) {
      int pos = startPositions[i] + (positions[i] - startPositions[i]) * progress;
      legServos[servoNames[i]].write(pos);
    }
    delay(15); // A small delay to smooth the motion
  }

  for (int i = 0; i < numLegServos; i++) {
    legServos[servoNames[i]].write(positions[i]);
  }
}