import sys
import numpy as np
import matplotlib.pyplot as plt

import matplotlib.font_manager as fm
if len(sys.argv) != 5:
    print('引数に パターンのファイル名 傾きの値 切片の値 画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

data_file = sys.argv[1]
a = float(sys.argv[2])
b = float(sys.argv[3])
png_file  = sys.argv[4]

x = np.loadtxt(data_file, usecols=[1, 2])
y = np.loadtxt(data_file, usecols=[0], dtype=int)

font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()

plt.axes().set_aspect('equal')
c1 = ( 64/ 255,   8/ 255, 255/ 255)
c2 = (224/ 255,   8/ 255,  64/ 255)

# ----------------------------------------------------------------------
margin = 0.5
x_min, x_max = x[:, 0].min() - margin, x[:, 0].max() + margin
y_min, y_max = x[:, 1].min() - margin, x[:, 1].max() + margin
# ----------------------------------------------------------------------

x1 = x[y == 0]
x2 = x[y == 1]

plt.scatter(x1[:, 0], x1[:, 1], color=c1, marker='o', s=20, label=r'クラス$\omega_1$')
plt.scatter(x2[:, 0], x2[:, 1], color=c2, marker='x', s=20, label=r'クラス$\omega_2$')

linex = np.linspace(x_min, x_max)
liney = a * linex + b
plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)
plt.plot(linex, liney)

plt.xlabel(r'特徴$x_1$')
plt.ylabel(r'特徴$x_2$')

plt.legend(loc='lower right')
plt.savefig(png_file, dpi=200)
