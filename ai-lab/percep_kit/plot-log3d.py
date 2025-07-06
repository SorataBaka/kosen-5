import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

import matplotlib.font_manager as fm
if len(sys.argv) != 5:
    print('引数に ログのファイル名1 ログのファイル名2 ログのファイル名3 画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

data_file1 = sys.argv[1]
data_file2 = sys.argv[2]
data_file3 = sys.argv[3]
png_file   = sys.argv[4]
font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()
c1 = ( 64/ 255,   8/ 255, 255/ 255)
c2 = (224/ 255,   8/ 255,  64/ 255)
c3 = (244/ 255, 160/ 255,   8/ 255)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.set_xlabel(r"重み$w_0$")
ax.set_ylabel(r"重み$w_1$")
ax.set_zlabel(r"重み$w_2$")

log1 = np.loadtxt(data_file1)
log2 = np.loadtxt(data_file2)
log3 = np.loadtxt(data_file3)

ax.plot(log1[:, 0], log1[:, 1], log1[:, 2], marker='o', c=c1, alpha=0.5)
ax.plot(log2[:, 0], log2[:, 1], log2[:, 2], marker='x', c=c2, alpha=0.5)
ax.plot(log3[:, 0], log3[:, 1], log3[:, 2], marker='^', c=c3, alpha=0.5)

plt.savefig(png_file, dpi=200)