function [w] = learn(X, y)
  [n m] = size(X);
  bias_vector = zeros(n, 1);
  for i = 1 : n
    bias_vector(i) = 1;
  endfor
  X = [X bias_vector];
  [Q R] = Householder(X);
  b = Q' * y;
  w = SST(R, b);
end
