function [ t,Y ] = mcintyre_final(dur, file, V_fe, V_applied, stim_start, stim_end)

    vrest = -80;        %mV
    fiberD=16.0;        %um
    mysalength=3;       %um  
    nodelength=1.0;     %um
    space_p1=0.002;     %um
    space_p2=0.004;     %um
    space_i=0.004;      %um
    r=70;               %Ohm*cm
    mycm=0.1;           %uF/cm2
    mygm=0.001;         %S/cm2
    c=2;                %uF/cm2

    g_nap = 0.010;      % sodium channel conductivity [S/cm^2]
    g_naf = 3;          %S/cm^2
    g_k = 0.080;        %S/cm^2
    g_kf = 0;           %S/cm^2 (deactivated)
    g_l = 0.007;        % leak channel conductivity [S/cm^2] 
    e_na = 50.0;        %mV
    e_k = -90.0;        %mV
    e_l	= -90.0;        %mV
    
    g_p1 = 0.001;       %S/cm^2
    g_p2 = 0.0001;      %S/cm^2 
    g_i = g_p2;         %S/cm^2
    
    if fiberD == 16.0
        axonD=12.7;          %um 
        nodeD=5.5;          %um
        mysaD=5.5;         %um
        flutD=12.7;         %um
        deltax=1500;        %um
        flutlength=60;      %um
        nl=150;             %dimensionless
    end
    
    if fiberD == 10.0
        axonD=6.9;          %um 
        nodeD=3.3;          %um
        mysaD=3.3;         %um
        flutD=6.9;         %um
        deltax=1250;        %um
        flutlength=46;      %um
        nl=120;             %dimensionless
        
    end
    interlength=(deltax-nodelength-(2*mysalength)-(2*flutlength))/6;
    
    
    celsius = 36;
    q10_1 = 2.2^((celsius-20)/10);
    q10_2 = 2.9^((celsius-20)/10);
    q10_3 = 3.0^((celsius-36)/10);

    
    [r_mysa,r_pn1,c_mysa,c_mysa_m,g_mysa,g_mysa_m] = paracomp( ...
        mysaD, mysalength, space_p1, fiberD, c, r, g_p1, nl, mycm, mygm);
    
    [r_flut,r_pn2,c_flut,c_flut_m,g_flut,g_flut_m] = paracomp( ...
        flutD, flutlength, space_p2, fiberD, c, r, g_p2, nl, mycm, mygm);
    
    [r_inter,r_px,c_inter,c_inter_m,g_inter,g_inter_m] = paracomp( ...
        axonD, interlength, space_i, fiberD, c, r, g_i, nl, mycm, mygm);
    
    g_nap = calcConductance(nodeD,nodelength,g_nap);
    g_k = calcConductance(nodeD,nodelength,g_k);
    g_l = calcConductance(nodeD,nodelength,g_l);
    g_naf = calcConductance(nodeD,nodelength,g_naf);
    r_node = calcResAxial(nodeD,nodelength,r);
    c_node = calcCapacity(nodeD,nodelength,c);
    r_pn0 = calcResPeriax(nodeD,nodelength,space_p1,r);
    
    
    [V_stim,N_nodes,x_af,af,Xlr] = interpolate(file);
    Xlr_stim = Xlr*V_applied/V_fe;
    V_stim = V_stim*V_applied/V_fe;
        
    
    N_inter = N_nodes-1;
    % index values of the dV Vektor
    i_node = [1,N_nodes];
    i_para_m = [i_node(2)+1,i_node(2)+N_nodes];
    i_para_h = [i_para_m(2)+1,i_para_m(2)+N_nodes];
    i_para_p = [i_para_h(2)+1,i_para_h(2)+N_nodes];
    i_para_s = [i_para_p(2)+1,i_para_p(2)+N_nodes];
    i_mysa = [i_para_s(2)+1,i_para_s(2)+N_inter, ...
        i_para_s(2)+N_inter+1,i_para_s(2)+N_inter*2];
    i_flut = [i_mysa(4)+1,i_mysa(4)+N_inter, ... 
        i_mysa(4)+N_inter+1,i_mysa(4)+N_inter*2];
    i_para_n = [i_flut(4)+1,i_flut(4)+N_inter, ...
        i_flut(4)+N_inter+1,i_flut(4)+N_inter*2];
    i_inter = [i_para_n(4)+1,i_para_n(4)+N_inter; ... 
        i_para_n(4)+N_inter+1,i_para_n(4)+N_inter*2; ...
        i_para_n(4)+(2*N_inter)+1,i_para_n(4)+(3*N_inter);...
        i_para_n(4)+(3*N_inter)+1,i_para_n(4)+(4*N_inter);...
        i_para_n(4)+(4*N_inter)+1,i_para_n(4)+(5*N_inter);...
        i_para_n(4)+(5*N_inter)+1,i_para_n(4)+(6*N_inter)];
    i_mysa_b = [i_inter(12)+1,i_inter(12)+N_inter, ...
                i_inter(12)+N_inter+1,i_inter(12)+N_inter*2];
    i_flut_b = [i_mysa_b(4)+1,i_mysa_b(4)+N_inter, ... 
        i_mysa_b(4)+N_inter+1,i_mysa_b(4)+N_inter*2];
    i_inter_b = [i_flut_b(4)+1,i_flut_b(4)+N_inter; ... 
        i_flut_b(4)+N_inter+1,i_flut_b(4)+N_inter*2; ...
        i_flut_b(4)+(2*N_inter)+1,i_flut_b(4)+(3*N_inter);...
        i_flut_b(4)+(3*N_inter)+1,i_flut_b(4)+(4*N_inter);...
        i_flut_b(4)+(4*N_inter)+1,i_flut_b(4)+(5*N_inter);...
        i_flut_b(4)+(5*N_inter)+1,i_flut_b(4)+(6*N_inter)];
    
   
    %create IC
    IC = zeros(i_inter_b(6,2),1);
    IC(1:N_nodes) = -80;
    IC(i_mysa(1):i_flut(4)) = -80;
    IC(i_inter(1,1):i_inter(6,2)) = -80;
    [m_alpha,m_beta] = m_ab(-80);
    [h_alpha,h_beta] = h_ab(-80);
    [p_alpha,p_beta] = p_ab(-80);
    [s_alpha,s_beta] = s_ab(-80);
    IC(i_para_m(1):i_para_m(2)) = m_alpha/(m_alpha+m_beta);
    IC(i_para_h(1):i_para_h(2)) = h_alpha/(h_alpha+h_beta);
    IC(i_para_p(1):i_para_p(2)) = p_alpha/(p_alpha+p_beta);
    IC(i_para_s(1):i_para_s(2)) = s_alpha/(s_alpha+s_beta);

    options = CVodeSetOptions('RelTol',1.e-3,...
                          'AbsTol',1.e-4);

    Istim = zeros(N_nodes,1);
    dt = 0;
    
    CVodeInit(@odeCVode, 'BDF', 'Newton', 0, IC, options);
    
    dtout = 0.01;
    tout = dtout;
    t = [0.0];
    Y = [IC];
    for i = 1:dur/dtout
        [status, t1, Y1] = CVode(tout,'Normal');
        t = [t, t1];
        Y = [Y, Y1];
        tout = tout + dtout;
    end
    CVodeFree;
    
    csvwrite('debug_dump.csv', [t; Y]');
    Y = Y';

    figure(2);
    for i = 1:N_nodes
        V(i,:) = Y(:,i) - 40*(i-1);
    end
    plot(t,V);
    
    figure(3);
    for i = 1:N_nodes
        V(i,:) = Y(:,i) - 5*(i-1);
    end
    plot(t,V);
    
    function [dY,flag,new_data] = odeCVode(t,Y)
        dY = odeMcIntyr(t,Y);
        flag = [0];
        new_data = [];
    end
    
    function dY = odeMcIntyr(t,Y)
        if exist('stim','var') ==0
            if t >= stim_start && t <= stim_end
                V_e = V_stim;
                Xlr = Xlr_stim;
            else
                V_e = zeros(i_inter(6,2),1);
                Xlr = zeros(2,1);
                Istim(11) = 0;
            end
        end
        if t > dt
            
            dt=dt+0.1
        end
        inter = zeros(N_inter,6);
        inter_b = zeros(N_inter,6);
        
        %V^i
        node = Y(i_node(1):i_node(2));
        para_m = Y(i_para_m(1):i_para_m(2));
        para_h = Y(i_para_h(1):i_para_h(2));
        para_p = Y(i_para_p(1):i_para_p(2));
        para_s = Y(i_para_s(1):i_para_s(2));
        mysa_l = Y(i_mysa(1):i_mysa(2));
        mysa_r = Y(i_mysa(3):i_mysa(4));
        flut_l = Y(i_flut(1):i_flut(2));
        flut_r = Y(i_flut(3):i_flut(4));
        para_n_l = Y(i_para_n(1):i_para_n(2));
        para_n_r = Y(i_para_n(3):i_para_n(4));
        inter(:,1) = Y(i_inter(1,1):i_inter(1,2));
        inter(:,2) = Y(i_inter(2,1):i_inter(2,2));
        inter(:,3) = Y(i_inter(3,1):i_inter(3,2));
        inter(:,4) = Y(i_inter(4,1):i_inter(4,2));
        inter(:,5) = Y(i_inter(5,1):i_inter(5,2));
        inter(:,6) = Y(i_inter(6,1):i_inter(6,2));
       
        %V^p
        mysa_l_b = Y(i_mysa_b(1):i_mysa_b(2));
        mysa_r_b = Y(i_mysa_b(3):i_mysa_b(4));
        flut_l_b = Y(i_flut_b(1):i_flut_b(2));
        flut_r_b = Y(i_flut_b(3):i_flut_b(4));
        inter_b(:,1) = Y(i_inter_b(1,1):i_inter_b(1,2));
        inter_b(:,2) = Y(i_inter_b(2,1):i_inter_b(2,2));
        inter_b(:,3) = Y(i_inter_b(3,1):i_inter_b(3,2));
        inter_b(:,4) = Y(i_inter_b(4,1):i_inter_b(4,2));
        inter_b(:,5) = Y(i_inter_b(5,1):i_inter_b(5,2));
        inter_b(:,6) = Y(i_inter_b(6,1):i_inter_b(6,2)); 
 
        %if E^e is assumed to be constant d(V^p) equals d(E^p)
        mysa_l_b_e = mysa_l_b;
        mysa_r_b_e = mysa_r_b;
        flut_l_b_e = flut_l_b;
        flut_r_b_e = flut_r_b;
        inter_b_e = inter_b;
        

        %E^i
        node_e = node;
        mysa_l_e = mysa_l + mysa_l_b_e;
        mysa_r_e = mysa_r + mysa_r_b_e;
        flut_l_e = flut_l + flut_l_b_e;
        flut_r_e = flut_r + flut_r_b_e;
        inter_e = inter + inter_b_e;
        
        [dnode,dpara_m,dpara_h,dpara_p,dpara_s] = nodeEq(node,para_m, ...
            para_h,para_p,para_s,node_e,mysa_l_e,mysa_r_e,...
            V_e(i_node(1):i_node(2)),V_e(i_mysa(1):i_mysa(2)),...
            V_e(i_mysa(3):i_mysa(4)));
        
        [dmysa_l,dmysa_l_b] = mysaEq(mysa_l,mysa_l_b,...
            mysa_l_e, node_e(2:N_nodes), flut_l_e, ...
            mysa_l_b_e, 0, flut_l_b_e,V_e(i_mysa(1):i_mysa(2)),...
            V_e(2:N_nodes),V_e(i_flut(1):i_flut(2)));
        
        [dmysa_r,dmysa_r_b] = mysaEq(mysa_r,mysa_r_b, ... 
            mysa_r_e, node_e(1:N_inter), flut_r_e,...
            mysa_r_b_e, 0, flut_r_b_e,V_e(i_mysa(3):i_mysa(4)), ...
            V_e(1:N_inter),V_e(i_flut(3):i_flut(4)));
        
        [dflut_l,dflut_l_b] = flutEq(flut_l,flut_l_b,...
            flut_l_e, mysa_l_e ,inter_e(:,1),...
            flut_l_b_e,mysa_l_b_e,inter_b_e(:,1),...
            V_e(i_flut(1):i_flut(2)),V_e(i_mysa(1):i_mysa(2)), ...
            V_e(i_inter(1,1):i_inter(1,2)));
        
        [dflut_r,dflut_r_b] = flutEq(flut_r,flut_r_b,...
            flut_r_e, mysa_r_e, inter_e(:,6),...
            flut_r_b_e, mysa_r_b_e, inter_b_e(:,6),...
            V_e(i_flut(3):i_flut(4)),V_e(i_mysa(3):i_mysa(4)), ...
            V_e(i_inter(6,1):i_inter(6,2)));
        
        dpara_n_l = zeros(N_inter,1);
        dpara_n_r = zeros(N_inter,1);
        
        e_inter = zeros(N_inter,6);
        
        e_inter(:,1) = V_e(i_inter(1,1):i_inter(1,2));
        e_inter(:,2) = V_e(i_inter(2,1):i_inter(2,2));
        e_inter(:,3) = V_e(i_inter(3,1):i_inter(3,2));
        e_inter(:,4) = V_e(i_inter(4,1):i_inter(4,2));
        e_inter(:,5) = V_e(i_inter(5,1):i_inter(5,2));
        e_inter(:,6) = V_e(i_inter(6,1):i_inter(6,2));
        
        [dinter,dinter_b] = interEq(inter,inter_b,...
            inter_e, flut_l_e, flut_r_e, ...
            inter_b_e, flut_l_b_e, flut_r_b_e, e_inter, ...
            V_e(i_flut(1):i_flut(2)),V_e(i_flut(3):i_flut(4)));
        
        
        
        %finally assemble derivatives into an
        dY=[dnode;dpara_m;dpara_h;dpara_p;dpara_s;dmysa_l;dmysa_r;...
            dflut_l;dflut_r;dpara_n_l;dpara_n_r;dinter(:,1); ...
            dinter(:,2);dinter(:,3);dinter(:,4);dinter(:,5);...
            dinter(:,6);dmysa_l_b;dmysa_r_b;dflut_l_b;dflut_r_b;...
            dinter_b(:,1);dinter_b(:,2);dinter_b(:,3);...
            dinter_b(:,4);dinter_b(:,5);dinter_b(:,6)];
        
    end

    function [dV,dm,dh,dp,ds] = nodeEq(V,m,h,p,s,...
            Ei, EiMl,EiMr,Vex,VexMl,VexMr)
        [I,dm,dh,dp,ds] = axnode2(V,m,h,p,s);
        Iax = axialI(Ei,[vrest;EiMl],[EiMr;vrest],r_node,r_mysa,r_mysa);
        Iex = axialI(Vex,[Xlr(1);VexMl],[VexMr;Xlr(2)],...
            r_node,r_mysa,r_mysa);
        dV = (-I-Iax+Istim-Iex)./c_node;
       
    end

    function [dV,dVp] = interEq(V, Vp, Ei, EiFl, EiFr, Ep, EpFl,...
            EpFr,Vex,VexFl,VexFr)
        dV = zeros(N_inter,6);
        dVp = zeros(N_inter,6);
        
        Iax1 = axialI(Ei(:,1),EiFl,Ei(:,2),r_inter,r_flut,r_inter);
        Ipx1 = axialI(Ep(:,1),EpFl,Ep(:,2),r_px,r_pn2,r_px);
        Iex1 = axialI(Vex(:,1),VexFl,Vex(:,2),r_inter,r_flut,r_inter);
        [dV(:,1), dVp(:,1)] = compartment(V(:,1),Vp(:,1),Iax1,Ipx1,Iex1,...
             vrest, c_inter, c_inter_m, g_inter, g_inter_m);
        
        Iax6 = axialI(Ei(:,6),EiFr,Ei(:,5),r_inter,r_flut,r_inter);
        Ipx6 = axialI(Ep(:,6),EpFr,Ep(:,5),r_px,r_pn2,r_px);
        Iex6 = axialI(Vex(:,6),VexFr,Vex(:,5),r_inter,r_flut,r_inter);
        [dV(:,6), dVp(:,6)] = compartment(V(:,6),Vp(:,6),Iax6,Ipx6,Iex6,...
             vrest, c_inter, c_inter_m, g_inter, g_inter_m);
        
        for j = 2:5
            Iax = axialI(Ei(:,j),Ei(:,j-1),Ei(:,j+1),...
                r_inter,r_inter,r_inter);
            Ipx = axialI(Ep(:,j),Ep(:,j-1),Ep(:,j+1),r_px,r_px,r_px);
            Iex = axialI(Vex(:,j),Vex(:,j-1),Vex(:,j+1),...
                r_inter,r_inter,r_inter);
            [dV(:,j), dVp(:,j)] = compartment(V(:,j),Vp(:,j), ...
                Iax,Ipx,Iex,vrest,c_inter,c_inter_m,g_inter,g_inter_m);
        end
        
    end

    function [dV,dVp] = flutEq(V, Vp, Ei, EiM, EiI, Ep, EpM, EpI,...
            Vex,VexM,VexI)
       Iax = axialI(Ei,EiM,EiI,r_flut,r_mysa,r_inter);
       Ipx = axialI(Ep,EpM,EpI,r_pn2,r_pn1,r_px);
       Iex = axialI(Vex,VexM,VexI,r_flut,r_mysa,r_inter);
       
       [dV, dVp] = compartment(V,Vp, Iax, Ipx, Iex, vrest, c_flut, ...
           c_flut_m, g_flut, g_flut_m);
                                                  
    end

    function [dV, dVp] = mysaEq(V,Vp,Ei,EiN,EiF,Ep,EpN,EpF,Vex,VexN,VexF)
        Iax = axialI(Ei,EiN,EiF,r_mysa,r_node,r_flut);
        Ipx = axialI(Ep,EpN,EpF,r_pn1,r_pn0,r_pn2);
        Iex = axialI(Vex,VexN,VexF,r_mysa,r_node,r_flut);
        [dV, dVp] = compartment(V,Vp, Iax, Ipx, Iex, vrest, c_mysa, ...
           c_mysa_m, g_mysa, g_mysa_m);
    end

    function [dV, dVp] = compartment(V, Vp, Iaxonal, Iperiaxonal, Iex, ...
                                     epas, cmem, cmy, gmem, gmy)
        IPas = gmem.*(V - epas);
        Imyelin = gmy.*(Vp);
        ICmem = -IPas -Iaxonal-Iex;
        ICmyelin = - Imyelin -Iperiaxonal -Iaxonal-Iex;
        
        dV = (1./cmem).*(ICmem);
        dVp= (1./cmy).*(ICmyelin);
    end

    function I = axialI(V,V1,V2,r,r1,r2)
        I = (V-V1)./(r/2+r1/2)+(V-V2)./(r/2+r2/2);
    end

    % axnode: calculation of the currents of the axon
    function [I,dm,dh,dp,ds] = axnode(V,m,h,p,s)

        m_alpha = (6.57 .* (V+21.4))./(1-exp(-(V+21.4)./10.3));
        m_beta = (0.304 .* (-(V+25.7)))./(1-exp((V+25.7)./9.16));
        h_alpha = (0.34 .* (-(V+114)))./(1-exp((V+114)./11));
        h_beta = 12.6./(1+exp(-(V+31.8)./13.4));

        p_alpha = (0.0353 .* (V+27))./(1-exp(-(V+27)./10.2));
        p_beta = (0.000883 .* (-(V+34)))./(1-exp((V+34)./10));

        s_alpha = 0.3./(1+exp((V+53)./-5));
        s_beta = 0.03./(1+exp((V+90)./-1));

        %first derivatives of m, h, p, s
        dm = dpdt(m_alpha,m_beta,m);
        dh = dpdt(h_alpha,h_beta,h);
        dp = dpdt(p_alpha,p_beta,p);
        ds = dpdt(s_alpha,s_beta,s);

        I_Naf = g_naf.*m.^3.*h.*(V-e_na);       %Fast Sodium current
        I_Nap = g_nap.*p.^3.*(V-e_na);          %Persistent Sodium current
        I_Ks = g_k.*s.*(V-e_k);                 %Slow Potassium current
        I_Lk = g_l*(V-e_l);                     %Leakage current
        I = I_Naf + I_Nap + I_Ks + I_Lk;        %Sum of all nodal currents
    end

    function [I,dm,dh,dp,ds] = axnode2(V,m,h,p,s)
        
        [m_alpha,m_beta] = m_ab(V);
        [h_alpha,h_beta] = h_ab(V);
        [p_alpha,p_beta] = p_ab(V);
        [s_alpha,s_beta] = s_ab(V);
        
        %first derivatives of m, h, p, s
        dm = dpdt(m_alpha,m_beta,m);
        dh = dpdt(h_alpha,h_beta,h);
        dp = dpdt(p_alpha,p_beta,p);
        ds = dpdt(s_alpha,s_beta,s);

        I_Naf = g_naf.*m.^3.*h.*(V-e_na);       %Fast Sodium current
        I_Nap = g_nap.*p.^3.*(V-e_na);          %Persistent Sodium current
        I_Ks = g_k.*s.*(V-e_k);                 %Slow Potassium current
        I_Lk = g_l*(V-e_l);                     %Leakage current
        I = I_Naf + I_Nap + I_Ks + I_Lk;        %Sum of all nodal currents
    end

    % flutPotassim: flut potassium current
    function [I,dn] = flutPotassium(V,n)
        n_alpha = (0.0462 .* (V+83.2))./(1-exp(-(V+83.2)./1.1));
        n_beta = (0.0824 .* (-(V+66))) ./ (1-exp((V+66)./10.5));
        
        dn = dpdt(n_alpha,n_beta,n);
        
        I_Kf = g_kf.*n.^4.*(V-e_k);
        
        I = I_Kf; 
    end

    function [m_alpha,m_beta] = m_ab(V)
        m_alpha = (1.86 .* (V+21.4))./(1-exp(-(V+21.4)./10.3)) * q10_1;
        m_beta = (0.086 .* (-(V+25.7)))./(1-exp((V+25.7)./9.16)) * q10_1;
    end

    function [h_alpha,h_beta] = h_ab(V)
        h_alpha = (0.062 .* (-(V+114)))./(1-exp((V+114)./11)) * q10_2;
        h_beta = 2.3./(1+exp(-(V+31.8)./13.4)) * q10_2;
    end

    function [p_alpha,p_beta] = p_ab(V)
        p_alpha = (0.01 .* (V+27))./(1-exp(-(V+27)./10.2)) * q10_1;
        p_beta = (0.00025 .* (-(V+34)))./(1-exp((V+34)./10)) * q10_1;
    end

    function [s_alpha,s_beta] = s_ab(V)
        s_alpha = 0.3./(1+exp((V+53)./-5))*q10_3;
        s_beta = 0.03./(1+exp((V+90)./-1))*q10_3;
    end
    
    % dpdt: calculates the derivative of the of the parameter according to
    %       alpha, beta and the previous value
    function dp = dpdt(alpha, beta, para)
        dp = alpha.*(1-para)-beta.*para;
    end

    function [rax,rpx,cmem,cmy,gpas,gmy] = ...
            paracomp(diameter,length,space, fiberDia, c, r, g, nl, xc, xg)
       %args must be in um, ohm*cm and uF respectively
       rax = calcResAxial(diameter,length,r);
       rpx = calcResPeriax(diameter,length,space,r);
       cmem = calcCapacity(diameter, length, c);
       cmy = calcMyelinCap(fiberDia, length, xc, nl);
       gpas = calcConductance(diameter, length, g);
       gmy = calcMyelinCond(fiberDia, length, xg, nl);
    end

    function rax = calcResAxial(diameter, length, r)
       %um and Ohm*cm
       a=pi*diameter^2;
       rax = calcRes(a,length,r);
    end
    
    function rpx = calcResPeriax(diameter, length, space, r)
        %um and Ohm*cm
        a = pi*((diameter+(2*space))^2-diameter^2);
        rpx = calcRes(a,length,r);
    end

    function res = calcRes(area, length, r)

        ra = r*1e-5;     %GOhm*um
        res = (4*(length)*ra)/area;
    end

    function c = calcMyelinCap(fiberDiameter, length, xc, nl)
        xc = xc/(nl*2);
        c = calcCapacity(fiberDiameter, length, xc);
        %c is in uF
    end

    function c = calcCapacity(diameter, length, cap)
       %um and uF/cm^2
       cap = cap*1e-2;   %pF/um^2 
       c = cap*diameter*length*pi;
       %c is in uF
    end

    function gmy = calcMyelinCond(fiberDiameter, length, xg, nl)
       xg = xg/(nl*2);
       gmy = calcConductance(fiberDiameter, length, xg);
    end

    function g = calcConductance(diameter, length, gi)
        %in S/cm^2 and um
        gi = gi*1e1; %nS/um^2
        g = gi*diameter*length*pi;
    end

    function [Ve,N,x_af,af,Vlr] = interpolate(file)
        data = importdata(file);
        % to mV
        Ve_pulse = 1e3*data(:,4);
        % to cm
        x = 100*data(:,1);
        y = 100*data(:,2);
        z = 100*data(:,3);
        s(1) = 0;
        for i=1:length(x)-1
            s(i+1) = s(i) + sqrt((x(i+1)-x(i))^2 + (y(i+1)-y(i))^2 +...
                (z(i+1)-z(i))^2);
        end
        n = floor(s(length(x)-1)/(deltax*1e-4))+16;
        N = n+1;
        
        half = 0;
        
        if half == 0
            [x_n,x_m,x_f,x_i] = calcX(N);
            x_n=x_n-8*(deltax+1)*1e-4;
            x_m=x_m-8*(deltax+1)*1e-4;
            x_f=x_f-8*(deltax+1)*1e-4;
            x_i=x_i-8*(deltax+1)*1e-4;
           
        end
        if half == 1
            [x_n,x_m,x_f,x_i] = calcX(floor(N/2));
            x_n = x_n + floor(N/2)*(deltax+1)*1e-4;
            x_m = x_m + floor(N/2)*(deltax+1)*1e-4;
            x_f = x_f + floor(N/2)*(deltax+1)*1e-4;
            x_i = x_i + floor(N/2)*(deltax+1)*1e-4;
            N = floor(N/2);
            n = N-1;
        end
        if half == 2
            [x_n,x_m,x_f,x_i] = calcX(floor(N/2));
            N = floor(N/2);
            n = N-1;
        end  
        
        xlr=[x_n(1)-2e-4,x_n(N)+2e-4];
        
        displacment = -1;
        x_n=x_n+displacment*1e-4*deltax/10;
        x_m=x_m+displacment*1e-4*deltax/10;
        x_f=x_f+displacment*1e-4*deltax/10;
        x_i=x_i+displacment*1e-4*deltax/10;
        xlr=xlr+displacment*1e-4*deltax/10;
        
        Vlr = interp1(s,Ve_pulse,xlr,'linear','extrap');
        
        Ve_n = interp1(s,Ve_pulse,x_n,'linear','extrap');
        Ve_m = [interp1(s,Ve_pulse,x_m(:,1),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_m(:,2),'linear','extrap')];
        Ve_f = [interp1(s,Ve_pulse,x_f(:,1),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_f(:,2),'linear','extrap')];
        Ve_i = [interp1(s,Ve_pulse,x_i(:,1),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_i(:,2),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_i(:,3),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_i(:,4),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_i(:,5),'linear','extrap'); ...
                interp1(s,Ve_pulse,x_i(:,6),'linear','extrap')];
        Ve = [Ve_n;zeros(N*4,1);Ve_m;Ve_f;zeros((N-1)*2,1);Ve_i];
        x_af = [];
        af = [];
        expot = [];
        
         for i = 1:n
             
             x_af = [x_af,x_n(i),x_m(i,2),x_f(i,2),x_i(i,6),...
                 x_i(i,5),x_i(i,4),x_i(i,3),x_i(i,2),x_i(i,1),...
                 x_f(i,1),x_m(i,1)];
             expot = [expot,Ve_n(i),Ve_m(i+n),Ve_f(i+n),Ve_i(i+5*n),...
                 Ve_i(i+4*n),Ve_i(i+3*n),Ve_i(i+2*n),Ve_i(i+n),Ve_i(i),...
                 Ve_f(i),Ve_m(i)];
         end
         x_af = [x_af,x_n(N)];
         expot = [expot,Ve_n(N)];
        
         figure(1);
         plot(x_af,expot);
        
    end

    function [x_n,x_m1,x_f1,x_i1] = calcX(N)
        x_n(1) = 0.5*1e-4;
        x_m(1,1) = x_n(1) + 0.5*1e-4 + mysalength/2*1e-4;
        x_m(1,2) = x_n(1) + (1+deltax)*1e-4 -mysalength/2*1e-4;
        x_f(1,1) = x_m(1,1) + flutlength/2*1e-4 + mysalength/2*1e-4;
        x_f(1,2) = x_m(1,2) - flutlength*1e-4 - mysalength/2*1e-4;
        x_i = zeros(N-1,6);
        x_i(1,1) = x_f(1,1) + flutlength/2*1e-4 +interlength/2*1e-4;
        for j = 2:6
            x_i(1,j) = x_i(1,1) + (j-1)*interlength*1e-4;
        end
        for i=2:N
            x_n(i) = x_n(i-1) + deltax*1e-4+1e-4;
        end
        N
        for i=2:N-1
            x_m(i,1) = x_m(i-1,1) + (1+deltax)*1e-4;
            x_m(i,2) = x_m(i-1,2) + (1+deltax)*1e-4;
            x_f(i,1) = x_f(i-1,1) + (1+deltax)*1e-4;
            x_f(i,2) = x_f(i-1,2) + (1+deltax)*1e-4;
            for j = 1:6
                x_i(i,j) = x_i(i-1,j) + (1+deltax)*1e-4;
            end 
        end
        
        x_m1(:,1) = x_m(:,2);
        x_m1(:,2) = x_m(:,1);
        x_f1(:,1) = x_f(:,2);
        x_f1(:,2) = x_f(:,1);
        x_i1=zeros(N-1,6);
        for i=1:6
            x_i1(:,i) = x_i(:,7-i);
        end
        x_n=x_n';
    end
end

