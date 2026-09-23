#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// L298N
int ENA = 5;
int ENB = 6;

int IN1 = 7;
int IN2 = 8;

int IN3 = 9;
int IN4 = 10;

// PID values from project documentation
float Kp = 3.5;
float Ki = 0.02;
float Kd = 0.8;

float angle = 0;
float error = 0;
float previousError = 0;
float integral = 0;

unsigned long previousTime;

void setup() {

  Wire.begin();

  mpu.initialize();

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  previousTime = millis();

  Serial.begin(9600);
}

void loop() {

  // Read MPU6050
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Simple accelerometer angle
  angle = atan2(ax, az) * 180 / PI;

  // PID
  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0;

  if (dt <= 0) {
    dt = 0.008;
  }

  previousTime = currentTime;

  error = angle;

  integral += error * dt;

  float derivative = (error - previousError) / dt;

  float output =
    Kp * error +
    Ki * integral +
    Kd * derivative;

  previousError = error;

  output = constrain(output, -255, 255);

  if (output > 0) {
    forward(abs(output));
  }
  else {
    backward(abs(output));
  }

  Serial.print("Angle: ");
  Serial.print(angle);

  Serial.print("  Output: ");
  Serial.println(output);
}

void forward(int speed) {

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward(int speed) {

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
