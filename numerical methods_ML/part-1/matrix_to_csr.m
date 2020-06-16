function [values, colind, rowptr] = matrix_to_csr(A)
  nz = 1;
  index_rowptr = 1;
  first = 0;
  [n n] = size(A);
  for i = 1 : n
    first = 1;
    for j = 1 : n
      if A(i, j) != 0
        values(nz) = A(i, j);
        colind(nz) = j;
        if first == 1
          rowptr(index_rowptr) = nz;
          index_rowptr++;
          first = 0;
        endif
        nz++;
      endif
    endfor
  endfor
  rowptr(index_rowptr) = nz;
endfunction