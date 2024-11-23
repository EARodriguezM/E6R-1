% Trajectory Planning of Robot Manipulators with MATLAB and Simulink
% Startup script
%

clear, clc, close all;
disp('Starting Robot Manipulator Trajectory...')

% Set up the MATLAB search path
rootDir = fileparts(which(mfilename));
addpath(genpath('meshes'), genpath('helpers'), genpath('kinematics'));

% Set the code generation and cache folders to a work folder
% If the folder does not exist, create it
if ~isfolder('work')
    mkdir('work');
end
Simulink.fileGenControl('set','CacheFolder','work','CodeGenFolder','work');