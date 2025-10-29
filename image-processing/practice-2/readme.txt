-どのスクリプトがどのアルゴリズムを実装したものであるか
二つのアルゴリズムはoptimize.pyに含んでいます

使い方としては
python3 optimize.py <ファイル名> --algorithm {kmeans | dispersion}

-どの画像が、どのスクリプトに対する入力画像、および出力画像であるか
入力画像ファイル:
image.png

分散比による出力ファイル:
out_dispersion_image.png
KMeansにとる出力ファイル:
out_kmeans_image.png