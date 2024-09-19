%% set font (latex)
Lw = 8; Fsize = 24;

%% Section 1
Filename = "Lab2_1.csv";
DATA = readmatrix(Filename);
time  = DATA(:, 1) * 1000;
Vs = DATA(:, 2);
Vc = DATA(:, 3);

plot(time, [Vs, Vc], LineWidth = Lw)
xlim([0 10])
legend("$V_{s}$","$V_{c}$", 'Interpreter', 'latex',FontSize = Fsize)
xlabel('$time (ms)$', 'Interpreter', 'latex',FontSize = Fsize)
ylabel('$Voltage (V)$', 'Interpreter', 'latex',FontSize = Fsize)
grid on

%% Section 2
Filename = "Lab2_2.csv";
DATA = readmatrix(Filename);
time  = DATA(:, 1) * 1000;
Vs = DATA(:, 2);
Vc = DATA(:, 3);

plot(time, [Vs, Vc], LineWidth = Lw)
xlim([0 10])
legend("$V_{s}$","$V_{c}$", FontSize = Fsize)
xlabel('$time (ms)$', FontSize = Fsize)
ylabel('$Voltage (V)$', FontSize = Fsize)
grid on
