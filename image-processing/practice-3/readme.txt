課題1: 線形変換の濃度変換を使って、グレースケール画像のコントラストを改善するプログラムを実装してください。実装したPythonのプログラムと入力画像、コントラストを改善した画像を提出してください。

提出されたファイル名：1-contrast.py

実行方法について、python3 1-contrast.py --help の実行し、コマンドラインの使い方を表示する：
❯ py 1-contrast.py --help
usage: 1-contrast.py [-h] [--min_output MIN_OUTPUT] [--max_output MAX_OUTPUT] [--out] image_path

Threshold generators.

positional arguments:
  image_path            Path to the input image.

options:
  -h, --help            show this help message and exit
  --min_output MIN_OUTPUT
                        Minimum output pixel value.
  --max_output MAX_OUTPUT
                        Maximum output pixel value.
  --out                 Specifies if output should be created

--min_output と --max_output のあたいはそれぞれ公式であったmin_oとmax_oとなる。--outを追加すると、実行出力画像が出てくる。

実行例：

❯ py 1-contrast.py image.png --min_output 50 --max_output 100
Min Output: 50, Max Output: 100
Min Pixel Value: 39.0, Max Pixel Value: 245.0
Image Width: 512, Image Height: 512

ファイルimage.pngを入力して、--min_output と --max_output をそれぞれ50と100にすると、出力された画像はmodified_image.pngとなる。
=============================================================================

課題2: Sobelフィルタ、Prewittフィルタ、ラプラシアンフィルタ、先鋭化フィルタのいずれかのフィルタ処理をグレースケール画像に適用するプログラムを実装してください。実装したPythonのプログラムと入力画像、フィルタを適用した画像を提出してください。SobelフィルタとPrewittフィルタについては、エッジ強度の出力も可とします。

提出されたファイル名：2-filter.py

実行方法について、python3 2-filter.py --help の実行し、コマンドラインの使い方を表示する：

❯ py 2-filter.py --help
usage: 2-filter.py [-h] [--filter_type {sobel,prewitt,laplacian,sharpness}] [--direction {x,y}] [--laplacian_type {4,8}] [--out] image_path

Threshold generators.

positional arguments:
  image_path            Path to the input image.

options:
  -h, --help            show this help message and exit
  --filter_type {sobel,prewitt,laplacian,sharpness}
                        Type of filter to apply
  --direction {x,y}     Direction of the filter
  --laplacian_type {4,8}
                        Type of laplacian filter (4 or 8)
  --out                 Specifies if output should be created

--directionをxまたはyにして、フィルタの方向を設定できる。
--filter_typeには複数のフィルタを実施しました. sobelまたはprewittにすれば、ー-directionをを追加し、フィルタの実行方向を設定できる。laplacianにすれば、--directionではなく--laplacian_typeを設定すれば良い。--laplacian_typeに使えるあたいは4か8しかない。さらに、--filter_typeをsharpnessにすれば、他の変数は無関係である。

前と同じように、--outを追加すると、実行出力画像が出てくる。

実行例：
❯ py 2-filter.py image.png --filter_type sobel --direction y --out
Applying filter: sobel
With settings - Direction: y Laplacian type: 4
Output image saved to sobel_filtered_image.png

sobelフィルタのy方向の実行結果はsobel_filtered_image.png

また、すべての組み合わせはfilter_combo.pngに表示される。
=============================================================================
課題3: 入力画像(グレースケール)の画素値の平均、画素値の分散、画素値を重さとみなした重心を計算するプログラムを実装してください。実装したPythonのプログラムと入力画像、プログラムを実行した際のコマンドライン(入力とプログラムからの出力)を提出してください。

提出されたファイル名：3-properties.py

実行方法について、python3 3-properties.py --help の実行し、コマンドラインの使い方を表示する：

❯ py 3-properties.py --help
usage: 3-properties.py [-h] image_path

Threshold generators.

positional arguments:
  image_path  Path to the input image.

options:
  -h, --help  show this help message and exit

image.pngを入力とし、プログラムを実行すると次の結果になる。

❯ py 3-properties.py image.png
mu = 132.42729568481445
mu_2 = 2016.1985715044284
(x_G, y_G) = (264.3249774787692, 247.51069538457142)

=============================================================================
課題4: 8ビットのグレースケール画像を入力とし、画素値を8階調に変換したもの(画素値を32で割った商)についての、Δ𝑥=1,Δ𝑦=0とΔ𝑥=0,Δ𝑦=1に関する同時生起行列を求めるプログラムを実装してください。実装したPythonのプログラムと入力画像、プログラムを実行した際のコマンドライン(入力とプログラムからの出力)を提出してください。プログラムは、求める同時生起行列に合わせたものを二つでも、二つの生起行列を一度に求めるもの一つでも、どちらでも構いません。

提出されたファイル名：4-cooccurance.py

実行方法について、python3 4-cooccurance.py --help の実行し、コマンドラインの使い方を表示する：
❯ py 4-cooccurance.py --help
usage: 4-cooccurance.py [-h] [--direction {dx,dy}] image_path

Threshold generators.

positional arguments:
  image_path           Path to the input image.

options:
  -h, --help           show this help message and exit
  --direction {dx,dy}  Direction of co-occurance

--directionをdxかdyにすると、同時生起行列の計算方向を設定できる。
dxにするとx軸方向、または dx = 1, dy = 0
dyにするとy軸方向、または dx = 0, dy = 1

image.pngを入力画像とし、x軸とy軸に実行すると、次の結果になる。
❯ py 4-cooccurance.py image.png --direction dx
Horizontal Co-occurance Matrix:
[[     0      0      0      0      0      0      0      0]
 [     0  38160  11591    526     67      6      0      0]
 [     0  11591  50652   8474    755    117      7      0]
 [     0    526   8474  75520   9355    490     68      0]
 [     0     67    755   9355 132412   9817    297      2]
 [     0      6    117    490   9817  87632   3825     22]
 [     0      0      7     68    297   3825  46260    478]
 [     0      0      0      0      2     22    478    834]]
❯ py 4-cooccurance.py image.png --direction dy
Vertical Co-occurance Matrix:
[[     0      0      0      0      0      0      0      0]
 [     0  41450   8895    108      3      0      0      0]
 [     0   8895  56398   6044    297     33      2      0]
 [     0    108   6044  80778   7362    244      6      0]
 [     0      3    297   7362 136726   7884    115      1]
 [     0      0     33    244   7884  90142   3584      1]
 [     0      0      2      6    115   3584  46894    384]
 [     0      0      0      0      1      1    384    950]]