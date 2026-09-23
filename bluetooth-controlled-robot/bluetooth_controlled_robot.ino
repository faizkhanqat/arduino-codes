#include <SoftwareSerial.h>

// HC-05
SoftwareSerial bluetooth(2, 3);
// Arduino D2 = RX
// Arduino D3 = TX

// L298N
int ENA = 5;
int ENB = 6;

int IN1 = 7;
int IN2 = 8;

int IN3 = 9;
int IN4 = 10;

void setup() {

  bluetooth.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

void loop() {

  if (bluetooth.available()) {

    char command = bluetooth.read();

    if (command == 'F') {
      forward();
    }

    else if (command == 'B') {
      backward();
    }

    else if (command == 'L') {
      left();
    }

    else if (command == 'R') {
      right();
    }

    else if (command == 'S') {
      stopMotors();
    }
  }
}

void forward() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
