/*
 * RC car controlled by smartphone with bluetooth communication
 * 
 * Control commands send through bluetooth module such as HC-06, HM-10 etc.
 * L9110S motor driver is used for controlling two motors.
 * For more informations : https://www.youtube.com/toymakers or http://cafe.naver.com/toymakers
 * 
 * September 17, 2018 programmed by Maker Mentor
 * 
 */

// Inialize pin number for motor A
#define A_1A  5
#define A_1B  6

// Inialize pin number for motor B
#define B_1A  10
#define B_1B  11

int carSpeed = 200; // Speed of motor

void setup() {
  Serial.begin(9600);

  // Set pin mode as OUTPUT for motor A
  pinMode(A_1A, OUTPUT);
  pinMode(A_1A, OUTPUT);

  // Set pin mode as OUTPUT for motor B
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);

  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
}

void loop() {

  if (Serial.available()) {
    
    char command = Serial.read(); // Save a command received from bluetooth module

    if (command == 'F' || command == 'f') {       // Moving forward
      moving_forward();
    }
    else if (command == 'B' || command == 'b') {  // Moving backward
      moving_backward();
    }
    else if (command == 'L' || command == 'l') {  // Moving left
      moving_left();
    }
    else if (command == 'R' || command == 'r') {  // Moving right
      moving_right();
    }
    else if (command == 'S' || command == 's') {  // Stop moving
      stop_moving();
    }
    else {  // Stop moving
      stop_moving();
    }
    
  }

  // Delay 100ms
  delay(100);
}

void moving_forward() {
  analogWrite(A_1A, LOW);
  analogWrite(A_1B, carSpeed);

  analogWrite(B_1A, carSpeed);
  analogWrite(B_1B, LOW);
}

void moving_backward() {
  analogWrite(A_1A, carSpeed);
  analogWrite(A_1B, LOW);

  analogWrite(B_1A, LOW);
  analogWrite(B_1B, carSpeed);
}

void moving_left() {
  analogWrite(A_1A, LOW);
  analogWrite(A_1B, carSpeed);
  
  analogWrite(B_1A, LOW);
  analogWrite(B_1B, LOW);
}

void moving_right() {
  analogWrite(A_1A, LOW);
  analogWrite(A_1B, LOW);
  
  analogWrite(B_1A, carSpeed);
  analogWrite(B_1B, LOW);
}

void stop_moving() {
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
}

