#include <Servo.h>  
#include <PS2X_lib.h>
 
Servo motorA;
Servo motorB;
Servo motorC;
Servo motorD;
PS2X ps2x; 

//right now, the library does NOT support hot-pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
//Motor Pins
int IN = 5;      //Enable pin for second motor
//Initializing variables to store data
int PWMvalue = 1500;

void setup(){
Serial.begin(57600);

motorA.attach(3); //associate the object to a pin
motorB.attach(5);
motorC.attach(6);
motorD.attach(9);

pinMode(IN, OUTPUT);

error = ps2x.config_gamepad(13,11,10,12, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
if(error == 0){
 Serial.println("Found Controller, configured successful");
 Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
 Serial.println("holding L1 or R1 will print out the analog stick values.");
 Serial.println("Go to www.billporter.info for updates and to report bugs.");
}
 else if(error == 1)
  Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
 else if(error == 2)
  Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
    switch(type) {
      case 0:
       Serial.println("Unknown Controller type");
      break;
      case 1:
       Serial.println("DualShock Controller Found");
      break;
    }
}
void loop(){


//DRIVE-TRAIN
//*********************************************************************//
//IDLE
/*if(ps2x.ButtonReleased(PSB_PAD_UP))
{
  int PWMvalue = 1500;
  
  Serial.println(PWMvalue);
  motorA.writeMicroseconds(PWMvalue);
  motorB.writeMicroseconds(PWMvalue);
  motorC.writeMicroseconds(PWMvalue);
  motorD.writeMicroseconds(PWMvalue);
}*/

//FORWARD
if(ps2x.ButtonPressed(PSB_TRIANGLE))
{
  
Serial.println("Forward PWM values");
  
  int PWMvalueA = 1600;
  int PWMvalueB = 1600;
  int PWMvalueC = 1600;
  int PWMvalueD = 1600;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}

//BACKWARD
if(ps2x.Button(PSB_PAD_DOWN))
{
  Serial.println("Backward PWM values");
  int PWMvalueA = 1400;
  int PWMvalueB = 1400;
  int PWMvalueC = 1400;
  int PWMvalueD = 1400;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}

//LEFT
if(ps2x.Button(PSB_PAD_LEFT))
{
  Serial.println("Left PWM values");
  int PWMvalueA = 1400;
  int PWMvalueB = 1600;
  int PWMvalueC = 1600;
  int PWMvalueD = 1400;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}

//RIGHT
if(ps2x.Button(PSB_PAD_RIGHT))
{
  Serial.println("Right PWM values");
  int PWMvalueA = 1600;
  int PWMvalueB = 1400;
  int PWMvalueC = 1400;
  int PWMvalueD = 1600;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}

//TURN RIGHT
if(ps2x.Analog(PSS_RX) < 120)
{
  Serial.println("Turn Right PWM values");
  int PWMvalueA = 1600;
  int PWMvalueB = 1500;
  int PWMvalueC = 1600;
  int PWMvalueD = 1500;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}

//TURN LEFT
if(ps2x.Analog(PSS_RX) > 134)
{
  Serial.println("Turn Left values");
  int PWMvalueA = 1500;
  int PWMvalueB = 1600;
  int PWMvalueC = 1500;
  int PWMvalueD = 1600;

  motorA.writeMicroseconds(PWMvalueA);
  motorB.writeMicroseconds(PWMvalueB);
  motorC.writeMicroseconds(PWMvalueC);
  motorD.writeMicroseconds(PWMvalueD);
}
//***************************************************************//

/*if(ps2x.Analog(PSS_LY) == 127)
{
  int PWMvalue = 1500;
  
  Serial.println(PWMvalue);
  motorA.writeMicroseconds(PWMvalue);
}

if(ps2x.Analog(PSS_LY) < 120)
{
    int PWMvalue = 1450; //scale up to 1000-2000

    Serial.println(PWMvalue);
    motorA.writeMicroseconds(PWMvalue);
}

if(ps2x.Analog(PSS_LY) > 135)
{
    int PWMvalue = 1550; //scale up to 1000-2000

    Serial.println(PWMvalue);
    motorA.writeMicroseconds(PWMvalue);
}
*/
  
if(error == 1) 
 return; 
else { //DualShock Controller
   ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
   if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
   if(ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");
    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
      //int PWMvalue = 1550;
      //Serial.print("Up held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      while (PWMvalue <= 1650)
      {
      for(int i = 0; i < 100; i++)
      {
        PWMvalue = 1550 + i;
        //Serial.println(PWMvalue);
        motorA.writeMicroseconds(PWMvalue);
        delay(150);
      }
      motorA.writeMicroseconds(PWMvalue);
     }
     }
     if(ps2x.ButtonReleased(PSB_PAD_UP)){
      int PWMvalue = 1500;
      motorA.writeMicroseconds(PWMvalue);
     }
     if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
     }
     if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
     }
     if(ps2x.Button(PSB_PAD_DOWN)){
      //int PWMvalue = 1450;
      //Serial.print("DOWN held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      while (PWMvalue >= 1350)
      {
      for(int i = 0; i <= 100; i++)
      {
        PWMvalue = 1450 - i;
        Serial.println(PWMvalue);
        motorA.writeMicroseconds(PWMvalue);
        delay(120);
      }
     }   
     motorA.writeMicroseconds(PWMvalue);
     }
     
     if(ps2x.ButtonReleased(PSB_PAD_DOWN)){
      int PWMvalue=1500;
      motorA.writeMicroseconds(PWMvalue);
     }
          
     vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                             //how hard you press the blue (X) button    
   if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
   {   
       if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
       if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
       if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
       if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
       if(ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");
   }   
   if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
   if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
        Serial.println("Square just released");     
   if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
        Serial.println("X just changed");    
   if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
   {
       Serial.print("Stick Values:");
       Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_LX), DEC); 
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_RY), DEC); 
       Serial.print(",");
       Serial.println(ps2x.Analog(PSS_RX), DEC); 
   } 
}
delay(50);
}
