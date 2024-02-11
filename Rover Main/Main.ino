// Set constan variables
#define TrigWavePin 13
#define EchoReceivePin 12
#define ScaleFactor 10
#define IRLeft 3
#define IRRight 2
#define LeftMotorEnable 9
#define LeftMotorIn1 8
#define LeftMotorIn2 7
#define RightMotorEnable 6
#define RightMotorIn1 5
#define RightMotorIn2 4

void set_direction(int in1, int in2, char direction[]) {
  if (direction == "Forward") {
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
  } else if (direction == "Backward"){
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
  } else { //Turns motor off as unaccepted string arguent was suplied 
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
  }
}

void move_forward(int speed) {
  char direction[] = "Forward";
  set_direction(LeftMotorIn1, LeftMotorIn2, direction);
  analogWrite(LeftMotorEnable, speed);
  set_direction(RightMotorIn1, RightMotorIn2, direction);
  analogWrite(RightMotorEnable, speed);
}

void turn_left(int speed) {
  char For[] = "Forward";
  char Back[] = "Backward";
  set_direction(LeftMotorIn1, LeftMotorIn2, Back);
  analogWrite(LeftMotorEnable, speed);
  set_direction(RightMotorIn1, RightMotorIn2, For);
  analogWrite(RightMotorEnable, speed);
}

void turn_right(int speed) {
  char For[] = "Forward";
  char Back[] = "Backward";
  set_direction(LeftMotorIn1, LeftMotorIn2, For);
  analogWrite(LeftMotorEnable, speed);
  set_direction(RightMotorIn1, RightMotorIn2, Back);
  analogWrite(RightMotorEnable, speed);
}

void move_backward(int speed) {
  char direction[] = "Backward";
  set_direction(LeftMotorIn1, LeftMotorIn2, direction);
  analogWrite(LeftMotorEnable, speed);
  set_direction(RightMotorIn1, RightMotorIn2, direction);
  analogWrite(RightMotorEnable, speed);
}

void stop_moving() {
  char stop[] = "Stop";
  set_direction(LeftMotorIn1, LeftMotorIn2, stop);
  analogWrite(LeftMotorEnable, 0);
  set_direction(RightMotorIn1, RightMotorIn2, stop);
  analogWrite(RightMotorEnable, 0);
}



void setup() {
  // put your setup code here (Pins etc), to run once:

  // Set up ultrasonic distance sensor
  pinMode(TrigWavePin, OUTPUT); // Sets pin 13 to output to trigger ultrasonic pulse
  pinMode(EchoReceivePin, INPUT); // Receives echo from sensor

  //Set up IR Sensors
  pinMode(IRLeft, INPUT);
  pinMode(IRRight, INPUT);

  //Set up motor pins
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(LeftMotorIn1, OUTPUT);
  pinMode(LeftMotorIn2, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);
  pinMode(RightMotorIn1, OUTPUT);
  pinMode(RightMotorIn2, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int Left_IR = digitalRead(IRLeft);
  int Right_IR = digitalRead(IRRight);

  if (Left_IR == 0 and Right_IR == 0) {
    move_forward(175);
  } else if (Left_IR == 1 and Right_IR == 0) {
    turn_left(100);
  } else if (Left_IR == 0 and Right_IR == 1) {
    turn_right(100);
  } else if (Left_IR == 1 and Right_IR == 1) {
    stop_moving();
    // need to move forward and somehow orient whihc way to go as this means we have met an impass where the road splits or we are somehow the wrong way
  }
  delay(0.5);
}
