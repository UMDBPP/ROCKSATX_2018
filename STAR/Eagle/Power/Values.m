Vin = 30; % Volts
Vout = 5; % Volts 
Vin_Max = 35; % Volts

D = Vout / Vin;

R_fbb = 13.3e3; % Ohms
R_fbt = (Vout - .75)*(R_fbb / 0.75); % Ohms

f_sw = 1000e3; % kHz
Rt = 42904 * (f_sw/1e3)^-1.088;

Kind = 0.4;
Iout = 1; % Amps

L = ((Vin_Max - Vout) / (Iout * Kind)) * (Vout / (Vin_Max * f_sw));

