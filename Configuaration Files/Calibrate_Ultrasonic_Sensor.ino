#define TrigWavePin 13
#define EchoReceivePin 12
double KnownDistance = 23.7; // Note this is in meters
double Convert = 1000000.0;
double SPEEDOFSOUND = 331;
double scalingFactor = 1.13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);

  // Set up ultrasonic distance sensor
  pinMode(TrigWavePin, OUTPUT); // Sets pin 13 to output to trigger ultrasonic pulse
  pinMode(EchoReceivePin, INPUT); // Receives echo from sensor

}

void loop() {
  // put your main code here, to run repeatedly:
  double duration, distance;
  digitalWrite(TrigWavePin, LOW);
  delayMicroseconds(2);

  // Trigger Wave
  digitalWrite(TrigWavePin, HIGH);
  delayMicroseconds(50);
  digitalWrite(TrigWavePin, LOW); //Untrigger wave

  //Calculate distance
  duration = pulseIn(EchoReceivePin, HIGH);
  distance = scalingFactor * ((duration/Convert)*SPEEDOFSOUND)/2;
  //scalingFactor = KnownDistance/distance;
  
  Serial.println("Measured Distance:");
  Serial.print(distance);
  Serial.println();

  delay(5000);

}

