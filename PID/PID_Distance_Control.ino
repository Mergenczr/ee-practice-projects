#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Servo.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

Servo myServo;

float setpoint = 87;       // target distance in mm

float Kp = 0.05;
float Ki = 0.001;
float Kd = 0.01;

float centerAngle = 93;

float previousError = 0;
float integral = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Starting VL53L0X...");

  if (!lox.begin()) {
    Serial.println("Sensor not found!");
    while (1);
  }

  Serial.println("Sensor ready!");

  myServo.attach(11);
  myServo.write(centerAngle);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {

    float distance = measure.RangeMilliMeter;

    float error = distance - setpoint;

    // D
    float derivative =
        (error - previousError) / 0.05;

    // I
    integral =
        integral + error * 0.05;

    // prevent integral windup
    integral = constrain(integral, -300, 300);

    // PID
    float output =
        Kp * error +
        Ki * integral +
        Kd * derivative;

    float angle =
        centerAngle - output;

    angle = constrain(angle, 75, 107);

    myServo.write(angle);


    previousError = error;
  }
  else {
    Serial.println("Out of range");
  }

  delay(50);
}