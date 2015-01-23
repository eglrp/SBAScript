%% 数据初始化
% 本程序使用的输入数据分为两部分
%1、各摄像机的图像坐标：Pic88.txt,Pic89.txt,Pic98.txt,Pic99.txt
%2、各摄像机的初始参数 : InitData2.m


clear
close all

InitData2%包含各个摄像机初始的标定结果

%%
P_3d = cell(6,1);
cnt = size(Psrc{1},1);
for i=1:cnt
    pn = Im2D23D(Psrc{1}(i,:),M{1},Psrc{2}(i,:),M{2});
    P_3d{1} = [P_3d{1};pn];
    pn = Im2D23D(Psrc{1}(i,:),M{1},Psrc{3}(i,:),M{3});
    P_3d{2} = [P_3d{2};pn];
    pn = Im2D23D(Psrc{1}(i,:),M{1},Psrc{4}(i,:),M{4});
    P_3d{3} = [P_3d{3};pn];
    pn = Im2D23D(Psrc{2}(i,:),M{2},Psrc{3}(i,:),M{3});
    P_3d{4} = [P_3d{4};pn];
    pn = Im2D23D(Psrc{2}(i,:),M{2},Psrc{4}(i,:),M{4});
    P_3d{5} = [P_3d{5};pn];
    pn = Im2D23D(Psrc{3}(i,:),M{3},Psrc{4}(i,:),M{4});
    P_3d{6} = [P_3d{6};pn];
end
Pavg =  zeros(size(pic88,1),3);
for i = 1:6
    Pavg = Pavg + P_3d{i};
end
Pavg = Pavg/6;

%%

R88 = rodrigues(Cam88ExData(1:3,1:3))';
T88 = Cam88ExData(1:3,4)';
OUT88 = [Cam88InData(1:3,1:3);[0 0 0];R88;T88];
save ./datafile/Par88.txt OUT88 -ascii


R89 = rodrigues(Cam89ExData(1:3,1:3))';
T89 = Cam89ExData(1:3,4)';
OUT89 = [Cam89InData(1:3,1:3);[0 0 0];R89;T89];
save ./datafile/Par89.txt OUT89 -ascii


R98 = rodrigues(Cam98ExData(1:3,1:3))';
T98 = Cam98ExData(1:3,4)';
OUT98 = [Cam98InData(1:3,1:3);[0 0 0];R98;T98];
save ./datafile/Par98.txt OUT98 -ascii


R99 = rodrigues(Cam99ExData(1:3,1:3))';
T99 = Cam99ExData(1:3,4)';
OUT99 = [Cam99InData(1:3,1:3);[0 0 0];R99;T99];
save ./datafile/Par99.txt OUT99 -ascii

%%

save ./datafile/threeD.txt Pavg -ascii 

P2d = Psrc{1};
save ./datafile/Pic88.txt P2d -ascii 
P2d = Psrc{2};
save ./datafile/Pic89.txt P2d -ascii 
P2d = Psrc{3};
save ./datafile/Pic98.txt P2d -ascii 
P2d = Psrc{4};
save ./datafile/Pic99.txt P2d -ascii 
%%
%到这里运行cvsba,计算结果生成cvCBA_Result.m文件
NCAMS    = size(Psrc,2);
NPOINTS = size(Pavg,1);
cmd = ['cvsbaV2.exe ' , num2str(NCAMS,'%d'), '  ',  num2str(NPOINTS,'%d')];
system(cmd); 
%%
cvCBA_Result

Cam88Ex_cba = [rodrigues(R0),T0;[0 0 0 1]];
Cam89Ex_cba = [rodrigues(R1),T1;[0 0 0 1]];
Cam98Ex_cba = [rodrigues(R2),T2;[0 0 0 1]];
Cam99Ex_cba = [rodrigues(R3),T3;[0 0 0 1]];

M{1} = Cam88InData*Cam88Ex_cba;
M{2} = Cam89InData*Cam89Ex_cba;
M{3} = Cam98InData*Cam98Ex_cba;
M{4} = Cam99InData*Cam99Ex_cba;

disP_3d(M,Psrc);










