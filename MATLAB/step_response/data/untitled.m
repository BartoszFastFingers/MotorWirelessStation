%% Wczytanie danych
data = readmatrix('step_response_filtered.csv');

t = data(:,1);      % czas
y = data(:,2);      % odpowiedź obiektu

Ts = mean(diff(t)); % czas próbkowania

%% Definicja sygnału wejściowego (skok 4500)
u = 4500 * ones(size(t));

%% Utworzenie obiektu iddata
z = iddata(y, u, Ts);

%% Identyfikacja modelu
% 1) Model inercyjny I rzędu z opóźnieniem
sys1 = procest(z, 'P1D');

% 2) Model inercyjny II rzędu z opóźnieniem
sys2 = procest(z, 'P2D');

% 3) Model transmitancji (ARX/TF)
sys_tf = tfest(z, 2, 0);

%% Porównanie modeli
figure;
compare(z, sys1, sys2, sys_tf);
grid on;

%% Wyświetlenie transmitancji
disp('Model P1D:');
sys1

disp('Model P2D:');
sys2

disp('Model TF:');
sys_tf

K = sys1.Kp;        % wzmocnienie obiektu
T = sys1.Tp1;       % stała czasowa
L = sys1.Td;  

lambda = 11*L;  

Kc = T / (K * (lambda + L));
Ti = min(T, 4*(lambda + L));

% Regulator PI
C_PI = pid(Kc, Kc/Ti);

disp('Regulator PI (SIMC):');
C_PI
