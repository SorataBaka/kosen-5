#!/usr/bin/env python3

import cv2
import numpy as np
import sys

cmd, *argv = sys.argv

src = cv2.imread(argv[0])
ycrcb = cv2.cvtColor(src, cv2.COLOR_BGR2YCR_CB).astype(int)

h, w, ch = ycrcb.shape
pad_h = h % 2
pad_w = w % 2

padded_ycrcb = np.pad(ycrcb, ((0, pad_h), (0, pad_w), (0, 0)), mode='edge')
h, w, ch = padded_ycrcb.shape

for y in range(0, h, 2):
    for x in range(0, w, 2):
        pix = (padded_ycrcb[y, x] +
               padded_ycrcb[y, x + 1] +
               padded_ycrcb[y + 1, x] +
               padded_ycrcb[y + 1, x + 1]) / 4
        # padded_ycrcb[y:y+2, x:x+2, 1:3] = pix[1:3] # 色要素だけ
        padded_ycrcb[y:y+2, x:x+2, 0:3] = pix[0:3] # 全要素
        
final_img = padded_ycrcb[:h, :w]
dst = cv2.cvtColor(final_img.astype(np.uint8), cv2.COLOR_YCR_CB2BGR)

cv2.imwrite('out.png', dst)
