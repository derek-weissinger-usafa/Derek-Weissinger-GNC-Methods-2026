function outputmat =  quat2dcm(quat)
%==========================================================================
%
% Use: outputmat =  quat2dcm(quat)
%
% Given rotation quaternion quat, convert to 321 passive DCM.  
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
%   quat: Unit quaternion, expressed as [q0, q1, q2, q3], where q0 is the
%   real part and q1, q2, q3 aligned with i, j, k respectively.
%
% Outputs
%  outputmat: a 3x3 rotation matrix.
%
% Coupling:
%   N/A
%
% References:
%   Wie, Bong. Space Vehicle Dynamics and Control, Chapter 5 Page 335
%
%==========================================================================

%Define Identity Matrix
I = [1 0 0; 0 1 0; 0 0 1];

%Check for valid unit quaternion
if norm(quat) - 1 > 0.1
    error("Invalid Quaternion, Norm is not equal to 1.")
end

%Check for quaternion
if length(quat) ~= 4
    error("Invalid Vector, Quaternions have 4 elements.")
end

q0 = quat(1);
q1 = quat(2);
q2 = quat(3);
q3 = quat(4);

%Found in Wie 335
outputmat = [1 - 2*(q2^2 + q3^2) 2*(q1*q2 + q3*q0) 2*(q1*q3 - q2*q0);
             2*(q2*q1 - q3*q0) 1 - 2*(q1^2 + q3^2) 2*(q2*q3 + q1*q0);
             2*(q3*q1 + q2*q0) 2*(q3*q2 - q1*q0) 1 - 2*(q1^2 + q2^2)];

%Checks to make sure the matrix is orthogonal
if abs(norm(outputmat * transpose(outputmat) - I)) > 0.01
    error("Rotation Matrix Invalid.")
end

if abs(det(outputmat) - 1) > 0.01
    error("Rotation Matrix Invalid.")
end

if abs(norm(transpose(outputmat) - inv(outputmat))) > 0.01
    error("Rotation Matrix Invalid.")
end


end