import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import matplotlib.font_manager as fm

if len(sys.argv) != 5:
    print('引数に ログのファイル名1 ログのファイル名2 ログのファイル名3 画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

data_file1 = sys.argv[1]
data_file2 = sys.argv[2]
data_file3 = sys.argv[3]
png_file   = sys.argv[4]

x1 = np.loadtxt(data_file1, usecols=[1, 0])
x2 = np.loadtxt(data_file2, usecols=[1, 0])
x3 = np.loadtxt(data_file3, usecols=[1, 0])

font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()

plt.axes().set_aspect('equal')
c1 = ( 64/ 255,   8/ 255, 255/ 255)
c2 = (224/ 255,   8/ 255,  64/ 255)
c3 = (244/ 255, 160/ 255,   8/ 255)

plt.grid()
plt.xlim(-1, 20)
plt.ylim(-10, 15)

patch = matplotlib.patches.Polygon([ [0, 0], [20, 20*0.5], [20, 20*0.2] ], alpha=0.2, hatch='\\\\', ec='black', fc='black')
plt.gca().add_patch(patch)

plt.axline((0, 0), slope=-1.2, lw=0.5)
plt.axline((0, 0), slope=-0.2, lw=0.5)
plt.axline((0, 0), slope= 0.2, lw=0.5)
plt.axline((0, 0), slope= 0.5, lw=0.5)
plt.axline((0, 0), slope= 1.0, lw=0.5)
plt.axline((0, 0), slope= 1.5, lw=0.5)

plt.plot(x1[:, 0], x1[:, 1], color=c1, marker='o', markersize=3.0, linewidth=1.0, label=r'初期値$(2,-7), \rho=1.2$')
plt.plot(x2[:, 0], x2[:, 1], color=c2, marker='x', markersize=3.0, linewidth=1.0, label=r'初期値$(2,-7), \rho=3.6$')
plt.plot(x3[:, 0], x3[:, 1], color=c3, marker='^', markersize=3.0, linewidth=1.0, label=r'初期値$(5,11), \rho=2.0$')

plt.xlabel(r'重み$w_1$')
plt.ylabel(r'重み$w_0$')

plt.legend(loc='upper right')
plt.savefig(png_file, dpi=200)
