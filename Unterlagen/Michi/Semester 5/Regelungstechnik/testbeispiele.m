% RT Test 18
% Author: Michael Geuze
% Date: 28.11.2023
% 1.)
% Is the following system fully controllable?

A = [-1  0 
      0 -2];
b = [1; 1;];
C = [1  1];
sys = ss(A,b,C, 0);

isControllable = det(ctrb(sys));

if isControllable == 0
    disp('System is not controllable');
else
    disp('System is controllable');
end

% 2.)
% Root Locus diagramm
% Create tf with Kr = 1
clear

%%%%
% Plot options
%%%%

x_range = [-15, 5]; % Define the desired range for x-axis
y_range = [-20, 20]; % Define the desired range for y-axis

%%% END

s = tf('s');
G = 10/(s*(s+1)*(s+10));

PD1 = (s + 1); % PD controller, Kp = 1, Kd = 1
PD10 = (s + 10); % PD controller, Kp = 1, Kd = 0.1

Gpd1 = G * PD1;
Gpd10 = G * PD10;

figure(1)

subplot(1, 3, 1)
rlocus(G)
title('Root Locus Plot with P Controller')
axis([x_range y_range])

subplot(1, 3, 2)
rlocus(Gpd1)
title('Root Locus Plot with PD Controller, eliminating s+1 pole')
axis([x_range y_range])

subplot(1, 3, 3)
rlocus(Gpd10)
title('Root Locus Plot with PD Controller, eliminating s+10 pole')
axis([x_range y_range])

% Calculation of Kr


% 4.)
% 
% 
G = 10*(s+4)/(s+1)/(s+2)/(s+5);
Gclosed = G/(1+G);

figure(2)
step(Gclosed)
title('Step response for the closed loop tf')

                            % Calculate steady-state error manually
t = 0:0.01:100;             % Time values for srmulation
[y, t] = step(Gclosed, t);
ssAmplitude = y(end);        % Steady-state amplitude for a unit step input
ssError = 1 - ssAmplitude;   % Steady-state error for a unit step input

% Display steady-state error on the plot
text(1, 0.7, sprintf('Steady-State Error = %.4f', ssError), 'VerticalAlignment', 'middle');
