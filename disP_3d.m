function P_3d = disP_3d(M,Psrc)
    cnt = size(Psrc{1},1);
    P_3d = cell(6,1);
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
    
    figure,
    plot3(P_3d{1}(:,1),P_3d{1}(:,2),P_3d{1}(:,3),'r.');
    hold on
    plot3(P_3d{2}(:,1),P_3d{2}(:,2),P_3d{2}(:,3),'b.');
    hold on
   % plot3(P_3d{3}(:,1),P_3d{3}(:,2),P_3d{3}(:,3),'g.');
    hold on
    plot3(P_3d{4}(:,1),P_3d{4}(:,2),P_3d{4}(:,3),'k.');
    hold on
    plot3(P_3d{5}(:,1),P_3d{5}(:,2),P_3d{5}(:,3),'c.');
    hold on
    plot3(P_3d{6}(:,1),P_3d{6}(:,2),P_3d{6}(:,3),'m.');
    hold off
end