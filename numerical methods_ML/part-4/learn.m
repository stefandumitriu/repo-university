function [w] = learn(X, y, lr, epochs)
  
  [n m] = size(X);
  bias_column = ones(n,1);
  X = [X bias_column];
  [n m] = size(X);
  for i = 1 : m - 1
    X(:,i) = (X(:, i) - mean(X(:, i))) / std(X(:, i));
  endfor
  
  w = 0.2 * rand(m, 1) - 0.1;
  
  for epoch = 1 : epochs
    rand_rows = randperm(n, 64);
    Xbatch = X(rand_rows, :);
    ybatch = y(rand_rows);
    for i = 1 : m
      S = 0;
      for j = 1 : 64
        S = S + (Xbatch(j, :) * w - ybatch(j)) * Xbatch(j, i);
      endfor
      w(i) = w(i) - lr * (1 / n) * S;
    endfor
  endfor
endfunction
