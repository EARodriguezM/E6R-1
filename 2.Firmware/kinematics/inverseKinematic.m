function solution = inverseKinematic(robot, gst0, gst_theta)
    a2 = robot(1);
    a3 = robot(2);
    d4 = robot(3);
    d5 = robot(4);
    % Joint twist vectors for each joint
    
    w1 = [0; 0; 1];    % rotation axis of the first joint
    w2 = [1; 0; 0];
    w3 = [1; 0; 0];
    w4 = [1; 0; 0];
    w5 = [0; 0; 1];
    w6 = [1; 0; 0];
    % Define the points on each joint axis (Assuming initial configuration)
    
    r1 = [0; 0; 0];    % point on the rotation axis of the first joint
    r2 = [0; 0; 0];
    r3 = [0; 0; a2];
    r4 = [0; 0; a2 + a3];
    r5 = [d4; 0; a2 + a3];
    r6 = [d4; 0; a2 + a3 + d5];
    % Define twists for each joint
    
    xi1 = [w1; cross(-w1, r1)];
    xi2 = [w2; cross(-w2, r2)];
    xi3 = [w3; cross(-w3, r3)];
    xi4 = [w4; cross(-w4, r4)];
    xi5 = [w5; cross(-w5, r5)];
    xi6 = [w6; cross(-w6, r6)];
    
    % Define R
    syms q1 q2 q3 q4 q5 q6;
    e_xi1_theta1 = computeExponential(xi1, q1);
    e_xi2_theta2 = computeExponential(xi2, q2);
    e_xi3_theta3 = computeExponential(xi3, q3);
    e_xi4_theta4 = computeExponential(xi4, q4);
    e_xi5_theta5 = computeExponential(xi5, q5);
    e_xi6_theta6 = computeExponential(xi6, q6);
    % Define initial configuration of end-effector
    %% Inverse kinematics solution steps
    % Solve for each joint angle using the Paden-Kahan subproblems and asumming 
    % 8 possible solutions for the kinematic, initialize the solution storage
    
    solutions = zeros(8, 6)
    % Step-by-step solving of joint angles
    % Solve for q1 based
    
    [p1, q1_solutions, gst1] = solve_q1(gst_theta,gst0, w1, r1, d4, a2, a3, d5);
    solutions(1:8,1) = fill_solution(q1_solutions);
    %% 
    % Obtained q1, do a loop throught possible q1 solutions and solve for other 
    % joint angles
    
    q5_solutions = zeros(length(q1_solutions),2); 
    q6_solutions = zeros(length(q5_solutions),2);
    q2_q3_q4_solutions = zeros(length(q5_solutions),2);
    
    for i = 1:length(q1_solutions)
        q1 = q1_solutions(i);
        e_xi1_theta1_eval = vpa(subs(e_xi1_theta1));
        % Step 2: Solve q5 and q6
        [q5_solutions(i,:), q6_solutions(i,:), q2_q3_q4_solutions(i,:)] = solve_q5_q6(gst_theta, w1, q1);    
    end
    
    
    q2_solutions = [];
    q3_solutions = [];
    q4_solutions = [];
    for i = 1:length(q1_solutions)
        q1 = q1_solutions(i);
        e_xi1_theta1_eval = vpa(subs(e_xi1_theta1));
        % % % Step 3: Solve q2, q3, and q4
        for j = 1:length(q5_solutions)
            q5 = q5_solutions(i,j);
            q6 = q6_solutions(i,j);
            q2_q3_q4 = q2_q3_q4_solutions(i,j);
            e_xi5_theta5_eval = vpa(subs(e_xi5_theta5));
            e_xi6_theta6_eval = vpa(subs(e_xi6_theta6));
            [q2_par, q3_par, q4_par] = solve_q234_solutions(e_xi1_theta1_eval, e_xi5_theta5_eval, e_xi6_theta6_eval, gst1, q2_q3_q4, a2, a3);
            q2_solutions =  [q2_solutions q2_par];
            q3_solutions =  [q3_solutions q3_par];
            q4_solutions =  [q4_solutions q4_par];
        end
    end
    q5_solutions = [q5_solutions(1,:) q5_solutions(2,:)].';
    q6_solutions = [q6_solutions(1,:) q6_solutions(2,:)].';
    q2_q3_q4_solutions = [q2_q3_q4_solutions(1,:) q2_q3_q4_solutions(2,:)].';
    
    q2_solutions = q2_solutions.';
    q3_solutions = q3_solutions.';
    q4_solutions = q4_solutions.';
    
    solutions(1:8,5) = fill_solution(q5_solutions);
    solutions(1:8,6) = fill_solution(q6_solutions);
    solutions(1:8,2) = fill_solution(q2_solutions);
    solutions(1:8,3) = fill_solution(q3_solutions);
    solutions(1:8,4) = fill_solution(q4_solutions);

        % Function to find the first row where all values are between -pi and pi
    
    % Iterate through each row to check the condition
    for i = 1:size(solutions, 1)
        if all(solutions(i, :) >= -pi & solutions(i, :) <= pi)
            % Return the first row that satisfies the condition
            solution = solutions(i, :);
            return;
        end
    end
    
    % If no valid row is found, return an empty array
    solution = [90 90 90 90 90 90];
