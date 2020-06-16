function [y] = csr_multiplication(values, colind, rowptr, x)
  n = length(x);
  y = zeros(n, 1);
  for i = 1:n
    for j = rowptr(i):rowptr(i+1) - 1
      y(i) = y(i) + values(j) * x(colind(j));
    end
  end
endfunction