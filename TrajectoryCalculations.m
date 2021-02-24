format compact 
format long
clc; clear;
close all

%{This program is used to estimate the proper initial velocity of the 
% projectile of the robot}%

n = 10*10^6;    % Variable Declaration
time = zeros(1,n);
theta = 30;
dt = 0.001;
drag = .507;
rho = 1.29;
mass = 0.0577;
gravity = 9.8;
radius = 0.06858;
area = pi*radius^2;
initialVelocity = 60;

xPosition = zeros(1,n); % setting up arrays
yPosition = zeros(1,n);
magnitudeVelocity = zeros(1,n);
xVelocity = zeros(1,n);
yVelocity = zeros(1,n);
xaccleration = zeros(1,n);
yaccleration = zeros(1,n);

xPosition(1) = 0; % initial conditions for arrays
yPosition(1) = 0;
xVelocity(1) = initialVelocity*cos(deg2rad(theta));
yVelocity(1) = initialVelocity*sin(deg2rad(theta));
magnitudeVelocity(1) = initialVelocity;
xaccleration(1) = - ((drag*area*rho*(magnitudeVelocity(1))*xVelocity(1))/(2*mass));
yaccleration(1) = -gravity - ((drag*area*rho*(magnitudeVelocity(1))*yVelocity(1))/(2*mass));

for i=3:n+1  %for loop to fill in arrays
    time(i-1)=(i-1)*dt;
    
    magnitudeVelocity(i-1) = sqrt((xVelocity(i-2))^2+(yVelocity(i-2))^2);
    yaccleration(i-1) = -gravity - ((drag*area*rho*(magnitudeVelocity(i-2))*yVelocity(i-2))/(2*mass));
    xaccleration(i-1) = - ((drag*area*rho*(magnitudeVelocity(i-2))*xVelocity(i-2))/(2*mass));
    
    yVelocity(i-1) = (yVelocity(i-2))+yaccleration(i-2)*dt;
    xVelocity(i-1) = (xVelocity(i-2))+xaccleration(i-2)*dt;
    
    yPosition(i-1) = (yPosition(i-2))+yVelocity(i-1)*dt;
    xPosition(i-1) = (xPosition(i-2))+xVelocity(i-1)*dt;
end           
   %{ and used to determine maximum and minimum values. once the value is found
   % the index is then recorded for further use%}
    Z = 0.01; 
    [~,idx] = min(abs(Z-yPosition));
    [~,idy] = max(yPosition);
    maxXDistance = xPosition(idx);
    maxYDistance = yPosition(idy);
    
    finalVelocity = magnitudeVelocity(idx);
   %graph of the trajectory marked with max distance and height
    Trajectory = figure('Name','Trajectory'); 
       plot(xPosition,yPosition, '-s','MarkerIndices',[idx idy],...
       'MarkerFaceColor','red', 'MarkerSize',7.5)
       %used for marking the positions of max range and distace on the graph 
       stx = string (maxXDistance);
       sty = string (maxYDistance);
       x = strcat('range = ',stx, ' m');
       y = strcat('height = ',sty, ' m');
       text(18,8.125,y,'HorizontalAlignment','left')
       text(17,.75,x,'HorizontalAlignment','left')

       title('Trajectory')
       xlabel('X Position (m)')
       ylabel('Y Position (m)')
       xlim([0 30])
       ylim([0 10])
              
   fprintf('Maximum X Distance = %f\n', maxXDistance);
   fprintf('Maximum Y Distance = %f\n', maxYDistance);
   fprintf('Final Velocity = %f\n', finalVelocity);
