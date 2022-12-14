clear; clc; close all

syms l1 l2 lb theta1 theta2 d3 ao 'real'
l1_dh = [0, lb, 0, 0];
l2_dh = [theta1, 2*ao, l1-2*ao, 0];
l3_dh = [theta2, ao, l2-ao, 0];
l4_dh = [0, d3-ao, ao, 0];

syms theta d a alpha 'real'
A = [cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), a*cos(theta);
     sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta);
     0, sin(alpha), cos(alpha), d;
     0, 0, 0, 1];

A1 = simplify(subs(A, [theta,d,a,alpha], l1_dh));
A2 = simplify(subs(A, [theta,d,a,alpha], l2_dh));
A3 = simplify(subs(A, [theta,d,a,alpha], l3_dh));
A4 = simplify(subs(A, [theta,d,a,alpha], l4_dh));

H0_1 = A1;
H0_1_filled_in = simplify(subs(H0_1, [l1, l2, lb, ao],[1,1,2,0.05]));
H0_2 = simplify(A1*A2);
H0_2_filled_in = simplify(subs(H0_2, [l1, l2, lb, ao],[1,1,2,0.05]));
H0_3 = simplify(A1*A2*A3);
H0_3_filled_in = simplify(subs(H0_3, [l1, l2, lb, ao],[1,1,2,0.05]));
H0_4 = simplify(A1*A2*A3*A4);
H0_4_filled_in = simplify(subs(H0_4, [l1, l2, lb, ao],[1,1,2,0.05]));

display(H0_1);
display(H0_1_filled_in);
display(H0_2);
display(H0_2_filled_in);
display(H0_3);
display(H0_3_filled_in);
display(H0_4);
display(H0_4_filled_in);

z0_1 = H0_1_filled_in(1:3, 3);
o0_1 = H0_1_filled_in(1:3, 4);
z0_2 = H0_2_filled_in(1:3, 3);
o0_2 = H0_2_filled_in(1:3, 4);
z0_3 = H0_3_filled_in(1:3, 3);
o0_4 = H0_4_filled_in(1:3, 4);

Jv1 = simplify(cross(z0_1, (o0_4-o0_1)));
Jw1 = z0_1;
Jv2 = simplify(cross(z0_2, (o0_4-o0_2)));
Jw2 = z0_2;
Jv3 = z0_3;
Jw3 = [0; 0; 0];

jacobian_matrix = [Jv1, Jv2, Jv3;
                   Jw1, Jw2, Jw3];
display(jacobian_matrix);

syms q1_dot q2_dot q3_dot 'real'

joint_velocities = [q1_dot; q2_dot; q3_dot];
twist = jacobian_matrix * joint_velocities;
display(twist);

inv_jacobian = simplify(inv(jacobian_matrix(1:3, 1:3)));
display(inv_jacobian);

syms vx vy vz 'real'
twist_input = [vx; vy; vz];
joint_vel_output = simplify(inv_jacobian*twist_input);
display(joint_vel_output);