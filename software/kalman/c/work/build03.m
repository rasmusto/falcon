% Load the position vector
load position.mat
% Get the first 5 vectors in the position matrix to use as an example input
z = position(1:2,1:5);
% Generate C code only, create a compilation report
emlc -c -T RTW -report kalman03.m -eg {z}