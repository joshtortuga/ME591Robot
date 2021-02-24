format compact 
format long
clc; clear;
close all

%{
This program is used to estimate the proper gear ratio of the shooter
flywheel to launch the projectile at the velocity calculated in the
trajectory program
%}

FlyWheelRadius = .0508;
ProjectileVelocity = 60;

WheelAngularVelocity = (ProjectileVelocity/(FlyWheelRadius))*9.549297;
%result in rpm
fprintf('WheelAngularVelocity = %.7f\n',WheelAngularVelocity)

%CIM motor free speed =  5,330 rpm; stall torque = 2.41 N-m (21.33 in-lb)
MotorFreeSpeed = 5330;
ThreeQuarterSpeed = MotorFreeSpeed*.75;
HalfSpeed = MotorFreeSpeed*.5;
QuarterSpeed = MotorFreeSpeed*.25;

%1st layer - connected to motor
LargeGearTeeth = 50;
SmallGearTeeth = 18;

SmallGear1AngularVelocity = (LargeGearTeeth/SmallGearTeeth)*QuarterSpeed;
%fprintf('SmallGear1AngularVelocity = %.7f\n',SmallGear1AngularVelocity);

%Second layer - connected to flywheel
LargeGearTeeth2 = 38;
SmallGearTeeth2 = 18;

SmallGear2AngularVelocity = (LargeGearTeeth2/SmallGearTeeth2)*SmallGear1AngularVelocity;
fprintf('SmallGear2AngularVelocity = %.7f\n',SmallGear2AngularVelocity)
