%% load positions

    jointAnglesHome=[90;90;90;90;90;90];
    
    jointAnglesRetract=[0;180;180;90;90;90];
    
    % toolOrientationHome=[2.80,72.393,19.194];
    toolOrientationHome=[0.0895 0 0.467513];
        
    % toolPositionHome=[0.041,0.72393,0.184942];
    toolPositionHome=[0.0895 0 0.467513];

    robot.a2 = 165.6;
    robot.a3 = 165.6;
    robot.d4 = 53.3;
    robot.d5 = 53.3;

    robot_measure = [ robot.a2; robot.a3; robot.d4; robot.d5];

    gst0 = [1 0 0 robot.d4;
        0 1 0 0;
        0 0 1 robot.a2 + robot.a3 + robot.d5;
        0 0 0 1];

%% Common parameters
    load eour6dof.mat
    eeName = 'link_7_export2';
    numJoints = numel(eour6dof.homeConfiguration);
    ikInitGuess = [eour6dof.homeConfiguration.JointPosition];
    % ikInitGuess = jointAnglesHome;

%% Points

    % Maximum number of waypoints
    maxWaypoints = 20;
    
    % Positions (X Y Z)
    % waypoints = [ 0.5 0.1 0.2 ; -0.3 0.2 0.4]';
    % waypoints = [0.0895 0.1 0.40;
    %             0.0895 0.05 0.40;
    %             0.0895 0    0.40;
    %             0.0895 -0.1 0.40; 
    %             0.0895 -0.1 0.3; 
    %             0.0895 -0.1 0.3;
    %             0.0895 0.1 0.3]';
        waypoints = [0.1 0.2 0.40;
                0.2 -0.1 0.40; 
                0.1 -0.1 0.3; 
                0.0895 0.1 0.3;
                0.2 -0.1 0.4;
                0.1 -0.1 0.3;
                0.0895 0.1 0.3]';
         
    % Euler Angles (Z Y X) relative to the home orientation       
    orientations = [0     0    0;
                    0     0    0;
                    0     0    0;
                    0     0    0;
                    0     0    0;
                    0     0    pi/2;
                    0     0    0]';   
            
    % Array of waypoint times
    waypointTimes = 0:6:36;
    % waypointTimes = 0:4:4;

    % Trajectory sample time
    ts = 0.5;
    trajTimes = 0:ts:waypointTimes(end);

%% Boundary conditions (for polynomial trajectories)
    % Velocity (cubic and quintic)
    waypointVels = 0.1 *[ 0  1  0;
                         -1  0  0;
                          0 -1  0;
                          0  0  -1;
                          0  0  0;
                          0  0  0;
                          0  0  0]';
    
    % Acceleration (quintic only)
    waypointAccels = zeros(size(waypointVels));
    
    % Acceleration times (trapezoidal only)
    waypointAccelTimes = diff(waypointTimes)/4;
