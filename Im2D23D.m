%p1,p2是图像坐标，[u,v]
%M1,M2是相应的参数矩阵

function P = Im2D23D(p1,M1,p2,M2)
    u1 = p1(1);
    v1 = p1(2);
    u2 = p2(1);
    v2 = p2(2);
    
    Hl = [ M1(3,:)*u1-M1(1,:) ;
           M1(3,:)*v1-M1(2,:) ;
           M2(3,:)*u2-M2(1,:) ;
           M2(3,:)*v2-M2(2,:) ];
    
    gls = -Hl(:,end);
    Hl  = Hl(:,1:3);
    
    P = (Hl'*Hl)\Hl'*gls;
    P = P';
end