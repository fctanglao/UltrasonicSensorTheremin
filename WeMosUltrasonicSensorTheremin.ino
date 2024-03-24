// variables
int ledPin = 16; // pin assignment for the LED
int trigPin = 14; // pin assignment for the trigger
int echoPin = 12; // pin assignment for the echo
int speakerPin = 0; // pin assignment for the speaker
long duration;
int distance;
int pitch;

 
void setup() {
  // initializing the serial monitor
  Serial.begin (9600);
  
  // defining the inputs and outputs
  pinMode(trigPin, OUTPUT); // sends ultrasonic sound pulses
  pinMode(echoPin, INPUT); // receives transmitted signal
  pinMode(ledPin, OUTPUT); // visualizes pitch of the speaker
}
 
void loop() {
  // setting up the trigger to omit ultrasonic sound pulses
  // we give a LOW pulse first to ensure that we give a clean HIGH pulse afterwards
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5); // omits the LOW pulse for 5 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // omits the HIGH pulse for 10 microseconds
  digitalWrite(trigPin, LOW);
 
  // setting up echo to read the HIGH transmitted signal 
  duration = pulseIn(echoPin, HIGH); // returns the length of the pulse off an object in microseconds
  distance = (duration/2) / 29; // converts the length from time to distance (ms to cm); the formula used was found from banana robotics
  // mapping the distance from the device to the distance between A3 and C5
  // trying to make the speaker replicate a mezzo-soprano voice
  pitch = constrain(map(distance, 1, 40, 256, 523), 220, 523); // constrain() constrains a number to be within range; map() re-maps a number from one range to another; 1-40 is the initial pitch; 256-523 is the target pitch; 220-523 is the constraint
  
  // playing the pitch
  tone(speakerPin, pitch); // tone() generates a square wave of the specified pitch; tones can't be any lower than 31 Hz

  // visualizes the pitch using the same mapping;
  analogWrite(ledPin, map(pitch, 256, 523, 0, 255)); // analogWrite() writes a PWM wave to the pin; 256-523 is the current pitch; 0-255 is the target brightness
  
  // prints the pitch in the serial monitor
  Serial.println(pitch); // the monitor currently outputs symbols and letters. this is a work in progress and may be a board issue
  
  // pauses the program for 100 milliseconds before looping again
  delay(100);
}
