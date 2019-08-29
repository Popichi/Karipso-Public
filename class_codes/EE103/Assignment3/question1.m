%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Name: Anil Celik Maral
% Cruz ID: amaral
% amaral@ucsc.edu
% Student ID: 1454995
% EE103, Lab-3, Question-1
% Date: 04/26/18  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

R = 2;    % 2 Ohms
C = 1;    % 1 Farad
L = 0.5;  % H

t = -10:0.01:30;

Use Matlab
built-in differential equation solver dsolve() to derive the impulse response
h(t)

RC * d^2y(t)/dt^2 + dy(t)/dt + R/L*y(t) = dx(t)/d(t) (1)