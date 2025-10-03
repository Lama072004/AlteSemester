Kr = 2.45
K0 = 10
% let Td = 1
s = tf('s')
G = K0*Kr/s/(s+10)
Gclosed = G/(1+G)
figure(1)
subplot(1, 3, 1)
pzmap(Gclosed)

subplot(1, 3, 2)
