#include <Servo.h>

int pins[] = {5}; //the signal output pins (as many as you'd like)

int percent = 0;  //between -100 and 100, indicates how fast the motor 

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
      Serial.begin (9600); //Starting the serial communication at 9600 baud rate
      //Initializing the motor pins as output
      pinMode(IN, OUTPUT);
      //Initializng the joystick pins as input
      pinMode (x_key, INPUT) ;                     
      pinMode (y_key, INPUT) ;               
    }
    void loop () {      
      Serial.println(analogRead(x_key));
        x_pos = analogRead (x_key) ;  //Reading the horizontal movement value

  int PWMvalue = 1000; //scale up to 1000-2000

  for (int i=0; i<arraySize; i++)
    controllers[i].writeMicroseconds(PWMvalue);

    int proposedValue = x_pos;
  }
  /*
    if (x_pos < 400){     //Rotating the left motor in clockwise direction
        motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
        digitalWrite(IN, HIGH);
        //digitalWrite(IN2, HIGH);
        analogWrite(IN, motor_speed);
      }
    else if (x_pos > 400 && x_pos <600){  //Motors will not move when the joystick will be at center
        digitalWrite(IN, LOW);
        //digitalWrite(IN2, LOW);
      }
      
    else if (x_pos > 600){    //Rotating the left motor in anticlockwise direction
        motor_speed = map(x_pos, 600, 1023, 0, 255);
        digitalWrite(IN, HIGH);
        //digitalWrite(IN2, LOW);
        analogWrite(IN, motor_speed);
      }*/
