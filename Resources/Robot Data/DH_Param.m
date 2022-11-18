clc;
clear all;
close all;
%% Defining DH Parameters

syms l1 l2 lb theta1 theta2 d3 ao
% Theta D A Alpha
l1_dh = [0 lb 0 0]
l2_dh = [theta1 2*ao l1-2*ao 0]
l3_dh = [theta2 ao l2-ao 0]
l4_dh = [0 d3-ao ao 0]
%% Making Symbolic A Matrix

syms theta d a alpha
A = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta);
    sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta);
    0 sin(alpha) cos(alpha) d;
    0 0 0 1]
A1 = simplify(subs(A,[theta,d,a,alpha],l1_dh));
A2 = simplify(subs(A,[theta,d,a,alpha],l2_dh));
A3 = simplify(subs(A,[theta,d,a,alpha],l3_dh));
A4 = simplify(subs(A,[theta,d,a,alpha],l4_dh));
T = A1*A2*A3*A4;
T = simplify(subs(T,[l1,l2,lb,ao],[1,1,2,0.05]))
%% Modelling the Robot from DH Parameters

L(1) =  Link(double(subs(l1_dh,[l1,l2,lb,theta1,theta2,d3,ao],[1,1,1,0,0,1.2,0.05])),'standard');
L(1).qlim = pi/180 * [-90 90];
L(2) =  Link(double(subs(l2_dh,[l1,l2,lb,theta1,theta2,d3,ao],[1,1,1,0,0,1.2,0.05])),'standard');
L(2).qlim = pi/180 * [-90 90];
L(3) =  Link(double(subs(l3_dh,[l1,l2,lb,theta1,theta2,d3,ao],[1,1,1,0,0,1.2,0.05])),'standard');
L(3).qlim = pi/180 * [-90 90];
L(4) =  Link([double(subs(l4_dh,[l1,l2,lb,theta1,theta2,d3,ao],[1,1,1,0,0,1.2,0.05])),1],'standard');
L(4).qlim = [0 2];
scara_robot = SerialLink(L);
scara_robot.name = 'SCARA Robot';
scara_robot.plot([0 0 0 0],'workspace',[-2 2 -2 2 0 2])
scara_robot.teach