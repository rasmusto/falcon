% Pitch Tilt Yaw correction
% State = (roll pitch yaw xacc yacc zacc). We only observe (xacc yacc zacc)
% dirrectly

% X(t+1) = F X(t) + noise(Q)
% Y(t) = H X(t) + noise(R)

ss = 6; % state size
os = 6; % observation size
F = [1 0 0 0 0 0;
     0 1 0 0 0 0; 
     0 0 1 0 0 0; 
     0 0 0 1 0 0;
     0 0 0 0 1 0;
     0 0 0 0 0 1];
 
H = [1 0 0 0 0 0;
     0 1 0 0 0 0;
     0 0 1 0 0 0;
     0 0 0 1 0 0;
     0 0 0 0 1 0;
     0 0 0 0 0 1];
 
Q = 0.01*eye(ss);
R = 3*eye(os);
initx = [0 0 0 0 0 0]';
initV = 10*eye(ss);

T = size(data, 1);
y = data';

[xfilt, Vfilt, VVfilt, loglik] = kalman_filter(y, F, H, Q, R, initx, initV);
[xsmooth, Vsmooth] = kalman_smoother(y, F, H, Q, R, initx, initV);


%figure(1)
%clf
hold on
plot(y(1,:), 'go')
plot(xfilt(1,:), 'bs-')
plot(xsmooth(1,:), 'k^-')
%axis square;
grid on;
hold off;
legend('observed', 'kalman', 'smoothed', 3)
xlabel('x')
ylabel('y')
zlabel('z')
