import argparse
import cv2 as cv
import numpy as np
import os
import math

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
spec = np.log(1 + np.abs(F))
spec = spec / spec.max() * 255

if args.out:
    out_path = f"1_fft_no_shift_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, spec.astype(np.uint8))
    print(f"Output image saved to {out_path}")