end

function solutions = fill_solution(q_solutions)
    n = 8/length(q_solutions);
    
    for i = 1:length(q_solutions)
        for j = 1:n
            solutions(j+n*(i-1), 1) = q_solutions(i);
        end
    end
end
% Functions for de differents q
%% 
% * Function for all possible q1
%% 
% $$ g_{st}(\theta) g_{st}^{-1}(0) = e^{\xi_1 \theta_1}e^{\xi_2 \theta_2} e^{\xi_3 
% \theta_3} e^{\xi_4 \theta_4} e^{\xi_5 \theta_5} e^{\xi_6 \theta_6} = g_{st1}$$

function [p1, q1_solutions, gst1] = solve_q1(gst_theta, gst0, w1, r1, d4,a2,a3,d5)
    % get globals

    % Function to solve for q1 in the inverse kinematics of a 6-DOF robot
    % using Paden-Kahan Subproblem 1.

    gst1 = gst_theta * inv(gst0);

    %gst1 * p56 = p1 = (px,py,pz,1).

    %
    % Extract the desired position of the end-effector from gst_theta.
    p_target = gst_theta(1:3, 4);
    % p_1 is equal to [p_tarjet; 1]
    
    % Define twist parameters from xi1 for the first joint
    p56 = [d4; 0; a2 + a3 + d5];

    % Calculate p1 based on the relationship given in the article
    % We want to find p2 such that:
    %  (p2 - p56) x w2 = 0
    %  (p2 - r1) x w1 = 0
    %  ||p2 - r1|| = ||p1 - r1||
    
    % Compute auxiliary variables for calculating p2
    px = p_target(1);
    py = p_target(2);
    pz = p_target(3);
    
    % Calculate intermediate p2 position
    % Determine p1 (position of the end-effector after first joint rotation)
    % This is based on rotation by q1 around w1
    p1 = [px; py; pz; 1 ]; % Initialize with the target position for simplicity
    s1 = sqrt(px^2 + py^2 - d4^2);

    % Compute potential solutions for q1 using atan2 based on p_target
    q1_solutions = [atan2(-px * s1 + d4 * py, d4 * px + py * s1);
                    atan2(px * s1 + d4 * py, d4 * px - py * s1)];
end
%% 
% * Function for all possible q5 and q6

