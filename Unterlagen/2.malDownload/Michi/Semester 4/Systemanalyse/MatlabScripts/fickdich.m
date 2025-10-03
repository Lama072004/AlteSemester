%A. Engler, Vorlesung FHV, 30.04.2016
%Definition Leistungsimpedanz und Stromberechnung
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Leitungsimpedanz R / L
ZL1R=0.2		% [Ohm] R_Leitung_1
ZL2R=0.2		% [Ohm] R_Leitung_2
ZL3R=0.2		% [Ohm] R_Leitung_3
ZL1L=0.0016	% [H] L_Leitung_1
ZL2L=0.0016	% [H] L_Leitung_2
ZL3L=0.0016	% [H] L_Leitung_3

dt=TEND/SAMPLES	% Integrationsintervall
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Berechnung Strom Leitung 1
iL1(1)=0;		% Initialisation
for n=2 : SAMPLES
   iL1(n)=iL1(n-1)+(delta_u1(n)-ZL1R*iL1(n-1))/ZL1L*dt;	% int(delta_u - uR)*dt/L
   iL1(n)=iL1(n-1)+(2*delta_u1(n)-ZL1R*(iL1(n-1)+iL1(n)))/2/ZL1L*dt;
end
% Berechnung Strom Leitung 2
iL2(1)=0;		% Initialisation
for n=2 : SAMPLES
   iL2(n)=iL2(n-1)+(delta_u2(n)-ZL2R*iL2(n-1))/ZL2L*dt;	% int(delta_u - uR)*dt/L
   iL2(n)=iL2(n-1)+(2*delta_u2(n)-ZL2R*(iL2(n-1)+iL2(n)))/2/ZL2L*dt;
end
% Berechnung Strom Leitung 3
iL3(1)=0;		% Initialisation
for n=2 : SAMPLES
   iL3(n)=iL3(n-1)+(delta_u3(n)-ZL3R*iL3(n-1))/ZL3L*dt;	% int(delta_u - uR)*dt/L
   iL3(n)=iL3(n-1)+(2*delta_u3(n)-ZL3R*(iL3(n-1)+iL3(n)))/2/ZL3L*dt;
end
h4 = figure;
plot(t,iL1,t,iL2,t,iL3),title('Leitungsströme: iL 1-3')




% A. Engler, Vorlesung FHV, 30.04.2016
% Skript: erzeugt Zeit- und Spannungssystem
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Konstanten
TEND=0.4			% [s] Berechnungsdauer
SAMPLES=2000	% [1]	Anzahl der Stützstellen
F=50				% [1/s] Netzfrequenz
U1P=326			% [V] Spitzenspannung
U2P=326			% [V] Spitzenspannung
U3P=326			% [V] Spitzenspannung
OMEGA=2*pi*F	% [1/s] Kreisfrequenz Netz
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t=linspace(0,TEND,SAMPLES);		% Zeitbasis

% Spannungsquelle 1
u1=U1P*sin(OMEGA*t);
u2=U2P*sin(OMEGA*t+(2*pi/3));
u3=U3P*sin(OMEGA*t+(4*pi/3));
h1=figure;
plot(t,u1,t,u2,t,u3),title('Spannungsquelle_1: U1-3')

% Spannungsquelle 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
K1=1.05										% Änderung Spannung
K2=1.05										% Änderung Spannung
K3=1.05										% Änderung Spannung
PHI1=-0.10										% Änderung Winkel
PHI2=-0.10										% Änderung Winkel
PHI3=-0.10                                   % Änderung Winkel
u4=K1*U1P*sin(OMEGA*t+PHI1);
u5=K2*U2P*sin(OMEGA*t+(2*pi/3)+PHI2);
u6=K3*U3P*sin(OMEGA*t+(4*pi/3)+PHI3);
h2=figure;
plot(t,u1,t,u2,t,u3),title('Spannungsquelle_2: U4-6')

% Spannungsabfall über Leitungsimpedanz
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
delta_u1= u1 - u4;
delta_u2= u2 - u5;
delta_u3= u3 - u6;
h3=figure;
plot(t,delta_u1,t,delta_u2,t,delta_u3),title('Spannungsabfall Leitungsimpedanz')
%%%%%%%%%%%%%%%% EOF

Ualpha = 1/sqrt(3) * (delta_u1 - 0.5*delta_u2 - 0.5*delta_u3);
Ubeta = 1/sqrt(3) * (0 + sqrt(3)/2*delta_u2 - sqrt(3)/2*delta_u3);
Ialpha = 1/sqrt(3) * (IL1 - 0.5*IL2 - 0.5*IL3);
Ibeta = 1/sqrt(3) * (0 + sqrt(3)/2*IL2 - sqrt(3)/2*IL3);

P = 1/2.*(Ualpha.*Ialpha + Ubeta .* Ibeta);
Q = 1/2.*(Ubeta .*Ialpha + Ualpha .* Ibeta);
h3=figure;
plot(t,P,"r",t,Q,"b"),title('Leistungsberechnung')

%%%%% EOF