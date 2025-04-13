clc
clear all 
close all

data = readtable("output.csv");

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
yyaxis left
plot(data.pressure, 'rx-', 'LineWidth', 2)
hold on;
yyaxis right
plot(data.temperature, 'bx-', 'LineWidth', 2)
hold on;
legend("presure", "temperature")
