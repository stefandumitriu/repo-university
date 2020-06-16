function [percentage] = evaluate(path_to_testset, w, histogram, count_bins)
    
  no_of_correct_predictions = 0;
  no_of_images = 0;
   #cats images
  path_to_imgs_cats = strcat(path_to_testset, 'cats/');
  path_to_imgs_cats = strcat(path_to_imgs_cats,  '*jpg');
	img_files_cats = dir(path_to_imgs_cats);
  path_to_testset_cats = strcat(path_to_testset, 'cats/');
	n = length(img_files_cats);
  
	for i = 1:n
		l = 1:length(img_files_cats(i).name);
		imgs_cats(i, l) = img_files_cats(i).name;
	endfor
  
	imgs_cats = char(imgs_cats);
  [n m] = size(imgs_cats);
  
  #not cats images
  path_to_imgs_not_cats = strcat(path_to_testset, 'not_cats/');
  path_to_imgs_not_cats = strcat(path_to_imgs_not_cats,  '*jpg');
	img_files_not_cats = dir(path_to_imgs_not_cats);
  path_to_testset_not_cats = strcat(path_to_testset, 'not_cats/');
	n1 = length(img_files_not_cats);
  
	for i = 1 : n1
		l = 1:length(img_files_not_cats(i).name);
		imgs_not_cats(i, l) = img_files_not_cats(i).name;
	endfor
  
	imgs_not_cats = char(imgs_not_cats);
  [n1 m1] = size(imgs_not_cats);
  
  no_of_images = n + n1;
   rgb = hsv = 0;
   if strcmp("RGB", histogram) == 1
      rgb = 1;
   else
      hsv = 1;
   endif
    
  for i = 1 : n
    img_path = strcat(path_to_testset_cats, imgs_cats(i, :));
    if rgb == 1
      x = rgbHistogram(img_path, count_bins);
    else
      x = hsvHistogram(img_path, count_bins);
    endif
    x(count_bins * 3 + 1) = 1;
    X(i,:) = x;
  endfor
  
  [n m] = size(X);
  for i = 1 : m - 1
    X(:,i) = (X(:, i) - mean(X(:, i))) / std(X(:, i));
  endfor
  
  for i = 1 : n
    y = w' * X(i,:)';
    if y >= 0
      no_of_correct_predictions = no_of_correct_predictions + 1;
    endif
  endfor
  
  for i = 1 : n1
    img_path = strcat(path_to_testset_not_cats, imgs_not_cats(i, :));
    if rgb == 1
      x = rgbHistogram(img_path, count_bins);
    else
      x = hsvHistogram(img_path, count_bins);
    endif
    x(count_bins * 3 + 1) = 1;
    X(i, :) = x;
  endfor
  
  for i = 1 : m - 1
    X(:,i) = (X(:, i) - mean(X(:, i))) / std(X(:, i));
  endfor
  
  for i = 1 : n1
    y = w' * X(i,:)';
    if y < 0
      no_of_correct_predictions = no_of_correct_predictions + 1;
    endif
  endfor
  
  percentage = double(no_of_correct_predictions) / double(no_of_images);
  
endfunction