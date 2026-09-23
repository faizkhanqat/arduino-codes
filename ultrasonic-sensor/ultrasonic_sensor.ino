#include <Servo.h>

Servo radarServo;

int trigPin = 9;
int echoPin = 10;

void setup() {

  radarServo.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  // Sweep left to right
  for (int angle = 0; angle <= 180; angle++) {

    radarServo.write(angle);
    delay(20);

    int distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }

  // Sweep right to left
  for (int angle = 180; angle >= 0; angle--) {

    radarServo.write(angle);
    delay(20);

    int distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.0343 / 2;

  return distance;
}
