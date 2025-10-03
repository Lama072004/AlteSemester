%% Aufgabe 3: Ein ansonsten idealer OPV... 
V0 = 100;
w0 = 10;
k = 1/10;
s = tf('s');

K0 = 10^(V0/20); % Get rid of log scaling
Gopv = K0/(1 + s/w0);

Gr = Gopv/(1 + k * Gopv);

figure;
margin(Gopv);
hold on;
margin(Gr);
legend('Gopv', 'Gr');
title('Bode Comparison of Gopv and Gr');
hold off;

% Get cut off frequency
w_c_Gr = bandwidth(Gr);

fprintf('Cutoff frequency of Gr: %.2f\n', w_c_Gr);



