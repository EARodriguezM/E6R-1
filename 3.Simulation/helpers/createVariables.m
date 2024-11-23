%% load positions

    jointAnglesHome=[0;0;0;0;0;0];
    
    jointAnglesRetract=[0;0;0;0;0;0];
    
    % toolOrientationHome=[2.80,72.393,19.194];
    toolOrientationHome=[0,0,0];
        
    % toolPositionHome=[0.041,0.72393,0.184942];
    toolPositionHome=[0.062667,0,0.427513];

%% Common parameters
    load eour6dof.mat
    eeName = 'link_7_export2';
    numJoints = numel(eour6dof.homeConfiguration);
    ikInitGuess = [eour6dof.homeConfiguration.JointPosition];

%% Points

    % Maximum number of waypoints
    maxWaypoints = 20;
    
    % Positions (X Y Z)
    % waypoints = [ 0.5 0.1 0.2 ; -0.3 0.2 0.4]';
    waypoints = [0.01 0.1 0.2 ; 
        -0.1 0.2 0.1; 
        -0.2 0.3 0.2; 
        0.2 0.2 0; 
        0.2 0.1 0.3; 
        0.01 0.1 0.2]';
         
    % Euler Angles (Z Y X) relative to the home orientation       
    orientations = [0     0    0;
                    pi/8  0    0;
                    0     0    0;
                    0     0    0;
                    0     0    0;
                    0     0    0]';   
            
    % Array of waypoint times
    waypointTimes = 0:4:20;
    % waypointTimes = 0:4:4;

    % Trajectory sample time
    ts = 0.2;
    trajTimes = 0:ts:waypointTimes(end);

%% Boundary conditions (for polynomial trajectories)
    % Velocity (cubic and quintic)
    waypointVels = 0.1 *[ 0  1  0;
                         -1  0  0;
                          0 -1  0;
                          0  0  -1;
                          0  0  0;
                          0  0  0]';
    
    % Acceleration (quintic only)
    waypointAccels = zeros(size(waypointVels));
    
    % Acceleration times (trapezoidal only)
    waypointAccelTimes = diff(waypointTimes)/4;
