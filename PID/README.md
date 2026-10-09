# PID Distance Control Experiment

A standalone Arduino experiment exploring **P, PD, and PID control** with distance feedback. This project is **unrelated to the 3 kg robofootball robot**.

## Hardware

- Arduino Nano ESP32 microcontroller
- VL53L0X time-of-flight distance sensor (I²C)
- Servo motor (controlled in the provided sketch, signal on pin 11)
- Stepper motor (mentioned as available hardware, but **not controlled by this sketch**)

**Note:** The provided program uses the Arduino `Servo` library and `myServo.write()`. A stepper motor needs a separate driver and different code. Verify pin compatibility, sensor wiring, and servo power requirements for the exact board before running.

## Control Settings

| Parameter | Value |
| --- | --- |
| Target distance (setpoint) | 87 mm |
| Proportional gain, Kp | 0.05 |
| Integral gain, Ki | 0.001 |
| Derivative gain, Kd | 0.01 |
| Servo center | 93° |
| Servo output limits | 75°–107° |
| Assumed sample time | 0.05 s |
| Integral clamp | −300 to 300 |

The error is `distance - setpoint`. The proportional term reacts to present error, the derivative term to changes in error, and the integral term to accumulated error. The computed correction adjusts the servo angle.

## P / PD / PID Tuning

To experiment with each mode, keep the same code and set:

| Mode | Kp | Ki | Kd |
| --- | --- | --- | --- |
| P | 0.05 | 0 | 0 |
| PD | 0.05 | 0 | 0.01 |
| PID | 0.05 | 0.001 | 0.01 |

These are parameter configurations for comparison, **not claimed measurements or tuning results**. Tune P first, introduce D to reduce overshoot if needed, and add I only if persistent error remains.

## Code

[**View the original Arduino sketch**](PID_Distance_Control.ino)

The sketch is preserved as provided, including the sensor initialization, distance reading, error calculation, integral clamp, and servo commands.

## Technical Notes

- The servo angle is constrained for mechanical safety. Sensor and hardware compatibility must be verified before running.
- The sensor's use 3.3v only extended amount of 5v will burn the sensor. During initial testing, I connected the VL53L0X sensor module to a 5 V supply, which resulted in permanent damage to the sensor. Fortunately, I had a replacement available and continued the experiment using 3.3 V. This experience taught me the importance of checking component voltage requirements and verifying the power supply before connecting hardware. Although some VL53L0X breakout boards support 5 V through onboard voltage regulation, the module I used did not tolerate the connection.
