function [sol] = hsvHistogram(path_to_image, count_bins)
  img = imread(path_to_image);
  [H S V] = rgb_hsv(img(:,:,1), img(:,:,2), img(:,:,3));
  [n m] = size(H);
  img_HSV = zeros(n, m, 3);
  img_HSV(:,:,1) = H;
  img_HSV(:,:,2) = S;
  img_HSV(:,:,3) = V;
  binranges = 0:(1.01/count_bins):1.01;
  vect_hist = length(count_bins * 3);
  for col_ind = 1 : 3
    hist_ind = (col_ind - 1) * count_bins;
    hist = histc(img_HSV(:,:,col_ind), binranges);
    [n m] = size(hist);
    for i = 1 : n
      vect_hist(hist_ind + i) = sum(hist(i, : ));
    endfor
  endfor
  sol = vect_hist(1 : count_bins * 3);
end