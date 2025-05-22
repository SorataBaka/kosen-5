import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
import knn
import matplotlib.font_manager as fm


font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()

print(plt.rcParams["font.family"])

if len(sys.argv) != 4:
    print('引数に クラス数 パターンのファイル名 出力画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

num_class = int(sys.argv[1])
data_file = sys.argv[2]
png_file  = sys.argv[3]

x = np.loadtxt(data_file, usecols=[1, 2])
y = np.loadtxt(data_file, usecols=[0], dtype=int)

plt.axes().set_aspect('equal')
c1 = ( 64/ 255,   8/ 255, 255/ 255)
c2 = (224/ 255,   8/ 255,  64/ 255)
c3 = (244/ 255, 160/ 255,   8/ 255)

# ----------------------------------------------------------------------
margin = 0.5
x_min, x_max = x[:, 0].min() - margin, x[:, 0].max() + margin
y_min, y_max = x[:, 1].min() - margin, x[:, 1].max() + margin
step = 0.01
xx, yy = np.meshgrid(np.arange(x_min, x_max, step), np.arange(y_min, y_max, step))
grid_data = np.concatenate([xx.reshape([-1, 1]), yy.reshape([-1, 1])], axis=1)
zz = knn.classify_all(1, grid_data, x, y)
zz = zz.reshape([xx.shape[0], xx.shape[1]])
if num_class == 2:
    plt.contourf(xx, yy, zz, cmap=LinearSegmentedColormap.from_list('custom_map', [c1, c2]), alpha=0.2)
else:
    plt.contourf(xx, yy, zz, cmap=LinearSegmentedColormap.from_list('custom_map', [c1, c2, c3]), alpha=0.2)
# ----------------------------------------------------------------------

x1 = x[y == 0]
x2 = x[y == 1]
x3 = x[y == 2]

plt.scatter(x1[:, 0], x1[:, 1], color=c1, marker='o', s=20, label=r'クラス$\omega_1$')
plt.scatter(x2[:, 0], x2[:, 1], color=c2, marker='x', s=20, label=r'クラス$\omega_2$')
if num_class == 3:
    plt.scatter(x3[:, 0], x3[:, 1], color=c3, marker='^', s=20, label=r'クラス$\omega_3$')

plt.xlabel(r'特徴$x_1$', fontdict={"fontfamily": "IPAexGothic"})
plt.ylabel(r'特徴$x_2$', fontdict={"fontfamily": "IPAexGothic"})

plt.legend(loc='upper right', prop=ipa_font)
plt.savefig(png_file, dpi=200)