// Set constan variables
#define TrigPinLeft 13
#define EchoPinLeft 12
#define TrigPinRight 11
#define EchoPinRight 10
#define IR 2
#define LeftMotorEnable 9
#define LeftMotorIn1 8
#define LeftMotorIn2 7
#define RightMotorEnable 6
#define RightMotorIn1 5
#define RightMotorIn2 4
#define KP 1
#define KI 1
#define KD 1
#define TrigWavePin 13
#define EchoReceivePin 12
double BASESPEED = 125
double ScalingFactorLeft = 1.13;
double ScalingFactorRight = 1.09;
double Convert = 1000000.0;
double SPEEDOFSOUND = 331;
double durationLeft, distanceLeft, durationRight, distanceRight;
double I = 0;
double last_error = 0;

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
  Serial.begin (9600);
  // Set up ultrasonic distance sensors
  pinMode(TrigPinLeft, OUTPUT); // Sets pin 13 to output to trigger ultrasonic pulse
  pinMode(EchoPinLeft, INPUT); // Receives echo from sensor
  pinMode(TrigPinRight, OUTPUT);
  pinMode(EchoPinRight, INPUT);

  //Set up IR Sensors
  pinMode(IR, INPUT);

  //Set up motor pins
  pinMode(LeftMotorEnable, OUTPUT);
  pinMode(LeftMotorIn1, OUTPUT);
  pinMode(LeftMotorIn2, OUTPUT);
  pinMode(RightMotorEnable, OUTPUT);
  pinMode(RightMotorIn1, OUTPUT);
  pinMode(RightMotorIn2, OUTPUT);
}

void loop () {
    set_direction(RightMotorIn1, RightMotorIn2, "Forward");
    set_direction(LeftMotorIn1, LeftMotorIn2, "Forward");
    move_forward(150);
    delay(1);
}

void control() {
  // Ultrasonic Sensor
  digitalWrite(TrigPinLeft, HIGH);
  digitalWrite(TrigPinRight, HIGH);
  delayMicroseconds(50);
  digitalWrite(TrigPinLeft, LOW);
  digitalWrite(TrigPinRight, LOW); //Untrigger wave
  //Calculate distance
  durationLeft = pulseIn(EchoPinLeft, HIGH);
  durationRight = pulseIn(EchoPinRight, HIGH);
  distanceLeft = ScalingFactorLeft * ((durationLeft/Convert)*SPEEDOFSOUND)/2;
  distanceRight =  ScalingFactorRight * ((durationRight/Convert)*SPEEDOFSOUND)/2;

  set_direction(LeftMotorIn1, LeftMotorIn2, "Forward");
  set_direction(RightMotorIn1, RightMotorIn2, "Forward");
  PID(distanceLeft, distanceRight, I, last_error);
  
  delay(1);
}

void PID(int LeftWallDist, int RightWallDist, int I, int last_error) {
    double error, P, D, correction, left_motor_speed, right_motor_speed;
    error = LeftWallDist - RightWallDist;
    P = error;
    I = I + error;
    D = error - last_error;

    correction = KP*P + KI*I + KD*D;
    left_motor_speed = max(0, min(255, (BASESPEED - correction)));
    right_motor_speed = max(0, min(255, (BASESPEED + correction)));
    analogWrite(LeftMotorEnable, left_motor_speed);
    analogWrite(RightMotorEnable, right_motor_speed);

    last_error = error;
}