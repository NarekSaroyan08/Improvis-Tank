// Motor control pins
int enA = 8;
int in1 = 9;
int in2 = 10;
int in3 = 12;
int in4 = 11;
int enB = 13;

void setup() {
  // Define motor control pins as OUTPUT
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Initialize the serial communication for keyboard input
  Serial.begin(9600);
}

void loop() {
  // Read the serial input
  if (Serial.available() > 0) {
    char command = Serial.read();
    motorControl(command);
  }
}

void motorControl(char command) {
  int motorSpeed = 255; // You can adjust this for the desired speed
  
  switch(command) {
    case 'W':
      // Move the motor forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, motorSpeed);
      analogWrite(enB, motorSpeed);

      break;
    case 'S':
      // Move the motor backward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, motorSpeed);
      analogWrite(enB, motorSpeed);
      break;
    case 'A':
      // Move the motor to the left
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, motorSpeed);
      analogWrite(enB, motorSpeed);
      break;
    case 'D':
      // Move the motor to the right
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, motorSpeed);
      analogWrite(enB, motorSpeed);
      break;
    default:
      // Stop the motor if an unknown command is received or no key is pressed
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      break;
  }
}
