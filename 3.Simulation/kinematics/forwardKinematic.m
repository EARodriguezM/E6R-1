function gst_theta = forwardKinematic(robot, gst0, angles)
    angles = deg2rad(angles);
    % Joint twist vectors for each joint
    w1 = [0; 0; 1];     % rotation axis of the first joint
    w2 = [1; 0; 0];     % the second joint and so on...
    w3 = [1; 0; 0];
    w4 = [1; 0; 0];
    w5 = [0; 0; 1];
    w6 = [1; 0; 0];

    % Define the points on each joint axis (Assuming initial configuration)
    r1 = [0; 0; 0];     % point on the rotation axis of the first joint
    r2 = [0; 0; 0];     % the second joint and so on...
    r3 = [0; 0; robot.a2];
    r4 = [0; 0; robot.a2 + robot.a3];
    r5 = [robot.d4; 0; robot.a2 + robot.a3];
    r6 = [robot.d4; 0; robot.a2 + robot.a3 + robot.d5];

    % Define twists for each joint
    xi1 = [w1; cross(-w1, r1)];
    xi2 = [w2; cross(-w2, r2)];
    xi3 = [w3; cross(-w3, r3)];
    xi4 = [w4; cross(-w4, r4)];
    xi5 = [w5; cross(-w5, r5)];
    xi6 = [w6; cross(-w6, r6)];
    
    % Define kinematics using POE formula
    e_xi1_theta1 = computeExponential(xi1, angles(1));
    e_xi2_theta2 = computeExponential(xi2, angles(2));
    e_xi3_theta3 = computeExponential(xi3, angles(3));
    e_xi4_theta4 = computeExponential(xi4, angles(4));
    e_xi5_theta5 = computeExponential(xi5, angles(5));
    e_xi6_theta6 = computeExponential(xi6, angles(6));

    % Calculate final position
    gst_theta = e_xi1_theta1 * e_xi2_theta2 * e_xi3_theta3 * e_xi4_theta4 *e_xi5_theta5 *e_xi6_theta6 * gst0;
end