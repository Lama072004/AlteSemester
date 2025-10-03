%% Plots in MATLAB


MinX = 3 ;
MinY = 5 ;
x = -MinX:1e-3:MinX; % Create x - values

axis([ -MinX MinX -MinY MinY]);
cla;
grid on ;
line([-MinX MinX], [0 0], 'Color', 'k');
line([0 0], [-MinY MinY], 'Color', 'k');
hold on;

for k = 0:2:10
    plot(x, x.^k, 'b');
    plot(x(x>0), x(x>0).^(k+0.5), 'c--');
end
for k = 1:2:10
    plot(x, x.^k, 'g');
    plot(x(x>0), x(x>0).^(k+0.5), 'r--');
end



hold off;
