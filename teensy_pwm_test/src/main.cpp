#include <Arduino.h>
#include <PWMServo.h>

PWMServo servo_leg_r1;
PWMServo servo_leg_r2;
PWMServo servo_leg_r3;
PWMServo servo_leg_r4;
PWMServo servo_blg_r1;
PWMServo servo_arm_r2;
PWMServo servo_arm_r1;

PWMServo servo_leg_l1;
PWMServo servo_leg_l2;
PWMServo servo_leg_l3;
PWMServo servo_leg_l4;
PWMServo servo_blg_l1;

void pose_main();
void pose_sit();

void setup() {
  Serial.begin(9600);
  servo_leg_r1.attach(1);
  servo_leg_r2.attach(2);
  servo_leg_r3.attach(3);
  servo_leg_r4.attach(4);

  servo_blg_r1.attach(5);

  servo_leg_l1.attach(8);
  servo_leg_l2.attach(9);
  servo_leg_l3.attach(10);
  servo_leg_l4.attach(11);

  servo_blg_l1.attach(12);

  // servo_arm_r2.attach(5);
  // servo_arm_r1.attach(6);
}
int aci = 0;

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case '1':
        pose_main();
        aci = 30;
        break;
      case '2':
        pose_sit();
        aci = 120;
        break;
      case '3':
        servo_leg_l3.write(aci);
        aci++;
        Serial.print("\naci degeri: ");
        Serial.print(aci);
        break;
      default:
        Serial.print("\nGecersiz komut");
        break;
    }
  }
  // servo_leg_l1.write(90);

}



void pose_main() {

  servo_leg_r1.write(90);
  servo_leg_l1.write(90);
  delay(150);
  servo_leg_r2.write(150);
  servo_leg_l2.write(30);
  delay(150);
  servo_leg_r3.write(150);
  servo_leg_l3.write(30);
  delay(150);
  servo_leg_r4.write(30);
  servo_leg_l4.write(150);
  delay(150);
  servo_blg_r1.write(90);
  servo_blg_l1.write(90);
  delay(150);
  // servo_arm_r1.write(30);
  // servo_arm_r2.write(30);

  Serial.print("\nmain pose");
}

void pose_sit() {

  servo_leg_r1.write(90);
  servo_leg_l1.write(90);
  delay(150);
  servo_leg_r2.write(70);
  servo_leg_l2.write(110);
  delay(150);
  servo_leg_r3.write(60);
  servo_leg_l3.write(120);
  delay(150);
  servo_leg_r4.write(30);
  servo_leg_l4.write(150);
  delay(150);
  servo_blg_r1.write(90);
  servo_blg_l1.write(90);
  delay(150);
  // servo_arm_r1.write(30);
  // servo_arm_r2.write(60);
  

  Serial.print("\nsit pose");
}