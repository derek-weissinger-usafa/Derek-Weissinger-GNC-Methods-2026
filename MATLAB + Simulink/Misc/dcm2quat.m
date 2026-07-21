function quatout = dcm2quat(inputmat)
%==========================================================================
%
% Use: outputmat =  quat2dcm(quat)
%
% Given 321 order passive directional cosine matrix (DCM), give the
% equivalent quaternion.
% 
% In this 499, The body frame is defined as: +x: direction of nose 
% (roll axis); y: arbitrary (pitch axis); 
% z: arbitrary, but right handed (yaw).
%
% The Navigation frame is defined as: x: Up; y: North; z: West. This change
% from convention allows a rocket on the launchpad/vertical attitude to be 
% modeled with pitch = 0.
%
% Author: C2C Derek Weissinger USAFA/DFAS
%  
% Inputs:
%   inputmat: 321 order passive Directional Cosine Matrix (DCM).
%
% Outputs
%  The function gives a unit quaternion representing the rotation encoded
%  by inputmat. The function will automatically give the quaternion with a
%  positive real component.
%  q0: the real component.
%  q1: imaginary component in i direction.
%  q2: imaginary component in j direction.
%  q3: imaginary component in k direction.
%
% Coupling:
%   N/A
%
% References:
%   AFIT MECH 653 Lesson 2 Attitude Kinematics Lecture Notes, Slide 23
%
%==========================================================================

%Define Identity Matrix
I = [1 0 0; 0 1 0; 0 0 1];

%Checks to make sure the matrix is orthogonal, and therefore valid rotation
%matrix
    if abs(norm(inputmat * transpose(inputmat) - I)) > 0.01
        error("Rotation Matrix Invalid.")
    end

    if abs(det(inputmat) - 1) > 0.01
        error("Rotation Matrix Invalid.")
    end

    if abs(norm(transpose(inputmat) - inv(inputmat))) > 0.01
        error("Rotation Matrix Invalid.")
    end

if rank(inputmat) ~= 3
    error("Rotation Matrix must be 3x3.")
end

%Real part of quaternion; negative value is possible but we default to
%positive
q0 = real(0.5 * sqrt(1 + trace(inputmat)));

%Imaginary parts
q1 = (1/(4*q0)) * (inputmat(2,3) - inputmat(3,2));
q2 = (1/(4*q0)) * (inputmat(3,1) - inputmat(1,3));
q3 = (1/(4*q0)) * (inputmat(1,2) - inputmat(2,1));

%Check to make sure unit quaternion is returned
if abs(norm([q0, q1, q2, q3]) - 1) > 0.01
    error("Invalid Quaternion.")
end

quatout = [q0, q1, q2, q3];

end