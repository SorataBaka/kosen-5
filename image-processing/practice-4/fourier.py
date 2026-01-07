#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

N = 32
ts = [0, 1, 2, 3]
cs = ['r', 'g', 'b', 'c']

fig = plt.figure(figsize = (8, 8))
ax = fig.add_subplot(111, projection = '3d')
ax.set_title(r'$e^{-i\frac{2\pi tx}{N}}$ N=%d' % N, size = 20)
ax.set_xlabel('Re', size = 14)
ax.set_ylabel('Im', size = 14)
ax.set_zlabel('$x$', size = 14)

ax.set_xticks([-1.0, -0.5, 0, 0.5, 1.0])
ax.set_yticks([-1.0, -0.5, 0, 0.5, 1.0])

pi = np.pi

arg = np.linspace(0, N, N)

for i in range(len(ts)):
    aa = -pi * 2.0 * arg * ts[i] / N
    x = np.cos(aa)
    y = np.sin(aa)
    z = arg

    l, = ax.plot(x, y, z, color = cs[i])
    l.set_label('t={}'.format(ts[i]))

ax.legend()
plt.show()
