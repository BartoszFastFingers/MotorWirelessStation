clear;
clc;
filename = "step_response.csv";
data = readmatrix(filename);

time_ms = data(:,1);
RPM = data(:,2);




RPMf = movmean(RPM,15);

figure
plot(time_ms,RPMf,'LineWidth',2)
hold on
plot(time_ms,RPM,'.','LineWidth',5)

grid on
xlabel("ms")
ylabel("RPM")
legend("raw","smoothed")
title("DC motor characteristics")