function [q5_solutions, q6_solutions, q2_q3_q4_solutions] = solve_q5_q6(gst_theta, w1, q1)
    % Function to solve for q5 and q6 in the inverse kinematics of a 6-DOF robot
    % using Paden-Kahan Subproblem.

    % Extract the desired orientation and position from gst_theta
    R_target = gst_theta(1:3, 1:3);  % Target rotation matrix
    p_target = gst_theta(1:3, 4);    % Target position vector
    
    % Update target configuration after the rotation of q1
    % gst2 = inv(e_xi1_theta1) * gst1;
    
    % Extract elements needed to solve for q5 and q6 based on gst1 matrix
    % Assuming the notation in the article, we can define:
    M1 = gst_theta(1, 1);
    M2 = gst_theta(2, 1);
    M3 = gst_theta(3, 1);
    N1 = gst_theta(1, 2);
    N2 = gst_theta(2, 2);
    N3 = gst_theta(3, 2);
    G1 = gst_theta(1, 3);
    G2 = gst_theta(2, 3);
    G3 = gst_theta(3, 3);
    H1 = gst_theta(1, 4);
    H2 = gst_theta(2, 4);
    H3 = gst_theta(3, 4);

    % Solve for q5 using the arctan function, ensuring we handle both solutions
    s2 = M1 * cos(q1) + M2 * sin(q1);
    s3 = G1 * cos(q1) + G2 * sin(q1);
    s4 = N1 * cos(q1) + N2 * sin(q1);
    s5 = M2 * cos(q1) - M1 * sin(q1);

    q5_solutions = atan2([sqrt(1 - s2^2), -sqrt(1 - s2^2)], s2);  % Two possible solutions

    % Initialize arrays to store q6 solutions for each q5
    % Solve for q6 based on q5 solutions
    q6_solutions = zeros(1,2);
    q2_q3_q4_solutions = zeros(1,2);
    for i = 1:length(q5_solutions)
        sin_q5 = sin(q5_solutions(i));
        
        % Conditions for q6 using the matrix elements
        q6_solutions(1,i) = atan2((s3) / sin_q5, -(s4) / sin_q5);
        q2_q3_q4_solutions(i) = atan2((M3/sin_q5),(s5 / sin_q5));
    end
end
%% 
% * Function for all possible q2, q3 and q4

function [q2, q3, q4] = solve_q234_solutions(e_xi1_theta1_eval, e_xi5_theta5_eval, e_xi6_theta6_eval, gst1, q2_q3_q4, a2, a3)
    
    gst2 = inv(e_xi1_theta1_eval) * gst1;
    gst3 = gst2 * inv(e_xi6_theta6_eval) * inv(e_xi5_theta5_eval);
    
    % disp(rad2deg(q5))
    % disp(rad2deg(q6))

    m1 = gst3(1, 1);
    m2 = gst3(2, 1);
    m3 = gst3(3, 1);
    n1 = gst3(1, 2);
    n2 = gst3(2, 2);
    n3 = gst3(3, 2);
    g1 = gst3(1, 3);
    g2 = gst3(2, 3);
    g3 = gst3(3, 3);
    t4 = gst3(1, 4);
    t5 = gst3(2, 4);
    t6 = gst3(3, 4);

    t7 = t5 - ((a2 + a3) * sin(q2_q3_q4));
    t8 = t6 + ((a2 + a3) * cos(q2_q3_q4));

    % Calculate A, B, C terms for solving q2 and q2 + q3
    A = 2 * a2 * t7;
    B = 2 * a2 * t8;
    C = a3^2 - a2^2 - t7^2 - t8^2;

    % disp(sqrt(A^2 + B^2 - C^2))
    % Solve for q2
    % q2 = atan2(B, A) + atan2(C, sqrt(A^2 + B^2 - C^2));
    q2 = atan2(B, A) + atan2(C, [sqrt(A^2 + B^2 - C^2), -sqrt(A^2 + B^2 - C^2)]);

    s6 = a2*sin(q2) + t7;
    s7 = t8 - a2*cos(q2);

    % Solve for (q2 + q3)
    q2_plus_q3 = atan2(-t7 - a2 * sin(q2), t8 - a2 * cos(q2));
    q2_plus_q3 = atan2(-s6/a3, s7/a3);

    % Solve for q3
    q3 = q2_plus_q3 - q2;

    % Solve for q4
    q4 = q2_q3_q4 - q2_plus_q3;

    % disp(vpa(rad2deg(q2)))
    % disp(vpa(rad2deg(q3)))
    % disp(vpa(rad2deg(q4)))
end

