#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685 I2C adresi
#define PCA9685_ADDRESS 0x40

// Servo nesnesi
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

// PCA9685 frekansı (varsayılan olarak 50Hz)
#define PWM_FREQUENCY 50

// Servo motorun minimum ve maksimum darbe genişliği değerleri
#define SERVO_MIN_PULSE_WIDTH 1000
#define SERVO_MAX_PULSE_WIDTH 2000

// Servo motorun minimum ve maksimum açı değerleri
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 360

// PCA9685 üzerindeki 16 kanal için hesaplanan minimum ve maksimum darbe genişliği değerleri
#define PCA9685_MIN_PULSE_WIDTH 150
#define PCA9685_MAX_PULSE_WIDTH 600

// PCA9685 üzerindeki 16 kanal için hesaplanan minimum ve maksimum açı değerleri
#define PCA9685_MIN_ANGLE 0
#define PCA9685_MAX_ANGLE 360

#define SERVO_1_CHANNEL 0
#define SERVO_2_CHANNEL 1
#define SERVO_3_CHANNEL 2

int SERVO_CHANNEL = 0;

void setup() {
  // I2C bağlantısını başlat
  Wire.begin();

  // PCA9685'i başlat
  pwm.begin();
  
  // Frekansı ayarla
  pwm.setPWMFreq(PWM_FREQUENCY);
}

// Servo motoru belirli bir açıya hareket ettirme fonksiyonu
void setServoAngle(uint8_t servoChannel, uint16_t angle) {
  // Açıyı sınırla
  if (angle < SERVO_MIN_ANGLE) {
    angle = SERVO_MIN_ANGLE;
  } else if (angle > SERVO_MAX_ANGLE) {
    angle = SERVO_MAX_ANGLE;
  }
  
  // PCA9685 üzerindeki darbe genişliğini hesapla
  uint16_t pulseWidth = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, PCA9685_MIN_PULSE_WIDTH, PCA9685_MAX_PULSE_WIDTH);
  

  pwm.setPWM(servoChannel, 0, pulseWidth);
}


void loop() {
  setServoAngle(SERVO_CHANNEL, 0);
  delay(1000);

  setServoAngle(SERVO_CHANNEL, 90);
  delay(1000);

  setServoAngle(SERVO_CHANNEL, 180);
  delay(1000);
}