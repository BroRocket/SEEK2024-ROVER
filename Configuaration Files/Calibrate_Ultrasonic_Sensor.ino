#define TrigWavePin 13
#define EchoReceivePin 12
#define KnownDistance 10 // Note this is in meters
long scalingFactor = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);

  // Set up ultrasonic distance sensor
  pinMode(TrigWavePin, OUTPUT); // Sets pin 13 to output to trigger ultrasonic pulse
  pinMode(EchoReceivePin, INPUT); // Receives echo from sensor

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(TrigWavePin, LOW);
  delayMicroseconds(2);

  // Trigger Wave
  digitalWrite(TrigWavePin, HIGH);
  delayMicroseconds(50);
  digitalWrite(TrigWavePin, LOW); //Untrigger wave

  //Calculate distance
  duration = pulseIn(EchoReceivePin, HIGH);
  if (scalingFactor == NULL) {
    distance = (duration * 340)/2;
    scalingFactor = KnownDistance/distance;
  } else {
    distance = scalingFactor * duration;
    scalingFactor = KnownDistance/distance;
  }

  Serial.println("Measured Distance:");
  Serial.print(distance);
  Serial.println("Scaling Factor:");
  Serial.print(scalingFactor);

  delay(1000);

}

