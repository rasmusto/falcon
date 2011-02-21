% Load the position vector
load position.mat
N=100;
% Get the first N vectors in the position matrix to
% use as an example input
z = position(1:2,1:N);
% Specify the upper bounds of the variable-size input z 
% using the emlcoder.egs declaration - the upper bound
% for the first dimension is 2; the upper bound for 
% the second dimension is N
eg_z = emlcoder.egs(z, [2 N], [0 1]);
% Create a Real-Time Workshop configuration object
% and set the GenerateReport and LaunchReport options
% to true to generate and open a compilation report.
% Default configuration object is for a GRT target.
rtwcfg=emlcoder.RTWConfig;
rtwcfg.GenerateReport=true;
rtwcfg.LaunchReport=true;
% Generate C code only 
% specify upper bounds for variable-size input z
% Use the Real-Time Workshop configuration object
% with the -s option
emlc -c -T RTW -s rtwcfg kalman03.m -eg {eg_z}