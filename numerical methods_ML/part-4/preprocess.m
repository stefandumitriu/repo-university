function [X, y] = preprocess(path_to_dataset, histogram, count_bins)
  
  #cats images
  path_to_imgs_cats = strcat(path_to_dataset, 'cats/');
  path_to_imgs_cats = strcat(path_to_imgs_cats,  '*jpg');
	img_files_cats = dir(path_to_imgs_cats);
  path_to_dataset_cats = strcat(path_to_dataset, 'cats/');
	n = length(img_files_cats);
  
	for i = 1:n
		l = 1:length(img_files_cats(i).name);
		imgs_cats(i, l) = img_files_cats(i).name;
	endfor
  
  [n m] = size(imgs_cats);
  
  #not cats images
  path_to_imgs_not_cats = strcat(path_to_dataset, 'not_cats/');
  path_to_imgs_not_cats = strcat(path_to_imgs_not_cats,  '*jpg');
	img_files_not_cats = dir(path_to_imgs_not_cats);
  path_to_dataset_not_cats = strcat(path_to_dataset, 'not_cats/');
	n1 = length(img_files_not_cats);
  
  
	for i = 1 : n1
		l = 1:length(img_files_not_cats(i).name);
		imgs_not_cats(i, l) = img_files_not_cats(i).name;
	endfor
  
	imgs_not_cats = char(imgs_not_cats);
  [n1 m1] = size(imgs_not_cats);
  
  X = zeros(n + n1, count_bins * 3);
  y = zeros(n + n1, 1);
  rgb = hsv = 0;
  if strcmp("RGB", histogram) == 1
    rgb = 1;
  else
    hsv = 1;
  endif
  
  for i = 1 : n
    y(i) = 1;
    img_path = strcat(path_to_dataset_cats, imgs_cats(i, :));
    if rgb == 1
      X(i, :) = rgbHistogram(img_path, count_bins);
    else
      X(i, :) = hsvHistogram(img_path, count_bins);
    endif
  endfor
  
  for i = 1 : n1
    y(i + n) = -1;
    img_path = strcat(path_to_dataset_not_cats, imgs_not_cats(i, :));
    if rgb == 1
      X(i + n, :) = rgbHistogram(img_path, count_bins);
    else
      X(i + n, :) = hsvHistogram(img_path, count_bins);
    endif
  endfor
  
endfunction
