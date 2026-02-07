#!/usr/bin/env python3

import cv2
import numpy as np
import sys

cmd, *argv = sys.argv

src = cv2.imread(argv[0])
ycrcb = cv2.cvtColor(src, cv2.COLOR_BGR2YCR_CB).astype(int)

h, w, ch = ycrcb.shape

for y in range(0, h, 2):
    for x in range(0, w, 2):
        pix = (ycrcb[y, x] +
               ycrcb[y, x + 1] +
               ycrcb[y + 1, x] +
               ycrcb[y + 1, x + 1]) / 4
        ycrcb[y:y+2, x:x+2, 1:3] = pix[1:3] # 色要素だけ
        # ycrcb[y:y+2, x:x+2, 0:3] = pix[0:3] # 全要素

dst = cv2.cvtColor(ycrcb.astype(np.uint8), cv2.COLOR_YCR_CB2BGR)

cv2.imwrite('out.png', dst)