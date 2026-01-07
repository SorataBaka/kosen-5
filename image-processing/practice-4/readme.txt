課題1: 2次元離散フーリエ変換の式をそのまま実装し、変換結果の画像をファイルとして出力するPythonのプログラムを結果をshiftしないバージョンとshiftするバージョンで作成してください。両バージョンで、circle-small.pngを変換して画像ファイルを出力するのにかかる時間をtimeコマンドで計測してください。実装したPythonのプログラムと出力画像、timeコマンドを使った時間計測のコマンドラインと応答を提出してください。

対象ファイル名：
1-no-shift.py shiftなし
1-with-shift.py shiftあり

出力画像ファイル名：
1_fft_no_shift_circle-small.png shiftなし
1_fft_with_shift_circle-small.png shiftあり

実行結果（かかる時間含み）：
shiftなし　
time py 1-no-shift.py circle-small.png --out

Output image saved to 1_fft_no_shift_circle-small.png
python 1-no-shift.py circle-small.png --out  10.99s user 0.05s system 99% cpu 11.144 total

shiftあり
time py 1-with-shift.py circle-small.png --out

Output image saved to 1_fft_with_shift_circle-small.png
python 1-with-shift.py circle-small.png --out  11.04s user 0.04s system 99% cpu 11.085 total

======================================================================

課題2: OpenCVのチュートリアルのプログラムを利用し、課題1のプログラムと同じ動作(変換結果の画像を出力、shiftしないバージョンとshiftするバージョン)をするプログラムを作成し、timeコマンドで実行時間を計測してください。実装したPythonのプログラムと出力画像、timeコマンドを使った時間計測のコマンドラインと応答を提出してください。

対象ファイル名：
2-no-shift.py shiftなし
2-with-shift.py shiftあり

出力画像ファイル名：
2_fft_no_shift_circle-small.png shiftなし
2_fft_with_shift_circle-small.png shiftあり

実行結果（かかる時間含み）：
shiftなし　
time py 2-no-shift.py circle-small.png --out

Output image saved to 2_fft_no_shift_circle-small.png
python 2-no-shift.py circle-small.png --out  0.08s user 0.03s system 54% cpu 0.201 total

shiftあり
time py 2-with-shift.py circle-small.png --out

Output image saved to 2_fft_with_shift_circle-small.png
python 2-with-shift.py circle-small.png --out  0.08s user 0.02s system 96% cpu 0.111 total

======================================================================

課題3: OpenCVのチュートリアルプログラムを利用し、FFTを使った低域通過フィルタと高域通過フィルタを実装し、iris-gray.pngを処理した画像を提出してください。実装したPythonのプログラムと出力画像を提出してください。

対象ファイル名：
高域通過フィルタ  3-high-pass.py
低域通過フィルタ  3-low-pass.py

出力画像ファイル名：
高域通過フィルタ  3_high_pass_iris-gray.png 
低域通過フィルタ  3_low_pass_iris-gray.png

======================================================================

課題4: 課題3のフィルタについて、フィルタの範囲(チュートリアルで±30でとっている範囲)を変更するとどのような結果になるか、いくつかの例で実際に実行して結果を調べてください。変更したパラメータの値とその時の周波数領域の画像および逆変換して得られた出力画像、パラメータと出力画像についての考察を、低域通過フィルタ、高域通過フィルタそれぞれで2例以上提出してください。

対象ファイル名：
4-high-pass-ranges.py
4-low-pass-ranges.py

出力画像ファイル名：
4_high_pass_range_iris-gray.png
4_low_pass_range_iris-gray.png

説明分：
各提出した画像には２行５列を配置しています。左から右には範囲10, 20, 30, 40, 50である。一行目には最終的な出力画像である（逆変換済み）。２行目には画像化されたパラメータである。

高域通過フィルタに設定した範囲を増加すると、低周波成分として除去される領域が広がり，画像中のエッジや細かいテクスチャがより強調される一方，ノイズも増加した。

低域通過フィルタに設定した範囲を増加すると、通過する高周波成分が増えるため、画像のぼやけが解消され、エッジや細かいディテールがより鮮明に再現されるようになった。

