function [H S V] = rgb_hsv(R, G, B)
  [n m] = size(R);
  H = S = V = zeros(n, m);
  R1 = double(R) / double(255);
  G1 = double(G) / double(255);
  B1 = double(B) / double(255);
  Cmax = max(R1, G1);
  Cmax = max(Cmax, B1);
  Cmin = min(R1, G1);
  Cmin = min(Cmin, B1);
  delta = Cmax - Cmin;
  S = delta ./ Cmax;
  V = Cmax;
  H = zeros(n,m);
  difR = Cmax - R1;
  GB = zeros(n, m);
  GB(find(difR==0)) = G1(find(difR==0)) - B1(find(difR==0));
  H(find(difR==0 & delta != 0)) = 60 * mod(GB(find(difR==0 & delta != 0)) ./ delta(find(difR==0 & delta != 0)), 6);
  difG = Cmax - G1;
  BR = zeros(n, m);
  BR(find(difG==0)) = B1(find(difG==0)) - R1(find(difG==0));
  H(find(difG==0 & delta != 0)) = 60 * (BR(find(difG==0 & delta != 0)) ./ delta(find(difG==0 & delta != 0)) + 2);
  difB = Cmax - B1;
  RG = zeros(n, m);
  RG(find(difB==0)) = R1(find(difB==0)) - G1(find(difB==0));
  H(find(difB==0 & delta != 0)) = 60 * (RG(find(difB==0 & delta != 0)) ./ delta(find(difB==0 & delta != 0)) + 4);
  H = H / 360; 
endfunction
