function [cost] = compute_cost_pc(points, centroids)
  [N D] = size(points);
  [NC D] = size(centroids);
  cost = 0;
  for i = 1 : N
    min_dist = inf;
    for j = 1 : NC
      dist = 0;
      dist_v = zeros(D);
      dist_v = points(i, : ) - centroids(j, : );
      dist = norm(dist_v);
      if dist < min_dist
        min_dist = dist;
      endif
    endfor
    cost = cost + min_dist;
  endfor
endfunction

