function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)
  x0 = zeros(1, length(c));
  y = csr_multiplication(G_values, G_colind, G_rowptr, x0);
  x = y + c;
  while norm(x - x0) > tol
    x0 = x;
    y = csr_multiplication(G_values, G_colind, G_rowptr, x0);
    x = y + c;
  endwhile
endfunction