
load('data/fitted_model2.mat');
params = coeffvalues(fittedmodel);
names  = coeffnames(fittedmodel);
K  = params(1);
T  = params(2)/6500; % fix that was solved by  version of determining the model's substitute parameters -> T = 100
t0 = params(3)/1000;
%normalized to seconds


fprintf('K = %.2f\nT = %.2f\nt0 = %.2f\n', K, T, t0);

tau_c_values = linspace(t0/2, t0 , 8);
results = zeros(length(tau_c_values), 3);
s = tf('s');
G = K/(T*s + 1)*exp(-t0*s);

for i = 1:length(tau_c_values)

    tau_c = tau_c_values(i);

    Kp = T/(K*(tau_c + t0));
    Ti = min(T, 4*(tau_c + t0));

    C = Kp*(1 + 1/(Ti*s));

    sys_cl = feedback(C*G, 1);

    t = 0:0.001:2;
    [y, t] = step(sys_cl, t);

    if any(isnan(y)) || max(abs(y)) > 5
        results(i,:) = [NaN NaN NaN];
        continue;
    end

    info = stepinfo(y, t, dcgain(sys_cl));

    results(i,:) = [info.SettlingTime, info.Overshoot, info.RiseTime];

end



tau_c_col = tau_c_values';
SettlingTime_col = results(:,1);
Overshoot_col = results(:,2);
RiseTime_col = results(:,3);

Tab = table(tau_c_col, SettlingTime_col, Overshoot_col, RiseTime_col);
Tab.Properties.VariableNames = {'Tau_c','Czas_ustalania_s','Przeregulowanie_pct','Czas_narastania_s'};

disp(Tab);
disp(table((1:length(tau_c_values))', tau_c_values', 'VariableNames', {'Index','Tau_c'}))

idx = input('Wybierz numer wiersza Tau_c: ');

tau_c = tau_c_values(idx);

Kp = T / (K * (tau_c + t0));
Ti = min(T, 4*(tau_c + t0));
Td = 0;

assignin('base', 'Kp', Kp);
assignin('base', 'Ti', Ti); 
assignin('base', 'Td', Td);

fprintf('\nWybrana wartość Tau_c = %.2f\n', tau_c);
fprintf('Parametry regulatora:\nKp = %.4f\nTi = %.4f\nTd = %.4f\n', Kp, Ti, Td);
