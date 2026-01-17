clear;
clc;
s = serialport("/dev/ttyACM1",115200);
configureTerminator(s,"LF");
flush(s);

sample_time_ms = 1000;
observation_time_ms = 60000;

CCR = [];
RPM = [];
samples = observation_time_ms /sample_time_ms;



while length(CCR) < samples
    line = strtrim(readline(s));
    C = sscanf(line, "%d CCR: %f RPM");
    if numel(C) == 2
        CCR(end+1) = C(1);
        RPM(end+1) = abs(C(2));
    end
end

clear s

data = [CCR(:) RPM(:)];

fid = fopen("data/characteristic_filtered.csv", "w");
fprintf(fid, "ccr,rpm\n");
fprintf(fid, "%d,%f\n",data');
fclose(fid);

figure
plot(CCR, RPM)
grid on
xlabel("CCR")
ylabel("RPM")

