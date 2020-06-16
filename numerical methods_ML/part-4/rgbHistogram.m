function [sol] = rgbHistogram(path_to_image, count_bins)
  img = imread(path_to_image);
  R = img(:,:,1);
  G = img(:,:,2);
  B = img(:,:,3);
  [H S V] = rgb_hsv(R, G, B);
  binranges = 0:(256/count_bins):256;
  vect_hist = length(count_bins * 3);
  for col_ind = 1 : 3
    hist_ind = (col_ind - 1) * count_bins;
    hist = histc(img(:,:,col_ind), binranges);
    [n m] = size(hist);
    for i = 1 : n
      vect_hist(hist_ind + i) = sum(hist(i, : ));
    endfor
  endfor
  sol = vect_hist(1 : count_bins * 3);
endfunction