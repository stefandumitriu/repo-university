function [centroids] = clustering_pc(points, NC)
  [N D] = size(points);
  centroids = zeros(NC, D);
  NC_list = zeros(NC, N);
  #cate elemente are fiecare cluster
  NC_col = zeros(1, NC);
  
  #initializam lista cu punctele din fiecare cluster
  for i = 1 : N
    if mod(i, NC) == 0
      NC_col(NC) = NC_col(NC) + 1;
      NC_list(NC, NC_col(NC)) = i;
    else
      NC_col(mod(i, NC)) = NC_col(mod(i, NC)) + 1;
      NC_list(mod(i, NC), NC_col(mod(i, NC))) = i;
    endif
  endfor
  
  #calculam cetroizii initiali
  for d = 1 : D
    for i = 1 : NC
      S = 0;
      for k = 1 : NC_col(i)
        S = S + points(NC_list(i, k), d);
      endfor
      centroids(i, d) = S / NC_col(i);
    endfor
  endfor
  
  new_NC_list = zeros(NC, N);
  new_NC_col = zeros(1, NC);
  while isequal(new_NC_list, NC_list) == false
    if isequal(new_NC_list, zeros(NC, N)) == false
      NC_list = new_NC_list;
      NC_col = new_NC_col;
    endif
    new_NC_list = zeros(NC, N);
    new_NC_col = zeros(1, NC);
    for i = 1 : N
      min_dist = inf;
      min_dist_index = 0;
      for j = 1 : NC
        dist = 0;
        dist_v = zeros(d);
        dist_v = points(i,:) - centroids(j,:);
        dist = norm(dist_v);
        if dist < min_dist
          min_dist = dist;
          min_dist_index = j;
        endif
      endfor
      new_NC_col(min_dist_index) = new_NC_col(min_dist_index) + 1;
      new_NC_list(min_dist_index, new_NC_col(min_dist_index)) = i;
    endfor
    
    for d = 1 : D
    for i = 1 : NC
      S = 0;
      for k = 1 : new_NC_col(i)
        S = S + points(new_NC_list(i, k), d);
      endfor
      if new_NC_col(i) != 0
        centroids(i, d) = S / new_NC_col(i);
      else
        centroids(i, d) = 0;
      endif
    endfor
  endfor
  endwhile
endfunction
