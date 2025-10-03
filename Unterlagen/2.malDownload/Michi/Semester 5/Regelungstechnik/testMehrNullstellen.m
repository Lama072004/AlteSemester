% 2.)
% Root Locus diagramm
% Create tf with Kr = 1
clear
s = tf('s');
G = 10*(s+10)/(s*(s+1));

PD1 = (s + 1); % PD controller, Kp = 1, Kd = 1
PD10 = (s + 10); % PD controller, Kp = 1, Kd = 0.1

Gpd1 = G * PD1;
Gpd10 = G * PD10;

figure(1)

subplot(1, 3, 1)
rlocus(G)
title('Root Locus Plot with P Controller')

subplot(1, 3, 2)
rlocus(Gpd1)
title('Root Locus Plot with PD Controller, eliminating s+1 pole')

subplot(1, 3, 3)
rlocus(Gpd10)
title('Root Locus Plot with PD Controller, eliminating s+10 pole')