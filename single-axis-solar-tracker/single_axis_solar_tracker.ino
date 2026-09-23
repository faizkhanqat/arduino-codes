// SINGLE AXIS SOLAR TRACKER

int leftLDR = A0;
int rightLDR = A1;

int ENA = 5;
int IN1 = 7;
int IN2 = 8;

void setup() {

  pinMode(leftLDR, INPUT);
  pinMode(rightLDR, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  stopMotor();

  Serial.begin(9600);
}

void loop() {

  int leftValue = analogRead(leftLDR);
  int rightValue = analogRead(rightLDR);

  int difference = leftValue - rightValue;

  Serial.print("Left: ");
  Serial.print(leftValue);

  Serial.print("  Right: ");
  Serial.println(rightValue);

  // Small difference = already aligned
  if (abs(difference) < 50) {
    stopMotor();
  }

  // Left side has more light
  else if (difference > 50) {
    rotateLeft();
  }

  // Right side has more light
  else {
    rotateRight();
  }

  delay(100);
}

void rotateLeft() {

  analogWrite(ENA, 150);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void rotateRight() {

  analogWrite(ENA, 150);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void stopMotor() {

  analogWrite(ENA, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
