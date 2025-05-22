import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
if len(sys.argv) != 4:
    print('引数に クラス数 パターンのファイル名 出力画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()

num_class = int(sys.argv[1])
data_file = sys.argv[2]
png_file  = sys.argv[3]

x = np.loadtxt(data_file, usecols=[1, 2])
y = np.loadtxt(data_file, usecols=[0], dtype=int)

plt.rcParams['font.family'] = 'IPAexGothic'
plt.axes().set_aspect('equal')
c1 = ( 64/ 255,   8/ 255, 255/ 255)
c2 = (224/ 255,   8/ 255,  64/ 255)
c3 = (244/ 255, 160/ 255,   8/ 255)

x1 = x[y == 0]
x2 = x[y == 1]
x3 = x[y == 2]

plt.scatter(x1[:, 0], x1[:, 1], color=c1, marker='o', s=20, label=r'クラス$\omega_1$')
plt.scatter(x2[:, 0], x2[:, 1], color=c2, marker='x', s=20, label=r'クラス$\omega_2$')
if num_class == 3:
    plt.scatter(x3[:, 0], x3[:, 1], color=c3, marker='^', s=20, label=r'クラス$\omega_3$')

plt.xlabel(r'特徴$x_1$', fontdict={"fontfamily":"IPAexGothic"})
plt.ylabel(r'特徴$x_2$', fontdict={"fontfamily": "IPAexGothic"})

plt.legend(loc='upper right')
plt.savefig(png_file, dpi=200)
