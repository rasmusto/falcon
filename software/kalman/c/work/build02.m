% Load the position vector
load position.mat
% Get the first vector in the position matrix 
% to use as an example input
z = position(1:2,1);
% Generate C code only, create a compilation report
emlc -c -T RTW -report kalman02.m -eg {z}