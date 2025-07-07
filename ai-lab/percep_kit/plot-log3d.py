import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

import matplotlib.font_manager as fm
if len(sys.argv) != 6:
    print('引数に ログのファイル名1 ログのファイル名2 ログのファイル名3 ログのファイル名4 画像ファイル名 を与えてください.', file=sys.stderr)
    exit()

data_file1 = sys.argv[1]
data_file2 = sys.argv[2]
data_file3 = sys.argv[3]
data_file4 = sys.argv[4]
png_file   = sys.argv[5]

font_path = "ipaexg.ttf"  # Adjust this to your IPAexGothic path
fm.fontManager.addfont(font_path)
ipa_font = fm.FontProperties(fname=font_path)
plt.rcParams["font.family"] = ipa_font.get_name()

c1 = (64/255, 8/255, 255/255)
c2 = (224/255, 8/255, 64/255)
c3 = (244/255, 160/255, 8/255)
c4 = (0, 0, 0)  # For the 4th dataset, black for example

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.set_xlabel(r"重み$w_0$")
ax.set_ylabel(r"重み$w_1$")
ax.set_zlabel(r"重み$w_2$")

log1 = np.loadtxt(data_file1)
log2 = np.loadtxt(data_file2)
log3 = np.loadtxt(data_file3)
log4 = np.loadtxt(data_file4)

log1 = np.atleast_2d(log1)
log2 = np.atleast_2d(log2)
log3 = np.atleast_2d(log3)
log4 = np.atleast_2d(log4)

# Plot trajectories
ax.plot(log1[:, 0], log1[:, 1], log1[:, 2], marker='o', c=c1, alpha=0.5, label='log1')
ax.plot(log2[:, 0], log2[:, 1], log2[:, 2], marker='x', c=c2, alpha=0.5, label='log2')
ax.plot(log3[:, 0], log3[:, 1], log3[:, 2], marker='^', c=c3, alpha=0.5, label='log3')

# Highlight final points distinctly
ax.scatter(log1[-1, 0], log1[-1, 1], log1[-1, 2], c=c1, s=100, edgecolors='k', marker='o', label='final log1')
ax.scatter(log2[-1, 0], log2[-1, 1], log2[-1, 2], c=c2, s=120, edgecolors='k', marker='X', label='final log2')
ax.scatter(log3[-1, 0], log3[-1, 1], log3[-1, 2], c=c3, s=140, edgecolors='k', marker='^', label='final log3')

# Lines from origin to final points
origin = np.zeros(3)
final_points = [log1[-1, :3], log2[-1, :3], log3[-1, :3]]
for fp, col, mark in zip(final_points, [c1, c2, c3], ['o', 'X', '^']):
    ax.plot([origin[0], fp[0]], [origin[1], fp[1]], [origin[2], fp[2]], c=col, linestyle='--', alpha=0.7)

# Lines connecting final points
pairs = [(0,1), (1,2), (2,0)]
for i,j in pairs:
    p1, p2 = final_points[i], final_points[j]
    ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], c='black', linewidth=1, alpha=0.7)

# Extrude plane into volume (thin slab)
v1, v2, v3 = final_points
d1 = v2 - v1
d2 = v3 - v1

# Normal vector and normalization
normal = np.cross(d1, d2)
normal /= np.linalg.norm(normal)

# Create grid for plane
s_vals = np.linspace(-0.5, 1.5, 20)
t_vals = np.linspace(-0.5, 1.5, 20)
s, t = np.meshgrid(s_vals, t_vals)

# Base plane points
plane_points = v1.reshape(3,1,1) + d1.reshape(3,1,1)*s + d2.reshape(3,1,1)*t

# Thickness (half thickness)
thickness = 1

# Offset planes (top and bottom)
plane_top = plane_points + thickness * normal.reshape(3,1,1)
plane_bottom = plane_points - thickness * normal.reshape(3,1,1)

X_top, Y_top, Z_top = plane_top
X_bot, Y_bot, Z_bot = plane_bottom

# Plot top and bottom planes with transparency
ax.plot_surface(X_top, Y_top, Z_top, color='gray', alpha=0.3, edgecolor='none')
ax.plot_surface(X_bot, Y_bot, Z_bot, color='gray', alpha=0.3, edgecolor='none')

# Optionally connect edges to form sides for full volume
# Connect corresponding edges between top and bottom planes:
for idx in [0, -1]:
    # Four edges along s=const or t=const, need to connect top and bottom
    ax.plot([X_top[idx,0], X_bot[idx,0]], [Y_top[idx,0], Y_bot[idx,0]], [Z_top[idx,0], Z_bot[idx,0]], c='gray', alpha=0.3)
    ax.plot([X_top[idx,-1], X_bot[idx,-1]], [Y_top[idx,-1], Y_bot[idx,-1]], [Z_top[idx,-1], Z_bot[idx,-1]], c='gray', alpha=0.3)
    ax.plot([X_top[0,idx], X_bot[0,idx]], [Y_top[0,idx], Y_bot[0,idx]], [Z_top[0,idx], Z_bot[0,idx]], c='gray', alpha=0.3)
    ax.plot([X_top[-1,idx], X_bot[-1,idx]], [Y_top[-1,idx], Y_bot[-1,idx]], [Z_top[-1,idx], Z_bot[-1,idx]], c='gray', alpha=0.3)

ax.set_title('3次元パーセプトロンの学習ログ', fontproperties=ipa_font)
ax.legend(loc='best')

plt.tight_layout()
plt.savefig(png_file, dpi=300, bbox_inches='tight')
plt.show()
