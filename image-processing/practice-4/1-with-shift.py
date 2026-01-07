import argparse
import cv2 as cv
import numpy as np
import os
import math


def dft_shift(F):
    height, width = F.shape
    Fs = np.zeros_like(F)
    for u in range(height):
        for v in range(width):
            Fs[(u + height // 2) % height, (v + width // 2) % width] = F[u, v]
    return Fs


parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument(
    "--out", help="Specifies if output should be created", action="store_true"
)
args = parser.parse_args()
img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE).astype(float)
original_img = img.copy()

f = np.array(img, dtype=np.float64)
height, width = f.shape

F = np.zeros((height, width), dtype=np.complex128)

for u in range(height):
    for v in range(width):
        s = 0.0 + 0.0j
        for x in range(height):
            for y in range(width):
                angle = -2 * math.pi * ((u * x) / height + (v * y) / width)
                s += f[x, y] * np.exp(1j * angle)
        F[u, v] = s

# visualize spectrum

Fs = dft_shift(F)
spec = np.log(1 + np.abs(Fs))
spec = spec / spec.max() * 255

if args.out:
    out_path = f"1_fft_with_shift_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, spec.astype(np.uint8))
    print(f"Output image saved to {out_path}")
