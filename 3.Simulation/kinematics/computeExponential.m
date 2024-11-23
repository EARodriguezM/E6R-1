function T = computeExponential(xi, q)
% computeExponential computes the matrix exponential e^(xi_hat * q)
% for a given twist xi and joint angle q.
%
% Input:
%   xi - A 6x1 vector representing the twist [omega; v], where:
%        omega: The rotational component (3x1 vector)
%        v: The translational component (3x1 vector)
%   q - The joint displacement/angle (scalar)
%
% Output:
%   T - The 4x4 transformation matrix e^(xi_hat * q)

    % Extract omega and v from xi
    omega = xi(1:3); % rotational component
    v = xi(4:6);     % translational component

    % Check if the joint is revolute or prismatic
    if norm(omega) > 1e-6 % Revolute joint
        % Compute the skew-symmetric matrix of omega
        omega_hat = skewSymmetric(omega);

        % Compute e^(omega_hat * q) using the Rodrigues formula
        R = eye(3) + omega_hat * sin(q) + (omega_hat^2) * (1 - cos(q));

        % Compute the translational part
        p = (eye(3) * q + (1 - cos(q)) * omega_hat + (q - sin(q)) * (omega_hat^2)) * v;
        % p = (eye(3) - R) * (cross(omega,v)) + (q * (omega_hat * omega_hat.') * v);
    else % Prismatic joint
        % Pure translation
        R = eye(3); % No rotation
        p = v * q;  % Translation
    end

    % Construct the 4x4 transformation matrix
    T = [R, p; 
         0, 0, 0, 1];
end

function omega_hat = skewSymmetric(omega)
% skewSymmetric generates the skew-symmetric matrix of a 3x1 vector omega.
    omega_hat = [  0,      -omega(3),  omega(2);
                 omega(3),   0,      -omega(1);
                -omega(2), omega(1),   0];
end