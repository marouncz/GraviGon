clc
clear all 
close all

data = readtable("Bilovice.csv");

figure;
plot(data.mpuAccelX)
hold on;
plot(data.mpuAccelY)
hold on;
plot(data.mpuAccelZ)
hold on;
legend("accelX", "accelZ", "accelZ")

figure;
plot(data.mpuGyroX)
hold on;
plot(data.mpuGyroY)
hold on;
plot(data.mpuGyroZ)
hold on;
legend("gyroX", "gyroY", "gyroZ")

figure;
plot(data.lsmMagX, 'rx-', 'LineWidth', 1)
hold on;
plot(data.lsmMagY, 'bx-', 'LineWidth', 1)
hold on;
plot(data.lsmMagZ, 'gx-', 'LineWidth', 1)
hold on;
legend("magX", "magY", "magZ")

figure;
yyaxis left
plot(data.pressure, 'rx-', 'LineWidth', 1)
hold on;
yyaxis right
plot(data.temperature, 'bx-', 'LineWidth', 1)
hold on;
legend("presure", "temperature")
