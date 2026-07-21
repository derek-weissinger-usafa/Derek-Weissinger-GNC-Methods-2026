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
%   AFIT MECH 653 Lesson 2 Attitude Kinematics Lecture Notes, Slide 17
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

%Calculate Angles, based from 3D DCM symbolically calculated in MATLAB

    phi = rad2deg(atan2(inputmat(2,3), inputmat(3,3)));
    theta = rad2deg(asin(-inputmat(1,3)));
    psi = rad2deg(atan2(inputmat(1,2), inputmat(1,1)));

%Prefer positive phi and psi to express pitch > 90
    if phi < 0 && psi < 0
        phi = 180 + phi;
        theta = 180 - theta;
        psi = 180 + psi;
    end

end