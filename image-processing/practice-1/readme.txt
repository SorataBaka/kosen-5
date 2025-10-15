-どのスクリプトがどのアルゴリズムを実装したものであるか
kadai1.py のスクリプトは画像ファイルからヒストグラムを作成するプログラムである
kadai2.py のスクリプトは画像ファイルにしきい値処理を行うプログラムである

-ヒストグラムの出力はどのファイルか
histogram_image.png

-しきい値処理のアルゴリズムごとに画像を生成するのに用いたしきい値の値
全アルゴリズムにしきい値0.5(255 * 0.5)を使用して処理を行った

-しきい値処理のアルゴリズムごとに生成した画像がどのファイルか
Threshold Binary = binary_image.png
Threshold Binary, Inverted = binary_inverted_image.png
Truncate = truncate_image.png
Threshold to Zero = to_zero_image.png
Threshold to Zero, Inverted = to_zero_inverted_image.png

また、全処理に同じ画像をして、image.pngである

kadai1.pyまたはヒストグラムを生成するプログラムの使い方では次のようになる
python3 kadai1.py <ファイル名>

kadai2.pyまたはしきい値アルゴリズムを実装するプログラムでは次のようになる。

使用方法: kadai2.py [-h] --algorithm {BINARY,BINARY_INVERTED,TRUNCATE,TO_ZERO,TO_ZERO_INVERTED} --threshold THRESHOLD [--out] image_path

しきい値生成プログラム。
位置引数:
  image_path            入力画像のパス。

オプション引数:
  -h, --help            このヘルプメッセージを表示して終了します。
  --algorithm {BINARY,BINARY_INVERTED,TRUNCATE,TO_ZERO,TO_ZERO_INVERTED}
                        使用するしきい値処理アルゴリズムを指定します。
  --threshold <しきい値>
                        アルゴリズムに使用するしきい値を指定します。
  --out                 出力画像を生成する場合に指定します。

アルゴリズムを選択に次の値を入力する
Threshold Binary = BINARY
Threshold Binary, Inverted = BINARY_INVERTED
Truncate = TRUNCATE
Threshold to Zero = TO_ZERO
Threshold to Zero, Inverted = TO_ZERO_INVERTED

しきい値の入力範囲は0から１までとなる。

一般実行とおけると、出力画像が自動的に表示される、出力ファイルが必要とならば、--outをコマンドラインに書いて（出力ファイル名はなしで）実行とする。
