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
#define BASESPEED 125
#define KP 1
#define KI 1
#define KD 1
#define TrigWavePin 13
#define EchoReceivePin 12
double scalingFactor = 1.13;
double Convert = 1000000.0;
double SPEEDOFSOUND = 331;

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
  Serial.begin (9600);
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
  
  // Set up ultrasonic distance sensor
  pinMode(TrigWavePin, OUTPUT); // Sets pin 13 to output to trigger ultrasonic pulse
  pinMode(EchoReceivePin, INPUT); // Receives echo from sensor

}

void loop() {
  // put your main code here, to run repeatedly:
  int Left_IR = digitalRead(IRLeft);
  int Right_IR = digitalRead(IRRight);
  Serial.println("Left IR: ");
  Serial.print(Left_IR);
  Serial.println();
  Serial.println("Right IR: ");
  Serial.print(Right_IR);
  Serial.println();

  //int I = 0;
  //int last_error = 0;
  //set_direction(LeftMotorIn1, LeftMotorIn2, "Forward");
  //set_direction(RightMotorIn1, RightMotorIn2, "Forward");
  //PID(Left_IR, Right_IR, I, last_error);

  //if (Left_IR == 0 and Right_IR == 0) {
    //move_forward(175);
  //} else if (Left_IR == 1 and Right_IR == 0) {
    //turn_left(100);
  //} else if (Left_IR == 0 and Right_IR == 1) {
    //turn_right(100);
  //} else if (Left_IR == 1 and Right_IR == 1) {
    //stop_moving();
    // need to move forward and somehow orient whihc way to go as this means we have met an impass where the road splits or we are somehow the wrong way
  //}

  // Ultrasonic Sensor
  double duration, distance;
  digitalWrite(TrigWavePin, HIGH);
  delayMicroseconds(50);
  digitalWrite(TrigWavePin, LOW); //Untrigger wave
  //Calculate distance
  duration = pulseIn(EchoReceivePin, HIGH);
  distance = scalingFactor * ((duration/Convert)*SPEEDOFSOUND)/2;

  delay(0.5);
}

void PID(int Left_IR, int Right_IR, int I, int last_error) {
    int error = Left_IR - Right_IR;
    int P = error;
    I = I + error;
    int D = error - last_error;

    int correction = KP*P + KI*I + KD*D;
    int left_motor_speed = BASESPEED + correction;
    int right_motor_speed = BASESPEED - correction;

}