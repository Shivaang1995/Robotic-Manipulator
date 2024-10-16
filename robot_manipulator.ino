#include <SoftwareSerial.h>
#include <Servo.h>

// Motor control pins
const int motor1Pin1 = A0; // Motor 1 control pin 1
const int motor1Pin2 = A1; // Motor 1 control pin 2
const int motor2Pin1 = A2; // Motor 2 control pin 1
const int motor2Pin2 = A3; // Motor 2 control pin 2

// Create Servo objects for each part of the robotic arm
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripperServo;
Servo wristPitchServo; // Added wrist pitch servo

// Define pins for each servo
int basePin = 4;
int shoulderPin = 5;
int elbowPin = 6;
int gripperPin = 9;
int wristPitchPin = 10; // Define pin for wrist pitch servo

// Initialize variables for current positions
int basePosition = 90;
int shoulderPosition = 90;
int elbowPosition = 90;
int gripperPosition = 90;
int wristPitchPosition; // Variable to store the wrist pitch position, no initial value

// Angle increment for each movement
int increment = 10;

// SoftwareSerial for Bluetooth communication
SoftwareSerial bluetooth(2, 3); // RX on pin 2, TX on pin 3

void setup() {
  // Motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Attach servos to their pins
  baseServo.attach(basePin);
  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  gripperServo.attach(gripperPin);
  wristPitchServo.attach(wristPitchPin); // Attach the wrist pitch servo

  // Start Serial communication with Bluetooth module and Serial Monitor
  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Bluetooth Controlled Car - Ready to receive commands");
}

void loop() {
  // Check if data is available to read from Bluetooth
  if (bluetooth.available() > 0) {
    char command = bluetooth.read(); // Read the incoming command
    Serial.print("Received command: ");
    Serial.println(command);
    
    // Process car commands
    switch (command) {
      case 'F':
        Serial.println("Command: Move Forward");
        moveForward();
        break;
        
      case 'G':
        Serial.println("Command: Move Backward");
        moveBackward();
        break;
        
      case 'L':
        Serial.println("Command: Turn Left");
        turnLeft();
        break;
        
      case 'R':
        Serial.println("Command: Turn Right");
        turnRight();
        break;

      case 'S': // Stop the motors
        Serial.println("Command: Stop");
        stopMotors();
        break;
        
      // Process robotic arm commands
      case 'B': // Base left
        basePosition = min(basePosition + increment, 180);
        baseServo.write(basePosition);
        Serial.print("Base Up: ");
        Serial.println(basePosition);
        break;
        
      case 'b': // Base right
        basePosition = max(basePosition - increment, 0);
        baseServo.write(basePosition);
        Serial.print("Base Down: ");
        Serial.println(basePosition);
        break;

      case 'X': // Shoulder Up
        shoulderPosition = min(shoulderPosition + increment, 180);
        shoulderServo.write(shoulderPosition);
        Serial.print("Shoulder Up: ");
        Serial.println(shoulderPosition);
        delay(20);
        break;

      case 'D': // Shoulder Down
        shoulderPosition = max(shoulderPosition - increment, 0);
        shoulderServo.write(shoulderPosition);
        Serial.print("Shoulder Down: ");
        Serial.println(shoulderPosition);
        delay(20);
        break;

      case 'E': // Elbow Up
        elbowPosition = min(elbowPosition + increment, 180);
        elbowServo.write(elbowPosition);
        Serial.print("Elbow Up: ");
        Serial.println(elbowPosition);
        break;

      case 'e': // Elbow Down
        elbowPosition = max(elbowPosition - increment, 0);
        elbowServo.write(elbowPosition);
        Serial.print("Elbow Down: ");
        Serial.println(elbowPosition);
        break;

      case 'O': // Gripper Open
        gripperPosition = min(gripperPosition + increment, 180);
        gripperServo.write(gripperPosition);
        Serial.print("Gripper Open: ");
        Serial.println(gripperPosition);
        break;

      case 'C': // Gripper Close
        gripperPosition = max(gripperPosition - increment, 0);
        gripperServo.write(gripperPosition);
        Serial.print("Gripper Close: ");
        Serial.println(gripperPosition);
        break;

      // Added wrist pitch commands
      case 'W': // Wrist Pitch Up
        wristPitchPosition = min(wristPitchPosition + increment, 180);
        wristPitchServo.write(wristPitchPosition);
        Serial.print("Wrist Pitch Up: ");
        Serial.println(wristPitchPosition);
        break;

      case 'w': // Wrist Pitch Down
        wristPitchPosition = max(wristPitchPosition - increment, 0);
        wristPitchServo.write(wristPitchPosition);
        Serial.print("Wrist Pitch Down: ");
        Serial.println(wristPitchPosition);
        break;

      default:
        Serial.println("Invalid command received.");
        break;
    }
  }
  
  delay(100); // Small delay for stability
}

// Function to move forward
void moveForward() {
  analogWrite(motor1Pin1, 180);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, 180);
  digitalWrite(motor2Pin2, LOW);
  Serial.println("Action: Moving Forward");
}

// Function to move backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, 180);
  digitalWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, 180);
  Serial.println("Action: Moving Backward");
}

// Function to turn left
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, 180);
  analogWrite(motor2Pin1, 180);
  digitalWrite(motor2Pin2, LOW);
  Serial.println("Action: Turning Left");
}

// Function to turn right
void turnRight() {
  analogWrite(motor1Pin1, 180);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  Serial.println("Action: Turning Right");
}

// Function to stop motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  Serial.println("Action: Stopping Motors");
}
