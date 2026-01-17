filename = "characteristic.csv";
data = readmatrix(filename);

CCR = data(:,1);
RPM = data(:,2);


RPMf = movmean(RPM,15);

figure
plot(CCR,RPMf,'LineWidth',2)
hold on
plot(CCR,RPM,'.','LineWidth',5)

grid on
xlabel("CCR")
ylabel("RPM")
legend("raw","smoothed")
title("DC motor characteristics")
