function outputmat =  euler2dcm(phi, theta, psi)
%==========================================================================
%
% Use: outputmat =  euler2dcm(phi, theta, psi)
%
% Given 3 fundamental euler angles phi, theta, and psi between two 
% coordinate frames, output a Directional Cosine Matrix (DCM), using 
% default aerospace ZYX passive rotation order (Yaw, Pitch, Roll).  
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
%   phi: angle of roll (deg)
%   theta: angle of pitch (deg)
%   psi: angle of yaw
%
% Outputs
%  outputmat: a 3x3 rotation matrix.
%
% Coupling:
%   N/A
%
% References:
%   Starlino DCM Tutorial; Accessed online
%   Rotation Matrix Wikipedia Article; Used to check work 
%
%==========================================================================

%Define 3x3 Identity Matrix
I = [1 0 0; 0 1 0; 0 0 1];

%Calculate the roll rotation matrix
roll = [[1; 0; 0] [0; cosd(phi); -sind(phi)] [0; sind(phi); cosd(phi)]];  

%Calculuate the pitch rotation matrix
pitch = [[cosd(theta); 0; sind(theta)] [0; 1; 0;] [-sind(theta); 0; cosd(theta)]];

%Calculate the yaw rotation matrix
yaw = [[cosd(psi); -sind(psi); 0] [sind(psi); cosd(psi); 0] [0; 0; 1]];

%ZYX Order Rotation Matrix
rotationmat = roll * pitch * yaw;

%Checks to make sure the matrix is orthogonal
if abs(norm(rotationmat * transpose(rotationmat) - I)) > 0.01
    error("Rotation Matrix Invalid.")
end

if abs(det(rotationmat) - 1) > 0.01
    error("Rotation Matrix Invalid.")
end

if abs(norm(transpose(rotationmat) - inv(rotationmat))) > 0.01
    error("Rotation Matrix Invalid.")
end

%If matrix is good, return it.
outputmat = rotationmat;