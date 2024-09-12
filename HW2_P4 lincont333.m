""" MATLAB code
 # Task: Homework3_Problem4
 # Code: Peerawich Sodsuay
 # Warning: Don't copy this code to submit.
 # If you do it, your score will be cancel immediately.
"""
K0 = 3.75;     % From problem 3

Ka = K0 / 2;
Kb = K0;
Kc = K0 + 1;

G = tf([1], [1 2 4 3 0]);
H_4a = feedback(Ka*G, 1);
H_4b = feedback(Kb*G, 1);
H_4c = feedback(Kc*G, 1);

%zpk(H_4a); zpk(H_4b); zpk(H_4c)

[y1, t1] = step(H_4a, 25);
[y2, t2] = step(H_4b, 25);
[y3, t3] = step(H_4c, 25);

plot(t1, y1, t2, y2, t3, y3, LineWidth = 3);

font_size = 18;
xlabel("Time (seconds)", 'fontsize', font_size, 'fontweight', 'b')
ylabel('Response','fontsize', font_size,'fontweight', 'b')

legend("4a) K = K0 / 2", "4b) K = K0", "4c) K = K0 + 1", 'fontsize', font_size + 5);
title("Step response when the input r(t) is a unit step", 'fontsize', font_size);
