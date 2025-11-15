#include <Arduino.h>
#include <XDuinoRails_MotorDriver.h>
#include <CmdLineParser.h>

// 1. Define Pin Connections
const int MOTOR_PWM_A_PIN = 7;
const int MOTOR_PWM_B_PIN = 8;
const int MOTOR_BEMF_A_PIN = A3;
const int MOTOR_BEMF_B_PIN = A2;

// 2. Create an instance of the motor driver
XDuinoRails_MotorDriver motor(MOTOR_PWM_A_PIN, MOTOR_PWM_B_PIN, MOTOR_BEMF_A_PIN, MOTOR_BEMF_B_PIN);

void setup() {
  Serial.begin(115200);
  motor.begin();
  Serial.println("Motor CLI initialized.");
  Serial.println("Commands:");
  Serial.println("  s <speed>        - Set target speed (PPS)");
  Serial.println("  d <0|1>          - Set direction (0=reverse, 1=forward)");
  Serial.println("  a <rate>         - Set acceleration (PPS/s)");
  Serial.println("  c <rate>         - Set deceleration (PPS/s)");
  Serial.println("  k <pwm> <ms>     - Set startup kick");
}

void loop() {
  motor.update();

  if (Serial.available() > 0) {
    String line = Serial.readStringUntil('\n');
    ModelRail::CmdLineParser parser(line);

    if (parser.getCmd() == "s") {
      motor.setTargetSpeed(parser.getArg(0).toInt());
    } else if (parser.getCmd() == "d") {
      motor.setDirection(parser.getArg(0).toInt() == 1);
    } else if (parser.getCmd() == "a") {
      motor.setAcceleration(parser.getArg(0).toFloat());
    } else if (parser.getCmd() == "c") {
      motor.setDeceleration(parser.getArg(0).toFloat());
    } else if (parser.getCmd() == "k") {
      motor.setStartupKick(parser.getArg(0).toInt(), parser.getArg(1).toInt());
    }
  }
}
