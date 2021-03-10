#include <Servo.h>

//User configuration:
int percent = 0;  //between -100 and 100, indicates how fast the motor 
      //will be moving when the arduino boots
int pins[] = {5}; //the signal output pins (as many as you'd like)


const int arraySize = sizeof(pins)/sizeof(int);
Servo controllers[arraySize];

//Joystick Pins
    int x_key = A0;                                               
    int y_key = A1;                                               
    int x_pos;
    int y_pos;
    //Motor Pins
    int IN = 5;      //Enable pin for second motor
    //Initializing variables to store data
    int motor_speed;

    
void setup ( ) {
  Serial.begin(9600);
 // Serial.println("you called, my guy?\n");
  for (int i=0; i<arraySize; i++)
    controllers[i].attach(pins[i]); //associate the object to a pin
  delay(1000);
  
    pinMode(IN, OUTPUT);
      //Initializng the joystick pins as input
      pinMode (x_key, INPUT) ;                     
      pinMode (y_key, INPUT) ;
  
 // Serial.println("type in a percent, and I will output your PWM.\n");
  
}


void loop() {
        Serial.println(analogRead(x_key));
        x_pos = analogRead (x_key) ;
        x_pos = digitalRead (x_key) ;
  
  
  int PWMvalue = percent * 5 + 1500; //scale up to 1000-2000

  for (int i=0; i<arraySize; i++)
    controllers[i].writeMicroseconds(PWMvalue);

//  if (Serial.available() > 1) {
//    long proposedValue = Serial.parseInt();
//    if (proposedValue == 0) {
//      Serial.println("ah... stop!  yes, right on it.");
//      percent = 0;
//    } else if (proposedValue >= -100 && proposedValue <= 100) {
//      percent = proposedValue;

      
    if (x_pos < 400){     //Rotating the left motor in clockwise direction
       percent=30;
       analogWrite(IN, 127);
       digitalWrite(IN, HIGH);
      }
    else if (x_pos > 400 && x_pos <600){  //Motors will not move when the joystick will be at center
        percent=0;
        digitalWrite(IN, LOW);
      }
      
    else if (x_pos > 600){    //Rotating the left motor in anticlockwise direction
        percent=60;
        analogWrite(IN,255);
        digitalWrite(IN, HIGH);
        }
    }
  
