function quatout = quatmult(quata,quatb)
%==========================================================================
%
% Use: outputmat =  quat2dcm(quat)
%
% Determine quata * quatb, in that order (hamilton product).
%
% Author: C2C Derek Weissinger USAFA/DFAS
%  
% Inputs:
%   quata: a quaternion, expressed with real part first (q0, q1, q2, q3).
%   quatb: a quaternion, expressed with real part first (q0, q1, q2, q3).
%
% Outputs
%  quatout: a quaternion, expressed with real part first (q0, q1, q2, q3).
% Coupling:
%   N/A
%
% References:
%   13 July Notes: Hand derivation
%
%==========================================================================

%define components
a0 = quata(1); a1 = quata(2); a2 = quata(3); a3 = quata(4);
b0 = quatb(1); b1 = quatb(2); b2 = quatb(3); b3 = quatb(4);

%real component
out0 = a0*b0 - (a1*b1 + a2*b2 + a3*b3);
%i component
out1 = a0*b1 + a2*b3 + a1*b0 - a3*b2;
%j component
out2 = a0*b2 + a2*b0 + a3*b1 - a1*b3;
%k component
out3 = a0*b3 + a3*b0 + a1*b2 - a2*b1;

quatout = [out0, out1, out2, out3];

end