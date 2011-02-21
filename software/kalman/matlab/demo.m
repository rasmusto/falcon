% Pitch Tilt Yaw correction
% State = (roll pitch yaw xacc yacc zacc). We only observe (xacc yacc zacc)

% X(t+1) = F X(t) + noise(Q)
% Y(t) = H X(t) + noise(R)

ss = 6; % state size
os = 3; % observation size
F = [.9 0 .8 0 1 0;
     0 1 0 1 0 1; 
     0 0 1 0 1 0; 
     0 0 0 1 0 1;
     0 0 0 0 1 0;
     0 0 0 0 0 1];
 
H = [1 0 0 0 0 0;
     0 1 0 0 0 0;
     0 0 1 0 0 0];
 
Q = 0.01*eye(ss);
R = 3*eye(os);
initx = [10 2 5 0 0 0]';
initV = 10*eye(ss);

T = 40;
[x,y] = sample_lds(F, H, Q, R, initx, T);

[xfilt, Vfilt, VVfilt, loglik] = kalman_filter(y, F, H, Q, R, initx, initV);
[xsmooth, Vsmooth] = kalman_smoother(y, F, H, Q, R, initx, initV);

dnone = x([1 2 3],:) - y([1 2 3],:);
mse = sqrt(sum(sum(dnone.^2)))

dfilt = x([1 2 3],:) - xfilt([1 2 3],:);
mse_filt = sqrt(sum(sum(dfilt.^2)))
%xfilt

dsmooth = x([1 2],:) - xsmooth([1 2],:);
mse_smooth = sqrt(sum(sum(dsmooth.^2)))
%xsmooth

%figure(1)
%clf
hold on
plot3(x(1,:), x(2,:), x(3,:), 'rs-')
plot3(y(1,:), y(2,:), y(3,:), 'go')
plot3(xfilt(1,:), xfilt(2,:), xfilt(3,:), 'bs-')
plot3(xsmooth(1,:), xsmooth(2,:), xsmooth(3,:), 'k^-')
%axis square;
grid on;
hold off;
legend('true', 'observed', 'filtered', 3)
xlabel('x')
ylabel('y')
zlabel('z')
