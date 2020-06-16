function [Q, R] = Householder(A)
    
  [m n] = size(A);
	Q = eye(m);
	
	for p = 1 : min(m-1,n)
		sigma = -norm(A(p:m, p));
		if A(p, p) < 0
			sigma = -sigma;
		endif

		vp(1:m, 1) = 0;
		vp(p) = A(p, p) + sigma;
		vp(p + 1:m) = A(p + 1:m, p);
    
		beta = sigma * vp(p);
	
		if beta ~= 0
      A(p, p) = -sigma;
		  A(p + 1:m, p) = 0;
		  
      for j = p + 1 : n
		    t = vp(p:m)' * A(p:m, j) / beta;
		    A(p:m, j) = A(p:m, j) - t * vp(p:m);
		  endfor
	
		  for j = 1:m
		    t = vp(p:m)' * Q(p:m, j) / beta;
		    Q(p:m, j) = Q(p:m, j) - t * vp(p:m);
		  endfor
     endif
  endfor
  
	R = A;
	Q = Q';
  
endfunction