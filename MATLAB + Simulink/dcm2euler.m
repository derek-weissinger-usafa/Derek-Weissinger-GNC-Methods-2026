function [phi, theta, psi] =  dcm2euler(inputmat)
%==========================================================================
%
% Use: [phi, theta, psi] =  dcm2euler(phi, theta, psi)
%
% Given a Directional Cosine Matrix (DCM), using a default aerospace ZYX 
% passive rotation order, output the 3 euler angles.  
% 
% In this 499, The body frame is defined as: +x: direction of nose 
% (roll axis); y: arbitrary (pitch axis); z: arbitrary, but right handed
% (yaw).
%
% The Navigation frame is defined as: x: Up; y: North; z: West. This change
% from convention allows a rocket on the launchpad/vertical attitude to be 
% modeled with pitch = 0.
%
% Author: C2C Derek Weissinger USAFA/DFAS
%  
% Inputs:
%
% Outputs
%   phi: angle of roll (deg)
%   theta: angle of pitch (deg)
%   psi: angle of yaw
%
% Coupling:
%   N/A
%
% References:
%   Starlino DCM Tutorial; Accessed online
%   Rotation Matrix Wikipedia Article; Used to check work 
%
%==========================================================================
%Define Identity Matrix
I = [1 0 0; 0 1 0; 0 0 1];

%Checks to make sure the matrix is orthogonal, and therefore valid rotation
%matrix
if norm(rotationmat * transpose(rotationmat) - I) > 0.1
    error("Rotation Matrix Invalid")
end

if det(rotationmat) - 1 > 0.0001
    error("Rotation Matrix Invalid")
end

if norm(transpose(rotationmat) - inv(rotationmat)) > 0.1
    error("Rotation Matrix Invalid")
end


end