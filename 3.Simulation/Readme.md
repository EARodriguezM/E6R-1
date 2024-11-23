# Simulation

## skew matriz
Example of Use.
syms a2;
syms a3;
% Define the twist for a revolute joint about the Z-axis
omega = [1; 0; 0];    % Rotation axis (Z-axis)
r = [0; 0; a2+a3];
v = 1 * cross(r,omega)        % Translation component
xi = [omega; v];      % Combine into twist

q = -0.9961; % Joint angle in radians

% Compute the transformation matrix
T = computeExponential(xi, q);

## Forward kinematic
Example of Use.
% Measures in mm
robot.a2 = 427;
robot.a3 = 328.5;
robot.d4 = 116.5;
robot.d5 = 116.5;


% Define initial configuration of end-effector
gst0 = [1 0 0 robot.d4;
    0 1 0 0;
    0 0 1 robot.a2 + robot.a3 + robot.d5;
    0 0 0 1];


% angles in deg
angles = [60 30 -50 150 20 -100];

gst_theta = forwardKinematic(robot,angles);
disp(gst_theta)


## Inverse kinematic
Example of Use.
% Measures in mm
robot.a2 = 427;
robot.a3 = 328.5;
robot.d4 = 116.5;
robot.d5 = 116.5;

% Define initial configuration of end-effector
gst0 = [1 0 0 robot.d4;
        0 1 0 0;
        0 0 1 robot.a2 + robot.a3 + robot.d5;
        0 0 0 1];

% final configuration of the end efector
gst_theta = [0.66 -0.71 0.23 223.13;
              0.70  0.48 -0.52 5.70;
              0.26  0.51  0.82 603.6;
              0    0    0    1];

solutions = inverseKinematic(robot, gst0, gst_theta);
disp(rad2deg(solutions))