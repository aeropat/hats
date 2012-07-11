% Code to Read Data from SD Card
clear all

% =========================================================================
% Load Data
% =========================================================================

filename=input('Please enter the data file name with extension as a string:');

data=load(filename);
%Day:Hour:Min:Sec
timedata=fopen(filename);
C=textscan(timedata, '%f %s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f');
timestamp=C{2};
fclose(timedata);
%t=datenum(timestamp);
t=timestamp;

%Time Since Start in milisec
tmss=data(:,1);

%Internal Temperature
ITemp=data(:,3);
%External Temperature
ETemp=data(:,4);

%Pressure before Apex 16
PressApexF=data(:,5);
%Pressure After Apex 16
PressApexB=data(:,6);
%Pressure Before NACA10
PressNacaF=data(:,7);
%Pressure After NACA10
PressNacaB=data(:,8);
%Ambient Pressure
PressA=data(:,9);

%Wind Velocity X
WindX=data(:,10);
%Wind Velocity Y
WindY=data(:,11);
%Wind Velocity Z
WindZ=data(:,12);
%Wind Velocity All directions
WindAll=data(:,13);

%APEX 16 Optical Encoder Data
OptEncApex=data(:,14);
%NACA 10 Optical Encoder Data
OptEncNaca=data(:,15);

%APEX 16 Strain Gauge Data
%StrainApex=data(:,16);
%NACA 10 Strain Gauge Data
%StrainNaca=data(:,17);

% =========================================================================
% Calibrate Data
% =========================================================================

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Calibrate Pressure Sensor Readings

% Data from pressure sensor test [Reading Press(Torr)]
PTestdat=[98	1
107	10
108	17
116	20
116	20
141	50
152	70
177	90
201	150
279	200
360	325
456	450
551	600
642	700
723	750];

% Establish linear fit
Plin=polyfit(PTestdat(:,1), PTestdat(:,2),1);

%Convert Pressure Values to torr
for i=1:length(PressApexF)
    Press1F(i)=polyval(Plin, PressApexF(i));
    Press1B(i)=polyval(Plin, PressApexB(i));
    Press2F(i)=polyval(Plin, PressNacaF(i));
    Press2B(i)=polyval(Plin, PressNacaB(i));
    APress(i)=polyval(Plin, PressA(i));
end

%Convert Pressure Values to kPa
Press1F=101.325/760.*Press1F;
Press1B=101.325/760.*Press1B;
Press2F=101.325/760.*Press2F;
Press2B=101.325/760.*Press2B;
APress=101.325/760.*APress;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Calculate altitude from ambient pressure data based on 1976 Standard
% Atmospheric Model

%Values from 1976 atmo model [Alt, PR, rho]
MAlt=[0
1000
3000
5000
10000
25000
50000
75000
100000
130000
160000
200000
300000
400000
600000
1000000];

MPR=[1
8.87E-01
6.69E-01
5.33E-01
2.62E-01
2.52E-02
7.87E-04
2.04E-05
3.16E-07
1.23E-08
3.00E-09
8.36E-10
1.43E-11
1.42E-11
8.11E-13
7.42E-14];

Mrho=[1.225
1.117
9.09E-01
7.63E-01
4.14E-01
4.01E-02
1.03E-03
3.49E-05
5.60E-07
8.15E-09
1.23E-09
2.54E-10
2.89E-12
2.80E-12
2.14E-13
3.56E-15];

% Establish piecewise polynomial based on atmospheric model where
% x=Pressure Ratio and y=Altitude
PP_Alt=pchip(MPR,MAlt);

% Calculate Pressure Ratio for each data point
PR=APress./101.325; %Assumes that Pressure values are already in kPa

%Calculate the altitude of each data point
for i=1:length(APress)
    alt(i)=PPVAL(PP_Alt,PR(i));
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Calculate Propeller Thrust from Pressure Values

% User Input of Propeller Disc area S given radius
S=pi*3^2*2.54^2;   %in cm^2

% Thrust Calculation at each data point for each propeller
for i=1:length(Press1F)
    T1(i)= S*(Press1B(i)-Press1F(i))*10;    %Thrust in N
    T2(i)= S*(Press2B(i)-Press2F(i))*10;    %Thrust in N
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Calculate Propeller Efficiency

%Determine atmospheric density base on ambient pressure and atmospheric
%model 1976

PP_Rho=pchip(MPR,Mrho);
for i=1:length(APress)
    rho(i)=PPVAL(PP_Rho,PR(i));
end

% Determine Vertical Velocity component
V=WindZ;

% Calculate Vs or velocity exiting the propeller
for i=1:length(Press1F)
    Vs1(i)=sqrt((Press1B(i)-Press1F(i))*2./rho(i)+V(i));
    Vs2(i)=sqrt((Press2B(i)-Press2F(i))*2./rho(i)+V(i));
end
%Transpose row vector to column vector
Vs1=Vs1';
Vs2=Vs2';

% Calculate V0 or velocity through the propeller
V01=1/2.*(Vs1+V);
V02=1/2.*(Vs2+V);

% Calculate propeller efficiency
n1=T1.*V./(0.5.*rho.*S.*V01.*(Vs1.^2-V.^2));
n2=T2.*V./(0.5.*rho.*S.*V02.*(Vs2.^2-V.^2));

% =========================================================================
% Display Data
% =========================================================================

figure
plot(datenum(t), ITemp, datenum(t), ETemp)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Temperature, Deg C')
legend('Internal Temperature', 'External Temperature')

figure
plot(datenum(t), APress)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Atmospheric Pressure, Pa')

figure
plot(datenum(t), WindX, datenum(t), WindY, datenum(t), WindZ,datenum(t), WindAll)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Wind Speed') 
legend('Wind Speed X', 'Wind Speed Y', 'Wind Speed Z', 'Wind Speed Tot')

figure
plot(datenum(t), OptEnc1,datenum(t), OptEnc2)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Propeller Speed, RPM')
legend('APEX 16 Speed', 'NACA 10 Speed')

figure
plot(datenum(t), Strain1,datenum(t), Strain2)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Strain, V')
legend('Strain APEX 16','Strain NACA 10')

figure
plot(datenum(t),T1, datenum(t), T2)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Thrust N')
legend('Apex 16 Thrust','NACA 10 Thrust')

figure
plot(datenum(t),n1, datenum(t), n2)
datetick('x', 'HH:MM:SS')
xlabel('Time, H:M:S')
ylabel('Efficiency')
legend('Apex 16 Efficiency','NACA 10 Efficiency')



