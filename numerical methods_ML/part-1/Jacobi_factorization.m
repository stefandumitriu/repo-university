function [G_J, c_J] = Jacobi_factorization(A, b)
  D = diag(diag(A));
  L = tril(A, -1);
  U = triu(A, 1);
  P = L + U;
  N = inv(D);
  G_J = -N * P;
  c_J = N * b;
endfunction
