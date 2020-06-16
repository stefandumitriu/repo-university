function [A, b] = generate_probabilities_system(rows)
  rowsA = (rows * (rows + 1)) / 2;
  A = zeros(rowsA);
  b = zeros([rowsA, 1]);
  
  #generare b
  for i = 1 : rowsA
    if i >= ((rows - 1) * rows) / 2 + 1
      b(i) = 1;
    endif
  endfor
  
  #generare diag. principala: numarul de "legaturi" cu alte intersectii
  #4 -> colturile triunghiului; 5-> exterioare(au legatura cu marginea)
  #6-> interioare (sunt inconjurate doar de numere)
  A(1, 1) = 4;
  A(rowsA, rowsA) = 4;
  for i = 2 : rowsA - 1
    A(i, i) = 5;
  endfor
  A(rowsA - rows + 1, rowsA - rows + 1) = 4;
  for n = 3 : rows - 1
    for k = (n * (n - 1)) / 2 + 2 : (n * (n + 1)) / 2 - 1
      A(k, k) = 6;
    endfor
  endfor
  
  #generare legaturi dintre numere
  #-1 la Aij, Aji daca i conectat cu j in diagrama
  for n = 2 : rows
    for k = (n * (n - 1)) / 2 + 1 : (n * (n + 1)) / 2
      if (k - n) > ((n - 2) * (n - 1)) / 2
        A(k, k - n) = -1;
        A(k - n, k) = -1;
      endif
      if (k - n + 1) <= ((n - 1) * n) / 2
        A(k, k - n + 1) = -1;
        A(k - n + 1, k) = -1;
      endif
      if k - 1 > (n * (n - 1)) / 2
        A(k, k - 1) = -1;
        A(k - 1, k) = -1;
      endif
      if k + 1 <= (n * (n + 1)) / 2
        A(k, k + 1) = -1;
        A(k + 1, k) = -1;
      endif
    endfor
  endfor
  
endfunction