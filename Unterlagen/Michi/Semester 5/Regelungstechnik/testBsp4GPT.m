clear
s = tf('s');
G = 10*(s+4)/(s+1)/(s+2)/(s+5);

Gclosed = G/(1+G);

figure(2)
step(Gclosed)
title('Step response for the closed loop tf')

% Calculate steady-state error manually
t = 0:0.01:100; % Time values for simulation
[y, t] = step(Gclosed, t);
steadyStateError = 1 - y(end); % Steady-state error for a unit step input

% Find the time index corresponding to the final value
finalTimeIndex = find(t >= max(t), 1);

% Display steady-state error on the plot
text(t(finalTimeIndex) * 0.9, y(end) * 0.9, sprintf('Steady-State Error: %.4f', steadyStateError), 'HorizontalAlignment', 'right', 'FontSize', 10, 'FontWeight', 'bold', 'BackgroundColor', 'white');
