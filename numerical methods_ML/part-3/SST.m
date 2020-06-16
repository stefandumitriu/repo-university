function [x] = SST(A, b)
  [n m] = size(A);
  x = zeros(1, m);
  min_ind = min([n m]);
  x(min_ind) = b(min_ind) / A(min_ind, min_ind);
  for i = (min_ind - 1) : -1 : 1
    S = 0;
    for j = i + 1 : min_ind
      S = S + x(j) * A(i, j);
    endfor
    x(i) = (b(i) - S) / A(i, i);
  endfor
  x = x';
end
    